/**
 *  @file       gdblk.h
 *
 *  @brief      Header file for generic driver block transfer extension.
 *
 *              Copyright 2014 (c) AGCO GmbH Marktoberdorf
 *
 *  @section     history
 *
 *  2011-01-14 /  Christian.Pischulti@xfendt.de
 *  - created
 *
 *  2014-01-28 / mattis.kornelius.euroeng@agcocorp.com
 *  - [PB-7043] modified to fit GD-Lib V0.14
 */
#ifndef _GDBLK_H
    #define _GDBLK_H

///! error codes for data read write functions
typedef enum
{
    GD_API_NO_ERROR = 0,
    GD_API_READONLYINDEX,   // Write request to a read only index field.
    GD_API_WRONGSIZE,       // The requested size of data field was rejected due to size mismatch.
    GD_API_MALLOCFAIL,      // Not enough memory free to store data of request. Can also mean depletion of Pxros objects.
    GD_API_INDEXLOCKED,     // another one has requested this index. Wait until this request is done.
    GD_API_NOHANDLESLEFT,   // gd has no more internal handling objects left.
    GD_API_ABORTED,         // Transfer was aborted.
    GD_API_TNNOTALIVE,      // The TN of the requested GD index is not alive.
    GD_API_PENDINGWRITE,    // A write transfer is pending.
    GD_API_PENDINGREAD,     // A read is pending.
    GD_API_TIMEOUT,         // Request has timed out. Other side isn't responding.
    GD_API_GDNOINIT,        // GD task can't be reached by mbx.
} GdBlkTrfApiErrCode_te;


/// Structure for one gd block index. Data storage has to be allocated by application.
typedef struct
{
    uint16                  gdIndex_u16;    ///< gd index number
    uint16                  dataSize_u16;   ///< size of block data in bytes.
    uint8 *                 data_pu8;       ///< pointer to data
    GdBlkTrfApiErrCode_te   status_u8;      ///< status of current data
} GdBlkIndex_ts;

/**
 *  @brief  gdBlkInitTask_s32 - init function for gd with blktransfer
 *
 *  @param  init_ps      - pointer to configuration data struct
 *  @param  *memstart_pe - pointer to the startadress of memory block
 *  @param  sizeInBytes_u32 - the size of the memory block in bytes
 *
 *  @return error != 0 ; success == 0
 */
sint32 gdBlkInitTask_s32( GdInit_ts *init_ps, uint32 *memStart_pa, uint32 sizeInBytes_u32);

/**
 *  @brief gdBlkInit_s32 - Initialize the GD for a single participant with blocktransfer.
 *
 *  @param tn_u8        Own participant number
 *  @param response_mbx Mailbox to receive requests from other GD participants
 *  @param request_mbx  Mailbox to receive answers of previous requests
 *  @param blktrans     Mailbox to receive message of gd-blocktransfer
 *
 *  @return             0 if initialization was successful transmitted
 */
sint32 gdBlkInit_s32(uint8 tn_u8, PxMbx_t response_mbx, PxMbx_t request_mbx, PxMbx_t blocktrans_mbx);

/**
 *  @brief request write of a data block with handshaking
 *
 *  @param myLogNodeNum_u8      own logical node number
 *  @param gdBlkIdx_ps          pointer to gd block index struct
 *
 *  @return error != 0 ; success == 0
 */
sint16 gdBlkWrite_s16(  uint8           myLogNodeNum_u8,                // own logical node number
                        GdBlkIndex_ts  *gdBlkIdx_ps);                   // GD block index struct with initialized parameters; status_u8 will be
                                                                        // overwritten by return value.

/**
 *  @brief request read of a data block with handshaking
 *
 *  @param myLogNodeNum_u8      own logical node number
 *  @param gdBlkIdx_ps          pointer to gd block index struct
 *
 *  @return error != 0 ; success == 0
 */
sint16  gdBlkRead_s16(      uint8           myLogNodeNum_u8,            // own logical node number
                            GdBlkIndex_ts  *gdBlkIdx_ps);               // GD block index struct with initialized parameters; status_u8 will be
                                                                        // overwritten with return value, dataSize may be changed to right size.

#endif  // _GDBLK_H
