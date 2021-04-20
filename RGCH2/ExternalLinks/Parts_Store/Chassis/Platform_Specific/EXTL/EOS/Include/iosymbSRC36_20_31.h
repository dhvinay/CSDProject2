/**
 *  \file   iosymbSRC36_20_31.h
 *
 *  \brief  Symbol definition for SRC36-20/31
 *
 *  SRC36-20/31 is the successor ecu of EXT also
 *  suitable as sparepart.
 *
 *  Copyright 2012 (c) AGCO GmbH, Marktoberdorf
 *
 *  \section History
 *
 *  2012-04-03 / Christian.Pischulti@xfendt.de
 *  - draft
 *
 *  2014-10-08 / Christian.Pischulti@AGCOcorp.com
 *  - [PB-5211] Added comment to DFI to show which frequency
 *    inputs can be used for phase measuring.
 *  - [PB-8563] Added DI_KL15 for direct reading of ignition key status to
 *    have same features as SRC4-5 and SRC14-34/31. Fixed pin numbers for CAN
 *    buses to match CAN numbers of EOS.
 */

#ifndef _IOSYMBSRC36_20_31_H
#define  _IOSYMBSRC36_20_31_H

/*
*       Common
*/
// Safe define to be used if a symbol for an I/O doesn't exits. With this define the Eos functions will return
// with an error.
#define DUMMY_PIN   MAXUINT8           // Try to avoid using this define.

/*
*       Outputs
*/

/*! \brief  all names for outputs to be used with output-functions  */
typedef enum
{
    POH_01,     ///< Pin 153     --  PDOH_13     EXT-LIGHT
    POH_02,     ///< Pin 177     --  POH_2       EXT_LIGHT
    POH_03,     ///< Pin 154     --  PDOH_14     EXT-LIGHT
    POH_04,     ///< Pin 186     --  POH_04      EXT-LIGHT
    POH_05,     ///< Pin 151     --  POH_05      EXT-LIGHT
    POH_06,     ///< Pin 175     --  POH_06      EXT-LIGHT
    POH_07,     ///< Pin 152     --  POH_07      EXT-LIGHT
    POH_08,     ///< Pin 176     --  PDOH_15     EXT-LIGHT
    POH_09,     ///< Pin 149     --  POH_09      EXT-LIGHT
    POH_10,     ///< Pin 173     --  POH_10      EXT-LIGHT
    POH_11,     ///< Pin 150     --  NC          EXT-LIGHT
    POH_12,     ///< Pin 174     --  NC          EXT-LIGHT
    POH_13,     ///< Pin 130     --  PDOH_17     EXT_LIGHT
    POH_14,     ///< Pin 131     --  NC          EXT-LIGHT
    POH_15,     ///< Pin 156     --  NC          EXT-LIGHT
    POH_16,     ///< Pin 155     --  NC          EXT-LIGHT
    POH_17,     ///< Pin 126     --  POH_17      EXT-LIGHT
    POH_18,     ///< Pin 101     --  NC          EXT-LIGHT
    POH_19,     ///< Pin 125     --  NC          EXT-LIGHT
    POH_20,     ///< Pin 129     --  PDOH_16     EXT-LIGHT

    PDOH_01,    ///< Pin 192     --  NC          EXT-LIGHT
    PDOH_02,    ///< Pin 191     --  NC          EXT-LIGHT
    PDOH_03,    ///< Pin 190     --  PDOH_03     EXT-LIGHT
    PDOH_04,    ///< Pin 189     --  PDOH_04     EXT-LIGHT
    PDOH_05,    ///< Pin 194     --  PDOH_05     EXT-LIGHT
    PDOH_06,    ///< Pin 193     --  PDOH_06     EXT-LIGHT
    PDOH_07,    ///< Pin 188     --  NC          EXT-LIGHT
    PDOH_08,    ///< Pin 187     --  PDOH_08     EXT-LIGHT
    PDOH_09,    ///< Pin 196     --  PDOH_09     EXT-LIGHT
    PDOH_10,    ///< Pin 249     --  PDOH_10     EXT-LIGHT
    PDOH_11,    ///< Pin 172     --  NC          EXT-LIGHT
    PDOH_12,    ///< Pin 195     --  NC          EXT-LIGHT

    DOH_01,     ///< Pin 115     --  DOH_01      EXT-LIGHT
    DOH_02,     ///< Pin 243     --  DOH_02      EXT-LIGHT
    DOH_03,     ///< Pin 241     --  DOH_03      EXT-LIGHT
    DOH_04,     ///< Pin 242     --  DOH_04      EXT-LIGHT
    DOH_05,     ///< Pin 114     --  DOH_05      EXT-LIGHT
    DOH_06,     ///< Pin 256     --  DOH_06      EXT-LIGHT
    DOH_07,     ///< Pin 244     --  DOH_07      EXT-LIGHT
    DOH_08,     ///< Pin 257     --  DOH_08      EXT-LIGHT

    POH_21,     ///< Pin 127     --  DOH_09      EXT-LIGHT  POBH_01 - EXT
    POH_22,     ///< Pin 102     --  DOH_10      EXT-LIGHT  POBH_02 - EXT
    POH_23,     ///< Pin 128     --  DOH_11      EXT-LIGHT  POBH_03 - EXT
    POH_24,     ///< Pin 103     --  DOH_12      EXT-LIGHT  POBH_04 - EXT
    POH_25,     ///< Pin 105     --  DOH_13      EXT-LIGHT  POBH_05 - EXT
    POH_26,     ///< Pin 104     --  DOH_14      EXT-LIGHT  POBH_06 - EXT
    POH_27,     ///< Pin 107     --  DOH_15      EXT-LIGHT  POBH_07 - EXT
    POH_28,     ///< Pin 106     --  DOH_16      EXT-LIGHT  POBH_08 - EXT

    POL_01,     ///< Pin 184     --  DOL_01      EXT-LIGHT  POBL_01 - EXT
    POL_02,     ///< Pin 185     --  DOL_02      EXT-LIGHT  POBL_02 - EXT
    POL_03,     ///< Pin 182     --  DOL_03      EXT-LIGHT  POBL_03 - EXT
    POL_04,     ///< Pin 183     --  DOL_04      EXT-LIGHT  POBL_04 - EXT
    POL_05,     ///< Pin 180     --  DOL_05      EXT-LIGHT  POBL_05 - EXT
    POL_06,     ///< Pin 181     --  DOL_06      EXT-LIGHT  POBL_06 - EXT
    POL_07,     ///< Pin 178     --  POL_01      EXT-LIGHT  POBL_07 - EXT
    POL_08,     ///< Pin 179     --  NC          EXT-LIGHT  POBL_08 - EXT

    AO_01,      ///< Pin 221  EXT  --  AO_01 EXT-LIGHT

    DOMR_01,    ///< main power relay for PXXX outputs ( highside ) ( net V_PO )
    DOMR_02,    ///< main power relay for DXXX outputs ( highside ) ( net V_DO )
    DOMR_03,    ///< main power relay for P_AI_UBAT

    DOPS_5V,    ///< Pin 219 VSS_1 5V external power supply (current????)
    DOPS_8V5    ///< Pin 232 VSS_2 8,5V external power supply

} EosOutName_te;

#define VSS_1 DOPS_5V
#define VSS_2 DOPS_8V5

#define     POH_Last    POH_20      ///< Just a definition; useful within loops ..
#define     PDOH_Last   PDOH_12     ///< Just a definition; useful within loops ...
#define     DOH_Last    DOH_08      ///< Just a definition; useful within loops ...
#define     POBH_Last   POH_28
#define     POBL_Last   POL_08

// needed for the init of outputs ..... ( The number in the gaps will return with an error and also the digital outputs )
#define FIRST_OUTPUT    POH_01
#define LAST_OUTPUT      AO_01

/*
*   Analog inputs
*/

/*! \brief  all names for digital inputs to be used with input-functions  */
typedef enum
{
    CI_01,          ///< Pin 138 Analog Current Input
    CI_02,          ///< Pin 168 Analog Current Input
    CI_03,          ///< Pin 218 Analog Current Input
    CI_04,          ///< Pin 229 Analog Current Input
    CI_05,          ///< Pin 171 Analog Current Input
    CI_06,          ///< Pin 227 Analog Current Input
    CI_07,          ///< Pin 167 Analog Current Input
    CI_08,          ///< Pin 169 Analog Current Input
    CI_09,          ///< Pin 170 Analog Current Input
    CI_10,          ///< Pin 165 Analog Current Input
    CI_11,          ///< Pin 230 Analog Current Input
    CI_12,          ///< Pin 140 Analog Current Input
    CI_13,          ///< Pin 139 Analog Current Input
    CI_14,          ///< Pin 166 Analog Current Input
    CI_15,          ///< Pin 164 Analog Current Input
    CI_16,          ///< Pin 141 Analog Current Input
    CI_17,          ///< Pin 231 Analog Current Input
    CI_18,          ///< Pin 217 Analog Current Input

    AI_01,          ///< Pin 119 Analog Voltage Input No 01
    AI_02,          ///< Pin 120 Analog Voltage Input No 02
    AI_03,          ///< Pin 121 Analog Voltage Input No 03
    AI_04,          ///< Pin 116 Analog Voltage Input No 04
    AI_05,          ///< Pin 117 Analog Voltage Input No 05
    AI_06,          ///< Pin 118 Analog Voltage Input No 06

    AI_UBAT,        ///< Kl30 power supply voltage
    AI_VREF,        ///< internal used power supply
    AI_VREF_1,      ///< VREF can be read from 2 different inputs

    AI_Num          ///< number of analog inputs
} EosAiName_te;

#define AI_VBAT     AI_UBAT

// Defines needed to remap the EosAiName_te to the description table of EOS
#define         NUM_CI_XX_PORTS         18

/*
*   Digital Inputs
*/

/*! \brief  all names for digital inputs to be used with input-functions  */
typedef enum
{
    DI_01,          ///< Pin 250 Digital Input
    DI_02,          ///< Pin 236 Digital Input
    DI_03,          ///< Pin 209 Digital Input
    DI_04,          ///< Pin 147 Digital Input
    DI_05,          ///< Pin 223 Digital Input
    DI_06,          ///< Pin 148 Digital Input
    DI_07,          ///< Pin 159 Digital Input
    DI_08,          ///< Pin 158 Digital Input
    DI_09,          ///< Pin 214 Digital Input
    DI_10,          ///< Pin 157 Digital Input
    DI_11,          ///< Pin 252 Digital Input
    DI_12,          ///< Pin 238 Digital Input
    DI_13,          ///< Pin 222 Digital Input
    DI_14,          ///< Pin 210 Digital Input
    DI_15,          ///< Pin 136 Digital Input
    DI_16,          ///< Pin 137 Digital Input
    DI_17,          ///< Pin 135 Digital Input
    DI_18,          ///< Pin 134 Digital Input
    DI_19,          ///< Pin 211 Digital Input
    DI_20,          ///< Pin 144 Digital Input
    DI_21,          ///< Pin 224 Digital Input
    DI_22,          ///< Pin 143 Digital Input
    DI_23,          ///< Pin 142 Digital Input
    DI_24,          ///< Pin 235 Digital Input
    DI_25,          ///< Pin 247 Digital Input
    DI_26,          ///< Pin 234 Digital Input
    DI_27,          ///< Pin 225 Digital Input
    DI_28,          ///< Pin 212 Digital Input
    DI_29,          ///< Pin 248 Digital Input
    DI_30,          ///< Pin 237 Digital Input
    DI_31,          ///< Pin 239 Digital Input
    DI_32,          ///< Pin 251 Digital Input

    DFI_01,         ///< Pin 112 Digital Frequency Input DFI_01/DFI_03 phase measuring
    DFI_02,         ///< Pin 113 Digital Frequency Input
    DFI_03,         ///< Pin 110 Digital Frequency Input
    DFI_04,         ///< Pin 111 Digital Frequency Input DFI_04/DFI_08 phase measuring
    DFI_05,         ///< Pin 109 Digital Frequency Input
    DFI_06,         ///< Pin 108 Digital Frequency Input DFI_06/DFI_07 phase measuring
    DFI_07,         ///< Pin 133 Digital Frequency Input
    DFI_08,         ///< Pin 132 Digital Frequency Input
    DFI_09,         ///< Pin 213 Digital Frequency Input DFI_09/DFI_10 phase measuring
    DFI_10,         ///< Pin 208 Digital Frequency Input

    DI_KL15         ///< Pin 240 ignition key input (GPIO)
} EosDiName_te;

/*! \brief ECU internal temperature sensors */
typedef enum
{
    PTEMP_01,       ///< Internal temperature sensor 1 mounted on pcb.
    PTEMP_02        ///< Internal temperature sensor 2 mounted on pcb.
} EosTiName_te;

// Defines needed to remap the EosAiName_te to the description table of EOS
#define         NUM_DI_XX_PORTS         32


    // communication pins (EOS numbering)
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
    // KL30_1 (outp)- 245/258 (supply for Cy-Chip, without power supply ECU will hang in core init)
    // KL15         - 240
    // GND          - 122/123/124/202/207/220/233/246/145/146

#endif   // _IOSYMBSRC36_20_31_H
