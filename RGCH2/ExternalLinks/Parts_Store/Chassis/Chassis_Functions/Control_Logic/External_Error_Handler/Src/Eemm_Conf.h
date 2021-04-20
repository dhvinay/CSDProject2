/**
 *  @file       emm_conf.h
 *
 *  @brief      Konfiguration einer EMM Slave ECU und deren Clients.
 *
 *
 *  @section    Historie
 *
 *  2012-12-07 / werner.unsinn@agcocorp.com
 *  - erstellt
 *
 */

#ifndef __EEMM_CONF_H
#define __EEMM_CONF_H

#include "Eemm_Def.h"

#include "Eos.h"


//> Declaration of the configuration data for each of the clients
typedef struct
{
    uint16          addrErrorCounter_u16;       //< Address of the error frequency counter of the client
    uint8           maxErrorCode_u8;            //< Largest usable error number of the client
    uint8           location_u8;                //< Error location (log. GD subscriber number) of the client
} EmmClient_ts;


// Declaration of the configuration data for the EMM slave ECU
typedef struct
{
    uint16          addrStartCounter_u16;       //< Address of the cold start counter of the EMM slave ECU
    uint16          addrErrorStorrage_u16;      //< Address of the fault memory of the EMM slave ECU
    uint8           numErrorStorrageEntries_u8; //< Number of entries of the fault memory of the EMM slave ECU
    uint16          identifier_u16;             //< GD Identifier der EMM Slave ECU
    EmmClient_ts    client_as[EMM_CLIENT_MAX];  //< Configuration data for the clients of the EMM slave ECU
} EmmConfig_ts;

extern const EmmConfig_ts emmConfig_cs;


#endif // __EEMM_CONF_H
