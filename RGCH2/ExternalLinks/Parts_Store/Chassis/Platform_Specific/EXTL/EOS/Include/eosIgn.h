/**
 *  \file eosIgn.h
 *
 *  \brief Ignition handler functions.
 *
 *  Support functions for ignition handler.
 *
 *  Copyright 2015 (c) AGCO GmbH, Marktoberdorf
 *
 *  \par History
 *
 *  2015-03-18 / Christian.Pischulti@AGCOcorp.com
 *  - [PB-8563] Moved ign functions from eos.h (2014-12-05) to own header file.
 */
#ifndef EOSIGN_H
#define EOSIGN_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup _ignition Ignition key
 * \{
 */
/* ignition mechanism / D-Plus */
typedef struct EosIgReq_ts *EosIgReq_pts; ///< \brief special type for pointer to administrate ignition mechanism

sint32  EosIgReqInstall_s32( EosIgReq_pts* req_pps, PxEvents_t evOff_u32, PxEvents_t evRS_u32);
sint32  EosIgReqRemove_s32 ( EosIgReq_pts* req_pps);
void    EosIgBurryMe       ( EosIgReq_pts* req_pps);
boolean EosIgTest_b        ( EosIgReq_pts  req_ps);
boolean EosIgStateOff_b( void );

// New functions for shutdown
sint32  eosIgReqInstallSd_s32( EosIgReq_pts* req_pps, PxEvents_t evOff_u32,
                               PxEvents_t evRS_u32, PxEvents_t evShutdown_u32);
sint32  eosIgLockShutdown_s32( EosIgReq_pts const *IgReq_cpps, boolean sdLock_b );
boolean eosIgCheckShutdown_b( void );
sint32  eosIgReqShutdown_s32( void );

void    ignStart( void );
boolean EosPwrEnDisableKl15AutoShutdown_b(boolean stsAutoShutdown_b);   // Enable or Disable the automatic shutdown by Kl.15
/**
 * \}
 */

#ifdef __cplusplus
} // extern "C"
#endif

#endif  // EOSIGN_H
