/**
 *  @file       emm_conf.c
 *
 *  @brief      Konfiguration einer EMM Slave ECU und deren Clients.
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


#include "Eemm_Conf.h"

#include "Project.h"


// Definition der Konfigurationsdaten fuer die EMM Slave ECU und deren Clients
const EmmConfig_ts emmConfig_cs =
{
    /* addrStartCounter_u16         = */ EEP_ADDR_KALTSTART,
    /* addrErrorStorrage_u16        = */ EEPR_ADR_ERROR_STORAGE,
    /* numErrorStorrageEntries_u8   = */ (59u),
    /* identifier_u16               = */ EEMM_ECU_ID,

    {
        // HC:
        {
            /* addrErrorCounter_u16 = */ EEPR_ADR_ERROR_COUNTER_START,
            /* maxErrorCode_u8      = */ EMM_ERROR_CODE_MAX,
            /* location_u8          = */ GD_LN_HC
        },
       //// MRC:
       //{
       //    /* addrErrorCounter_u16 = */ EEP_ADDR_ERROR_COUNTER_MRC,
       //    /* maxErrorCode_u8      = */ (255u),
       //    /* location_u8          = */ GD_TN_HVAC
       //}
    }
};
