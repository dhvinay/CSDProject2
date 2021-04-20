/**
 *  \file       iosymbSRC14_34_31.h
 *
 *  \brief      Symbol definition for global EXT-Light I/Os
 *
 *  This file contains the enums used to access I/O for the
 *  redesigned EXT-LIGHT.
 *
 *  Copyright 2014 (c) AGCO GmbH, Marktoberdorf
 *
 *  \par    history
 *
 *  2013-12-16 / Christian.Pischulti@xfendt.de
 *  - created for EXT-Light EFG or Bosch SRC14-34/31
 *
 *  2014-09-25 / Christian.Pischulti@AGCOcorp.com
 *  - [PB-8554] Changed enums for SRC14-34/31 B samples.
 *
 *  2014-10-24 / Christian.Pischulti@AGCOcorp.com
 *  - [Misc] Fixed pin numbers of CANs.
 *
 *  2014-11-24 / Christian.Pischulti@AGCOcorp.com
 *  - [Misc] Fixed some comments.
 *
 *  2015-09-08 / Christian.Pischulti@AGCOcorp.com
 *  - [PB-10268] Changed description and enums for C-sample.
 *  
 *  2016-04-19 / Christian.Pischulti@AGCOcorp.com
 *  - [PB-12141] Added comments for phase measuring pairs.
 */
#ifndef IOSYMBSRC14_34_31_H
#define IOSYMBSRC14_34_31_H

/*
 *       Outputs
 */
/*! \brief  all names for outputs to be used with output-functions  */
typedef enum
{
    POH_02,     ///< Pin 177 PWM-Output, 5A, good current measurement
    POH_04,     ///< Pin 186 PWM-Output, 5A, good current measurement
    POH_05,     ///< Pin 151 PWM-Output, 5A, good current measurement
    POH_06,     ///< Pin 175 PWM-Output, 5A, good current measurement
    POH_07,     ///< Pin 152 PWM-Output, 5A, good current measurement
    POH_09,     ///< Pin 149 PWM-Output, 5A, good current measurement      Notice: for EHR valve
    POH_10,     ///< Pin 173 PWM-Output, 5A, good current measurement      Notice: for EHR valve
    POH_17,     ///< Pin 126 PWM-Output, 5A, good current measurement

    PDOH_03,    ///< Pin 190 PWM-Output, 4.6A, medium quality current measurement
    PDOH_04,    ///< Pin 189 PWM-Output, 4.6A, medium quality current measurement
    PDOH_05,    ///< Pin 194 PWM-Output, 4.6A, medium quality current measurement
    PDOH_06,    ///< Pin 193 PWM-Output, 4.6A, medium quality current measurement
    PDOH_08,    ///< Pin 187 PWM-Output, 4.6A, medium quality current measurement
    PDOH_09,    ///< Pin 196 PWM-Output, 4.6A, medium quality current measurement
    PDOH_10,    ///< Pin 249 PWM-Output, 4.6A, medium quality current measurement
    PDOH_13,    ///< Pin 153 PWM-Output, 4.6A, medium quality current measurement
    PDOH_14,    ///< Pin 154 PWM-Output, 4.6A, medium quality current measurement
    PDOH_15,    ///< Pin 176 PWM-Output, 4.6A, medium quality current measurement
    PDOH_16,    ///< Pin 129 PWM-Output, 4.6A, medium quality current measurement
    PDOH_17,    ///< Pin 130 PWM-Output, 4.6A, medium quality current measurement
    PDOH_18,    ///< Pin 107 PWM-Output, 4.6A, medium quality current measurement   (EXTLT DOH_15)
    PDOH_19,    ///< Pin 104 PWM-Output, 4.6A, medium quality current measurement, no pullup (EXTLT DOH_14)
    PDOH_20,    ///< Pin 115 PWM-Output, 4.6A, medium quality current measurement   (EXTLT DOH_01)
    PDOH_21,    ///< Pin 243 PWM-Output, 4.6A, medium quality current measurement   (EXTLT DOH_02)

    DOH_01,     ///< Pin 256 PWM-Output, 4.6A, medium quality current measurement   (EXTLT  DOH_06)
    DOH_02,     ///< Pin 257 PWM-Output, 4.6A, medium quality current measurement   (EXTLT  DOH_08)
    DOH_03,     ///< Pin 241 PWM-Output, 4.6A, medium quality current measurement
    DOH_04,     ///< Pin 242 PWM-Output, 4.6A, medium quality current measurement
    DOH_05,     ///< Pin 114 PWM-Output, 4.6A, medium quality current measurement
    //DOH_06,   ///< Pin 256 --> SRC14-34/31 DOH_01
    DOH_07,     ///< Pin 244 PWM-Output, 4.6A, medium quality current measurement
    //DOH_08,   ///< Pin 257 --> SRC14-34/31 DOH_02
    //DOH_09,   ///< Pin 127 --> SRC14-34/31 DOH_15
    DOH_10,     ///< Pin 102 PWM-Output, 4.6A, medium quality current measurement
    //DOH_11,   ///< Pin 128 --> SRC14-34/31 DOH_14
    DOH_12,     ///< Pin 103 PWM-Output, 4.6A, medium quality current measurement
    DOH_13,     ///< Pin 105 PWM-Output, 4.6A, medium quality current measurement
    DOH_14,     ///< Pin 128 PWM-Output, 4.6A, medium quality current measurement   (EXTLT DOH_11)
    DOH_15,     ///< Pin 127 PWM-Output, 4.6A, medium quality current measurement   (EXTLT DOH_09)
    DOH_16,     ///< Pin 106 PWM-Output, 4.6A, medium quality current measurement

    AO_01,      ///< Pin 221 analog current output 4mA - 20mA

    POL_01,     ///< Pin 178 PWM-Output, 5A, good current measurement  Notice:  lowside switch for EHR valve coils
    POL_02,     ///< Pin 184 PWM-Output, 5A, good current measurement (EXTLT DOL_01)
    POL_03,     ///< Pin 185 PWM-Output, 5A, good current measurement (EXTLT DOL_02)
    POL_04,     ///< Pin 182 PWM-Output, 5A, good current measurement (EXTLT DOL_03)
    POL_05,     ///< Pin 183 PWM-Output, 5A, good current measurement (EXTLT DOL_04)
    POL_06,     ///< Pin 180 PWM-Output, 5A, good current measurement (EXTLT DOL_05)

    // supply LEDs only with VSS_1 +5.0V DOPS_5V
    DOL_01,     ///< Pin 179 PWM-Output, LED-Driver
    DOL_02,     ///< Pin 191 PWM-Output, LED-Driver
    DOL_03,     ///< Pin 192 PWM-Output, LED-Driver
    DOL_04,     ///< Pin 150 PWM-Output, LED-Driver
    DOL_05,     ///< Pin 174 PWM-Output, LED-Driver

    DOL_06,     ///< Pin 181 PWM-Output, 0.5A, good current measurement

    DOMR_01,    ///< main power relay for PXXX outputs ( highside ) ( net V_PO )
    DOMR_02,    ///< main power relay for DXXX outputs ( highside ) ( net V_DO )
    DOMR_03,    ///< main power relay for P_AI_UBAT

    DOPS_5V,    ///< Pin 219 VSS_1 5V external power supply
    DOPS_8V5,   ///< Pin 232/195 VSS_2 8,5V external power supply

    DO_PUDI,    ///< Turnon pullup voltage for DI_09-DI_16 (DI becomes AI)

} EosOutName_te;

/*
 *   Analog inputs
 */

/*! \brief  All names for analog inputs to be used with input-functions  */
typedef enum
{
    // analog current inputs
    CI_03,                      ///< Pin 218
    CI_04,                      ///< Pin 229
    CI_05,                      ///< Pin 171
    CI_06,                      ///< Pin 227
    CI_07,                      ///< Pin 167
    CI_09,                      ///< Pin 170
    CI_10,                      ///< Pin 165
    CI_11,                      ///< Pin 230
    CI_12,                      ///< Pin 140
    CI_13,                      ///< Pin 139
    CI_14,                      ///< Pin 166
    CI_15,                      ///< Pin 164
    CI_16,                      ///< Pin 141
    // analog voltage input
    AI_01,                      ///< Pin 119, 9.5 V
    AI_02,                      ///< Pin 120
    AI_03,                      ///< Pin 121
    AI_04,                      ///< Pin 116    especially for EHR force measure bolt
    AI_05,                      ///< Pin 117
    AI_06,                      ///< Pin 118
    AI_07,                      ///< Pin 231    especially for EHR force measure bolt
    AI_08,                      ///< Pin 217
    AI_09,                      ///< Pin 213
    AI_10,                      ///< Pin 226
    AI_11,                      ///< Pin 228
    AI_12,                      ///< Pin 188

    // analog voltage input with 7.5kOhm pullup to 5V  AI_5V_OUT (temperature measuring)
    AI_TEMP_1,                  ///< Pin 138
    AI_TEMP_2,                  ///< Pin 168
    AI_TEMP_3,                  ///< Pin 169
    AI_TEMP_4,                  ///< Pin 172

    AI_UBAT,                    ///< Kl30 power supply voltage (P_AI_KL30)
    AI_VREF,                    ///< internal used power supply (P_AI_VSS3)
    AI_5V_OUT,                  ///< VDD5 internal power supply
    AI_5V_TLE,                  ///< VDD5 internal power supply
    AI_2V54,                    ///< internal power supply
    AI_V_CI,                    ///< pullup supply for current inputs over current protection
    AI_VSS3,                    ///< internal boost supply (Cy141)

    AI_Num                      ///< number of analog inputs
} EosAiName_te;

#define AI_VBAT     AI_UBAT     ///< AI_VBAT is used in libs

/*
 *   Digital Inputs
 */

/*! \brief  All names for digital inputs to be used with input-functions  */
typedef enum
{
    // digital input (DO_PUDI = on) or analog inputs (DO_PUDI = off)
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
    // digital inputs
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
    DFI_01,                             ///< Pin 112 DFI_01/DFI_03 phase measuring
    DFI_02,                             ///< Pin 113
    DFI_03,                             ///< Pin 110 DFI_01/DFI_03 phase measuring
    DFI_04,                             ///< Pin 111 DFI_04/DFI_08 phase measuring
    DFI_05,                             ///< Pin 109
    DFI_06,                             ///< Pin 108 DFI_06/DFI_07 phase measuring
    DFI_07,                             ///< Pin 133 DFI_06/DFI_07 phase measuring
    DFI_08,                             ///< Pin 132 DFI_04/DFI_08 phase measuring
    // DSM digital frequency inputs
    DFI_09,                             ///< Pin 155 DFI_09(DSM_01)/DFI_10(DSM_02) phase measuring
    DFI_10,                             ///< Pin 156 DFI_09(DSM_01)/DFI_10(DSM_02) phase measuring

    DI_KL15,                            ///< Pin 240 Ignition Key status
    DI_SW_INH                           ///< Pin 131
} EosDiName_te;

/*! \brief ECU internal temperature sensors */
typedef enum
{
    PTEMP_01,                           ///< Internal temperature sensor (Rev polarity protection mosfet)
    PTEMP_02,                           ///< Internal temperature sensor (Cy327)
    PTEMP_03                            ///< Internal temperature sensor (powerstages)
} EosTiName_te;


// communication pins (Eos numbering)
// CAN1_H       - 215
// CAN1_L       - 216
// CAN2_H       - 253
// CAN2_L       - 254
// CAN3_H       - 163
// CAN3_L       - 162
// CAN4_H       - 161
// CAN4_L       - 160
// LIN_1        - 255

// power supply
// KL30         - 201/203/204/205/206
// KL30_1       - 245/258
// KL15         - 240
// GND          - 122/123/124/202/207/220/233/246/
// AGND         - 145/146


#endif   // IOSYMBSRC14_34_31_H
