/**
 *  \file       iosymbSRC9_34.h
 *
 *  \brief      Symbol definition for EXT-Light I/Os
 *
 *  This file contains the enums used to access I/O for the platform EXT-LIGHT.
 *
 *  Copyright 2009 (c) AGCO/Fendt GmbH & Co.
 *
 *  \section    history
 *
 *  2008-02-26 / Christian.Pischulti@xfendt.de
 *  - created for EXT-Light also called Bosch SRC 9-34
 *
 *  2008-07-03 / Christian.Pischulti@xfendt.de
 *  - Fixed comment about POH_17. The pin number 130 was wrong. The
 *  right pin number is 126. Code isn't affected by this comment.
 *
 *  2008-11-20 / Christian.Pischulti@xfendt.de
 *  - External components for inputs DI12, DI22, DI27, DI32, DFI_7 and DFI_8 are loaded
 *    for C samples. Fixed comment. Code isn't affected by this comment.
 *
 *  2010-06-23 / Christian.Pischulti@xfendt.de
 *  - New symbols DOMR_0X for main relays 1/2 and DOPS_XVX to turn on/off external
 *    sensor supplies.
 *
 *  2011-12-02 / florian.schwarz@euro-engineering.com
 *  - added AI_UBAT and AI_VREF as analog voltage inputs
 *  - added temperature input PTEMP_01
 *
 *  2012-05-15 / florian.schwarz@euro-engineering.com
 *  - added AI_Num to EosAiName_te enum to have a convenient way
 *    to determine the number of analog inputs.
 *
 *  2014-10-08 / Christian.Pischulti@AGCOcorp.com
 *  - [PB-8563] changed wrong pin number of AO_01 to 221 (comment only, no impact on code)
 *
 *  2015-01-27 / Christian.Pischulti@AGCOcorp.com
 *  - [PB-8563] Renamed file from iosymbEXTLT.h to iosymbSRC9_34.h.
 */
#ifndef IOSYMBSRC9_34_H
#define IOSYMBSRC9_34_H

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
    POH_02,     ///< Pin 177   PWM-Output, 3A, good current measurement
    POH_04,     ///< Pin 186   PWM-Output, 3A, good current measurement
    POH_05,     ///< Pin 151   PWM-Output, 3A, good current measurement
    POH_06,     ///< Pin 175   PWM-Output, 3A, good current measurement
    POH_07,     ///< Pin 152   PWM-Output, 3A, good current measurement
    POH_09,     ///< Pin 149   PWM-Output, 4.5A, good current measurement      Notice: for EHR valve
    POH_10,     ///< Pin 173   PWM-Output, 4.5A, good current measurement      Notice: for EHR valve
    POH_17,     ///< Pin 126   PWM-Output, 3A, good current measurement

    PDOH_03,    ///< Pin 190  PWM-Output, 3A, medium quality current measurement
    PDOH_04,    ///< Pin 189  PWM-Output, 3A, medium quality current measurement
    PDOH_05,    ///< Pin 194  PWM-Output, 3A, medium quality current measurement
    PDOH_06,    ///< Pin 193  PWM-Output, 3A, medium quality current measurement
    PDOH_08,    ///< Pin 187  PWM-Output, 3A, medium quality current measurement
    PDOH_09,    ///< Pin 196  PWM-Output, 3A, medium quality current measurement
    PDOH_10,    ///< Pin 249  PWM-Output, 3A, medium quality current measurement
    PDOH_13,    ///< Pin 153 PWM-Output, 3A, medium quality current measurement
    PDOH_14,    ///< Pin 154 PWM-Output, 3A, medium quality current measurement
    PDOH_15,    ///< Pin 176 PWM-Output, 3A, medium quality current measurement
    PDOH_16,    ///< Pin 129 PWM-Output, 3A, medium quality current measurement
    PDOH_17,    ///< Pin 130 PWM-Output, 3A, medium quality current measurement

    DOH_01,     ///< Pin 115 PWM-Output, 2.0A, no current measurement
    DOH_02,     ///< Pin 243 PWM-Output, 2.0A, no current measurement
    DOH_03,     ///< Pin 241 PWM-Output, 2.0A, no current measurement
    DOH_04,     ///< Pin 242 PWM-Output, 2.0A, no current measurement
    DOH_05,     ///< Pin 114 PWM-Output, 2.0A, no current measurement
    DOH_06,     ///< Pin 256 PWM-Output, 2.0A, no current measurement
    DOH_07,     ///< Pin 244 PWM-Output, 2.0A, no current measurement
    DOH_08 ,    ///< Pin 257 PWM-Output, 2.0A, no current measurement
    DOH_09,     ///< Pin 127 PWM-Output, 2.0A, no current measurement
    DOH_10,     ///< Pin 102 PWM-Output, 2.0A, no current measurement
    DOH_11,     ///< Pin 128 PWM-Output, 2.0A, no current measurement
    DOH_12,     ///< Pin 103 PWM-Output, 2.0A, no current measurement
    DOH_13,     ///< Pin 105 PWM-Output, 2.0A, no current measurement
    DOH_14,     ///< Pin 104 PWM-Output, 2.0A, no current measurement
    DOH_15,     ///< Pin 107 PWM-Output, 2.0A, no current measurement
    DOH_16,     ///< Pin 106 PWM-Output, 2.0A, no current measurement

    AO_01,      ///< Pin 221 analog current output 4mA - 20mA

    POL_01,     ///< Pin 178 PWM-Output, 4.5A, good current measurement  Notice:  lowside switch for EHR valve coils

    DOL_01,     ///< Pin 184 PWM-Output, 0.5A, no current measurement
    DOL_02,     ///< Pin 185 PWM-Output, 0.5A, no current measurement
    DOL_03,     ///< Pin 182 PWM-Output, 0.5A, no current measurement
    DOL_04,     ///< Pin 183 PWM-Output, 0.5A, no current measurement
    DOL_05,     ///< Pin 180 PWM-Output, 0.5A, no current measurement
    DOL_06,     ///< Pin 181 PWM-Output, 0.5A, no current measurement

    DOMR_01,    ///< main power relay for PXXX outputs ( highside ) ( net V_PO )
    DOMR_02,    ///< main power relay for DXXX outputs ( highside ) ( net V_DO )

    DOPS_5V,    ///< Pin 219 VSS_1 5V external power supply
    DOPS_8V5    ///< Pin 232 VSS_2 8,5V external power supply

} EosOutName_te;

#define FIRST_OUTPUT    POH_02
#define LAST_OUTPUT     DOL_06

// If application code written for use on EXT/EXT-LIGHT uses I/O symbols from EXT the symbols
// will be set to DUMMY_PIN.
#define         POH_01                  DUMMY_PIN
#define         POH_03                  DUMMY_PIN
#define         POH_08                  DUMMY_PIN

#define         POH_11                  DUMMY_PIN
#define         POH_12                  DUMMY_PIN
#define         POH_13                  DUMMY_PIN
#define         POH_14                  DUMMY_PIN
#define         POH_15                  DUMMY_PIN
#define         POH_16                  DUMMY_PIN
#define         POH_18                  DUMMY_PIN
#define         POH_19                  DUMMY_PIN
#define         POH_20                  DUMMY_PIN

#define         PDOH_01               DUMMY_PIN
#define         PDOH_02               DUMMY_PIN
#define         PDOH_07               DUMMY_PIN
#define         PDOH_11               DUMMY_PIN
#define         PDOH_12               DUMMY_PIN

#define         POBH_01               DUMMY_PIN
#define         POBH_02               DUMMY_PIN
#define         POBH_03             DUMMY_PIN
#define         POBH_04             DUMMY_PIN
#define         POBH_05             DUMMY_PIN
#define         POBH_06             DUMMY_PIN
#define         POBH_07             DUMMY_PIN
#define         POBH_08             DUMMY_PIN

#define         POBL_01             DUMMY_PIN
#define         POBL_02             DUMMY_PIN
#define         POBL_03             DUMMY_PIN
#define         POBL_04             DUMMY_PIN
#define         POBL_05             DUMMY_PIN
#define         POBL_06             DUMMY_PIN
#define         POBL_07             DUMMY_PIN
#define         POBL_08             DUMMY_PIN

/*
*   Analog inputs
*/

/*! \brief  All names for analog inputs to be used with input-functions  */
typedef enum
{
    // analog current inputs
    CI_01,                      ///< Pin 138   Notice: on ExtLight the external components aren't loaded for this pin but it can be routed to CI_14. If you read it you will get the value for CI_14.
    CI_02,                      ///< Pin 168   Notice: on ExtLight the external components aren't loaded for this pin but it can be routed to CI_15. If you read it you will get the value for CI_15.
    CI_03,                      ///< Pin 218
    CI_04,                      ///< Pin 229
    CI_05,                      ///< Pin 171
    CI_06,                      ///< Pin 227
    CI_07,                      ///< Pin 167
    CI_08,                      ///< Pin 169   Notice: on ExtLight the external components aren't loaded for this pin but it can be routed to CI_13. If you read it you will get the value for CI_13.
    CI_09,                      ///< Pin 170
    CI_10,                      ///< Pin 165
    CI_11,                      ///< Pin 230
    CI_12,                      ///< Pin 140
    CI_13,                      ///< Pin 139
    CI_14,                      ///< Pin 166
    CI_15,                      ///< Pin 164
    CI_16,                      ///< Pin 141
    // analog voltage input
    AI_01,                      ///< Pin 119
    AI_02,                      ///< Pin 120
    AI_03,                      ///< Pin 121
    AI_04,                      ///< Pin 116    especially for EHR force measure bolt
    AI_05,                      ///< Pin 117
    AI_06,                      ///< Pin 118
    AI_07,                      ///< Pin 231    especially for EHR force measure bolt
    AI_08,                      ///< Pin 217

    AI_UBAT,                    ///< Kl30 power supply voltage
    AI_VREF,                    ///< internal used power supply

    AI_Num                      ///< number of analog inputs
} EosAiName_te;

#define AI_VBAT     AI_UBAT

// If application code written for use on EXT/EXT-LIGHT uses I/O symbols from EXT the symbols
// will be set to DUMMY_PIN.
#define         CI_17       DUMMY_PIN
#define         CI_18       DUMMY_PIN

/*
*   Digital Inputs
*/

/*! \brief  All names for digital inputs to be used with input-functions  */
typedef enum
{
    // digital input
    DI_01,                              ///< Pin 250
    DI_02,                              ///< Pin 236
    DI_03,                              ///< Pin 209
    DI_04,                              ///< Pin 147
    DI_05,                              ///< Pin 223
    DI_06,                              ///< Pin 148
    DI_07,                              ///< Pin 159
    DI_08,                              ///< Pin 158
    DI_09,                              ///< Pin 214
    DI_10,                              ///< Pin 157
    DI_11,                              ///< Pin 252
    DI_12,                              ///< Pin 238
    DI_13,                              ///< Pin 222
    DI_14,                              ///< Pin 210
    DI_15,                              ///< Pin 136
    DI_16,                              ///< Pin 137
    DI_17,                              ///< Pin 135
    DI_18,                              ///< Pin 134
    DI_19,                              ///< Pin 211
    DI_20,                              ///< Pin 144
    DI_21,                              ///< Pin 224
    DI_22,                              ///< Pin 143
    DI_23,                              ///< Pin 142
    DI_24,                              ///< Pin 235
    DI_25,                              ///< Pin 247
    DI_26,                              ///< Pin 234
    DI_27,                              ///< Pin 225
    DI_28,                              ///< Pin 212
    DI_29,                              ///< Pin 248
    DI_30,                              ///< Pin 237
    DI_31,                              ///< Pin 239
    DI_32,                              ///< Pin 251
    // digital frequency input
    DFI_01,                             ///< Pin 112
    DFI_02,                             ///< Pin 113
    DFI_03,                             ///< Pin 110
    DFI_04,                             ///< Pin 111
    DFI_05,                             ///< Pin 109
    DFI_06,                             ///< Pin 108
    DFI_07,                             ///< Pin 133
    DFI_08                              ///< Pin 132
} EosDiName_te;

/*! \brief ECU internal temperature sensors */
typedef enum
{
    PTEMP_01                            ///< Internal temperature sensor mounted on pcb.
} EosTiName_te;

// If application code written for use on EXT/EXT-LIGHT uses I/O symbols from EXT the symbols
// will be set to DUMMY_PIN.
#define DFI_09                      DUMMY_PIN
#define DFI_10                      DUMMY_PIN

#endif   // IOSYMBSRC9_34_H
