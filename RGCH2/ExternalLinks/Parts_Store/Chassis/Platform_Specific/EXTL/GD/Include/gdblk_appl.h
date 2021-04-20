/**
 *  @file       gdblk_appl.h
 *
 *  @brief      Header file for application module of generic driver block transfer extension.
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
 *  2015-04-23 / florian.koppers.ruecker@agcocorp.com
 *  - [BUG-6165] gdBlkConnectRead() got a third parameter 'size', to make GD-block-read transfers variable in transmission-size.
 *               Additionally the callbackfunction 'gdBlkIdxRead_s16' is fitted to allow the third parameter.
 *
 */
#ifndef _GDBLK_APPL_H
    #define _GDBLK_APPL_H

/// Internal structure for application interface of GD
typedef struct
{
    sint16 (*gdBlkIdxWrite_s16)( uint16 arrayIdx_u16, uint8* wrData_pu8, uint16 wrSize_u16 );  // Function to write data to one of the application's gd indices
    sint16 (*gdBlkIdxRead_s16)( uint16 arrayIdx_u16, uint8* rdData_pu8, uint16 wSize_u16);     // Function to read data from one of our application gd indices
                                                                                               // Notice: parameter is the index for applGdBlkIndices_ps array not
                                                                                               // the gd index!!

    uint16          gdBlkIndexListSize_u16;                                 // Number of indices in array applGdBlkIndices_as;
    uint16          gdBlkIndexCount_u16;                                    // Number of current stored indices in array
    GdBlkIndex_ts  *applGdBlkIndices_ps;                                    // Pointer to first element in gdBlk indices array.

} GdBlkApplAdmin_ts;

/**
 *  @brief Initialize the GD application interface for own participant.
 *
 *  @param appl_ps      Pointer to structure of application interface
 *  @param loclist_as   Pointer to first item for local list management
 *  @param size_u16     Number of items for local list management
 */
void gdBlkInitApplStruct( GdBlkApplAdmin_ts *appl_ps, GdBlkIndex_ts *loclist_as, uint16 size_u16 );

/**
 *  @brief Add an index to local list management.
 *
 *  @param appl_ps      Pointer to structure of application interface
 *  @param index_u16    Index number
 *  @return             0 if index was added, otherwise no free element
 */
sint32 gdBlkAddIndexToApplStruct_s32( GdBlkApplAdmin_ts *appl_ps, uint16 index_u16, uint8 status_u8, uint8 *data_pu8, uint16 dataSize_u16 );

/**
 *  @brief Insert the function to write data via blocktransfer.
 *
 *  @param appl_ps      Pointer to structure of application interface
 *  @param fu_pf        Pointer to function for writing with blocktransfer
 */
void gdBlkConnectWrite( GdBlkApplAdmin_ts *appl_ps, sint16 (*fu_pf)(uint16, uint8*, uint16) );

/**
 *  @brief Insert the function to read data via blocktransfer.
 *
 *  @param appl_ps      Pointer to structure of application interface
 *  @param fu_pf        Pointer to function for reading with blocktransfer
 */
void gdBlkConnectRead( GdBlkApplAdmin_ts *appl_ps, sint16 (*fu_pf)(uint16, uint8 *, uint16) );

/**
 *  @brief Handle incoming gd blk mbx messages.
 *
 *  @param gdBlkAdmin_ps    pointer to internal structure for application interface of gd
 *  @param blkMbxMsg_ps     incoming message
 */
void gdBlkProcessMessage( GdBlkApplAdmin_ts *gdBlkAdmin_ps, PxMsg_t *blkMbxMsg_ps );


#endif  // _GDBLK_APPL_H
