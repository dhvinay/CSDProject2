/**
 *  @file       emm_gd.h
 *
 *  @brief      Uebergabe der GD Nachrichten einer EMM Client Task an die EMM Slave Task.
 *
 *
 *  @section    Historie
 *
 *  2012-12-07 / werner.unsinn@agcocorp.com
 *  - erstellt
 *
 */

#ifndef __EEMM_GD_H
#define __EEMM_GD_H


void signalEmmGdHandshake(uint8 client_u8, GdData_ts* data_ps);
void signalEmmGdWriteError(uint8 client_u8);
void signalEmmGdQuittance(uint8 client_u8, GdData_ts* data_ps);


#endif // __EEMM_GD_H
