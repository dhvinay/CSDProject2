/**
 *  @file       emm_func.c
 *
 *  @brief      Funktion Fehlersignalisierung einer EMM Slave ECU.
 *
 *
 *  @section    Historie
 *
 *  2012-12-07 / werner.unsinn@agcocorp.com
 *  - erstellt
 *
 *  2013-02-01 / werner.unsinn@agcocorp.com
 *  - Define EMM_SLAVE_ALONE wenn keine Verbindung zum Master besteht [PB-5126]
 *
 *  2013-03-22 / werner.unsinn@agcocorp.com
 *  - Define USE_MSG_ENVELOPE wenn Botschaften mit Briefumschlag verwendet werden
 *
 *  2013-11-08 / werner.unsinn@agcocorp.com
 *  - die Funktion PxBcopy() durch die Funktion memcpy() ersetzt [PB-6761]
 *
 *  2014-04-02 / Mattis Kornelius
 *  - [Misc] minor changes for better MISRA-C compliance
 */


#ifdef USE_MSG_ENVELOPE
#include "msgEnvelope.h"
#endif

#include "Eemm_Def.h"
#include "Eemm_Conf.h"
#include "Eemm_Eep.h"
#include "Eemm_Task.h"

#if !defined (EMM_SLAVE_ALONE)
#include "gd.h"
#include "Eemm_Gd.h"
#endif

#include "Eemm_Func.h"
#include "Eemm.h"

#include "Project.h"

#include "Eos.h"




#define EMM_BIT_ACTIVE          (0x01u)   // Error is active
#define EMM_BIT_SEND            (0x02u)   // Error should be sent to central EMM
#define EMM_BIT_PROCESS         (0x04u)   // Error is waiting to be sent to the central EMM
#define EMM_BIT_TRANSMITTED     (0x08u)   // Error was transmitted to the central EMM
#define EMM_BIT_QUITTED         (0x10u)   // Error was acknowledged by user


// Central structure for error signaling
typedef struct
{
    uint8   error_au8[EMM_ERROR_CODE_MAX + 1];

#if !defined (EMM_SLAVE_ALONE)
    uint8   serial_au8[EMM_ERROR_CODE_MAX + 1];
    uint8   acknowledge_au8[EMM_ERROR_CODE_MAX + 1];

    boolean sendTaskAlive_b;
    boolean sendJobExisting_b;
    boolean sendJobWaiting4HS_b;
    uint8   sendJobCode_u8;
    uint32  sendJobCount_u32;
#endif

} EmmStruct_ts;

static EmmStruct_ts emm_as[EMM_CLIENT_MAX];





/**
 *  Initialisierung der Fehlersignalisierung und des Fehlerspeichers.
 *
 */
void initEmmSlave(void)
{
    uint8 client_u8;
    uint16 code_u16;

    for (client_u8 = 0u; client_u8 < EMM_CLIENT_MAX; client_u8++)
    {
        for (code_u16 = 0u; code_u16 <= EMM_ERROR_CODE_MAX; code_u16++)
        {
            emm_as[client_u8].error_au8[code_u16] = 0x00u;

#if !defined (EMM_SLAVE_ALONE)
            emm_as[client_u8].serial_au8[code_u16] = 0x00u;
            emm_as[client_u8].acknowledge_au8[code_u16] = 0x00u;
#endif
        }

#if !defined (EMM_SLAVE_ALONE)
        emm_as[client_u8].sendTaskAlive_b = FALSE;
        emm_as[client_u8].sendJobExisting_b = FALSE;
        emm_as[client_u8].sendJobWaiting4HS_b = FALSE;
        emm_as[client_u8].sendJobCode_u8 = 0u;
        emm_as[client_u8].sendJobCount_u32 = 0u;
#endif
    }
}


/**
 *  Handler Function of fault management for external modules
 *
 *  @param reset_b      indicates whether a reset is to be performed
 */
void execEmmSlave(boolean reset_b)
{
#if !defined (EMM_SLAVE_ALONE)
    uint32 count_u32 = PxTickGetCount();
    uint8 client_u8;

    PARAM_UNUSED(reset_b);

    for (client_u8 = 0u; client_u8 < EMM_CLIENT_MAX; client_u8++)
    {
        if (emm_as[client_u8].sendTaskAlive_b == FALSE)
        {
            if (gdIsAlive_b(emmConfig_cs.client_as[client_u8].location_u8))
            {
                emm_as[client_u8].sendTaskAlive_b = TRUE;
            }
        }

        if (emm_as[client_u8].sendTaskAlive_b)
        {
            if (emm_as[client_u8].sendJobWaiting4HS_b)
            {
                uint32 delay_u32;

                if (count_u32 >= emm_as[client_u8].sendJobCount_u32)
                {
                    delay_u32 = count_u32 - emm_as[client_u8].sendJobCount_u32;
                }
                else
                {
                    delay_u32 = count_u32 + (MAXUINT32 - emm_as[client_u8].sendJobCount_u32);
                }

                if (delay_u32 > MSEC(5000u))
                {
                    emm_as[client_u8].sendJobWaiting4HS_b = FALSE;
                }
            }
            else
            {
                if (emm_as[client_u8].sendJobExisting_b)
                {
                    if (gdIsAlive_b(GD_LN_EMM)) // Send only if the "Central" is available
                    {
                        uint16 code_u16;
                        for (code_u16 = 0u; code_u16 <= EMM_ERROR_CODE_MAX; code_u16++)
                        {
                            if (emm_as[client_u8].error_au8[code_u16] & EMM_BIT_PROCESS)
                            {
                                break;
                            }
                        }

                        if (code_u16 <= EMM_ERROR_CODE_MAX)
                        {
                            uint8  ein_u8;
                            uint16 data_u16;
                            uint16 index_u16 = 0x3E00u + emmConfig_cs.client_as[client_u8].location_u8;

                            emm_as[client_u8].sendJobCode_u8 = (uint8) code_u16;
                            data_u16 = (uint16) (((uint16) emm_as[client_u8].serial_au8[emm_as[client_u8].sendJobCode_u8]) << 8) | ((uint16) emm_as[client_u8].sendJobCode_u8);
                            ein_u8 = (emm_as[client_u8].error_au8[emm_as[client_u8].sendJobCode_u8] & EMM_BIT_ACTIVE) ? TRUE : FALSE;

                            gdSendImmediateWrite_s32(emmConfig_cs.client_as[client_u8].location_u8, index_u16, TRUE, (sint16) data_u16, ein_u8, 0u);

                            emm_as[client_u8].sendJobCount_u32 = count_u32;
                            emm_as[client_u8].sendJobWaiting4HS_b = TRUE;
                        }
                        else
                        {
                            // kein zu sendender Auftrag mehr vorhanden
                            emm_as[client_u8].sendJobExisting_b = FALSE;
                        }
                    }
                }
            }
        }
        else
        {
            if (emm_as[client_u8].sendJobExisting_b)
            {
                uint32 delay_u32;

                if (count_u32 >= emm_as[client_u8].sendJobCount_u32)
                {
                    delay_u32 = count_u32 - emm_as[client_u8].sendJobCount_u32;
                }
                else
                {
                    delay_u32 = count_u32 + (MAXUINT32 - emm_as[client_u8].sendJobCount_u32);
                }

                if (delay_u32 > MSEC(5000u))
                {
                    uint16 code_u16;
                    for (code_u16 = 0u; code_u16 <= EMM_ERROR_CODE_MAX; code_u16++)
                    {
                        if ((emm_as[client_u8].error_au8[code_u16] & EMM_BIT_ACTIVE) &&
                            (emm_as[client_u8].error_au8[code_u16] & EMM_BIT_SEND))
                        {
                            uint16 index_u16 = 0x3E00u + emmConfig_cs.client_as[client_u8].location_u8;
                            uint8 data_au8[8];

                            data_au8[0] = 0x15u; // Home of the EMM
                            data_au8[1] = (uint8)  (index_u16       & 0xFFu);
                            data_au8[2] = (uint8) ((index_u16 >> 8) & 0xFFu) | 0x80u;
                            data_au8[3] = 0xD5u;
                            data_au8[4] = 0x80u;
                            data_au8[5] = (uint8) (code_u16 & 0xFFu);;
                            data_au8[6] = emm_as[client_u8].serial_au8[code_u16];
                            data_au8[7] = 0x00u;

                            // Send error to "Central"
                            EosCanSend_s32(CAN_1, emmConfig_cs.identifier_u16, &data_au8[0], 8u);
                        }
                    }
                    emm_as[client_u8].sendJobCount_u32 = count_u32;
                }
            }
        }
    }
#else
    PARAM_UNUSED(reset_b);
#endif
}


/**
 *  Bearbeitet die Fehlersignalisierungen und GD Nachrichten.
 *
 *  @param message_ps   Zeiger auf Nachricht
 */
void serveEmmMessage(EmmMessage_ts* message_ps)
{
    switch (message_ps->type_u8)
    {
        case 0u: // Error Signaling
        {
            uint8 client_u8 = message_ps->client_u8;

            if (client_u8 < EMM_CLIENT_MAX)
            {
                uint8 code_u8 = message_ps->code_u8;

#if EMM_ERROR_CODE_MAX < MAXUINT8
                if (code_u8 <= EMM_ERROR_CODE_MAX)
#endif
                {
                    if (message_ps->active_u8) // Anmelden eines Neufehlers
                    {
                        if (emm_as[client_u8].error_au8[code_u8] & EMM_BIT_ACTIVE)
                        {
                            // Fehler wurde schon signalisiert
                        }
                        else
                        {
                            emm_as[client_u8].error_au8[code_u8] |= EMM_BIT_ACTIVE;
                            if (message_ps->active_u8 & ERROR_ACTIVE_SAVE)
                            {
                                // Fehler in Fehlerspeicher eintragen
#if !defined (EMM_SLAVE_ALONE)
                                emm_as[client_u8].serial_au8[code_u8] =
#endif
                                    saveError_u8(client_u8, code_u8, message_ps->data1_u16, message_ps->data2_u16);
                            }

#if !defined (EMM_SLAVE_ALONE)
                            if (message_ps->active_u8 & ERROR_ACTIVE_SEND)
                            {
                                // Fehler an "Zentrale" senden
                                emm_as[client_u8].error_au8[code_u8] |= EMM_BIT_SEND;
                                emm_as[client_u8].error_au8[code_u8] |= EMM_BIT_PROCESS;
                                emm_as[client_u8].error_au8[code_u8] &= ~EMM_BIT_TRANSMITTED;
                                emm_as[client_u8].error_au8[code_u8] &= ~EMM_BIT_QUITTED;
                                emm_as[client_u8].sendJobExisting_b = TRUE;
                            }
#endif
                        }
                    }
                    else // Fehlerstornierung
                    {
                        if (emm_as[client_u8].error_au8[code_u8] & EMM_BIT_ACTIVE)
                        {
                            emm_as[client_u8].error_au8[code_u8] &= ~EMM_BIT_ACTIVE;

#if !defined (EMM_SLAVE_ALONE)
                            emm_as[client_u8].serial_au8[code_u8] = 0x00u;
#endif

#if !defined (EMM_SLAVE_ALONE)
                            if (emm_as[client_u8].error_au8[code_u8] & EMM_BIT_SEND)
                            {
                                // Stornierung an "Zentrale" senden
                                emm_as[client_u8].error_au8[code_u8] |= EMM_BIT_PROCESS;
                                emm_as[client_u8].error_au8[code_u8] &= ~EMM_BIT_TRANSMITTED;
                                emm_as[client_u8].error_au8[code_u8] &= ~EMM_BIT_QUITTED;
                                emm_as[client_u8].sendJobExisting_b = TRUE;
                            }
#endif
                        }
                        else
                        {
                            // Fehler braucht nicht storniert werden, da noch gar nicht signalisiert
                        }
                    }
                }
            }
            break;
        }

#if !defined (EMM_SLAVE_ALONE)
        case 1u: // GD handshake after issuing an error
        {
            uint8 client_u8 = message_ps->client_u8;

            if (client_u8 < EMM_CLIENT_MAX)
            {
                uint8 code_u8 = message_ps->code_u8;

#if EMM_ERROR_CODE_MAX < MAXUINT8
                if (code_u8 <= EMM_ERROR_CODE_MAX)
#endif
                {
                    if ((emm_as[client_u8].sendJobWaiting4HS_b)                          &&
                        (code_u8 == emm_as[client_u8].sendJobCode_u8)                    &&
                        (message_ps->data1_u16 == emm_as[client_u8].serial_au8[code_u8]) &&
                        (message_ps->active_u8 == ((emm_as[client_u8].error_au8[code_u8] & EMM_BIT_ACTIVE) ? 0x01u : 0x00u)))
                    {
                        emm_as[client_u8].error_au8[code_u8] &= ~EMM_BIT_PROCESS;
                        emm_as[client_u8].error_au8[code_u8] |= EMM_BIT_TRANSMITTED;

                        emm_as[client_u8].sendJobWaiting4HS_b = FALSE;
                    }
                }
            }
            break;
        }
        case 2u: // GD Write Error after issuing an error
        {
            uint8 client_u8 = message_ps->client_u8;

            if (client_u8 < EMM_CLIENT_MAX)
            {
                // If there is an error while issuing an immediateWrites,
                // it makes no sense to wait for the handshake
                emm_as[client_u8].sendJobWaiting4HS_b = FALSE;
            }
            break;
        }
        case 3: // GD Write to acknowledge an error
        {
            uint8 client_u8 = message_ps->client_u8;

            if (client_u8 < EMM_CLIENT_MAX)
            {
                uint8 code_u8 = message_ps->code_u8;

#if EMM_ERROR_CODE_MAX < MAXUINT8
                if (code_u8 <= EMM_ERROR_CODE_MAX)
#endif
                {
                    if ((message_ps->data1_u16 == 0x00u) && (message_ps->active_u8 == 0x01u))
                    {
                        emm_as[client_u8].error_au8[code_u8] |= EMM_BIT_QUITTED;
                        emm_as[client_u8].acknowledge_au8[code_u8] = (uint8) (message_ps->data2_u16 & MAXUINT8);
                    }
                }
            }
            break;
        }
#endif

        default:
        {
            break;
        }
    }
}


/**
 *  Verschickt eine Nachricht an "meine" Task.
 *
 *  @param message_ps  Zeiger auf Nachricht
 *  @return             0 wenn das Versenden der Nachricht erfolgreich war
 */
static sint32 sendMessage_s32(const EmmMessage_ts* message_ps);
static sint32 sendMessage_s32(const EmmMessage_ts* message_ps)
{
    PxTask_t taskId_ps;
    PxMsg_t msg_ps;
    sint32 err_s32;

    taskId_ps = getEmmTaskId_ps();

    if ((taskId_ps != 0) && (PxTaskCheck(taskId_ps)))
    {
#ifdef USE_MSG_ENVELOPE
        err_s32 = PxMsgRequest_NoWait(&msg_ps, sizeof(EmmMessage_ts) + sizeof(MsgEnvelope_ts), PXMcSystemdefault, PXOpoolSystemdefault);
#else
        err_s32 = PxMsgRequest_NoWait(&msg_ps, sizeof(EmmMessage_ts), PXMcSystemdefault, PXOpoolSystemdefault);
#endif

        if (err_s32 == 0)
        {
#ifdef USE_MSG_ENVELOPE
            MsgEnvelope_ts* env_ps  = PxMsgGetData(msg_ps);
            env_ps->msgType_u8      = MSG_ENV_EMM_TYPE;
            env_ps->msgSubType_u8   = MSG_ENV_EMM_MSG;
            env_ps->msgSize_u16     = (sizeof(EmmMessage_ts) + sizeof(MsgEnvelope_ts));
            memcpy(&env_ps[1], message_ps, sizeof(EmmMessage_ts));
#else
            memcpy(PxMsgGetData(msg_ps), message_ps, sizeof(EmmMessage_ts));
#endif
            PxMsgSend(&msg_ps, PxTaskGetMbx(taskId_ps));
        }
    }
    else
    {
        PxMsgRelease(&msg_ps);
        err_s32 = -1; // Task ist noch nicht aktiv
    }

    return err_s32;
}


#if !defined (EMM_SLAVE_ALONE)
/**
 *  Handles the handshake to a sent error.
 *
 *  @param client_u8    Client
 *  @param data_ps      Pointer to content of the GD message
 */
void signalEmmGdHandshake(uint8 client_u8, GdData_ts* data_ps)
{
    EmmMessage_ts message_s;

    message_s.type_u8   = 1u; // GD handshake after issuing an error
    message_s.client_u8 = client_u8;

    message_s.active_u8 = (data_ps->stbit_b) ? 0x01u : 0x00u;               // Status des Fehlers (GD-Nachricht MSB DB5)
    message_s.code_u8   = (((uint8)data_ps->val_s16) & 0xFFu);              // Fehlercode (GD-Nachricht DB6)
    message_s.data1_u16 = ((((uint16)data_ps->val_s16) >> 8) & 0xFFu);      // laufende Nummer des Fehlers (GD-Nachricht DB7)
    message_s.data2_u16 = 0u;

    sendMessage_s32(&message_s);
}


/**
 *  Treats an error to a sent error.
 *
 *  @param client_u8    Client
 */
void signalEmmGdWriteError(uint8 client_u8)
{
    EmmMessage_ts message_s;

    message_s.type_u8   = 2u; // GD Write Error after issuing an error
    message_s.client_u8 = client_u8;

    message_s.active_u8 = 0x00u;
    message_s.code_u8   = 0u;
    message_s.data1_u16 = 0u;
    message_s.data2_u16 = 0u;

    sendMessage_s32(&message_s);
}


/**
 *  Treats the GD message to acknowledge an error.
 *
 *  @param client_u8    Client
 *  @param data_ps      Pointer to content of the GD message
 */
void signalEmmGdQuittance(uint8 client_u8, GdData_ts* data_ps)
{
    EmmMessage_ts message_s;

    message_s.type_u8   = 3u; // GD Write to acknowledge an error
    message_s.client_u8 = client_u8;

    message_s.active_u8 = (data_ps->stbit_b) ? 0x01u : 0x00u;           // Status of the error (GD message MSB DB5)
    message_s.code_u8   = (((uint8)data_ps->val_s16) & 0xFFu);          // Error code (GD message DB6)
    message_s.data1_u16 = ((((uint16)data_ps->val_s16) >> 8) & 0xFFu);  // Serial number of the error (GD message DB7)
    message_s.data2_u16 = (uint8)(data_ps->diag_u8 & 0x0Fu);            // Return message of the error (GD message Low Nibble DB5)

    sendMessage_s32(&message_s);
}
#endif


/**
 *  Log on a new error or cancel an existing error.
 *
 *  @param client_u8    Client
 *  @param active_u8    the error should be re-registered (saving or sending) or canceled
 *  @param code_u8      Code of the error
 *  @param data1_u16    1. individual value saved with the error
 *  @param data2_u16    2. individual value saved with the error
 *  @return             0 if logging in or canceling was successful, otherwise != 0
 */
sint32 signalError_s32(uint8 client_u8, uint8 active_u8, uint8 code_u8, uint16 data1_u16, uint16 data2_u16)
{
    EmmMessage_ts message_s;

    message_s.type_u8   = 0u; // Fehlersignalisierung
    message_s.client_u8 = client_u8;

    message_s.active_u8 = active_u8;
    message_s.code_u8   = code_u8;
    message_s.data1_u16 = data1_u16;
    message_s.data2_u16 = data2_u16;

    return sendMessage_s32(&message_s);
}


/**
 *  Ermittelt, ob ein Fehler aktiv ist.
 *
 *  @param code_u8      Code des Fehlers
 *  @return             TRUE wenn der Fehler aktiv ist, sonst FALSE
 */
boolean isErrorActive_b(uint8 client_u8, uint8 code_u8)
{
    boolean active_b = FALSE;

    if (client_u8 < EMM_CLIENT_MAX)
    {
#if EMM_ERROR_CODE_MAX < MAXUINT8
        if (code_u8 <= EMM_ERROR_CODE_MAX)
#endif
        {
            if (emm_as[client_u8].error_au8[code_u8] & EMM_BIT_ACTIVE)
            {
                active_b = TRUE;
            }
        }
    }
    return active_b;
}


#if !defined (EMM_SLAVE_ALONE)
/**
 *  Determines whether an error has been transmitted to the central fault management (after receiving the HS).
 *
 *  @param code_u8      Code des Fehlers
 *  @return             TRUE wenn der Fehler uebertragen wurde, sonst FALSE
 */
boolean isErrorTransmitted_b(uint8 client_u8, uint8 code_u8)
{
    boolean transmitted_b = FALSE;

    if (client_u8 < EMM_CLIENT_MAX)
    {
#if EMM_ERROR_CODE_MAX < MAXUINT8
        if (code_u8 <= EMM_ERROR_CODE_MAX)
#endif
        {
            if (emm_as[client_u8].error_au8[code_u8] & EMM_BIT_TRANSMITTED)
            {
                transmitted_b = TRUE;
            }
        }
    }
    return transmitted_b;
}


/**
 *  Determines whether an error has been acknowledged by the user.
 *
 *  @param code_u8      Code des Fehlers
 *  @return             TRUE wenn der Fehler quittiert wurde, sonst FALSE
 */
boolean isErrorQuitted_b(uint8 client_u8, uint8 code_u8)
{
    boolean quitted_b = FALSE;

    if (client_u8 < EMM_CLIENT_MAX)
    {
#if EMM_ERROR_CODE_MAX < MAXUINT8
        if (code_u8 <= EMM_ERROR_CODE_MAX)
#endif
        {
            if (emm_as[client_u8].error_au8[code_u8] & EMM_BIT_QUITTED)
            {
                quitted_b = TRUE;
            }
        }
    }
    return quitted_b;
}


/**
 *  Returns the feedback for an error.
 *
 *  @param code_u8      Code des Fehlers
 *  @return             Rueckmeldung fuer den Fehler
 */
uint8 getErrorAcknowledge_u8(uint8 client_u8, uint8 code_u8)
{
    uint8 acknowledge_u8 = 0x00u;

    if (client_u8 < EMM_CLIENT_MAX)
    {
#if EMM_ERROR_CODE_MAX < MAXUINT8
        if (code_u8 <= EMM_ERROR_CODE_MAX)
#endif
        {
            acknowledge_u8 = emm_as[client_u8].acknowledge_au8[code_u8];
        }
    }
    return acknowledge_u8;
}
#endif
