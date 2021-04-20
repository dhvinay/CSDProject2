/**
 *  @file       iosymbSRC14_10.h
 *
 *  @brief      Symbol definition for SRC14_10 ios
 *
 *  This file contains the enums used to access I/O for the ECU SRC14/10
 *
 *  @section    history
 *
 *  2010-05-27 / Christian.Pischulti@xfendt.de
 *  - created
 *
 *  2012-05-15 / florian.schwarz@euro-engineering.com
 *  - added AI_Num to EosAiName_te enum to have a convenient way
 *    to determine the number of analog inputs.
 *  - Added DOPS_5V_3 (VPS_3) 
 *  
 */

#ifndef _IOSYMBSRC14_10_H
#define  _IOSYMBSRC14_10_H

/*
*       Common
*/
// Save define to be used if a symbol for an I/O doesn't exits. With this define the output functions will return
// an error.
#define DUMMY_PIN   30000           // Try to avoid use of this define.

/*
*       Outputs
*/
/*! \brief  all names for outputs to be used with output-functions  */
typedef enum
{
    // Highside outputs
    POH_01,     ///< Pin 74 PWM-Output, 3,5A, good current measurement
    POH_02,     ///< Pin 75 PWM-Output, 3,5A, good current measurement
    POH_03,     ///< Pin 76 PWM-Output, 3,5A, good current measurement
    POH_04,     ///< Pin 77 PWM-Output, 3,5A, good current measurement
    POH_05,     ///< Pin 78 PWM-Output, 3,5A, good current measurement
    POH_06,     ///< Pin 79 PWM-Output, 3,5A, good current measurement
    POH_07,     ///< Pin 80 PWM-Output, 3,5A, good current measurement
    POH_08,     ///< Pin 81 PWM-Output, 3,5A, good current measurement

    POH_09,     ///< Pin 29 PWM-Output, 3,5A, medium current measurment ( integrated sense output )
    POH_10,     ///< Pin 07 PWM-Output, 3,5A, medium current measurment ( integrated sense output )
    POH_11,     ///< Pin 82 PWM-Output, 3,5A, medium current measurment ( integrated sense output )
    POH_12,     ///< Pin 83 PWM-Output, 3,5A, medium current measurment ( integrated sense output )
    POH_13,     ///< Pin 84 PWM-Output, 3,5A, medium current measurment ( integrated sense output )
    POH_14,     ///< Pin 85 PWM-Output, 3,5A, medium current measurment ( integrated sense output )
    POH_15,     ///< Pin 86 PWM-Output, 3,5A, medium current measurment ( integrated sense output )
    POH_16,     ///< Pin 87 PWM-Output, 3,5A, medium current measurment ( integrated sense output )
    POH_19,     ///< Pin 90 PWM-Output, 3,5A, medium current measurment ( integrated sense output )
    POH_20,     ///< Pin 52 PWM-Output, 3,5A, medium current measurment ( integrated sense output )

    POH_17,     ///< Pin 88 PWM-Output, 0,1A, no feedback
    POH_18,     ///< Pin 89 PWM-Output, 0,1A, no feedback

    // Lowside outputs
    POL_01,     ///< Pin 73 PWM-Output, 5A, good current measurement
    POL_02,     ///< Pin 51 PWM-Output, 5A, good current measurement
    POL_03,     ///< Pin 91 PWM-Output, 5A, good current measurement
    POL_04,     ///< Pin 92 PWM-Output, 5A, good current measurement
    POL_05,     ///< Pin 93 PWM-Output, 5A, good current measurement
    POL_06,     ///< Pin 94 PWM-Output, 5A, good current measurement

    // External power supplies.
    DOPS_5V_2,  ///< Pin 71 VPS_2 5V external power supply max 0,3A
    DOPS_5V_3,  ///< Pin 72 VPS_3 5V external power supply max 0,3A

    // DSM enable gpio outputs ( internal )
    DO_ENDSM1,  ///< enable 200 Ohm resistor for DSM1 ( voltage to current mode )
    DO_ENDSM2,  ///< enable 200 Ohm resistor for DSM2 ( voltage to current mode )
    DO_ENDSM3,  ///< enable 200 Ohm resistor for DSM2 ( voltage to current mode )
    DO_ENDSM4,  ///< enable 200 Ohm resistor for DSM2 ( voltage to current mode )
} EosOutName_te;


/*
 *   Analog inputs
 */

/*! \brief  All names for analog inputs to be used with input-functions  */
typedef enum
{
    // analog voltage input
    AIV_01,             ///< Pin 22, 0-5,775V, no pullup
    AIV_02,             ///< Pin 23, 0-5,7V, no pullup
    AIV_03,             ///< Pin 24, 0-5,7V, no pullup
    AIV_04,             ///< Pin 25, 0-5,7V, no pullup
    AIV_05,             ///< Pin 26, 0-5,7V, no pullup
    AIV_06,             ///< Pin 32, 0-5,7V, no pullup
    AIV_07,             ///< Pin 33, 0-5,7V, no pullup
    AIV_08,             ///< Pin 34, 0-5,7V, no pullup
    AIV_09,             ///< Pin 35, 0-5,7V, no pullup
    AIV_10,             ///< Pin 36, 0-5,7V, no pullup
    AIV_11,             ///< Pin 37, 0-5,7V, no pullup
    AIV_12,             ///< Pin 38, 0-5,7V, no pullup
    AIV_13,             ///< Pin 39, 0-5,7V, no pullup
    AIV_14,             ///< Pin 40, 0-5,7V, no pullup
    AIV_15,             ///< Pin 41, 0-5,7V, no pullup
    AIV_16,             ///< Pin 42, 0-5,7V, no pullup

    AIV_17,             ///< Pin 43, 0-5,7V, 3,3V pullup

    AIV_18,             ///< Pin 44, 0-3,3V, no pullup

    AIV_19,             ///< Pin 45, 0-5,7V, no pullup
    AIV_20,             ///< Pin 46, 0-5,7V, no pullup
    AIV_21,             ///< Pin 47, 0-5,7V, no pullup
    AIV_22,             ///< Pin 48, 0-5,7V, no pullup
    AIV_23,             ///< Pin 54, 0-5,7V,  3,3V pullup
    AIV_24,             ///< Pin 55, 0-5,7V, no pullup
    AIV_25,             ///< Pin 56, 0-5,7V, no pullup
    AIV_26,             ///< Pin 57, 0-5,7V, no pullup

    AIV_27,             ///< Pin 58, 0-5,7V, 3,3V pullup
    AIV_28,             ///< Pin 59, 0-5,7V, 3,3V pullup
    AIV_29,             ///< Pin 60, 0-5,7V, 3,3V pullup
    AIV_30,             ///< Pin 61, 0-5,7V, 3,3V pullup
    AIV_31,             ///< Pin 62, 0-5,7V, 3,3V pullup
    AIV_32,             ///< Pin 63, 0-5,7V, 3,3V pullup
    AIV_33,             ///< Pin 64, 0-5,7V, 3,3V pullup
    AIV_34,             ///< Pin 65, 0-5,7V, 3,3V pullup
    AIV_35,             ///< Pin 66, 0-5,7V, 3,3V pullup
    AIV_36,             ///< Pin 67, 0-5,7V, 3,3V pullup
    AIV_37,             ///< Pin 68, 0-5,7V, 3,3V pullup
    AIV_38,             ///< Pin 69, 0-5,7V, 3,3V pullup

    AI_TEMP1,           ///< Pin 10, 0-3,3V, pulldown
    AI_TEMP2,           ///< Pin 11, 0-3,3V, pulldown

    AI_VP1,             ///< Pin 5, highside switch power
    AI_VP2,             ///< Pin 3, highside switch power
    AI_VP3,             ///< Pin 1, highside switch power
    AI_I5V0,            ///< internal 5V power supply
    AI_I2V6,            ///< internal 2V6 power supply
    AI_I1V5,            ///< internal 1V5 power supply
    AI_E5V_1,           ///< Pin 70 external 5V sensor supply, max. 0.3A
    AI_E5V_2,           ///< Pin 71 external 5V sensor supply, max. 0.3A
    AI_E3V3,            ///< Pin 72 external 3.3V sensor supply, max. 0.15A
    AI_IMUX,            ///< internal mux protection voltage

    AI_Num              ///< number of analog inputs
} EosAiName_te;

#define AI_UBAT     AI_VP1
#define AI_VBAT     AI_UBAT

/*
*   Digital Inputs
*/

/*! \brief  All names for digital inputs to be used with input-functions  */
typedef enum
{
    // digital frequency input
    FIV_01,             ///< Pin 14
    FIV_02,             ///< Pin 15
    FIV_03,             ///< Pin 16
    FIV_04,             ///< Pin 17
    FIV_05,             ///< Pin 18
    FIV_06,             ///< Pin 19
    FIV_07,             ///< Pin 20
    DSM_01,             ///< Pin 12
    DSM_02,             ///< Pin 13
    DSM_03,             ///< Pin 45     Notice: stuffing option for AIV 19
    DSM_04,             ///< Pin 46     Notice: stuffing option for AIV 20
    FIV_01_AC,          ///< Pin 14     Notice: stuffing option for FIV_01
    FIV_02_AC,          ///< Pin 15     Notice: stuffing option for FIV_02
    FIV_03_AC,          ///< Pin 16     Notice: stuffing option for FIV_03
    INH_01              ///< Pin 30     Notice: Stuffing option
} EosDiName_te;

/*! \brief ECU internal temperature sensors */
typedef enum
{
    PTEMP_01,
    PTEMP_02,
    PTEMP_03,
    PTEMP_04
} EosTiName_te;

// If application code written for use on EXT/EXT-LIGHT uses I/O symbols from EXT the symbols
// will be set to DUMMY_PIN.
#define DFI_09                      DUMMY_PIN
#define DFI_10                      DUMMY_PIN

#endif   // _IOSYMBEXTLT_H
