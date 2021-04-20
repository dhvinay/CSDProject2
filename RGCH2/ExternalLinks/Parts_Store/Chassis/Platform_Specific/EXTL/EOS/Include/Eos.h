/**
 * \file Eos.h
 *
 * \brief Main Header file to use with EOS-lib.
 *
 * Contains all global definitions, data and prototypes to use with EOS-lib
 *
 * Copyright (c) AGCO/Fendt GmbH & Co.
 *
 * \par history
 *
 * 2004-10-24 / W. Zaremba
 * - created
 *
 * 2005-01-04 / W. Zaremba
 * - changed values of "IODiag_te" so they can be used with OR-operation
 * - changed some structs containing microVolt; now using MilliVolt
 *
 * 2005-14-01 / W. Zaremba
 * - added IOD_Undef to IODiag_te
 * - extended comment for EosAiStatus_ts
 *
 * 2005-01-18 / W. Zaremba
 * - added definitions for highest/lowest task-prios for user-applications
 *
 * 2005-03-16 / W. Zaremba
 * - added new prototypes EosCanInstall() RemoveBoSignal_s32()
 *
 * 2005-04-20 / W. Zaremba
 * - EosOutStatus_ts now containing a raw/unfiltered diagnostic value
 * - added new prototype  EosOutSetFilter_s32() (!!! does not work so far !!!)
 * - extern Variable "Ubat_mV_u32" voltage of powersupply
 *
 * 2005-08-18 / E. Kemmler
 * - behaviar of PWM outputs can be changed, new structure EosOutPara_ts and function EosOutSetPara_s32() added
 * - Output values of analog 4-20mA Output are now uA
 *
 * 2005-10-13 / werner.unsinn@xfendt.de
 * - Wert fuer DOH_07 im Enum _outname_ berichtigt
 *
 * 2006-07-17 / E. Kemmler
 * - new functions and data-types to get information about
 *   internal voltages, power supplies and PCB-temperature added
 *
 * 2006-11-20 / E. Kemmler
 * - new functions and data-types for frequency evolution added
 *
 * 2006-11-23 / E. Kemmler
 * - data type _dficonfig_ modified
 *
 * 2006-12-19 / E. Kemmler
 * - SCD (ShortCutDetection) integrated
 *
 * 2007-01-04 / E. Kemmler
 * - implemetation of CPU & Hardware Identification
 *
 * 2007-05-02 / S. Bauer
 * - implemetation of get_cpu_utilisation_u16 (Function returns
 *   counter value in multiples of one byte
 *
 * 2007-05-15 / E. Kemmler
 * - struct  _dficonfig_ modified
 *
 * 2008-02-29 / Ch. Pischulti
 * - major rework for shared use with EXT and EXT-Light
 * - Applications using this file has to add define EXT or EXT_LIGHT
 *   to makefile/project to select the right I/O symbols.
 * - removed Easycode tags
 *
 * 2008-05-07 / Ch. Pischulti
 * - Changed EOS watchdog api to replace wd.c by Watchdog.c
 *
 * 2008-06-25 / Ch. Pischulti
 * - Changed back EOS watchdog api because the EHR-Lib is using the old one.
 *   Now we have again an uint32 id type and the disconnect command needs
 *   a pointer to the id value.
 *
 * 2008-07-14 / Ch. Pischulti
 * - Changed unit for dutycycle of frequency input result structure.
 *   New range from 0 - 10000 which means unit is 0.01%. Duty cycle is
 *   measured for high level of frequency input.
 *
 * 2010-10-04 / Ch. Pischulti
 * - New functions EosCanSend_Hnd_b() and EosCanSendExt_Hnd_b() for debugging
 *   utility functions.
 *
 * 2010-10-26 / Ch. Pischulti
 * - New function eosGetBootVersionString_s32( ) to read version string of
 *   of NXP Bootrom or Bosch Startblock.
 *
 * 2011-02-11 / Ch. Pischulti
 * - Added a check for valid can id to can send functions. The bosch core
 *   accepted std ids above 0x7FF but stalled in a endless lopp sending
 *   can messages with extended ID. New defines CAN_STD_ID_MAX and CAN_EXT_ID_MAX
 *   for can id range check.
 * - New functions for requested shutdown needed by KPW library.
 *
 * 2011-03-11 / Ch. Pischulti
 * - Replaced all bools by boolean for c++ builds
 * - Added extern c declaration for c++ buidls.
 *
 * 2011-03-31 / Ch. Pischulti
 * - New functions for shutdown support in D+/Ign section.
 *
 * 2011-07-18 / florian.schwarz@euro-engineering.com
 * - added missing parameter names in function prototypes
 * - doxygen adjustments
 *
 * 2011-09-07 / Christian.Pischulti@xfendt.com
 * - [PB-1524] Added property const for all config/write function data pointers.
 *
 * 2011-12-05 / florian.schwarz@euro-engineering.com
 * - Reduced EosECUGetSt_s32() and EosECUStatus_ts to UBAT.
 * - added EosViSetDiag_s32() and EosViDiag_ts for analog voltage input diagnostic
 * - added EosTiGetSt_s32() and EosTiStatus_ts for temperature sensors
 * - added EosOutGetSt2_s32() and EosOutStatus2_ts which can be used to read
 *   output voltage levels
 * - replaced __TC13__ with __tricore__ (valid for all TriCores, not just
 *   core rev 1.3)
 *
 * 2012-01-31 / Christian.Pischulti@xfendt.de
 * - Replaced ucontroller specific typedefs by eosStdType.h.
 * - Removed function EosCanInstallReqExe_s32().
 * - Removed functions EosViSetDiag_s32() and replaced it by EosDiReadConfig_s32()
 *   and EosDiSetConfig_s32( ) for digital inputs and EosAiSetConfig_s32( ) and
 *   EosAiReadConfig_s32( ) for voltage inputs.
 *
 * 2012-09-06 / florian.schwarz@euro-engineering.com
 * - stylistic changes for better MISRA-C compliance
 * - changed IOSYMB includes to allow a platform define together with define LIBRARY
 *
 * 2012-10-25 / florian.schwarz@euro-engineering.com
 * - added additional check for SRC36_20_31 define before inclusion of iosymbext.h
 *
 * 2014-10-14 / Christian.Pischulti@AGCOcorp.com
 * - [PB-8328] Added function eosAiGetSt2_s32() to get analog values of current and
 *   voltage inputs with latests ADC values and not from IO task diag array.
 *
 * 2014-09-25 / Christian.Pischulti@AGCOcorp.com
 * - [PB-5253] moved everything related to CAN to own header file eosCan.h
 * - [PB-5211] new functions for enabling of phase measuring.
 * - [PB-8554] Added header file with IO syms for SRC14-34/31.
 * - [PB-8560] Added function eosDfiGetSt2_s32() with absolute high pulse time for
 *   DSM sensor inputs. Added function eosDfiDsmLoadResEnable_s32() to enable or
 *   disable 200 Ohm load resistor for DSM inputs.
 * - [PB-8591] Added function eosOutSetMultiplePw_s32() for setting more than one
 *   output with one call.
 * - [PB-8563] Removed workaround for definition of EXT and SRC36_20_31 in one project.
 *
 * 2014-12-05 / Christian.Pischulti@AGCOcorp.com
 * - [BUG-5531] Added functions eosDfiStart_s32() and eosDfiStartAll_s32() to start
 *   measuring of frequency and pulscounter from application.
 *   NOTE: Startup configuration for DFIs is disabled.
 * - [PB-8563] Renamed ECU EXT to SRC36_20_31 and EXT light to SRC9_34.
 * - [PB-8563] Moved eep, watchdog, ignition functions to own header file and added new
 *   header file eosRtos.h.
 *
 * 2015-10-11 / Christian.Pischulti@AGCOcorp.com
 * - [Misc] Reduced define PWM_OUTPUT_MIN_HZ from 50 to 40 Hz.
 *
 * 2017-01-31 / Christian.Pischulti@AGCOcorp.com
 * - [PB-14761] Added functions eosIoDiagResetAll_s32(), eosIoDiagOutReset_s32(),
 *   eosIoDiagInpDigReset_s32() eosIoDiagInpAnaReset_s32( EosAiName_te aiName_e ).
 *   Removed function EosInputResetDiags_s32(). Calling functions EosDiSetConfig_s32(), EosDfiSetConfig_s32(),
 *   EosAiSetConfig_s32() and EosOutSetPara_s32() will reset diagnostic code (OK) and
 *   diagnostic counters.
 */

#ifndef _EOS_H
#define _EOS_H

#include "pxdef.h"

#include "eosStdType.h"
#include "eosCan.h"
#include "eosEep.h"
#include "eosWd.h"
#include "eosIgn.h"
#include "eosRtos.h"

#ifdef SRC36_20_30
    #include "iosymbSRC36_20_30.h"
    #define IOSYMB_INCLUDED
#endif

#ifdef SRC9_34
    #include "iosymbSRC9_34.h"
    #define IOSYMB_INCLUDED
#endif

#ifdef SRC14_10
    #include "iosymbSRC14_10.h"
    #define IOSYMB_INCLUDED
#endif

#ifdef RDRA
    #include "iosymbrdra.h"
    #define IOSYMB_INCLUDED
#endif

#ifdef EBT
    #include "iosymbebt.h"
    #define IOSYMB_INCLUDED
#endif

#ifdef ZEL
    #include "iosymbzel.h"
    #define IOSYMB_INCLUDED
#endif

#ifdef ZEFH
    #include "iosymbzefh.h"
    #define IOSYMB_INCLUDED
#endif

#ifdef MFA
    #include "iosymbmfa.h"
    #define IOSYMB_INCLUDED
#endif

#ifdef MRC
    #include "iosymbmrc.h"
    #define IOSYMB_INCLUDED
#endif

#ifdef SRC4_5
    #include "iosymbSRC4_5.h"
    #define IOSYMB_INCLUDED
#endif

#ifdef SRC36_20_31
    #include "iosymbSRC36_20_31.h"
    #define IOSYMB_INCLUDED
#endif

#ifdef SRC14_34_31
    #include "iosymbSRC14_34_31.h"
    #define IOSYMB_INCLUDED     ///< EOS internal
#endif

#ifndef IOSYMB_INCLUDED
    #ifdef LIBRARY
        #include "iosymbdefault.h"
    #endif
#endif

#ifdef __cplusplus
  extern "C" {
#endif // __cplusplus


 /**
   * \defgroup _mngmt_io IO diagnostic codes
   * \{
   */

 /// \brief  IO-diagnostic codes
 typedef enum IODiag
 {
     IOD_OK             = 0,        ///< no fault
     IOD_OPEN           = 1,        ///< broken wire / missing load or sensor
     IOD_SC_GND         = 2,        ///< short circuit to ground
     IOD_OPEN_SC_GND    = 3,        ///< short circuit to ground or open
     IOD_SC_HIGH        = 4,        ///< short circuit to supply voltage
     IOD_OPEN_SC_HIGH   = 5,        ///< short circuit to supply voltage or open
     IOD_SC_HIGH_SC_GND = 6         ///< short circuit to supply voltage or ground
 } IODiag_te;

#define IOD_Open        IOD_OPEN    ///< for backward compatibility
#define IOD_ScHigh      IOD_SC_HIGH ///< for backward compatibility
#define IOD_ScGnd       IOD_SC_GND  ///< for backward compatibility

sint32  eosIoDiagResetAll_s32( void );                     // Reset diag debounce counter and debounced diag codes of all inputs and outputs
sint32  eosIoDiagOutReset_s32( EosOutName_te outName_e );  // Reset diag debounce counter and debounced diag codes for one output
sint32  eosIoDiagInpDigReset_s32( EosDiName_te diName_e ); // Reset diag debounce counter and debounced diag codes for one digitial input
sint32  eosIoDiagInpAnaReset_s32( EosAiName_te aiName_e ); // Reset diag debounce counter and debounced diag codes for one analog input

 /**
   * \}
   */

/**
 * \defgroup _dig_inputs Digital inputs
 * \{
 */

/// \brief  data struct that contains all commonly needed data of a digital input
typedef struct
{
    IODiag_te   diag_e;         ///< \brief current state of diagnostic
    IODiag_te   rawDiag_e;      ///< \brief raw diag status
    boolean     inputlevel_b;   ///< \brief digital level of digital-input
    uint32      volt_mV_u32;    ///< \brief voltage related to input-pin in MilliVolt-units
} EosDiStatus_ts;
typedef EosDiStatus_ts *EosDiStatus_pts;    ///< \brief special type for pointer to digital-input-status

sint32  EosDiGetSt_s32( EosDiName_te diName_e, EosDiStatus_ts* diStatus_ps );
sint32  eosDiGetSt2_s32( EosDiName_te diInp_e, EosDiStatus_ts* diStatus_ps );


/// \brief  Structure for diagnostic configuration of digital inputs with voltage measurement and pure
/// voltage inputs (analog inputs).
// Notice: Certain input types may ignore some or all config parameters.
typedef struct
{
    sint32  diagLowBorder_mV_s32;       ///< \brief diagnostic lower voltage
    sint32  diagUpperBorder_mV_s32;     ///< \brief diagnostic upper voltage
    sint32  levelOnLow_mV_s32;          ///< \brief voltages below this value will be detected as low level
    sint32  levelOnHigh_mV_s32;         ///< \brief voltages above this value will be detected as high level
    uint16  diagDebounceTime_mS_u16;    ///< \brief debounce time for diagnostic in milli seconds.
    uint16  levelDebounceTime_mS_u16;   ///< \brief debounce time for level in milli seconds.
} EosViConfig_ts;


sint32  EosDiReadConfig_s32( EosDiName_te diName_e, EosViConfig_ts *viCfg_ps );         // read configuration of digital input
sint32  EosDiSetConfig_s32( EosDiName_te diName_e, EosViConfig_ts const *viCfg_ps );    // set configuration of digital input

/**
 * \}
 */

/**
 * \defgroup _digfreq_inputs Digital frequency inputs
 * \{
 */

/**
 * \brief  data struct that contains all commonly needed data of a digital frequency input
 */
typedef struct
{
    EosDiStatus_ts  stDi_s;             ///< \brief status of a normal digital input
    uint32          tiPeriod_us_u32;    ///< \brief measured time of one event in microsec
    uint32          freq_01Hz_u32;      ///< \brief frequency 1/10 Hz units, filterd
    uint32          count_u32;          ///< \brief number of events
    uint16          dutycycle_u16;      ///< \brief duty cycle for high level in 0.01 percent ( 0 - 10000 )
} EosDfiStatus_ts;
typedef EosDfiStatus_ts *EosDfiStatus_pts;  ///< \brief special type for pointer to digital-frequency-input-status

/**
 * \brief dfi result struct with high pulse time in micro seconds
 */
typedef struct
{
    EosDiStatus_ts  stDi_s;             ///< \brief status of a normal digital input
    uint32          tiPeriod_us_u32;    ///< \brief measured time of one event in micro seconds
    uint32          tiHigh_us_u32;      ///< \brief measured time of high pulse in micro seconds
    uint32          freq_01Hz_u32;      ///< \brief frequency 1/10 Hz units, filterd
    uint32          count_u32;          ///< \brief number of events  */
    uint16          dutycycle_u16;      ///< \brief duty cycle for high level in 0.01 percent ( 0 - 10000 )
} EosDfiStatus2_ts;

/**
 * \brief  struct to config frequency inputs
 */
typedef struct
{
    uint32        averagePeriod_us_u32;             ///< \brief if period time is below this value events will be combinded to one event
    boolean       gap_detection_on_b;               ///< \brief if TRUE Gap detection is one
    uint16        low_freq_detection_time_MS_u16;   ///< \brief Detection time to calculalate a maximum frequency when there are not many events
} EosDfiConfig_ts;
typedef EosDfiConfig_ts * EosDfiConfig_pts; ///< \brief special type for pointer to digital-frequency-input-status

/** runtime function to read and set up digital frequency inputs */
sint32  EosDfiGetSt_s32(EosDiName_te dfiName_e, EosDfiStatus_ts *dfiStatus_ps);
sint32  eosDfiGetSt2_s32(EosDiName_te dfiName_e, EosDfiStatus2_ts *dfiStatus_ps);

sint32  EosDfiConfigSt_s32 ( EosDiName_te dfiName_e, EosDfiConfig_ts const *dfiConfig_ps );

sint32  eosDfiStart_s32( EosDiName_te dfiName_e );  // Start measuring of frequency for a specific input
sint32  eosDfiStartAll_s32( void );                 // Start measuring of all frequency inputs

/**
 * \brief  result struct for phase measuring
 */
typedef struct
{
    uint32      timPrimSig_u32;         ///< \brief primary signal time stamp [us]
    uint32      timSecSig_u32;          ///< \brief secondary signal time stamp [us]
    uint32      timShift_u32;           ///< \brief signal phase shift [us]
    sint32      countPulse_s32;         ///< \brief pulse counter
    bool        levelSecSig_b;          ///< \brief level of second signal at the rising edge from the primary signal

    uint32      timPeriodPrimSig_u32;   ///< \brief period time primary signal [us]
    uint32      timPeriodSecSig_u32;    ///< \brief period time secondary signal [us]
    uint8       statusErrPrimSig_u8;    ///< \brief error state primary signal
                                        ///< \brief - Bit0 state at function call time ("1" for high or "0" for low
                                        ///< \brief - Bit1 no update available (request within the same period)
                                        ///< \brief - Bit2 period too long (timer overflow)
                                        ///< \brief - Bit3 measured period exceeds given maximum length
    uint8       statusErrSecSig_u8;     ///< \brief error state secondary signal
                                        ///< \brief - Bit0 state at function call time ("1" for high or "0" for low
                                        ///< \brief - Bit1 no update available (request within the same period)
                                        ///< \brief - Bit2 period too long (timer overflow)
                                        ///< \brief - Bit3 measured period exceeds given maximum length
} EosDfiPhaseDep_ts;

sint32  eosDfiGetPhaseDep_s32( EosDiName_te dfiPrim_e, EosDiName_te dfiSec_e, EosDfiPhaseDep_ts * dfiPhaseDep_ps );
sint32  eosDfiEnablePhaseDep_s32(EosDiName_te dfiPrim_e, EosDiName_te dfiSec_e);
sint32  eosDfiDisablePhaseDep_s32(EosDiName_te dfiPrim_e, EosDiName_te dfiSec_e);

sint32  eosDfiDsmLoadResEnable_s32( EosDiName_te dfiDsm_e, boolean enable_b);

/**
 * \}
 */

/**
 * \defgroup _analog_inputs Analog inputs
 * \{
 */
/// \brief data struct that contains all commonly needed data of a analog input
typedef struct
{
    IODiag_te   diag_e;         ///< \brief current state of diagnostic - this element is available ONLY for current inputs
    IODiag_te   rawDiag_e;      ///< \brief unfiltered diagnostic status
    uint32      volt_mV_u32;    ///< \brief voltage related to input-pin in MilliVolt-units this element is available for Current AND voltage inputs
    uint32      curr_uA_u32;    ///< \brief current at this input in microAmpere-units this element is available ONLY for Current-inputs
} EosAiStatus_ts;
typedef EosAiStatus_ts* EosAiStatus_pts;    ///< \brief special type for pointer to digital-input-status

sint32  EosAiGetSt_s32( EosAiName_te AiName_ce, EosAiStatus_ts *AiStatus_cps );         ///< \brief return current status of an voltage/current input
sint32  eosAiGetSt2_s32( EosAiName_te aiInp_e, EosAiStatus_ts* aiSts_ps);               ///< \brief return current status of an voltage/current input (latest ADC value)

sint32  EosAiSetConfig_s32(EosAiName_te aiName_e, EosViConfig_ts const *viCfg_ps);      ///< \brief set configuration parameters for diagnostic
sint32  EosAiReadConfig_s32( EosAiName_te aiName_e, EosViConfig_ts *viCfg_ps );         ///< \brief read current configuration parameters of analog voltage input.

/**
 * \}
 */

/**
 * \defgroup _outputs Outputs
 * \{
 */

/// \brief data struct that contains all commonly needed data of an output
typedef struct
{
    sint16      setvalue_s16;   ///< \brief currently used set-value for PWM-outputs
    sint32      i_uA_s32;       ///< \brief measured current (if possible) [uA]
    IODiag_te   diagraw_e;      ///< \brief current unfiltered state of diagnostic
    IODiag_te   diag_e;         ///< \brief current filtered state of diagnostic
    boolean     outlevel_b;     ///< \brief digital level of output
} EosOutStatus_ts;
typedef EosOutStatus_ts *EosOutStatus_pts; ///< \brief special type for pointer to output-status

/**
 * \brief used together with EosOutGetSt2_s32()
 *
 * includes voltage, which EosOutStatus_ts does not
 */
typedef struct
{
    sint16      setvalue_s16;   ///< \brief currently used set-value for PWM-outputs
    sint32      u_mV_s32;       ///< \brief measured voltage (if possible) [mV]
    sint32      i_uA_s32;       ///< \brief measured current (if possible) [uA]
    IODiag_te   diagraw_e;      ///< \brief current unfiltered state of diagnostic
    IODiag_te   diag_e;         ///< \brief current filtered state of diagnostic
    boolean     outlevel_b;     ///< \brief digital level of output
} EosOutStatus2_ts;

/// \brief structure to hold PWM output settings
typedef struct
{
    uint16  Pwfreq_Hz_u16;        ///< \brief frequency in Hz
    sint16  PwOffs_u16;           ///< \brief above this value a resistor diagnostic is done, 0 .. Max Duty cycle <em>not used</em>
    uint32  ResistMin_mOhm_u32;   ///< \brief minimum allowed resistance [mOhm]
    uint32  ResistMax_mOhm_u32;   ///< \brief maximum allowed resistance [mOhm]
    uint32  CurrentMax_uA_u32;    ///< \brief maximum allowed current [uA]
    uint32  Filtertime_MSek_u32;  ///< \brief if a detected error is still present after this time [ms], diag_e element is set
    uint16  SCD_Max_cnt_u16;      ///< \brief maximum allowed errors for short circuit detection, 0xffff = scd of <em>not used</em>
}EosOutPara_ts;
typedef EosOutPara_ts *EosOutPara_pts;  ///< special type for pointer to output parameter

/*
 * note: formerly there was a variable resolution depending on CPU-speed
 *       according to this experience we decided to define this to a fixed value
 */
#define EOSOUT_MAX_PW_RESOLUTION    ((sint16)10000) ///< \brief maximum value for PWM output duty cycle
#define EOSOUT_PWM_OFF_VALUE        ((sint16) 0)    ///< \brief minium value (just to have a better readable code, always zero)

#define EOSOUT_MIN_uA_ANALOGOUT     4000u           ///< \brief minimum analog output current [uA]
#define EOSOUT_MAX_uA_ANALOGOUT     20000u          ///< \brief maximum Analog output current [uA]

#define STD_FREQUENCY_PWM_Hz       100u            ///< \brief 100Hz Standard Frequency
#define PWM_OUTPUT_MIN_HZ          40u             ///< \brief minimum frequency for pwm outputs
#define STD_ERROR_TIME_PWM_MS      240u            ///< \brief final error After 240ms
#define STD_MAX_RESISTOR_PWM_mOHM  65000u          ///< \brief resistance > 65 ohms means open load
#define STD_MIN_RESISTOR_PWM_mOHM  3500u           ///< \brief resistance < 3.5 ohms means short circuit to GND
#define STD_MAX_CURRENT_PWM_uA     (3000u*1000u)   ///< \brief current > 3A means short cut to ground or overload
#define STD_MAX_CNT_SCD            3u              ///< \brief maximum errors for short cut detection
#define SCD_OFF                    0xFFFFu         ///< \brief this value for SCD_CNT disables SCD-detection
#define STD_PWM_DIAG_OFFSET        (EOSOUT_MAX_PW_RESOLUTION/10)   ///< \brief below this value no resistance diagnostic is done

sint32  EosOutSetPw_s32     (EosOutName_te name_e, sint16 value_s16);
sint32  EosOutSetSwitch_s32 (EosOutName_te name_e, boolean switch_b);
sint32  EosOutGetSt_s32     (EosOutName_te name_e, EosOutStatus_ts *status_ps);
sint32  EosOutGetSt2_s32    (EosOutName_te outName_e, EosOutStatus2_ts *outStatus_ps);
sint32  EosOutSetPara_s32   (EosOutName_te outName_ce, EosOutPara_ts const *para_ps);
sint32  EosOutGetPara_s32   (EosOutName_te outName_e, EosOutPara_ts *para_ps);

/// \brief set multiple outputs with one call (one RTOS message)
typedef struct
{
    uint8   outSymb_u8;     ///< output Symbol
    boolean coherent_b;     ///< FALSE: immediate update for pwm TRUE: dc will be updated on next pwm period
    sint16  setValue_s16;   ///< -EOSOUT_MAX_PW_RESOLUTION / 0 / EOSOUT_MAX_PW_RESOLUTION
} EosOutMultipleSet_ts;

sint32  eosOutSetMultiplePw_s32( EosOutMultipleSet_ts const* multiSetVal_ps, uint16 nofSetVals_u16);

/**
 * \}
 */

/**
 * \defgroup _ecu_status ECU status
 * \{
 */

/**
 * \brief  all defs, data, prototypes to access ECU internal voltage and temperature values
 */
typedef enum
{
    UBAT  = 3       ///< \brief power supply voltage
} EosECUNntName_te;

/**
 * \brief  struct used to read internal voltages, power supply voltages and temperatures
 */
typedef struct
{
    IODiag_te   diag_e;             ///< \brief current state of diagnostic
    uint32      volt_mV_u32;        ///< \brief voltage [mV]
    sint32      temperature_C_s32;  ///< \brief temperature on PCB [degrees C] (only valid for ECU_TEMP item)
    boolean     supply_on_b;        ///< \brief power supply ON/OFF of digital/PWM outputs
} EosECUStatus_ts;
typedef EosECUStatus_ts *EosECUStatus_pts;  ///< \brief special type of pointer to ECU-status

sint32  EosECUGetSt_s32( EosECUNntName_te ECUName_ce, EosECUStatus_ts *ECUStatus_cps ) __attribute__((deprecated));
/**
 * \}
 */


/**
 * \defgroup _inp_temp_pcb PCB temperature inputs
 * \{
 */

/**
 * \brief data struct to hold information about temperature inputs
 */
typedef struct
{
    uint16  adcRaw_u16;         ///< \brief raw value from ADC
    sint16  temp_10ths_C_s16;   ///< \brief temperature in 1/10ths degrees celsius
} EosTiStatus_ts;

sint32 EosTiGetSt_s32(EosTiName_te tempName_e, EosTiStatus_ts *tiStatus_s);
/**
 * \}
 */

#ifdef __cplusplus
  }
#endif // __cplusplus

#endif   //  _EOS_H
