#include "HighClearance_eeprom.h"
#include "Project.h"

extern "C"
{
#include "Checksum.h"
}

namespace HighClearance
{

	sint32 highClearanceEeprom::paramsEepromRead( EepromData_Params_pts EepromData_Params_ps )
	{
		uint16 EeAdr_u16 = EEPROM_HIGH_CLEARANCE_PARAMS;
		sint32 err_S32;

		err_S32 = EosEepromRead_s32( EeAdr_u16, (uint8 *)EepromData_Params_ps, sizeof( EepromData_Params_ts ) );

		if ( err_S32 == 0 )
		{
			uint16 checksum_u16;
			checksum_u16 = calcChecksum( (uint8 *)EepromData_Params_ps, sizeof( EepromData_Params_ts ) );
			if ( checksum_u16 != EepromData_Params_ps->checksum )
			{
				err_S32 = -1;
			}
		}

		return err_S32;
	}

	//sint32 highClearanceEeprom::paramsEepromWrite( EepromData_Params_pts EepromData_Params_ps )
	//{
	//	uint16 EeAdr_u16 = EEPROM_HIGH_CLEARANCE_PARAMS;
	//	sint32 err_S32;
	//
	//	EepromData_Params_ps->checksum = calcChecksum( (uint8 *)EepromData_Params_ps, sizeof( EepromData_Params_ts ) );
	//	err_S32 = EosEepromWrite_s32( EeAdr_u16, (uint8 *)EepromData_Params_ps, sizeof( EepromData_Params_ts ) );
	//
	//	return err_S32;
	//}

	sint32 highClearanceEeprom::optionsEepromRead( EepromData_Options_pts EepromData_Options_ps )
	{
		uint16 EeAdr_u16 = EEPROM_HIGH_CLEARANCE_OPTIONS;
		sint32 err_S32;

		err_S32 = EosEepromRead_s32( EeAdr_u16, (uint8 *)EepromData_Options_ps, sizeof( EepromData_Options_ts ) );

		if ( err_S32 == 0 )
		{
			uint16 checksum_u16;
			checksum_u16 = calcChecksum( (uint8 *)EepromData_Options_ps, sizeof( EepromData_Options_ts ) );
			if ( checksum_u16 != EepromData_Options_ps->checksum )
			{
				err_S32 = -1;
			}
		}

		return err_S32;
	}

	sint32 highClearanceEeprom::optionsEepromWrite( EepromData_Options_pts EepromData_Options_ps )
	{
		uint16 EeAdr_u16 = EEPROM_HIGH_CLEARANCE_OPTIONS;
		sint32 err_S32;

		EepromData_Options_ps->checksum = calcChecksum( (uint8 *)EepromData_Options_ps, sizeof( EepromData_Options_ts ) );
		err_S32 = EosEepromWrite_s32( EeAdr_u16, (uint8 *)EepromData_Options_ps, sizeof( EepromData_Options_ts ) );

		return err_S32;
	}

	sint32 highClearanceEeprom::calsEepromRead( EepromData_Cals_pts EepromData_Cals_ps )
	{
		uint16 EeAdr_u16 = EEPROM_HIGH_CLEARANCE_CALS;
		sint32 err_S32;

		err_S32 = EosEepromRead_s32( EeAdr_u16, (uint8 *)EepromData_Cals_ps, sizeof( EepromData_Cals_ts ) );

		if ( err_S32 == 0 )
		{
			uint16 checksum_u16;
			checksum_u16 = calcChecksum( (uint8 *)EepromData_Cals_ps, sizeof( EepromData_Cals_ts ) );
			if ( checksum_u16 != EepromData_Cals_ps->checksum )
			{
				err_S32 = -1;
			}
		}

		return err_S32;
	}

	sint32 highClearanceEeprom::calsEepromWrite( EepromData_Cals_pts EepromData_Cals_ps )
	{
		uint16 EeAdr_u16 = EEPROM_HIGH_CLEARANCE_CALS;
		sint32 err_S32;

		EepromData_Cals_ps->checksum = calcChecksum( (uint8 *)EepromData_Cals_ps, sizeof( EepromData_Cals_ts ) );
		err_S32 = EosEepromWrite_s32( EeAdr_u16, (uint8 *)EepromData_Cals_ps, sizeof( EepromData_Cals_ts ) );

		return err_S32;
	}
}
