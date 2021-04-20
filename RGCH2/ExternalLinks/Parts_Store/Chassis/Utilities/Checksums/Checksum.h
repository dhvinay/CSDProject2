#include "gd.h"
#include "gdx.h"
//#include "std_type.h"

#ifndef __CHECKSUM_H
    #define __CHECKSUM_H

uint16 calcChecksum( uint8* EepromData_ps, uint16 size );
uint16 cvtCalcHexSum( uint8* EepromData_ps, uint16 size );

#endif // __CHECKSUM_H
