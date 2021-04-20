/**
 * \file eosWd.h
 *
 * \brief Watchdog related functions and types
 *
 * Support functions for watchdogs
 *
 * Copyright 2015 (c) AGCO GmbH, Marktoberdorf
 *
 * \par History
 *
 * 2015-03-18 / Christian.Pischulti@AGCOcorp.com
 * - [PB-8563] Moved watchdog functions from eos.h (2014-12-05) to own header file.
 */
#ifndef EOSWD_H
#define EOSWD_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup _watchdog Watchdog
 * \{
 */
/**
 * \brief error codes returned by watchdog functions
 */
enum WdErrorCodes_e
{
    WdErrCapacityExeeded    =  0,   ///< \brief The internal capacity of the watchdog task has been reached.
    WdErrWrongAliveId       =  1    ///< \brief The Alive Id doesn't fit to given task id or the alive id is out of range */
} ;

/*! runtime functions for watchdog */
sint32  EosWdConnect_s32( uint32 * wdAliveId_pu32);            /**< Register the task. The alive id is filled in by the watchdog task. Every
                                                                     call to disconnect or alive has to be done with the id value. */
sint32  EosWdDisconnect_s32( uint32 const *wdAliveId_pu32 );   /**< Unregister the task. The Alive id used as double check before the task
                                                                     is removed from the internal list. */
sint32  EosWdAlive_s32( uint32 wdAliveId_u32 );                /**< Send alive signal to watchdog task. The alive id is used for a double check
                                                         against task id. */
/**
 * \}
 */

/**
  * \defgroup _mngmt_cpuwd CPU Watchdog Management
  * \{
  */
sint32  EosCpuWatchdogEnable( void );

/* Sends a can message with the first eight ASCII letters of task name which wasn't able to
   send alive message right in time. The task name will only be valid if project was built
   with the pxdbg or pxmprod pxros library.
*/
sint32  eosCpuWatchdogDbgEnable_s32( EosCan_te canNode_e, uint16 canId_u16 );
/**
  * \}
  */

/**
  * \defgroup _mngmt_extwd External Watchdog Management
  * \{
  */
    sint32  EosExtWDGetErrLevel(uint32  * extWdErrLevel_pu32);
    boolean EosEnDisableExtWdReset_b(boolean enableWdReset_b);
    boolean EosGetExtWdResetStatus_b(boolean * isEnabled_pb);
/**
  * \}
  */

#ifdef __cplusplus
} // extern "C"
#endif

#endif  // EOSWD_H
