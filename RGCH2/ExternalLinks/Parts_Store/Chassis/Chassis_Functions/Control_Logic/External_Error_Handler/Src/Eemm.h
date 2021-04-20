/**
 *  @file       emm.h
 *
 *  @brief      Client Interface der Fehlersignalisierung einer EMM Slave ECU.
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

#ifndef __EEMM_H
#define __EEMM_H

#include "Eemm_Def.h"

#define EXTERNAL_EMM

#define ERROR_ACTIVE_STORNO         (0x00u)
#define ERROR_ACTIVE_SAVE           (0x01u)
#define ERROR_ACTIVE_SEND           (0x02u)
#define ERROR_ACTIVE_SAVE_AND_SEND  (0x03u)


sint32 signalError_s32(uint8 client_u8, uint8 active_u8, uint8 code_u8, uint16 data1_u16, uint16 data2_u16);

boolean isErrorActive_b(uint8 client_u8, uint8 code_u8);
boolean isErrorTransmitted_b(uint8 client_u8, uint8 code_u8);
boolean isErrorQuitted_b(uint8 client_u8, uint8 code_u8);
uint8   getErrorAcknowledge_u8(uint8 client_u8, uint8 code_u8);


#endif // __EEMM_H
