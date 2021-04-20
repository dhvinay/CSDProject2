/**
 *  \file   eosFlashUtil.h
 *
 *  \brief  utility functions for read/write access to data flash
 *
 *  Copyright 2012 (c) AGCO/Fendt GmbH & Co.
 *
 *  \par    history
 *
 *  2012-03-19 / Christian.Pischulti@xfendt.de
 *  - [PB-2988] initial release
 *
 *  2012-10-01 / florian.schwarz@euro-engineering.net
 *  - moved from application code to EOS and renamed to eosFlashUtil.h (was FlashHandler.h)
 *  - renamed functions ReadDataFlash_s32(), WriteDataFlash_s32() to eosReadFlash_s32(), eosWriteFlash_s32()
 */

#ifndef _FLASHUTIL_H_
    #define _FLASHUTIL_H_

    sint32 eosReadFlash_s32(uint32 StartAdr_u32, uint8 *Data_pu8, uint32 DataAnz_u32);
    sint32 eosWriteFlash_s32(uint32 FlashAdr_u32, uint8 *Data_pu8, uint32 DataAnz_u32, boolean disableInts_b);

#endif  // _FLASHUTIL_H_
