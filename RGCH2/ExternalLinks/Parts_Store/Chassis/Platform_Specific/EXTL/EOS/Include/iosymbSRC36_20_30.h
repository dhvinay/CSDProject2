/**
 *  \file       iosymbSRC36_20_30.h
 *
 *  \brief      Symbol definition for EXT I/Os
 *
 *  \section    history
 *
 *  2008-02-26 / Christian.Pischulti@xfendt.de
 *  - draft
 *
 *  2008-04-07 / Christian Pischulti
 *  - Removed semicolon after DUMMY_PIN define.
 *
 *  2009-01-06 / Christian Pischulti
 *  - Enum element AO_01 is set fixed to 500 to fit to EOS_IO_ENUMDISTANCE.
 *
 *  2010-07-09 / Christian.Pischulti@xfendt.de
 *  - Added pin numbers for EXT to comment line.
 *  - Changed pin number for AO_01 from 215 to 221 in comment.
 *
 *  2010-09-16 / Christian.Pischulti@fendt.de
 *  - Removed fixed enum values for ios. Be aware that sizeof
 *    output enum type is reduced from two bytes to one byte.
 *
 *  2011-12-02 / florian.schwarz@euro-engineering.com
 *  - added AI_UBAT and AI_VREF as analog voltage inputs
 *  - added temperature input PTEMP_01
 *
 *  2012-06-21 / florian.schwarz@euro-engineering.com
 *   - renamed AI_Last to AI_Num
 *
 *  2012-09-06 / florian.schwarz@euro-engineering.com
 *  - stylistic changes for better MISRA-C compliance
 *
 *  2015-01-27 / Christian.Pischulti@AGCOcorp.com
 *  - [PB-8563] Renamed file from iosymbEXT.h to iosymbSRC36_20_30.h.
 */

#ifndef IOSYMBSRC36_20_30_H
#define IOSYMBSRC36_20_30_H

/*
*       Common
*/
// Save define to be used if a symbol for an I/O doesn't exits. With this define the Eos functions will return
// with an error.
#define DUMMY_PIN   30000           // Try to avoid using this define.

// Needed to remap the
#define     EOS_IO_ENUMDISTANCE      100

/*
*       Outputs
*/

/*! \brief  all names for outputs to be used with output-functions  */
typedef enum
{
    POH_01,     ///< Pin 153 PWM-Output    --  PDOH_13     EXT-LIGHT
    POH_02,     ///< Pin 177 PWM-Output    --  POH_2       EXT_LIGHT
    POH_03,     ///< Pin 154 PWM-Output    --  PDOH_14     EXT-LIGHT
    POH_04,     ///< Pin 186 PWM-Output    --  POH_04      EXT-LIGHT
    POH_05,     ///< Pin 151 PWM-Output    --  POH_05      EXT-LIGHT
    POH_06,     ///< Pin 175 PWM-Output    --  POH_06      EXT-LIGHT
    POH_07,     ///< Pin 152 PWM-Output    --  POH_07      EXT-LIGHT
    POH_08,     ///< Pin 176 PWM-Output    --  PDOH_15     EXT-LIGHT
    POH_09,     ///< Pin 149 PWM-Output    --  POH_09      EXT-LIGHT
    POH_10,     ///< Pin 173 PWM-Output    --  POH_10      EXT-LIGHT
    POH_11,     ///< Pin 150 PWM-Output    --  NC          EXT-LIGHT
    POH_12,     ///< Pin 174 PWM-Output    --  NC          EXT-LIGHT
    POH_13,     ///< Pin 130 PWM-Output    --  PDOH_17     EXT_LIGHT
    POH_14,     ///< Pin 131 PWM-Output    --  NC          EXT-LIGHT
    POH_15,     ///< Pin 156 PWM-Output    --  NC          EXT-LIGHT
    POH_16,     ///< Pin 155 PWM-Output    --  NC          EXT-LIGHT
    POH_17,     ///< Pin 126 PWM-Output    --  POH_17      EXT-LIGHT
    POH_18,     ///< Pin 101 PWM-Output    --  NC          EXT-LIGHT
    POH_19,     ///< Pin 125 PWM-Output    --  NC          EXT-LIGHT
    POH_20,     ///< Pin 129 PWM-Output    --  PDOH_16     EXT-LIGHT

    PDOH_01,    ///< Pin 192 PWM-Output    --  NC          EXT-LIGHT
    PDOH_02,    ///< Pin 191 PWM-Output    --  NC          EXT-LIGHT
    PDOH_03,    ///< Pin 190 PWM-Output    --  PDOH_03     EXT-LIGHT
    PDOH_04,    ///< Pin 189 PWM-Output    --  PDOH_04     EXT-LIGHT
    PDOH_05,    ///< Pin 194 PWM-Output    --  PDOH_05     EXT-LIGHT
    PDOH_06,    ///< Pin 193 PWM-Output    --  PDOH_06     EXT-LIGHT
    PDOH_07,    ///< Pin 188 PWM-Output    --  NC          EXT-LIGHT
    PDOH_08,    ///< Pin 187 PWM-Output    --  PDOH_08     EXT-LIGHT
    PDOH_09,    ///< Pin 196 PWM-Output    --  PDOH_09     EXT-LIGHT
    PDOH_10,    ///< Pin 249 PWM-Output    --  PDOH_10     EXT-LIGHT
    PDOH_11,    ///< Pin 172 PWM-Output    --  NC          EXT-LIGHT
    PDOH_12,    ///< Pin 195 PWM-Output    --  NC          EXT-LIGHT

    DOH_01,     ///< Pin 115 Dig-Output    --  DOH_01      EXT-LIGHT
    DOH_02,     ///< Pin 243 Dig-Output    --  DOH_02      EXT-LIGHT
    DOH_03,     ///< Pin 241 Dig-Output    --  DOH_03      EXT-LIGHT
    DOH_04,     ///< Pin 242 Dig-Output    --  DOH_04      EXT-LIGHT
    DOH_05,     ///< Pin 114 Dig-Output    --  DOH_05      EXT-LIGHT
    DOH_06,     ///< Pin 256 Dig-Output    --  DOH_06      EXT-LIGHT
    DOH_07,     ///< Pin 244 Dig-Output    --  DOH_07      EXT-LIGHT
    DOH_08,     ///< Pin 257 Dig-Output    --  DOH_08      EXT-LIGHT

    POBH_01,    ///< Pin 127 PWM-Output    --  DOH_09      EXT-LIGHT
    POBH_02,    ///< Pin 102 PWM-Output    --  DOH_10      EXT-LIGHT
    POBH_03,    ///< Pin 128 PWM-Output    --  DOH_11      EXT-LIGHT
    POBH_04,    ///< Pin 103 PWM-Output    --  DOH_12      EXT-LIGHT
    POBH_05,    ///< Pin 105 PWM-Output    --  DOH_13      EXT-LIGHT
    POBH_06,    ///< Pin 104 PWM-Output    --  DOH_14      EXT-LIGHT
    POBH_07,    ///< Pin 107 PWM-Output    --  DOH_15      EXT-LIGHT
    POBH_08,    ///< Pin 106 PWM-Output    --  DOH_16      EXT-LIGHT

    POBL_01,    ///< Pin 184 PWM-Output    --  DOL_01      EXT-LIGHT
    POBL_02,    ///< Pin 185 PWM-Output    --  DOL_02      EXT-LIGHT
    POBL_03,    ///< Pin 182 PWM-Output    --  DOL_03      EXT-LIGHT
    POBL_04,    ///< Pin 183 PWM-Output    --  DOL_04      EXT-LIGHT
    POBL_05,    ///< Pin 180 PWM-Output    --  DOL_05      EXT-LIGHT
    POBL_06,    ///< Pin 181 PWM-Output    --  DOL_06      EXT-LIGHT
    POBL_07,    ///< Pin 178 PWM-Output    --  POL_01      EXT-LIGHT
    POBL_08,    ///< Pin 179 PWM-Output    --  NC          EXT-LIGHT

    AO_01,      ///< Pin 221  EXT  --  AO_01 EXT-LIGHT

    DOMR_01,    ///< main power relay for PXXX outputs ( highside ) ( net V_PO )
    DOMR_02,    ///< main power relay for DXXX outputs ( highside ) ( net V_DO )

    DOPS_5V,    ///< Pin 219 VSS_1 5V external power supply
    DOPS_8V5    ///< Pin 232 VSS_2 8,5V external power supply

} EosOutName_te;

#define VSS_1 DOPS_5V
#define VSS_2 DOPS_8V5

#define     POH_Last    POH_20      ///< Just a definition; useful within loops ..
#define     PDOH_Last   PDOH_12     ///< Just a definition; useful within loops ...
#define     DOH_Last    DOH_08      ///< Just a definition; useful within loops ...
#define     POBH_Last   POBH_08
#define     POBL_Last   POBL_08

// needed for the init of outputs ..... ( The number in the gaps will return with an error and also the digital outputs )
#define FIRST_OUTPUT    POH_01
#define LAST_OUTPUT     AO_01


// If application code written for use on EXT/EXT-LIGHT uses I/O symbols from EXT-Light the symbols
// will be set to DUMMY_PIN.
#define         PDOH_13          DUMMY_PIN
#define         PDOH_14          DUMMY_PIN
#define         PDOH_15          DUMMY_PIN
#define         PDOH_17          DUMMY_PIN
#define         PDOH_16          DUMMY_PIN

#define         DOH_09           DUMMY_PIN
#define         DOH_10           DUMMY_PIN
#define         DOH_11           DUMMY_PIN
#define         DOH_12           DUMMY_PIN
#define         DOH_13           DUMMY_PIN
#define         DOH_14           DUMMY_PIN
#define         DOH_15           DUMMY_PIN
#define         DOH_16           DUMMY_PIN

#define         DOL_01           DUMMY_PIN
#define         DOL_02           DUMMY_PIN
#define         DOL_03           DUMMY_PIN
#define         DOL_04           DUMMY_PIN
#define         DOL_05           DUMMY_PIN
#define         DOL_06           DUMMY_PIN
#define         POL_01           DUMMY_PIN

/*
*   Analog inputs
*/

/*! \brief  all names for digital inputs to be used with input-functions  */
typedef enum
{
    CI_01,          ///< Pin 138 Analog Current Input Notice: on ExtLight the external components aren't loaded for this pin but it can be routed to CI_14. If you read it you will get the value for CI_14.
    CI_02,          ///< Pin 168 Analog Current Input Notice: on ExtLight the external components aren't loaded for this pin but it can be routed to CI_15. If you read it you will get the value for CI_15.
    CI_03,          ///< Pin 218 Analog Current Input
    CI_04,          ///< Pin 229 Analog Current Input
    CI_05,          ///< Pin 171 Analog Current Input
    CI_06,          ///< Pin 227 Analog Current Input
    CI_07,          ///< Pin 167 Analog Current Input
    CI_08,          ///< Pin 169 Analog Current Input Notice: on ExtLight the external components aren't loaded for this pin but it can be routed to CI_13. If you read it you will get the value for CI_13.
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

    AI_Num          ///< number of analog inputs
}      EosAiName_te ;

#define AI_VBAT     AI_UBAT

// If application code written for use on EXT/EXT-LIGHT uses I/O symbols from EXT-Light the symbols
// will be set to DUMMY_PIN.
#define         AI_07       DUMMY_PIN
#define         AI_08       DUMMY_PIN

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

    DFI_01,         ///< Pin 112 Digital Frequency Input
    DFI_02,         ///< Pin 113 Digital Frequency Input
    DFI_03,         ///< Pin 110 Digital Frequency Input
    DFI_04,         ///< Pin 111 Digital Frequency Input
    DFI_05,         ///< Pin 109 Digital Frequency Input
    DFI_06,         ///< Pin 108 Digital Frequency Input
    DFI_07,         ///< Pin 133 Digital Frequency Input
    DFI_08,         ///< Pin 132 Digital Frequency Input
    DFI_09,         ///< Pin 213 Digital Frequency Input
    DFI_10,         ///< Pin 208 Digital Frequency Input
} EosDiName_te;

/*! \brief ECU internal temperature sensors */
typedef enum
{
    PTEMP_01        ///< Internal temperature sensor mounted on pcb.
} EosTiName_te;

// Defines needed to remap the EosAiName_te to the description table of EOS
#define         NUM_DI_XX_PORTS         32

#endif   // IOSYMBSRC36_20_30_H
