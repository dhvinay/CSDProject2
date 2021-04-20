/**
 *  @file       emm_task.h
 *
 *  @brief      EMM Slave Task (PxROS).
 *
 *
 *  @section    Historie
 *
 *  2012-12-07 / werner.unsinn@agcocorp.com
 *  - erstellt
 *
 *  2013-03-22 / werner.unsinn@agcocorp.com
 *  - Define USE_MSG_ENVELOPE wenn Botschaften mit Briefumschlag verwendet werden
 *  - bei CortexM3 (Define __ARM_ARCH_7M__) erhoehter Stackverbrauch
 *
 *  2013-11-08 / werner.unsinn@agcocorp.com
 *  - die Funktion PxBcopy() durch die Funktion memcpy() ersetzt [PB-6761]
 *
 *  2014-02-28 / Mattis Kornelius
 *  - [Misc] increased EMM-Task stack to prevent sporadic resets of ZEK
 *
 *  2014-04-02 / Mattis Kornelius
 *  - [Misc] minor changes for better MISRA-C compliance
 */



#include "Eemm_Def.h"
#include "Eemm_Conf.h"
#include "Eemm_Func.h"
#include "Eemm_Kwp.h"

#include "Eemm_Task.h"

#include "kwp.h"
#include "Eos.h"





#define EMM_TASK_PRIO           (6u)
#define EMM_TASK_TICK           MSEC(100u)

#ifdef __ARM_ARCH_7M__
#define EMM_TASK_STACK          (512u + 256u) // beim CortexM3 erhoehter Stackverbrauch
#else
#define EMM_TASK_STACK          (250u)
#endif

#define EMM_PE_EVENT            EVENT(0)    // periodisches Event
#define EMM_IG_OFF_EVENT        EVENT(1)    // Event bei Klemme 15 aus
#define EMM_IG_ON_EVENT         EVENT(2)    // Event bei Klemme 15 ein
#define EMM_IG_SD_EVENT         EVENT(3)    // Event fuer Abschaltanforderung




static PxTask_t emmTaskId_ps = 0;





/**
 *  PXROS-Task.
 *
 *  @param taskId_ps    zugeordnete Task-Id
 *  @param mbxId_ps     Id der privaten Mailbox
 *  @param events_u32   Ereignisse, durch die die Task gestartet wurde
 */
static void emmTask(PxTask_t taskId_ps, PxMbx_t mbxId_ps, PxEvents_t events_u32);
static void emmTask(PxTask_t taskId_ps, PxMbx_t mbxId_ps, PxEvents_t events_u32)
{
    uint32  watchdogId_u32 = 0u;

    PxPe_T  pe_s;
    PxMsg_t msg_ps;

    EosIgReq_pts    ignitionReq_ps = (EosIgReq_pts) 0;  // Klemme 15 Ueberwachung
    boolean         ignitionOff_b = FALSE;
    boolean         shutdown_b = FALSE;


    boolean locked_b = FALSE;       // herunterfahren gesperrt
    boolean suspend_b = FALSE;      // ausser Kraft gesetzt (frueher "BURRY ME")
    boolean reset_b = TRUE;         // wieder in Betrieb nehmen


    PARAM_UNUSED(events_u32);

#ifdef USE_MSG_ENVELOPE
    PxMsgInit(&msg_ps);
#endif

    // Fehlersignalisierung und Fehlerspeicher initialisieren
    emmTaskId_ps = taskId_ps;
    initEmmSlave();
    initEmmKwpRequest(mbxId_ps);


    // Watchdog initialisieren
    EosWdConnect_s32(&watchdogId_u32);

    // Periodic Events initialisieren
    PxPeInit(&pe_s, EMM_TASK_TICK, EMM_PE_EVENT);
    PxPeStart(&pe_s);

    // Mechanismus zu D-Plus installieren
    eosIgReqInstallSd_s32(&ignitionReq_ps, EMM_IG_OFF_EVENT, EMM_IG_ON_EVENT, EMM_IG_SD_EVENT);


    FOREVER
    {
        PxEvents_t ev_u32;

        ev_u32 = PxMsgReceive_EvWait(&msg_ps, mbxId_ps, EMM_PE_EVENT | EMM_IG_OFF_EVENT | EMM_IG_ON_EVENT | EMM_IG_SD_EVENT);

#ifdef USE_MSG_ENVELOPE
        if (PxMsgCheck(&msg_ps))
        {
            MsgEnvelope_ts* env_ps = (MsgEnvelope_ts*) PxMsgGetData(msg_ps);

            switch (env_ps->msgType_u8)
            {
                case MSG_ENV_EMM_TYPE:
                {
                    EmmMessage_ts message_s;

                    memcpy(&message_s, &env_ps[1], sizeof(message_s));
                    PxMsgRelease(&msg_ps);

                    serveEmmMessage(&message_s);
                    break;
                }
                case MSG_ENV_KWP_TYPE:
                {
                    if (env_ps->msgSubType_u8 == MSG_ENV_KWP_DISPATCH)
                    {
                        KwpRequest_ts* kwpRequest_ps;
                        boolean responded_b;

                        kwpRequest_ps = (KwpRequest_ts*) &env_ps[1];
                        responded_b = serveEmmKwpRequest_b(kwpRequest_ps);

                        if (responded_b == FALSE)
                        {
                            kwpHandlerReject(kwpRequest_ps);
                        }
                    }

                    PxMsgRelease(&msg_ps);
                    break;
                }
                default:
                {
                    PxMsgRelease(&msg_ps);
                    break;
                }
            }
        }
#else
        if (msg_ps != (PxMsg_t) 0)
        {
            uint32 msgSize_u32;

            msgSize_u32 = PxMsgGetBuffersize(msg_ps);

            switch (msgSize_u32)
            {
                case sizeof(EmmMessage_ts):
                {
                    EmmMessage_ts message_s;

                    memcpy(&message_s, PxMsgGetData(msg_ps), sizeof(message_s));
                    PxMsgRelease(&msg_ps);

                    serveEmmMessage(&message_s);
                    break;
                }
                case sizeof(KwpRequest_ts):
                {
                    KwpRequest_ts* kwpRequest_ps;
                    boolean responded_b;

                    kwpRequest_ps = (KwpRequest_ts*) PxMsgGetData(msg_ps);
                    responded_b = serveEmmKwpRequest_b(kwpRequest_ps);

                    if (responded_b == FALSE)
                    {
                        kwpHandlerReject(kwpRequest_ps);
                    }

                    PxMsgRelease(&msg_ps);
                    break;
                }
                default:
                {
                    PxMsgRelease(&msg_ps);
                    break;
                }
            }
        }
#endif


        if (ev_u32 & EMM_IG_OFF_EVENT)
        {
            ignitionOff_b = TRUE;
        }

        if (ev_u32 & EMM_IG_ON_EVENT)
        {
            ignitionOff_b = FALSE;

            reset_b = TRUE;
        }

        if (ev_u32 & EMM_IG_SD_EVENT)
        {
            shutdown_b = TRUE; // dieses Flag wird einmalig gesetzt und nie wieder geloescht
        }


        if (ev_u32 & EMM_PE_EVENT)
        {
#if 0
            if (FALSE)
            {
                if (locked_b)
                {
                    eosIgLockShutdown_s32(&ignitionReq_ps, FALSE);
                    locked_b = FALSE;
                }
            }
            else
            {
                if (locked_b == FALSE)
                {
                    eosIgLockShutdown_s32(&ignitionReq_ps, TRUE);
                    locked_b = TRUE;
                }
            }
#endif

            if (suspend_b == FALSE)
            {
                EosWdAlive_s32(watchdogId_u32);



                execEmmSlave(reset_b);



                reset_b = FALSE; // jetzt ist Initialisierung beendet


                if ((ignitionOff_b) && (locked_b == FALSE))
                {
                    suspend_b = TRUE;
                }

                if ((shutdown_b) && (locked_b == FALSE))
                {
                    suspend_b = TRUE;
                }

                if (suspend_b)
                {
                    EosWdDisconnect_s32(&watchdogId_u32);

                    EosIgReqRemove_s32(&ignitionReq_ps);
                }
            }
            else
            {
                if ((ignitionOff_b == FALSE) && (shutdown_b == FALSE))
                {
                    eosIgReqInstallSd_s32(&ignitionReq_ps, EMM_IG_OFF_EVENT, EMM_IG_ON_EVENT, EMM_IG_SD_EVENT);

                    EosWdConnect_s32(&watchdogId_u32);

                    reset_b = TRUE;
                    suspend_b = FALSE;
                }
            }
        }
    }
}


/**
 *  Initialisiert EMM Slave Task.
 */
void initEmmTask(void)
{
    PxTask_t taskId_ps = 0;
    PxError_t err_e;

    err_e = CreateUsrtask(&taskId_ps, "EEMM", &emmTask, EMM_TASK_STACK, EMM_TASK_PRIO);

    if (err_e != PXERR_NOERROR)
    {
        PxPanic();
    }
}


PxTask_t getEmmTaskId_ps(void)
{
    return emmTaskId_ps;
}
