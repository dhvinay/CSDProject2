/**
 *  @file       emm_func.h
 *
 *  @brief      Einbindung der Funktion Fehlersignalisierung in EMM Task.
 *
 *
 *  @section    Historie
 *
 *  2012-12-07 / werner.unsinn@agcocorp.com
 *  - erstellt
 *
 *  2013-03-22 / werner.unsinn@agcocorp.com
 *  - Define USE_MSG_ENVELOPE wenn Botschaften mit Briefumschlag verwendet werden
 *
 *  2014-04-02 / Mattis Kornelius
 *  - [Misc] minor changes for better MISRA-C compliance
 */


#ifndef __EEMM_EXEC_H
#define __EEMM_EXEC_H


#ifdef USE_MSG_ENVELOPE
// Message type: ID zum unterscheiden unterschiedlicher Botschaften (Briefumschlag)
#define MSG_ENV_EMM_TYPE    (0x22u)

// Message subtype: ID zum unterscheiden des Botschaftinhalts (vorlaeufig nur eine ID)
#define MSG_ENV_EMM_MSG     (0x00u)
#endif


void initEmmSlave(void);
void execEmmSlave(boolean reset_b);


typedef struct
{
    uint8   type_u8;
    uint8   client_u8;

    uint8   active_u8;
    uint8   code_u8;
    uint16  data1_u16;  // serial_u8
    uint16  data2_u16;  // acknowledge_u8
} EmmMessage_ts;

void serveEmmMessage(EmmMessage_ts* message_ps);


#endif // __EEMM_EXEC_H
