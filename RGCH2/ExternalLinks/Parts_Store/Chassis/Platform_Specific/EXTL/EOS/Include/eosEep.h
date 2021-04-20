/**
 * \file eosEep.h
 *
 * \brief Eep related functions and types
 *
 * Support functions for non volatile memory like SPI eeprom,
 * eep flash emulations or similar systems. 
 *
 * Copyright 2015 (c) AGCO GmbH, Marktoberdorf
 *
 * \par History
 *
 * 2015-02-19 / Christian.Pischulti@AGCOcorp.com
 * - [PB-8563] Moved eep functions from eos.h (2014-12-05) to own header file.
 */
#ifndef EOSEEP_H
#define EOSEEP_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup _eeprom Eeprom
 * \{
 */

/**
 * \brief error codes returned by eep task
 */
typedef enum 
{
    EOSEEP_NO_ERROR = 0,        ///< \brief no error
    EOSEEP_UNKNOWN_REQ,         ///< \brief request type is unknown
    EOSEEP_QUEUE_FULL,          ///< \brief EEPROM buffer queue is full, retry later
    EOSEEP_TSK_NOT_READY,       ///< \brief task is not ready to accept commands
    EOSEEP_INTERNAL_ERROR,      ///< \brief task has encountered an internal error and acknowledged request with error, retry
    EOSEEP_TIME_OUT,            ///< \brief SPI timeout, retry later
    EOSEEP_WRONG_PARAMETER      ///< \brief parameters are wrong, maybe an address larger than the available NVRAM was requested
} EosEepErrorCodes_te;

/**
 * \brief state of eeprom module
 */
typedef enum EosEepStates_te
{
    EOSEEP_UNCACHED,            ///< \brief EEPROM is not cached
    EOSEEP_CACHED,              ///< \brief EEPROM content is mirrored in RAM
    EOSEEP_LOCKED,              ///< \brief no more writes are accepted, only reads will be served
    EOSEEP_SYNCED               ///< \brief all write operations are finished
} EosEepStates_te;

sint32  EosEepromRead_s32( uint16 EeAdr_u16, uint8 *DestData_pu8, uint16 Size_u16 );
sint32  EosEepromWrite_s32( uint16 EeAdr_u16, uint8 const *SrcData_pu8, uint16 Size_u16);
sint32  EosEepromFill_s32( uint16 EeAdr_u16, uint8 fillPattern_u8, uint16 Size_u16 );
 
sint32  EosEepromLock_s32 ( void );                     // Lock further writes to eep
sint32  EosEepromGetState_s32 ( uint16 * state_pu16 );  // returns current eep state (EosEepStates_te)
sint32  EosEepromSynced_s32 ( bool * synced_pb );       // TRUE: fifo empty (everything written) FALSE: still something to write.
/**
  * \}
  */

#ifdef __cplusplus
} // extern "C"
#endif

#endif  // EOSEEP_H
