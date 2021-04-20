/**
 *  @file       emm_kwp.h
 *
 *  @brief      KWP Zugriff auf den Fehlerspeicher einer EMM Slave ECU.
 *
 *
 *  @section    Historie
 *
 *  2012-12-07 / werner.unsinn@agcocorp.com
 *  - erstellt
 *
 *  2014-04-02 / Mattis Kornelius
 *  - [Misc] minor changes for better MISRA-C compliance
 */

#include "Eemm_Eep.h"

#include "Eemm_Kwp.h"

#include "kwp.h"
#include "Eos.h"



/**
 *  Am KWP Task fuer Anfragen registrieren.
 *
 *  @param mbxId_ps     Mailbox fuer den Empfang von Anfragen vom KWP Task
 */
void initEmmKwpRequest(PxMbx_t mbxId_ps)
{
    // am KWP Task fuer Anfragen registrieren
    kwpHandlerRegister_s32(KWP_REQGROUP_TROUBLECODES, mbxId_ps);
    kwpHandlerRegister_s32(KWP_REQGROUP_ROUTINE, mbxId_ps);
}


/**
 *  Bearbeitet die Anfragen an das Fehlermanagement (Diagnose KWP).
 *
 *  @param request_ps   Zeiger auf Nachricht
 *  @return             TRUE wenn die Nachricht verarbeitet (beantwortet) wurde, sonst FALSE
 */
boolean serveEmmKwpRequest_b(KwpRequest_ts* request_ps)
{
    uint8* data_au8 = request_ps->data_p;

    boolean responded_b = FALSE;

    switch (request_ps->id_u8)
    {
        case 0x14u: // Loeschen des Fehlerspeichers
        {
            if (request_ps->msgSize_u16 == 2u)
            {
                uint16 group_u16 = (((uint16) data_au8[0]) << 8) | data_au8[1];

                if (group_u16 == 1u)
                {
                    if (request_ps->flags_u8 & (uint8) KWP_HANDLER_FLAG_DIAGMODE)
                    {
                        sint32 err_s32 = clearErrorStorage_s32();

                        if (err_s32 == 0)
                        {
                            kwpHandlerRespond(request_ps, 0u, 2u);
                        }
                        else
                        {
                            // Fehler beim loeschen des Fehlerspeichers aufgetreten
                            kwpHandlerRespond(request_ps, KWP_RESPONSE_GENERAL_REJECT, 0u);
                        }
                    }
                    else
                    {
                        kwpHandlerRespond(request_ps, KWP_RESPONSE_INCORRECT_CONDITIONS, 0u);
                    }
                    responded_b = TRUE;
                }
            }
            break;
        }

        case 0x17u: // Auslesen des Fehlerspeichers
        {
            if (request_ps->msgSize_u16 == 2u)
            {
                uint16 group_u16 = (((uint16) data_au8[0]) << 8) | data_au8[1];

                if (group_u16 == 1u)
                {
                    if (request_ps->flags_u8 & (uint8) KWP_HANDLER_FLAG_DIAGMODE)
                    {
                        uint16 n_u16 = readErrorStorage_u16(&data_au8[0], request_ps->bufSize_u16);

                        if (n_u16 <= request_ps->bufSize_u16)
                        {
                            kwpHandlerRespond(request_ps, 0u, n_u16);
                        }
                        else
                        {
                            kwpHandlerRespond(request_ps, KWP_RESPONSE_GENERAL_REJECT, 0u);
                        }
                    }
                    else
                    {
                        kwpHandlerRespond(request_ps, KWP_RESPONSE_INCORRECT_CONDITIONS, 0u);
                    }
                    responded_b = TRUE;
                }
            }
            break;
        }

        case 0x31u:
        {
            if (request_ps->msgSize_u16 >= 1u)
            {
                switch (data_au8[0])
                {
                    case 0x14u: // Loeschen der Haeufigkeitszaehler
                    {
                        if (request_ps->msgSize_u16 == 3)
                        {
                            uint16 group_u16 = (((uint16) data_au8[1]) << 8) | data_au8[2];

                            if (group_u16 == 1u)
                            {
                                if (request_ps->flags_u8 & (uint8) KWP_HANDLER_FLAG_DIAGMODE)
                                {
                                    if (request_ps->flags_u8 & (uint8) KWP_HANDLER_FLAG_AUTH)
                                    {
                                        sint32 err_s32 = clearErrorCounters_s32();

                                        if (err_s32 == 0)
                                        {
                                            kwpHandlerRespond(request_ps, 0u, 3u);
                                        }
                                        else
                                        {
                                            // Fehler beim Loeschen der Haeufigkeistszaehler aufgetreten
                                            kwpHandlerRespond(request_ps, KWP_RESPONSE_GENERAL_REJECT, 0u);
                                        }
                                    }
                                    else
                                    {
                                        kwpHandlerRespond(request_ps, KWP_RESPONSE_SECURITY_ACCESS_DENIED, 0u);
                                    }
                                }
                                else
                                {
                                    kwpHandlerRespond(request_ps, KWP_RESPONSE_INCORRECT_CONDITIONS, 0u);
                                }
                                responded_b = TRUE;
                            }
                        }
                        break;
                    }
                    case 0x17u: // Auslesen der Haeufigkeitszaehler
                    {
                        if ((request_ps->msgSize_u16 == 3u) && (request_ps->bufSize_u16 >= 1u))
                        {
                            uint16 group_u16 = (((uint16) data_au8[1]) << 8) | data_au8[2];

                            if (group_u16 == 1u)
                            {
                                if (request_ps->flags_u8 & (uint8) KWP_HANDLER_FLAG_DIAGMODE)
                                {
                                    uint16 n_u16 = readErrorCounters_u16((uint8*) &data_au8[1], request_ps->bufSize_u16 - 1);

                                    if (n_u16 <= (request_ps->bufSize_u16 - 1u))
                                    {
                                        kwpHandlerRespond(request_ps, 0u, n_u16 + 1u);
                                    }
                                    else
                                    {
                                        kwpHandlerRespond(request_ps, KWP_RESPONSE_GENERAL_REJECT, 0u);
                                    }
                                }
                                else
                                {
                                    kwpHandlerRespond(request_ps, KWP_RESPONSE_INCORRECT_CONDITIONS, 0);
                                }
                                responded_b = TRUE;
                            }
                        }
                        break;
                    }

                    case 0x20u:  // Auslesen der Umgebungsvariablen fuer einen Eintrag im Fehlerspeicher
                    {
                        if ((request_ps->msgSize_u16 == 4u) && (request_ps->bufSize_u16 >= 1u))
                        {
                            uint16 group_u16 = (((uint16) data_au8[1]) << 8) | data_au8[2];

                            if (group_u16 == 1u)
                            {
                                if (request_ps->flags_u8 & (uint8) KWP_HANDLER_FLAG_DIAGMODE)
                                {
                                    sint32 size_s32 = readEnvironmentValues_s32(data_au8[3], &data_au8[1], request_ps->bufSize_u16 - 1u);

                                    if (size_s32 < 0)
                                    {
                                        kwpHandlerRespond(request_ps, KWP_RESPONSE_GENERAL_REJECT, 0u);
                                    }
                                    else if (size_s32 <= (sint32)(request_ps->bufSize_u16 - 1u))
                                    {
                                        kwpHandlerRespond(request_ps, 0u, (uint16) size_s32 + 1);
                                    }
                                    else
                                    {
                                        kwpHandlerRespond(request_ps, KWP_RESPONSE_GENERAL_REJECT, 0u);
                                    }
                                }
                                else
                                {
                                    kwpHandlerRespond(request_ps, KWP_RESPONSE_INCORRECT_CONDITIONS, 0u);
                                }
                                responded_b = TRUE;
                            }
                        }
                        break;
                    }

                    default:
                    {
                        break;
                    }
                }
            }
            break;
        }

        default:
        {
            break;
        }
    }
    return responded_b;
}


