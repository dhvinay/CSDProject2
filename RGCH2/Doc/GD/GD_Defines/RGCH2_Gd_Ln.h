/*
 *  @Copyright: AGCO Corporation
 *
 *  @Machine Variant: RGCH2
 *
 *  This as an AutoGenerated file from: GD_Routing_RGCH2.xlsm
 *
 *  Do NOT modify this source file
 */

#ifndef __GD_LN_H 
    #define __GD_LN_H

    #define GD_ID( LN , index ) ( LN * 512 + index )
    #define PN( bus , node ) ( bus * 16 + node) //0x[bus][node]

    //Define Logical Node Numbers  
    enum
    {// Logical Node Name                LN     PN  Description
        GD_LN_DASH                     = 0 , //  0   Dash
        GD_LN_ES                       = 1 , //  5   Engine Speed
        GD_LN_NT01                     = 2 , //  2   Console
        GD_LN_MFA                      = 3 , //  3   Multifunctional Armrest
        GD_LN_DRIVE                    = 4 , //  5   Drive Control Module
        GD_LN_TI                       = 11, //  5   TeachIn Master
        GD_LN_DIAGNOSE                 = 12, //  12  Diagnostics
        GD_LN_TELEM                    = 13, //  13  VarioDoc
        GD_LN_ZE                       = 15, //  15  Central Electric
        GD_LN_LCP                      = 17, //  7   Lighting Control Panel
        GD_LN_INFO                     = 20, //  5   Machine Information Module
        GD_LN_SCT                      = 24, //  5   Electo-Hydraulic Steering Module
        GD_LN_WBZ                      = 25, //  5   WBZ Bridge Module
        GD_LN_SBL                      = 26, //  5   System Brightness
        GD_LN_TA                       = 27, //  5   Track Adjust Module
        GD_LN_EMM                      = 31, //  5   Error Managment Module
        GD_LN_CEAG                     = 32, //  13  VarioGuide Light
        GD_LN_PICTO                    = 33, //  5   Pictogrom Interface Module
        GD_LN_EFC                      = 51, //  5   Engine Fan Control
        GD_LN_HC                       = 54, //  6   High Clearance
        GD_LN_4WS                      = 55, //  5   4 Wheel Steer Module
        GD_LN_ACM                      = 63, //  1   AGCO Connectivity Module

        GD_LN_MAX                      = 64
    };


    //Define Physical Node Numbers  
    enum
    {// Physical Node Name                   Bus   PN         Description
        GD_PN_DASH                     = PN( 1   , 0  ), //  Dash
        GD_PN_ACM                      = PN( 1   , 1  ), //  AGCO Connectivity Module
        GD_PN_NT01                     = PN( 1   , 2  ), //  NT01
        GD_PN_MFA                      = PN( 1   , 3  ), //  MFA
        GD_PN_CHS2                     = PN( 1   , 4  ), //  
        GD_PN_CHS                      = PN( 1   , 5  ), //  Chassis
        GD_PN_LCP                      = PN( 1   , 7  ), //  Light Control Panel
        GD_PN_DIAGNOSE                 = PN( 1   , 12 ), //  Diagnostics
        GD_PN_VD03                     = PN( 1   , 13 ), //  VarioDoc
        GD_PN_ZE                       = PN( 1   , 15 ), //  Central Electric

        GD_PN_MAX                      = 0xFF
};

#endif //__GD_LN_H
