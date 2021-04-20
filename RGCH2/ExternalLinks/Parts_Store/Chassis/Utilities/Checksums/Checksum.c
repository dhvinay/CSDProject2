//common checksum functions

#include "eos.h"
#include "util.h"
#include "Checksum.h"
// Project specific header
#include "Project.h"


uint16 calcChecksum( uint8* EepromData_ps , uint16 size )
{
	uint16 checksum = 45, i;
	
	for( i = 0; i < size - 2; i++ )
	{
		checksum += EepromData_ps[i] * ((i & 0x7F) + 1);
	}

	return checksum;
}

uint16 cvtCalcHexSum( uint8* EepromData_ps, uint16 size )
{
	uint16 byteOffSet;
	uint16 byteSum_u16 = 0;
	
	for( byteOffSet = 0; byteOffSet < 126; byteOffSet++ )
	{
		if (byteOffSet < (size - 2) )
		{
			byteSum_u16 += *(EepromData_ps + byteOffSet);
		}
		else
		{
			byteSum_u16 += 0xFF;
		}
	}

	byteSum_u16 ^= 0xFFFF;

	return byteSum_u16;
}

