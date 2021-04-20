/**
 *  \file       iosymbSRC4_5.h
 *
 *  \brief      Symbol definition for SRC4_5 IOs
 *
 *  Copyright 2012 (c) AGCO/Fendt GmbH & Co
 *
 *  This file contains the enums used to access I/O for the ECU SRC4/5
 *
 *  \section    History
 *
 *  2013-07-02 / florian.schwarz@euro-engineering.com
 *  - created 
 *
 *  2015-07-02 / Christian.Pischulti@AGCOcorp.com
 *  - [PB-8563] Fixed comments for IOs (measuring range/pullup values).
 *
 *  2015-09-17 / Christian.Pischulti@AGCOcorp.com
 *  - [Misc] Improved IO description.
 *
 */

#ifndef _IOSYMBSRC4_5_H
#define  _IOSYMBSRC4_5_H

    /// \brief names of all digital and PWM outputs
    typedef enum
    {
        POL_01,                     ///< Pin 237 3,5A meas: 6A
        POL_02,                     ///< Pin 225 3,5A meas: 6A
        POL_03,                     ///< Pin 214 2,3A meas: 6A
        POL_04,                     ///< Pin 213 2,3A meas: 6A

        DOH_01,                     ///< Pin 255 3,2A meas: 5,2
        DOH_02,                     ///< Pin 256 1,3A meas: 5,2
        DOH_03,                     ///< Pin 253 1,3A meas: 5,2
        DOH_04,                     ///< Pin 254 1,3A meas: 5,2
        DOH_05,                     ///< Pin 201 1,3A meas: 5,2

        DOL_01,                     ///< Pin 247 20mA, 0-32(33)V voltage feedback
        DOL_02,                     ///< Pin 246 20mA, 0-32(33)V voltage feedback
        DOL_03,                     ///< Pin 226 20mA, 0-32(33)V voltage feedback
        DOL_04,                     ///< Pin 229 20mA, 0-32(33)V voltage feedback

        AO_01,                      ///< Pin 240 analog voltage output 0-5(5.8)V, 100Hz-2kHZ, DC

        DOMR_01,                    ///< Main relay (WDA_TEST in schematics)

        DOPS_5V_1,                  ///< Pin 243 LDO 5V 150mA (schematics VSS_1)
        DOPS_5V_2,                  ///< Pin 242 LDO 5V 150mA (schematics VSS_2)
        DOPS_5V_3,                  ///< Pin 202 LDO 5V 150mA (schematics VSS_3)
        DOPS_8V5                    ///< Pin 241 SMPS 8.5V (schematics VSS_4)
    } EosOutName_te;

    /// \brief names of all analog inputs
    typedef enum
    {
        // analog current inputs
        CI_01,                      ///< Pin 245 current 4-20(22)mA (schematics AI_01, shunt 200 Ohm is stuffed).
        CI_02,                      ///< Pin 238 current 4-20(22)mA (schematics AI_02, shunt 200 Ohm is stuffed).
        CI_03,                      ///< Pin 248 current 4-20(22)mA (schematics AI_03, shunt 200 Ohm is stuffed).
        CI_04,                      ///< Pin 235 current 4-20(22)mA (schematics AI_04, shunt 200 Ohm is stuffed).

        // analog voltage input
        AI_05,                      ///< Pin 236 voltage 0-5(5.89)V
        AI_06,                      ///< Pin 244 voltage 0-5(5.89)V
        AI_07,                      ///< Pin 239 voltage 0-5(5.89)V
        AI_08,                      ///< Pin 232 voltage 0-5(5.89)V
        AI_09,                      ///< Pin 230 voltage 0-5(5.89)V
        AI_10,                      ///< Pin 233 voltage 0-5(5.89)V
        AI_11,                      ///< Pin 231 voltage 0-5(5.89)V
        AI_12,                      ///< Pin 227 voltage 0-5(5.89)V
        AI_13,                      ///< Pin 218 voltage 0-5(5.89)V 1k pullup to 5.0V
        AI_14,                      ///< Pin 206 voltage 0-5(5.89)V 1k pullup to 5.0V
        AI_15,                      ///< Pin 217 voltage 0-15(15.75)V
        AI_16,                      ///< Pin 222 voltage 0-15(15.75)V
        AI_17,                      ///< Pin 215 voltage 0-15(15.75)V
        AI_18,                      ///< Pin 221 voltage 0-15(15.75)V
        AI_19,                      ///< Pin 216 voltage 0-5(5.89)V 1k pullup to 5.0V

        AI_VOUT,                    ///< powersupply voltage for highside switches
        AI_UBAT,                    ///< KL30 before main switch/relay
        AI_UBAT_MR,                 ///< KL30 after internal main switch/relay
        AI_VREF,                    ///< internal used power supply

        AI_Num                      ///< number of analog inputs
    } EosAiName_te;

    #define AI_VBAT     AI_UBAT

    /// names of all digital inputs
    typedef enum
    {
        DFI_01,                     ///< Pin 224 digital frequency input, 0-15V
        DFI_02,                     ///< Pin 228 digital frequency input, 0-15V
        DFI_03,                     ///< Pin 219 digital frequency input DSM
        DFI_04,                     ///< Pin 223 digital frequency input DSM
        DFI_05,                     ///< Pin 234 digital frequency input, no diag

        DI_HW_INH,                  ///< Pin 220 hardware inhibit input (Low: disabled; High (Ubat): operational)
        DI_EMCY,                    ///< Pin 205 Emergency input (thresholds 2.49/4.00V) 100k Pullup

        DI_ERR_V_TEST,              ///< internal signal (non application use)
        DI_KL15,                    ///< Pin 207 ignition
        DI_V_2V54                   ///< internal signal (non application use)
    } EosDiName_te;

    /// names of all temperature inputs
    typedef enum
    {
        PTEMP_01,
        TI_MAX
    } EosTiName_te;

    // communication pins
    // CAN1_H       - 212
    // CAN1_L       - 211
    // CAN2_H       - 209
    // CAN2_L       - 210
    // LIN_1        - 208

    // power supply
    // KL30         - 249/250
    // KL15         - 207
    // GND          - 203/204/252/251



#endif   // _IOSYMBSRC4_5_H
