/**
 *  @file   util_eosGd.h
 *
 *      
 */
 
#include "eos.h"
#include "gd.h"
#include "gdx.h"

#include "Project.h"

#define ARRAY_SIZE( a )   ( sizeof( a ) / sizeof( ( a )[0] ) )
 
#ifndef __UTIL_EOSGD_H
    #define __UTIL_EOSGD_H

	real32 Low_Pass_Filter (real32 oldVal, uint32 newVal, real32 alpha);
	
	real32 Low_Pass_Filter_signed (real32 oldVal, real32 newVal, real32 alpha);

	uint8 translateDiag_u8 (uint8 eosDiag);

	uint8 translateGdDiag_u8 (uint8 gdDiag);

	uint8 getDiagnostic_Ai_u8(uint32 volt_mV_u32);
#ifndef EXTERNAL_EMM
	bool handleDiag_iA_mV( 	uint8 Diag_u8, uint16 data_u16, bool *error_SCGND_OR_OPEN_Active_pb, 
							bool *error_SCVCC_Active_pb, uint8 location_u8, uint8 codeSCGND_OR_OPEN_u8, uint8 code_SCVCC_u8 );
							
	bool handleDiag_iA_mA( 	uint8 Diag_u8, uint16 data_u16, bool *error_SCGND_OR_OPEN_Active_pb, 
							bool *error_SCVCC_Active_pb, uint8 location_u8, uint8 codeSCGND_OR_OPEN_u8, uint8 code_SCVCC_u8 );
	
	bool handleDiag_iD_mV( 	uint8 Diag_u8, uint16 data_u16, bool *error_SCGND_Active_pb, 
							bool *error_SCVCC_OR_OPEN_Active_pb, uint8 location_u8, uint8 codeSCGND_u8, uint8 code_SCVCC_OR_OPEN_u8 );
	
	bool handleDiag_iA_dutyCycle( 	uint8 Diag_u8, uint16 data_u16, bool *error_UNDEF_Active_pb, 
									uint8 location_u8, uint8 codeUNDEF_u8 );

	bool handleDiag_Out( uint8 Diag_u8, uint16 data_u16, bool *error_SCGND_Active_pb, 
						 bool *error_SCVCC_OR_OPEN_Active_pb, uint8 location_u8, uint8 codeSCGND_u8, uint8 code_SCVCC_OR_OPEN_u8 );

	bool handleDiag_iA_mV_GD( 	uint8 Diag_u8, bool *error_SCGND_OR_OPEN_Active_pb, bool *error_SCVCC_Active_pb, 
								uint8 location_u8, uint8 codeSCGND_OR_OPEN_u8, uint8 code_SCVCC_u8 );

	bool handleDiag_iA_mA_GD( 	uint8 Diag_u8, bool *error_SCGND_OR_OPEN_Active_pb, bool *error_SCVCC_Active_pb, 
								uint8 location_u8, uint8 codeSCGND_OR_OPEN_u8, uint8 code_SCVCC_u8 );

	bool handleDiag_iA_dutyCycle_GD(	uint8 Diag_u8, bool *error_SCGND_Active_pb, bool *error_SCVCC_Active_pb, 
										uint8 location_u8, uint8 codeSCGND_u8, uint8 code_SCVCC_u8 );

	bool handleDiag_Out_GD( 	uint8 Diag_u8, bool *error_SCGND_Active_pb, bool *error_SCVCC_OR_OPEN_Active_pb, 
								uint8 location_u8, uint8 codeSCGND_u8, uint8 code_SCVCC_OR_OPEN_u8 );
#endif
	bool triggerError_b( uint8 Diag_u8, uint16 *errorCounter_pu16, uint16 triggerTime_u16, uint16 tickTime_u16 );

	GdData_ts checkGdXData( GdXRequestData_ts *GdXData_ps );

	uint8 diagDutyCycleInput_u8( uint16 dutycycle_u16 );

    uint8 getLogicalNodeFromIndex( uint16 index_16 );

    bool isNodeAliveByIndex( uint16 index_16 );

#endif // __UTIL_EOSGD_H
