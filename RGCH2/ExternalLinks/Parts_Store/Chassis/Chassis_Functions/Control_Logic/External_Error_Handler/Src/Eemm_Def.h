/**
 *  @file       emm_def.h
 *
 *  @brief      Definition der Clients der EMM Slave ECU.
 *
 *
 *  @section    Historie
 *
 *  2013-03-22 / werner.unsinn@agcocorp.com
 *  - erstellt
 *
 *  2014-04-02 / Mattis Kornelius
 *  - [Misc] minor changes for better MISRA-C compliance
 */


#ifndef __EEMM_DEF_H
#define __EEMM_DEF_H


//> Aufzaehlung der Clients dieses EMM Slaves
enum
{
    EMM_CLIENT_HC,
    EMM_CLIENT_MAX
};


//> Groesste verwendbare Fehlernummer
#define EMM_ERROR_CODE_MAX (255u)


#endif // __EEMM_DEF_H
