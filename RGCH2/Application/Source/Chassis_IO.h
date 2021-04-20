// Chassis_IO.h
#ifndef CHASSIS_IO_H
#define CHASSIS_IO_H

#include <Eos.h>

//I/O mapping defines
//#define LADDER_EXTENTION_PDOH                   DUMMY_PIN //Ladder extention feature removed 
//#define IO_DOH                                  DOH_10    //Connector J1, Pin  2
//#define IO_DOH                                  DOH_12    //Connector J1, Pin  3
//#define IO_DOH                                  DOH_14    //Connector J1, Pin  4
//#define IO_DOH                                  DOH_13    //Connector J1, Pin  5
//#define IO_DOH                                  DOH_16    //Connector J1, Pin  6
//#define IO_DOH                                  DOH_15    //Connector J1, Pin  7
//#define IO_DFI                                  DFI_06    //Connector J1, Pin  8
//#define IO_DFI                                  DFI_05    //Connector J1, Pin  9
//#define IO_DFI                                  DFI_03    //Connector J1, Pin 10
//#define IO_DFI                                  DFI_04    //Connector J1, Pin 11
//#define IO_DFI                                  DFI_01    //Connector J1, Pin 12
//#define IO_DFI                                  DFI_02    //Connector J1, Pin 13
//#define IO_DOH                                  DOH_05    //Connector J1, Pin 14
//#define IO_DOH                                  DOH_01    //Connector J1, Pin 15
//#define IO_AI                                   AI_04     //Connector J1, Pin 16
//#define IO_AI                                   AI_05     //Connector J1, Pin 17
//#define IO_AI                                   AI_06     //Connector J1, Pin 18
//#define IO_AI                                   AI_01     //Connector J1, Pin 19
//#define IO_AI                                   AI_02     //Connector J1, Pin 20
//#define IO_AI                                   AI_03     //Connector J1, Pin 21
  #define HC_EXTEND_FL_POH                        POH_17    //Connector J1, Pin 26
//#define IO_PDOH                                 PDOH_18   //Connector J1, Pin 27
//#define IO_PDOH                                 PDOH_19   //Connector J1, Pin 28
//#define IO_PDOH                                 PDOH_16   //Connector J1, Pin 29
//#define IO_PDOH                                 PDOH_17   //Connector J1, Pin 30
//#define IO_DFI                                  DFI_08    //Connector J1, Pin 32
//#define IO_DFI                                  DFI_07    //Connector J1, Pin 33
//#define IO_DI                                   DI_18     //Connector J1, Pin 34
//#define IO_DI                                   DI_17     //Connector J1, Pin 35
//#define IO_DI                                   DI_15     //Connector J1, Pin 36
//#define IO_DI                                   DI_16     //Connector J1, Pin 37
//#define IO_AI_TEMP                              AI_TEMP_1 //Connector J1, Pin 38
//#define IO_CI                                   CI_13     //Connector J1, Pin 39
//#define IO_CI                                   CI_12     //Connector J1, Pin 40
//#define IO_CI                                   CI_16     //Connector J1, Pin 41
//#define IO_DI                                   DI_23     //Connector J1, Pin 42
//#define IO_DI                                   DI_22     //Connector J1, Pin 43
//#define IO_DI                                   DI_20     //Connector J1, Pin 44
//#define IO_DI                                   DI_04     //Connector J1, Pin 47
//#define IO_DI                                   DI_06     //Connector J1, Pin 48
  #define HC_RETRACT_FL_POH                       POH_09    //Connector J1, Pin 49, NPU
//#define IO_DOL                                  DOL_04    //Connector J1, Pin 50
  #define HC_EXTEND_RL_POH                        POH_05    //Connector J1, Pin 51
  #define HC_RETRACT_RL_POH                       POH_07    //Connector J1, Pin 52
//#define IO_PDOH                                 PDOH_13   //Connector J1, Pin 53
//#define IO_PDOH                                 PDOH_14   //Connector J1, Pin 54
//#define IO_DFI                                  DFI_09    //Connector J1, Pin 55
//#define IO_DFI                                  DFI_10    //Connector J1, Pin 56
//#define IO_DI                                   DI_10     //Connector J1, Pin 57
//#define IO_DI                                   DI_08     //Connector J1, Pin 58
//#define IO_DI                                   DI_07     //Connector J1, Pin 59
//#define CAN_IO                                  CAN_4     //Connector J1, Pin 60
//#define CAN_IO                                  CAN_2     //Connector J1, Pin 62
  #define HC_POSITION_SENSOR_FL_CI                CI_15     //Connector J1, Pin 64
  #define HC_POSITION_SENSOR_RL_CI                CI_10     //Connector J1, Pin 65
  #define HC_POSITION_SENSOR_FR_CI                CI_14     //Connector J1, Pin 66
  #define HC_POSITION_SENSOR_RR_CI                CI_07     //Connector J1, Pin 67
//#define IO_AI_TEMP                              AI_TEMP_2 //Connector J1, Pin 68
//#define IO_AI_TEMP                              AI_TEMP_3 //Connector J1, Pin 69
//#define IO_CI                                   CI_09     //Connector J1, Pin 70
//#define IO_CI                                   CI_05     //Connector J1, Pin 71
//#define IO_AI_TEMP                              AI_TEMP_4 //Connector J1, Pin 72
  #define HC_EXTEND_FR_POH                        POH_10    //Connector J1, Pin 73, NPU
//#define IO_DOL                                  DOL_05    //Connector J1, Pin 74
  #define HC_RETRACT_FR_POH                       POH_06    //Connector J1, Pin 75
//#define IO_PDOH                                 PDOH_15   //Connector J1, Pin 76
  #define HC_EXTEND_RR_POH                        POH_02    //Connector J1, Pin 77
//#define IO_POL                                  POL_01    //Connector J1, Pin 78
//#define IO_DOL                                  DOL_01    //Connector J1, Pin 79
//#define IO_POL                                  POL_06    //Connector J1, Pin 80
//#define IO_DOL                                  DOL_06    //Connector J1, Pin 81
//#define IO_POL                                  POL_04    //Connector J1, Pin 82
//#define IO_POL                                  POL_05    //Connector J1, Pin 83
//#define IO_POL                                  POL_02    //Connector J1, Pin 84
//#define IO_POL                                  POL_03    //Connector J1, Pin 85
  #define HC_RETRACT_RR_POH                       POH_04    //Connector J1, Pin 86
//#define IO_PDOH                                 PDOH_08   //Connector J1, Pin 87
//#define IO_AI                                   AI_12     //Connector J1, Pin 88
//#define IO_PDOH                                 PDOH_04   //Connector J1, Pin 89
//#define IO_PDOH                                 PDOH_03   //Connector J1, Pin 90
//#define IO_DOL                                  DOL_02    //Connector J1, Pin 91
//#define IO_DOL                                  DOL_03    //Connector J1, Pin 92
//#define IO_PDOH                                 PDOH_06   //Connector J1, Pin 93
//#define IO_PDOH                                 PDOH_05   //Connector J1, Pin 94
  #define SENSOR_ENABLE_PDOH                      PDOH_09   //Connector J1, Pin 96 //For LED at Desk
//
//#define IO_DI                                   DI_03     //Connector J2, Pin  9
//#define IO_DI                                   DI_14     //Connector J2, Pin 10
//#define IO_DI                                   DI_19     //Connector J2, Pin 11
//#define IO_DI                                   DI_28     //Connector J2, Pin 12
//#define IO_AI                                   AI_09     //Connector J2, Pin 13
//#define IO_DI                                   DI_09     //Connector J2, Pin 14
  #define CAN_GD                                  CAN_1     //Connector J2, Pin 15
//#define IO_AI                                   AI_08     //Connector J2, Pin 17
//#define IO_CI                                   CI_03     //Connector J2, Pin 18
//#define IO_AO                                   AO_01     //Connector J2, Pin 21
//#define IO_DI                                   DI_13     //Connector J2, Pin 22
//#define IO_DI                                   DI_05     //Connector J2, Pin 23
//#define IO_DI                                   DI_21     //Connector J2, Pin 24
//#define IO_DI                                   DI_27     //Connector J2, Pin 25
//#define IO_AI                                   AI_10     //Connector J2, Pin 26
//#define IO_CI                                   CI_06     //Connector J2, Pin 27
//#define IO_AI                                   AI_11     //Connector J2, Pin 28
//#define IO_CI                                   CI_04     //Connector J2, Pin 29
//#define IO_CI                                   CI_11     //Connector J2, Pin 30
//#define IO_AI                                   AI_07     //Connector J2, Pin 31
//#define IO_DI                                   DI_26     //Connector J2, Pin 34
//#define IO_DI                                   DI_24     //Connector J2, Pin 35
//#define IO_DI                                   DI_02     //Connector J2, Pin 36
//#define IO_DI                                   DI_30     //Connector J2, Pin 37
//#define IO_DI                                   DI_12     //Connector J2, Pin 38
//#define IO_DI                                   DI_31     //Connector J2, Pin 39
//#define IO_KeySwitch                            DI_KL15   //Connector J2, Pin 40
//#define IO_DOH                                  DOH_03    //Connector J2, Pin 41
//#define IO_DOH                                  DOH_04    //Connector J2, Pin 42
//#define IO_DOH                                  DOH_02    //Connector J2, Pin 43
//#define IO_DOH                                  DOH_07    //Connector J2, Pin 44
//#define IO_DI                                   DI_25     //Connector J2, Pin 47
//#define IO_DI                                   DI_29     //Connector J2, Pin 48
//#define IO_PDOH                                 PDOH_10   //Connector J2, Pin 49
//#define IO_DI                                   DI_01     //Connector J2, Pin 50
//#define IO_DI                                   DI_32     //Connector J2, Pin 51
//#define IO_DI                                   DI_11     //Connector J2, Pin 52
//#define CAN_IO                                  CAN_2     //Connector J2, Pin 53
//#define IO_LIN                                  LIN_1     //Connector J2, Pin 55
//#define IO_PDOH                                 PDOH_20   //Connector J2, Pin 56
//#define IO_PDOH                                 PDOH_21   //Connector J2, Pin 57


#endif // CHASSIS_IO_H
