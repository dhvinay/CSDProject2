/**
 * \file util.h
 *
 * \brief Header file for utility functions
 *
 * Copyright (c) AGCO/Fendt GmbH & Co.
 *
 *
 * \section History
 *
 * 2012-06-21 / florian.schwarz@euro-engineering.com
 * - Copied utility functions from Fendt EOS to EOS trunk.
 *
 * 2012-09-06 / florian.schwarz@euro-engineering.com
 *  - stylistic changes for better MISRA-C compliance
 */

#ifndef _UTIL_H
#define _UTIL_H

/*
*   miscellaneous functions
*/
//{
    /**
     * \defgroup _misc miscellaneous
     * \{
     */

    /*   auxiliary functions due to historical reasons */
    /*!  used for normalization: a * b / c
        result MUST be 32-Bit again; multiplication can exceed 32-Bit range  */
    uint32 muldivlu( uint32 fak1_u32, uint32 fak2_u32, uint32 div_u32 );
    /*!  same as above but SIGNED  */
    sint32 muldivl ( sint32 fak1_s32, sint32 fak2_s32, sint32 div_s32 );

    /*  convert BCD to Binary format and vise versa  */
    uint16   bin2bcd( uint16 binval_cu16 );
    uint16   bcd2bin( uint16 bcdval_cu16 );

    /* convert a decimal number to a string */
    uint8 bin2string( uint16 number_u16, uint8 * charBuffer_pu8 );

    /**
     * \}
     */

//}  miscellaneous

#endif
