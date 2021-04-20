/**
*  @file   Eeprom.h
*
*  @brief  define all Eeprom adresses on
*/

#ifndef __EEPROM_H
#define __EEPROM_H

enum
{
	EEP_ADDR_KWP_HW_VERSION = 0x00D6,   // Hardware Version         (8 Byte) {r}
									// - CPU-ID                 (1 Byte)
									// - Programm-Flash         (1 Byte)
									// - Daten/Projekt-Flash    (1 Byte)
									// - Daten-SRAM             (1 Byte)
									// - Ausstattung            (2 Byte)
									// - HW-Aenderungen         (2 Byte)

	EEP_ADDR_KWP_HW_NUMBER  = 0x00E2,   // Hardware Number         (10 Byte) {r}
									// - Pruefbyte              (2 Byte)
									// - Reserviert             (2 Byte)
									// - G-Nummer               (6 Byte)


	EEP_ADDR_FOO_PARAM      = 0x0200,   // Parameter fuer ...       (5 Byte) {r/w}
									// - Checksumme             (2 Byte)
									// - BYTE Parameter         (1 Byte)
									// - WORD Parameter         (2 Byte)
									
	EEP_ADDR_MAX            = 0x7FFF
};

//Need to define Eeprom adress areas for all tasks !!!
//This is only done to get stuff to compile !!
#define EEPROM_KWP2000

#define EEP_ADDR_KALTSTART					0x0000 //Cold Start counter place holder

//	#define EEPROM_BOSCH_PARAMS				0x0100;//0x0100 - 0x05FF
//	#define EEPROM_BOSCH_CALS				0x0600;//0x0600 - 0x06FF

#define EEPROM_HIGH_CLEARANCE_PARAMS		0x0700//0x0700 - 0x08FF
#define EEPROM_HIGH_CLEARANCE_CALS			0x0900//0x0900 - 0x09FF
#define EEPROM_HIGH_CLEARANCE_OPTIONS		0x0A00//0x0A00 - 0x0AFF
//#define EEPROM_HIGH_CLEARANCE_SETTINGS	0x0B00;//0x0B00 - 0x0BFF



// Error Management counters		[28416 .. 29759]
#define EEPR_ADR_ERROR_COUNTER_START    0x6F00 // Start address error counters
#define EEPR_ADR_ERROR_COUNTER_END      0x73FF // End address error counters

//////////////////////////////////////
// Fehlerspeicher  [0x7440..0x7FFF] //
//////////////////////////////////////
// Error Managment error storage	[29760 .. 32767]
#define EEPR_ADR_ERROR_STORAGE          0x7440 // 125 x 24 Byte

#define EEPR_ADR_MAX                    0x7FFF

#define EEPROM_SIZE						0x8000 // 32 * 1024

#endif // __EEPROM_H
