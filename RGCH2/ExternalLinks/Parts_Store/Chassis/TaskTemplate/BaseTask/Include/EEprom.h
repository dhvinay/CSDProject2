extern "C"
{
#include "Eos.h"
#include "Checksum.h"
}


namespace NoMirrorEeprom
{

    template< class EepromStruct >
    sint32 readEeprom( uint16 startLocation, EepromStruct* fillStruct )
    {
        sint32 err_S32;

        err_S32 = EosEepromRead_s32( startLocation, (uint8 *)fillStruct, sizeof( EepromStruct ) );

        if( err_S32 == 0 )
        {
            uint16 checksum_u16;
            checksum_u16 = calcChecksum( (uint8 *)fillStruct, sizeof( EepromStruct ) );
            if( checksum_u16 != fillStruct->checksum )
            {
                err_S32 = -1;
            }
        }

        return err_S32;
    }

    template< class EepromWriteStruct >
    sint32 writeEeprom( uint16 startLocation, EepromWriteStruct* fillStruct_ps )
    {
        sint32 err_s32;

        if( !fillStruct_ps )
        {
            return 1;
        }

        fillStruct_ps->checksum = calcChecksum( (uint8*)fillStruct_ps, sizeof( EepromWriteStruct ) );

        err_s32 = EosEepromWrite_s32( startLocation, (uint8*)fillStruct_ps, sizeof( EepromWriteStruct ) );

        return err_s32;
    }

}

#ifdef _TT_EEPROM
namespace TT_EEPROM
{
extern "C"
{
#include "eep_mirror.h"
}
	
    template< class EepromStruct >
    sint32 readEeprom( uint16 startLocation, EepromStruct* fillStruct )
    {
        uint32 EeprAdr = startLocation;
        sint32 err_S32;

        err_S32 = eeprom_inp( &EeprAdr, (uint8*)fillStruct, sizeof( EepromStruct ) );

        if( err_S32 == 0 )
        {
            uint16 checksum_u16;
            checksum_u16 = calcChecksum( (uint8 *)fillStruct, sizeof( EepromStruct ) );
            if( checksum_u16 != fillStruct->checksum )
            {
                err_S32 = -1;
            }
        }

        return err_S32;
    }

    template< class EepromWriteStruct >
    sint32 writeEeprom( uint16 startLocation, EepromWriteStruct* fillStruct_ps )
    {
        uint32 EeAdr = startLocation;
        sint32 err_s32;

        if( !fillStruct_ps )
        {
            return 1;
        }

        fillStruct_ps->checksum = calcChecksum( (uint8*)fillStruct_ps, sizeof( EepromWriteStruct ) );

        err_s32 = eeprom_out( &EeAdr, (uint8*)fillStruct_ps, sizeof( EepromWriteStruct ) );

        return err_s32;
    }


}
#endif
