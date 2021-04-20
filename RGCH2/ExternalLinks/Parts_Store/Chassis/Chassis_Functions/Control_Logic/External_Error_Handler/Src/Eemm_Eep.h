/**
 *  @file       emm_eep.h
 *
 *  @brief      EEPROM Zugriff (Fehlerspeicher, Fehler Haeufigkeitszaehler) einer EMM Slave Task.
 *
 *
 *  @section    Historie
 *
 *  2012-12-07 / werner.unsinn@agcocorp.com
 *  - erstellt
 *
 */

#ifndef __EEMM_EEP_H
#define __EEMM_EEP_H

#include "Eos.h"

/// Deklaration Fehlerspeichereintrags
typedef struct
{
    uint8   location_u8;    //< Fehlerort
    uint8   code_u8;        //< Fehlercode

    uint8   serial_u8;      //< laufende Nummer des Fehlers
    uint8   counter_u8;     //< Fehlerhaeufigkeit

    uint16  data1_u16;      //< 1. Individueller Wert (0)
    uint16  data2_u16;      //< 2. Individueller Wert (39)

    uint16  ub_u16;         //< Versorgungsspannung (38)
    uint16  starts_u16;     //< Kaltstartzaehler (36)
    uint32  ticks_u32;      //< Millisekundenzaehler (37)

} EmmStorageEntry_ts;


uint8 saveError_u8(uint8 client_u8, uint8 code_u8, uint16 data1_u16, uint16 data2_u16);

uint16 readErrorCounters_u16(uint8* data_pu8, uint16 n_u16);
uint16 readErrorStorage_u16(uint8* data_pu8, uint16 n_u16);
sint32 readEnvironmentValues_s32(uint16 i_u16, uint8* data_pu8, uint16 n_u16);

sint32 clearErrorCounters_s32(void);
sint32 clearErrorStorage_s32(void);


#endif // __EEMM_EEP_H
