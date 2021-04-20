/**
 *  @file             flashcrc.c
 *
 *  @brief          Utility functions to calculate the CRC checksum over flash content.
 *
 *    Replaces old file memcheck.
 *
 *  @section     history
 *
 *  2008-11-10 / Christian Pischulti
 *  - draft
 *
 *  2011-11-15 / werner.unsinn@xfendt.de
 *  - eliminated compiler warnings [PB-2358]
 *
 *  2013-09-20 / mattis.kornelius.euroeng@agcocorp.com
 *  - [MISC] changed from const to extern declaration for chksum_bios_u16 and end_address_bios_u32 because of
 *    optimization of Compiler (GNU Tools for ARM 2012Q2)
 *
 */
#include "Eos.h"
#include "crc16.h"
#include "flashcrc.h"


// First address of flash image used for checksum verification. Address is filled in by linker invocation file.
extern uint32*  __chksum_start_address;

// Location of the CRC checksum of build time. The checksum is located in the info area before application code.
extern uint16 chksum_bios_u16;

// Location of the absolute end address of bios. This pointer is filled in by the FileCut before application code.
extern uint32 end_address_bios_u32;

// First address after end of used flash area. This address is compared against the end address stored in the header.
// A wrong end address can cause a trap during crc calculation...
extern uint32*  __chksum_end_address;


/**
 *    @brief      flashCrcInit_v - initialize struct for crc calculation over flash
 *
 *    @param  flashCrcAdmin_ps - pointer to a crc admin struct
 *
 */
void flashCrcInit_v(flashCrcAdmin_pts flashCrcAdmin_ps)
{
    flashCrcAdmin_ps->currentAddress_pu8 = (uint8*) &__chksum_start_address;  // The checksum starts at application entry vector.
    flashCrcAdmin_ps->endAddress_pu8 = (uint8*)(end_address_bios_u32 + 1);    // Increase address to point one byte after the last data byte. This is needed for checking end of flash.
    flashCrcAdmin_ps->flashCrc_u16  = 0;

    // Compare endAddress stored in header with automatic generated label of linker file. A wrong end address can cause a trap
    // when the crc calculation is done for memory which isn't availible. The end address of linker file points to the first byte after used flash.
    if (flashCrcAdmin_ps->endAddress_pu8 == (uint8*) &__chksum_end_address)
    {
        flashCrcAdmin_ps->flashCrcState_e = FLASH_CRC_RUNNING;         // Preset running state
    }
    else
    {
        flashCrcAdmin_ps->flashCrcState_e = FLASH_CRC_NOTEQUAL;         // Preset fault if linker generated end address doesn't match to the address in header
    }
}

/**
 *    @brief      flashCrcChunkCalc - calculate the crc over a chunk of flash
 *
 *    @param  flashCrcAdmin_ps - pointer to crc admin struct
 *    @param  chunkSizeInBytes_u32 - chunk size in bytes
 */
void flashCrcChunkCalc_v(flashCrcAdmin_pts flashCrcAdmin_ps, uint32 chunkSizeInBytes_u32)
{
    // Calculate remaining chunk size if we have nearly reached end of flash content.
    if (((uint32)(flashCrcAdmin_ps->endAddress_pu8  - flashCrcAdmin_ps->currentAddress_pu8)) < chunkSizeInBytes_u32)
    {
        chunkSizeInBytes_u32 = flashCrcAdmin_ps->endAddress_pu8 - flashCrcAdmin_ps->currentAddress_pu8;
    }
    // call utility function
    addCRC16Chksum(flashCrcAdmin_ps->currentAddress_pu8 , chunkSizeInBytes_u32, &flashCrcAdmin_ps->flashCrc_u16);
    // set current address for next run
    flashCrcAdmin_ps->currentAddress_pu8 = &flashCrcAdmin_ps->currentAddress_pu8[chunkSizeInBytes_u32];

    // Compare checksum and set result if end of flash reached.
    if (chunkSizeInBytes_u32 == 0)
    {
        if (flashCrcAdmin_ps->flashCrc_u16 == chksum_bios_u16)
        {
            flashCrcAdmin_ps->flashCrcState_e = FLASH_CRC_EQUAL;
        }
        else
        {
            flashCrcAdmin_ps->flashCrcState_e = FLASH_CRC_NOTEQUAL;
        }
    }
}

