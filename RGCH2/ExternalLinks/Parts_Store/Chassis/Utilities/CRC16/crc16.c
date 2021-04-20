/**
 *  @file       crc16.c
 *
 *  @brief      Berechnung der CRC16 Checksumme.
 *
 *
 *  @section    Historie
 *
 *  2005-07-25 / werner-unsinn@xfendt.de
 *  - erstellt
 *
 *  2005-11-03 / werner-unsinn@xfendt.de
 *  - EXT: Tabelle in externes RAM verlagert
 *
 *  2006-04-07 / werner-unsinn@xfendt.de
 *  - Code zur Berechnung der Tabelle dokumentiert
 *
 *  2008-02-12 / werner-unsinn@xfendt.de
 *  - define "EXT_LIGHT" hinzugefuegt
 *
 *  2008-11-25 / werner-unsinn@xfendt.de
 *  - Funktion addCRC16Chksum() hinzugefuegt
 *
 *  2008-12-08 / werner-unsinn@xfendt.de
 *  - Funktion calcCRC16Chksum_u16() hinzugefuegt
 *
 *  2009-07-01 / werner-unsinn@xfendt.de
 *  - verschiedene Aenderungen wegen PolySpace
 *
 */


#include <eos.h>

#include "crc16.h"


// Makro zur Berechnung der CRC16 Checksumme
#define CALC_CRC16(dat, crc) (crc16Tab_acu16[((crc) ^ (dat)) & 0xFFu] ^ ((crc) >> 8))

// Tabelle zur Berechnung der CRC16 Checksumme
static const uint16 crc16Tab_acu16[256] = // CRC polynomial 0xA001
{
    0x0000u, 0xC0C1u, 0xC181u, 0x0140u, 0xC301u, 0x03C0u, 0x0280u, 0xC241u,
    0xC601u, 0x06C0u, 0x0780u, 0xC741u, 0x0500u, 0xC5C1u, 0xC481u, 0x0440u,
    0xCC01u, 0x0CC0u, 0x0D80u, 0xCD41u, 0x0F00u, 0xCFC1u, 0xCE81u, 0x0E40u,
    0x0A00u, 0xCAC1u, 0xCB81u, 0x0B40u, 0xC901u, 0x09C0u, 0x0880u, 0xC841u,
    0xD801u, 0x18C0u, 0x1980u, 0xD941u, 0x1B00u, 0xDBC1u, 0xDA81u, 0x1A40u,
    0x1E00u, 0xDEC1u, 0xDF81u, 0x1F40u, 0xDD01u, 0x1DC0u, 0x1C80u, 0xDC41u,
    0x1400u, 0xD4C1u, 0xD581u, 0x1540u, 0xD701u, 0x17C0u, 0x1680u, 0xD641u,
    0xD201u, 0x12C0u, 0x1380u, 0xD341u, 0x1100u, 0xD1C1u, 0xD081u, 0x1040u,
    0xF001u, 0x30C0u, 0x3180u, 0xF141u, 0x3300u, 0xF3C1u, 0xF281u, 0x3240u,
    0x3600u, 0xF6C1u, 0xF781u, 0x3740u, 0xF501u, 0x35C0u, 0x3480u, 0xF441u,
    0x3C00u, 0xFCC1u, 0xFD81u, 0x3D40u, 0xFF01u, 0x3FC0u, 0x3E80u, 0xFE41u,
    0xFA01u, 0x3AC0u, 0x3B80u, 0xFB41u, 0x3900u, 0xF9C1u, 0xF881u, 0x3840u,
    0x2800u, 0xE8C1u, 0xE981u, 0x2940u, 0xEB01u, 0x2BC0u, 0x2A80u, 0xEA41u,
    0xEE01u, 0x2EC0u, 0x2F80u, 0xEF41u, 0x2D00u, 0xEDC1u, 0xEC81u, 0x2C40u,
    0xE401u, 0x24C0u, 0x2580u, 0xE541u, 0x2700u, 0xE7C1u, 0xE681u, 0x2640u,
    0x2200u, 0xE2C1u, 0xE381u, 0x2340u, 0xE101u, 0x21C0u, 0x2080u, 0xE041u,
    0xA001u, 0x60C0u, 0x6180u, 0xA141u, 0x6300u, 0xA3C1u, 0xA281u, 0x6240u,
    0x6600u, 0xA6C1u, 0xA781u, 0x6740u, 0xA501u, 0x65C0u, 0x6480u, 0xA441u,
    0x6C00u, 0xACC1u, 0xAD81u, 0x6D40u, 0xAF01u, 0x6FC0u, 0x6E80u, 0xAE41u,
    0xAA01u, 0x6AC0u, 0x6B80u, 0xAB41u, 0x6900u, 0xA9C1u, 0xA881u, 0x6840u,
    0x7800u, 0xB8C1u, 0xB981u, 0x7940u, 0xBB01u, 0x7BC0u, 0x7A80u, 0xBA41u,
    0xBE01u, 0x7EC0u, 0x7F80u, 0xBF41u, 0x7D00u, 0xBDC1u, 0xBC81u, 0x7C40u,
    0xB401u, 0x74C0u, 0x7580u, 0xB541u, 0x7700u, 0xB7C1u, 0xB681u, 0x7640u,
    0x7200u, 0xB2C1u, 0xB381u, 0x7340u, 0xB101u, 0x71C0u, 0x7080u, 0xB041u,
    0x5000u, 0x90C1u, 0x9181u, 0x5140u, 0x9301u, 0x53C0u, 0x5280u, 0x9241u,
    0x9601u, 0x56C0u, 0x5780u, 0x9741u, 0x5500u, 0x95C1u, 0x9481u, 0x5440u,
    0x9C01u, 0x5CC0u, 0x5D80u, 0x9D41u, 0x5F00u, 0x9FC1u, 0x9E81u, 0x5E40u,
    0x5A00u, 0x9AC1u, 0x9B81u, 0x5B40u, 0x9901u, 0x59C0u, 0x5880u, 0x9841u,
    0x8801u, 0x48C0u, 0x4980u, 0x8941u, 0x4B00u, 0x8BC1u, 0x8A81u, 0x4A40u,
    0x4E00u, 0x8EC1u, 0x8F81u, 0x4F40u, 0x8D01u, 0x4DC0u, 0x4C80u, 0x8C41u,
    0x4400u, 0x84C1u, 0x8581u, 0x4540u, 0x8701u, 0x47C0u, 0x4680u, 0x8641u,
    0x8201u, 0x42C0u, 0x4380u, 0x8341u, 0x4100u, 0x81C1u, 0x8081u, 0x4040u,
};


/**
 *  Addiert das Byte einer 8-Bit Variablen zur vorhandenen CRC16-Checksumme hinzu.
 *
 *  @param data_u8      8-Bit Variable
 *  @param chksum_pu16  Checksumme die aufaddiert wird
 */
void addCRC16Chksum8bit (uint8 data_u8, uint16 *chksum_pu16)
{
    *chksum_pu16 = CALC_CRC16(data_u8, *chksum_pu16);
}

/**
 *  Addiert die 2 Byte einer 16-Bit Variablen zur vorhandenen CRC16-Checksumme hinzu.
 *
 *  @param data_u16     16-Bit Variable
 *  @param chksum_pu16  Checksumme die aufaddiert wird
 */
void addCRC16Chksum16bit (uint16 data_u16, uint16 *chksum_pu16)
{
    *chksum_pu16 = CALC_CRC16((uint8) (data_u16       & 0xFFu), *chksum_pu16);
    *chksum_pu16 = CALC_CRC16((uint8)((data_u16 >> 8) & 0xFFu), *chksum_pu16);
}

/**
 *  Addiert die 4 Byte einer 32-Bit Variablen zur vorhandenen CRC16-Checksumme hinzu.
 *
 *  @param data_u32     32-Bit Variable
 *  @param chksum_pu16  Checksumme die aufaddiert wird
 */
void addCRC16Chksum32bit (uint32 data_u32, uint16 *chksum_pu16)
{
    *chksum_pu16 = CALC_CRC16((uint8) (data_u32        & 0xFFu), *chksum_pu16);
    *chksum_pu16 = CALC_CRC16((uint8)((data_u32 >>  8) & 0xFFu), *chksum_pu16);
    *chksum_pu16 = CALC_CRC16((uint8)((data_u32 >> 16) & 0xFFu), *chksum_pu16);
    *chksum_pu16 = CALC_CRC16((uint8)((data_u32 >> 24) & 0xFFu), *chksum_pu16);
}

/**
 *  Addiert n Byte ab der angegebenen Adresse zur vorhandenen CRC16-Checksumme hinzu.
 *
 *  @param data_pu8     Zeiger auf die Daten
 *  @param n_u16        Anzahl der Byte
 *  @param chksum_pu16  Checksumme die aufaddiert wird
 */
void addCRC16Chksum (uint8 *data_pu8, uint16 n_u16, uint16 *chksum_pu16)
{
    uint16 i_u16;

    for (i_u16 = 0; i_u16 < n_u16; i_u16++)
    {
        *chksum_pu16 = CALC_CRC16(data_pu8[i_u16], *chksum_pu16);
    }
}

/**
 *  Berechnet die CRC16-Checksumme ueber n Byte ab der angegebenen Adresse.
 *
 *  @param data_pu8     Zeiger auf die Daten
 *  @param n_u16        Anzahl der Byte fuer Checksummenberechnung
 *  @return             Checksumme
 */
uint16 calcCRC16Chksum_u16 (uint8 *data_pu8, uint16 n_u16)
{
    uint16 chksum_u16 = 0;

    addCRC16Chksum(data_pu8, n_u16, &chksum_u16);

    return chksum_u16;
}



#if 0 // Dokumentation

#define CRC16_POLYNOM   0xA001

/**
 *  Berechnet einen Eintrag fuer die obige Tabelle.
 *
 *  @param polynom_u16  Polynom fuer die CRC-Berechnung
 *  @param index_u8     Index fuer den der Wert berechnet werden soll
 *  @return             Wert fuer CRC-Berechnung
 */
uint16 calcCRC16Tab_u16 (uint16 polynom_u16, uint8 index_u8)
{
    uint16 crc_u16;
    uint16 k_u16;

    crc_u16 = (uint16) index_u8;

    for (k_u16 = 0; k_u16 < 8; k_u16++)
    {
        if (crc_u16 & 1)
        {
            crc_u16 >>= 1;
            crc_u16 ^= polynom_u16;
        }
        else
        {
            crc_u16 >>= 1;
        }
    }

    return crc_u16;
}

/**
 *  Berechnet die CRC-Checksumme in dem ein Byte der vorhandenen Checksumme hinzugefuegt wird.
 *
 *  @param chksum_u16   vorhandenen Checksumme
 *  @param data_u8      Byte das der Checksumme hinzugefuegt wird
 *  @return             neue CRC-Checksumme
 */
uint16 calcCRC16_u16 (uint16 chksum_u16, uint8 data_u8)
{
    chksum_u16 = calcCRC16Tab_u16(CRC16_POLYNOM, (chksum_u16 ^ data_u8) & 0xff) ^ (chksum_u16 >> 8);
    return chksum_u16;
}

/**
 *  Ausgabe der Tabelle zur Berechnung der CRC16 Checksumme mit "printf".
 *  ACHTUNG: stdio.h notwendig
 */
void printCRC16Tab (void)
{
    sint8* pre_aps8[8]  = { "    ", " ", " ", " ", " ", " ", " ", " " };
    sint8* post_aps8[8] = { ",", ",", ",", ",", ",", ",", ",", ",\n" };
    uint16 index_u16;

    printf("// Tabelle zur Berechnung der CRC16 Checksumme\n");
    printf("static const uint16 crc16Tab_acu16[256] = // CRC polynomial 0x%04X\n", CRC16_POLYNOM);
    printf("{\n");

    for (index_u16 = 0; index_u16 < 256; index_u16++)
    {
        printf("%s0x%04Xu%s", pre_aps8[index_u16 % 8],
                              calcCRC16Tab_u16(CRC16_POLYNOM, index_u16),
                              post_aps8[index_u16 % 8]);
    }

    printf("};\n");
}

#endif
