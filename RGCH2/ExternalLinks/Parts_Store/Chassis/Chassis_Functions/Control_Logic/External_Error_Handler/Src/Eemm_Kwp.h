/**
 *  @file       emm_kwp.h
 *
 *  @brief      KWP Zugriff auf den Fehlerspeicher einer EMM Slave ECU.
 *
 *
 *  @section    Historie
 *
 *  2012-12-07 / werner.unsinn@agcocorp.com
 *  - erstellt
 *
 */

#ifndef __EEMM_KWP_H
#define __EEMM_KWP_H

#include "kwp.h"
#include "Eos.h"

void initEmmKwpRequest(PxMbx_t mbxId_ps);
boolean serveEmmKwpRequest_b(KwpRequest_ts* request_ps);


#endif // __EEMM_KWP_H
