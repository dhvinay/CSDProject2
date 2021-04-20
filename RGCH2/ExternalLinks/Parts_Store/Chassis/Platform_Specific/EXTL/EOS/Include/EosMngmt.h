/**
 *  \file   EosMngmt.h
 *
 *  \brief  Hardware independant header file for functions related
 *          to management of ECU like turning on/off powersupplies,
 *          selftest, shutdown, powerup uso.
 *          The functions in this file are only intended for use in the
 *          managment task of the ECU which is usually the idle task.
 *
 *  Copyright 2014 (c) AGCO/Fendt GmbH & Co
 *
 *  \par history
 *
 *  2008-08-01 / Christian.Pischulti@xfendt.de
 *  - created
 *
 *  2009-07-30 / Christian.Pischulti@xfendt.de
 *  - Removed function EosEcuPowerOff_v() because function is the same
 *    as EosSystemReset_v() following a EosPwrEnDisableKl15Aut...
 *
 *  2010-03-01 / Christian.Pischulti@xfendt.de
 *  - New functions for locking of eeprom and status function to determine
 *    when everything has been written for proper system shutdown.
 *
 *  2010-10-04 / Christian.Pischulti@xfendt.de
 *  - New function EosSystemResetSB_v() for SRCXX-XX bootloaders.
 *    This functin uses the bosch core to tell sb not to jump to bootloader.
 *  - New function to turn on debugging support for traps.
 *
 *  2011-03-11 / Christian.Pischulti@xfendt.de
 *  - Replaced bool by boolean to be C++ ready.
 *  - Added extern C++ declaration if compiled with c++.
 *
 *  2011-05-06 / Christian.Pischulti@xfendt.de
 *  - New function EosEepromSynced_s32() for bootloader to be able to check
 *    if everything from eep fifo is written to eep.
 *
 *  2011-12-02 / florian.schwarz@euro-engineering.com
 *  - changed type bool to boolean
 *  - added missing eos.h include
 *  - added eosSystemResetCB() prototype (Christian Pischulti)
 *
 *  2012-02-14 / Christian.Pischulti@xfendt.de
 *  - Added function eosDbgGetResetCause_u16() to get cause
 *    of last start.
 *  - Added function eosGetSysUptimeInMs_u32() which returns system
 *    uptime from a hardware counter. This function is only available
 *    on ECUs with a system tick counter like tricore.
 *
 *  2014-10-08 / Christian.Pischulti@AGCOcorp.com
 *  - [PB-8563] Improved comments for reset cause enum values.
 *
 *  2015-02-23 / Christian.Pischulti@AGCOcorp.com
 *  - [PB-8563] Moved eep functions to own header files. Moved EcuStatus functions
 *    from eos.h to this file. Removed all functions for wake support.
 *  - [PB-9598] Added functions for CRC calculation eosCrcxxx().
 */
#ifndef EOSMNGMT_H
#define EOSMNGMT_H

#include "eos.h"

#ifdef __cplusplus
  extern "C" {
#endif // __cplusplus

/**
  * \defgroup _mngmt_power Power Management
  * \{
  */

void    EosSystemReset_v( void );                                       // Reset system with cpu reset. Function never returns.
void    EosSystemResetSB_v( void );                                     // Reset system but tell bosch startblock not to continue boot
                                                                        // process with bootloader.
void    eosSystemResetCB( void );                                       // Reset system ant tell bosch startblock to start customer block
                                                                        // ECUs with bosch core.

/**
  * \}
  */

/**
  * \defgroup _mngmt_version ECU hardware/software version services
  * \{
  */

/**
 * \brief struct to hold hardware version information of ECU, used in EosECUConfig_ts
 */
typedef struct
{
    uint8    minor_u8;          ///< \brief minor revision for format Major.Minor
    uint8    major_first_u8;    ///< \brief major revision for format Major.Minor
    uint8    major_second_u8;   ///< \brief major second identifies the ECU: 0 = EXT, 1 = EXT_LIGHT
} ECU_HW_Version_ts;

 /**
  * \brief struct to hold startup configuration, cpu identifiers and hardware revision of ECU,
  * see EosECUGetConfig_s32()
  */
typedef struct
{
    uint8               CPU_Startup_Mode_u8;    ///< \brief CPU startup mode defined by Port 10
    uint16              CPU_Manufactor_u16;     ///< \brief CPU manufacturer, 0xC1 = Infineon Technologies
    uint8               CPU_Man_Department;     ///< \brief department of manufacturer, 0x00: Automotive & Industrial microcontroller department within Infineon Technologies
    uint8               CPU_Type_u8;            ///< \brief chip type, 0x8A = TC1796
    uint8               CPU_Chip_Rev_u8;        ///< \brief revision of silicon, for A Steps value == 1, B Steps value == 2
    ECU_HW_Version_ts   ECU_HW_Version;         ///< \brief hardware version of ECU
} EosECUConfig_ts;

/**
 *  \brief  Get/read Configuration-information of ECU
 *
 *  Returns a struct with hardwarerevision cpu type, some
 *  strapping options and other ecu specific data.
 *
 *  \param  config_ps   pointer to ecu data struct
 *
 *  \return Zero, if ok, else != 0.
 */
sint32  EosECUGetConfig_s32( EosECUConfig_ts* config_ps );

/**
 *  \brief  read version string of boot(block/code)
 *
 *  \param  string_au8      pointer to storage for string
 *  \param  strLength_pu16  pointer to storage for stringlength
 *
 *  \return ==0 Ok; != 0 error
 */
sint32  eosGetBootVersionString_s32( uint8* string_au8, uint16* strLength_pu16);    // string is copied string_au8, strLength_pu16 returns length

/**
 * \}
 */

/**
  * \defgroup _mngmt_crc CRC Device
  * \{
  */

sint32 eosCrcDevStart_s32( uint32 initialVal_u32, uint32 startAddress_u32, uint32 endAddress_u32 );
sint32 eosCrcDevGetResult_s32( uint32* crcResult_pu32 );
sint32 eosCrcCalcCrc_s32( uint32 initialVal_u32, uint32 startAddress_u32, uint32 endAddress_u32, uint32* crcResult_pu32 );

/**
  * \}
  */

/**
  * \defgroup _mngmt_dbg Debugging support
  * \{
  */

/// \brief possible reset causes
typedef enum
{
    RST_CAUSE_UNKNOWN,          ///< \brief reset cause couldn't be determined
    RST_CAUSE_POR,              ///< \brief Power on reset
    RST_CAUSE_EXTRST,           ///< \brief External reset (hardware)
    RST_CAUSE_INTWD,            ///< \brief Reset by internal watchdog
    RST_CAUSE_BROWNOUT,         ///< \brief Reset by internal voltage supervisor ( usually called brownout detector )
    RST_CAUSE_POR_KL15          ///< \brief Power on reset caused by Kl15 and not KL30. Only supported on some ECUs which can detect this.
} ResetCauses_te;

uint16  eosDbgGetResetCause_u16( void );    // returns the enum value of reset cause
                                            // This function can only be called once. The second call will return
                                            // wrong reset cause.

/*  If a trap occurs the cause of trap and the trap address is send in a can message over
    canNode_e with the can identifier canMsgId_u16.

    DataField:
    ----------
    canData_au8[0]   - trap class
    canData_au8[1]   - Tricore: tin
                       ARM7-TDMI-S: previous mode bits ( mode at which trap was triggered )
    canData_au8[2-5] - 32 bit address at which trap was triggered ( big endian format )
    canData_au8[6-7] - unused
*/
sint32 eosDbgTrapSendCanMsgConfig_s32( EosCan_te canNode_e, uint16 canMsgId_u16 );


/* This function returns the system uptime counted by a hardwaretimer. The time returned
   might differ strongly from pxros tick timer due to rounding. Not every ucontroller
   provides a hardware and therefore this function. This function is usefull if interrupts
   are disabled. */
uint32 eosGetSysUptimeInMs_u32( void );
/**
  * \}
  */


#ifdef __cplusplus
  }
#endif // __cplusplus

#endif  //  EOSMNGMT_H

