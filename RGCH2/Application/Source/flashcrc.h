/**
 *  @file             flashcrc.h
 *
 *  @brief          Utility functions to calculate the CRC checksum over flash content.
 *
 *    Replaces old file memcheck.h
 *
 *  @section     history
 *
 *  2008-11-10 / Christian Pischulti
 *  - draft
 */
#ifndef _FLASHCRC_H
#define _FLASHCRC_H

typedef enum
{
      FLASH_CRC_NOINIT,
      FLASH_CRC_RUNNING,
      FLASH_CRC_STOPPED,
      FLASH_CRC_EQUAL,
      FLASH_CRC_NOTEQUAL
} flashCrcState_te;

typedef struct
{
      uint8 * currentAddress_pu8;      // first address from which the first byte for crc is taken
      uint8 * endAddress_pu8;       // last address from which the last byte for crc is taken
      uint16 flashCrc_u16;
      flashCrcState_te flashCrcState_e;
} flashCrcAdmin_ts, * flashCrcAdmin_pts;

void flashCrcInit_v( flashCrcAdmin_pts flashCrcAdmin_ps );
void flashCrcChunkCalc_v(flashCrcAdmin_pts flashCrcAdmin_ps, uint32 chunkSizeInBytes_u32 );

#endif  //_FLASHCRC_H

