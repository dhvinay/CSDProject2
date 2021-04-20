/**
 *  @file       crc16.h
 *
 *  @brief      Berechnung der CRC16 Checksumme.
 *
 *
 *  @section    Historie
 *
 *  2005-07-25 / werner-unsinn@xfendt.de
 *  - erstellt
 *
 *  2008-11-25 / werner-unsinn@xfendt.de
 *  - Funktion addCRC16Chksum() hinzugefuegt
 *
 *  2008-12-08 / werner-unsinn@xfendt.de
 *  - Funktion calcCRC16Chksum_u16() hinzugefuegt
 *
 */

#ifndef __CRC16_H
    #define __CRC16_H

    void addCRC16Chksum8bit (uint8 data_u8, uint16 *chksum_pu16);
    void addCRC16Chksum16bit (uint16 data_u16, uint16 *chksum_pu16);
    void addCRC16Chksum32bit (uint32 data_u32, uint16 *chksum_pu16);
    void addCRC16Chksum (uint8 *data_pu8, uint16 n_u16, uint16 *chksum_pu16);

    uint16 calcCRC16Chksum_u16 (uint8 *data_pu8, uint16 n_u16);

#endif // __CRC16_H
