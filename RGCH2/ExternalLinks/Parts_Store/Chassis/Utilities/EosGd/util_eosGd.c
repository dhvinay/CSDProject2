/**
 *  @file   util_eosGd.c
 *
 *    
 */


#include "util_eosGd.h"

/**
 *  Apply low pass filter
 *
 *  @param oldVal			previous value
 *  @param newVal			new value
 *  @param alpha			alpha value for low pass filter (between 0 and 1)
 *							if not between 0 and 1, newVal is returned
 *  @return               	filtered value
 */
real32 Low_Pass_Filter (real32 oldVal, uint32 newVal, real32 alpha)
{
	real32 retVal;

	if( alpha >= 0 && alpha <= 1 )
		retVal = (1.0 - alpha) * oldVal + alpha * newVal;
	else
		retVal = newVal;

	return retVal;
}

/**
 *  Apply low pass filter
 *
 *  @param oldVal			previous value
 *  @param newVal			new value
 *  @param alpha			alpha value for low pass filter (between 0 and 1)
 *							if not between 0 and 1, newVal is returned
 *  @return               	filtered value
 */
real32 Low_Pass_Filter_signed (real32 oldVal, real32 newVal, real32 alpha)
{
	real32 retVal;

	if( alpha >= 0 && alpha <= 1 )
		retVal = (1.0 - alpha) * oldVal + alpha * newVal;
	else
		retVal = newVal;

	return retVal;
}

/**
 *  Translate EOS diagnostic value to GD diganostic value.
 *
 *  @param diag_e           EOS diagnostic value
 *  @return                 GD diagnostic value
 */
uint8 translateDiag_u8 (uint8 eosDiag)
{
    uint8 diag_u8;

    switch (eosDiag)
    {
        case IOD_OK:
            diag_u8 = GD_DIAG_OK;
            break;
        case IOD_Open:
            diag_u8 = GD_DIAG_OPEN;
            break;
        case IOD_ScGnd:
            diag_u8 = GD_DIAG_SCGND;
            break;
        case IOD_ScGnd + IOD_Open:
            diag_u8 = GD_DIAG_SCGND_OR_OPEN;
            break;
        case IOD_ScHigh:
            diag_u8 = GD_DIAG_SCVCC;
            break;
        case IOD_ScHigh + IOD_Open:
            diag_u8 = GD_DIAG_SCVCC_OR_OPEN;
            break;
        default:
            diag_u8 = GD_DIAG_UNDEF;
            break;
    }
    return diag_u8;
}

/**
 *  Translate GD diagnostic value to EOS diganostic value.
 *
 *  @param gdDiag           GD diagnostic value
 *  @return                 EOS diagnostic value
 */
uint8 translateGdDiag_u8 (uint8 gdDiag)
{
    uint8 diag_u8;

    switch (gdDiag)
    {
        case GD_DIAG_OK:
            diag_u8 = IOD_OK;
            break;
        case GD_DIAG_OPEN:
            diag_u8 = IOD_Open;
            break;
        case GD_DIAG_SCGND:
            diag_u8 = IOD_ScGnd;
            break;
        case GD_DIAG_SCGND_OR_OPEN:
            diag_u8 = IOD_ScGnd + IOD_Open;
            break;
        case GD_DIAG_SCVCC:
            diag_u8 = IOD_ScHigh;
            break;
        case GD_DIAG_SCVCC_OR_OPEN:
            diag_u8 = IOD_ScHigh + IOD_Open;
            break;
        default:
            diag_u8 = 0xFF;
            break;
    }
    return diag_u8;
}
uint8 getDiagnostic_Ai_u8(uint32 volt_mV_u32)
{
/**
 *  Translate mV value of a analog voltage input value to GD diganostic value.
 *
 *  @param volt_mV_u32      mV value of analog input value
 *  @return                 GD diagnostic value
 */
 
	uint8 diag_u8;
 
	uint32 volt_mV_Low = 200; //Report GD_DIAG_SCGND_OR_OPEN if value is below volt_mV_Low 
	uint32 volt_mV_High = 6000; //Report GD_DIAG_SCVCC_OR_OPEN if value is below volt_mV_Low 
 
	if(volt_mV_u32 < volt_mV_Low)
		diag_u8 = GD_DIAG_SCGND_OR_OPEN;
	else if (volt_mV_u32 > volt_mV_High)
		diag_u8 = GD_DIAG_SCVCC;
	else
		diag_u8 = GD_DIAG_OK;

	return diag_u8;
}
#ifndef EXTERNAL_EMM
bool handleDiag_iA_mV( 	uint8 Diag_u8, uint16 data_u16, bool *error_SCGND_OR_OPEN_Active_pb, 
						bool *error_SCVCC_Active_pb, uint8 location_u8, uint8 codeSCGND_OR_OPEN_u8, uint8 code_SCVCC_u8 )
{
	bool errorActive_b;
	
	if( Diag_u8 == GD_DIAG_SCGND_OR_OPEN && !*error_SCGND_OR_OPEN_Active_pb )
	{	
		signalErrorWithData_s32 (TRUE, getErrorHandle_s32 ( location_u8, codeSCGND_OR_OPEN_u8), data_u16 );
		*error_SCGND_OR_OPEN_Active_pb = TRUE;
	}
	else if( Diag_u8 == GD_DIAG_SCVCC && !*error_SCVCC_Active_pb) 
	{
		signalErrorWithData_s32 (TRUE, getErrorHandle_s32 ( location_u8, code_SCVCC_u8), data_u16 );
		*error_SCVCC_Active_pb = TRUE;
	}
	else if( Diag_u8 != GD_DIAG_SCGND_OR_OPEN && *error_SCGND_OR_OPEN_Active_pb ) 
	{	
		signalErrorWithData_s32 (FALSE, getErrorHandle_s32 ( location_u8, codeSCGND_OR_OPEN_u8), data_u16 );
		*error_SCGND_OR_OPEN_Active_pb = FALSE;
	}
	else if( Diag_u8 != GD_DIAG_SCVCC && *error_SCVCC_Active_pb )
	{
		signalErrorWithData_s32 (FALSE, getErrorHandle_s32 ( location_u8, code_SCVCC_u8), data_u16 );
		*error_SCVCC_Active_pb = FALSE;
	}		
	
	if( !*error_SCGND_OR_OPEN_Active_pb && !*error_SCVCC_Active_pb)
		errorActive_b = FALSE;
	else
		errorActive_b = TRUE;
		
	return errorActive_b;
}

bool handleDiag_iA_mA( 	uint8 Diag_u8, uint16 data_u16, bool *error_SCGND_OR_OPEN_Active_pb, 
						bool *error_SCVCC_Active_pb, uint8 location_u8, uint8 codeSCGND_OR_OPEN_u8, uint8 code_SCVCC_u8 )
{
	bool errorActive_b;
	
	if( Diag_u8 == GD_DIAG_SCGND_OR_OPEN && !*error_SCGND_OR_OPEN_Active_pb )
	{	
		signalErrorWithData_s32 (TRUE, getErrorHandle_s32 ( location_u8, codeSCGND_OR_OPEN_u8), data_u16 );
		*error_SCGND_OR_OPEN_Active_pb = TRUE;
	}
	else if( Diag_u8 == GD_DIAG_SCVCC && !*error_SCVCC_Active_pb) 
	{
		signalErrorWithData_s32 (TRUE, getErrorHandle_s32 ( location_u8, code_SCVCC_u8), data_u16 );
		*error_SCVCC_Active_pb = TRUE;
	}
	else if( Diag_u8 != GD_DIAG_SCGND_OR_OPEN && *error_SCGND_OR_OPEN_Active_pb ) 
	{	
		signalErrorWithData_s32 (FALSE, getErrorHandle_s32 ( location_u8, codeSCGND_OR_OPEN_u8), data_u16 );
		*error_SCGND_OR_OPEN_Active_pb = FALSE;
	}
	else if( Diag_u8 != GD_DIAG_SCVCC && *error_SCVCC_Active_pb )
	{
		signalErrorWithData_s32 (FALSE, getErrorHandle_s32 ( location_u8, code_SCVCC_u8), data_u16 );
		*error_SCVCC_Active_pb = FALSE;
	}		
	
	if( !*error_SCGND_OR_OPEN_Active_pb && !*error_SCVCC_Active_pb)
		errorActive_b = FALSE;
	else
		errorActive_b = TRUE;
		
	return errorActive_b;
}

bool handleDiag_iD_mV( 	uint8 Diag_u8, uint16 data_u16, bool *error_SCGND_Active_pb, 
						bool *error_SCVCC_OR_OPEN_Active_pb, uint8 location_u8, uint8 codeSCGND_u8, uint8 code_SCVCC_OR_OPEN_u8 )
{
	bool errorActive_b;
	
	if( Diag_u8 == GD_DIAG_SCGND && !*error_SCGND_Active_pb )
	{	
		signalErrorWithData_s32 (TRUE, getErrorHandle_s32 ( location_u8, codeSCGND_u8), data_u16 );
		*error_SCGND_Active_pb = TRUE;
	}
	else if( Diag_u8 == GD_DIAG_SCVCC && !*error_SCVCC_OR_OPEN_Active_pb) 
	{
		signalErrorWithData_s32 (TRUE, getErrorHandle_s32 ( location_u8, code_SCVCC_OR_OPEN_u8), data_u16 );
		*error_SCVCC_OR_OPEN_Active_pb = TRUE;
	}
	else if( Diag_u8 != GD_DIAG_SCGND && *error_SCGND_Active_pb ) 
	{	
		signalErrorWithData_s32 (FALSE, getErrorHandle_s32 ( location_u8, codeSCGND_u8), data_u16 );
		*error_SCGND_Active_pb = FALSE;
	}
	else if( Diag_u8 != GD_DIAG_SCVCC && *error_SCVCC_OR_OPEN_Active_pb )
	{
		signalErrorWithData_s32 (FALSE, getErrorHandle_s32 ( location_u8, code_SCVCC_OR_OPEN_u8), data_u16 );
		*error_SCVCC_OR_OPEN_Active_pb = FALSE;
	}		
	
	if( !*error_SCGND_Active_pb && !*error_SCVCC_OR_OPEN_Active_pb)
		errorActive_b = FALSE;
	else
		errorActive_b = TRUE;
		
	return errorActive_b;
}

bool handleDiag_iA_dutyCycle( 	uint8 Diag_u8, uint16 data_u16, bool *error_UNDEF_Active_pb, 
								uint8 location_u8, uint8 codeUNDEF_u8 )
{
	bool errorActive_b;
	
	if( Diag_u8 == GD_DIAG_UNDEF && !*error_UNDEF_Active_pb )
	{	
		signalErrorWithData_s32 (TRUE, getErrorHandle_s32 ( location_u8, codeUNDEF_u8), data_u16 );
		*error_UNDEF_Active_pb = TRUE;
	}
	else if( Diag_u8 != GD_DIAG_UNDEF && *error_UNDEF_Active_pb ) 
	{	
		signalErrorWithData_s32 (FALSE, getErrorHandle_s32 ( location_u8, codeUNDEF_u8), data_u16 );
		*error_UNDEF_Active_pb = FALSE;
	}
	
	if( !*error_UNDEF_Active_pb )
		errorActive_b = FALSE;
	else
		errorActive_b = TRUE;
		
	return errorActive_b;
}

bool handleDiag_Out( uint8 Diag_u8, uint16 data_u16, bool *error_SCGND_Active_pb, 
					bool *error_SCVCC_OR_OPEN_Active_pb, uint8 location_u8, uint8 codeSCGND_u8, uint8 code_SCVCC_OR_OPEN_u8 )
{
	bool errorActive_b;
	
	if( Diag_u8 == GD_DIAG_SCGND && !*error_SCGND_Active_pb )
	{	
		signalErrorWithData_s32 (TRUE, getErrorHandle_s32 ( location_u8, codeSCGND_u8), data_u16 );
		*error_SCGND_Active_pb = TRUE;
	}
	else if( Diag_u8 == GD_DIAG_SCVCC_OR_OPEN && !*error_SCVCC_OR_OPEN_Active_pb) 
	{
		signalErrorWithData_s32 (TRUE, getErrorHandle_s32 ( location_u8, code_SCVCC_OR_OPEN_u8 ), data_u16 );
		*error_SCVCC_OR_OPEN_Active_pb = TRUE;
	}
	else if( Diag_u8 != GD_DIAG_SCGND && *error_SCGND_Active_pb ) 
	{	
		signalErrorWithData_s32 (FALSE, getErrorHandle_s32 ( location_u8, codeSCGND_u8), data_u16 );
		*error_SCGND_Active_pb = FALSE;
	}
	else if( Diag_u8 != GD_DIAG_SCVCC_OR_OPEN && *error_SCVCC_OR_OPEN_Active_pb )
	{
		signalErrorWithData_s32 (FALSE, getErrorHandle_s32 ( location_u8, code_SCVCC_OR_OPEN_u8 ), data_u16 );
		*error_SCVCC_OR_OPEN_Active_pb = FALSE;
	}		
	
	if( !*error_SCGND_Active_pb && !*error_SCVCC_OR_OPEN_Active_pb)
		errorActive_b = FALSE;
	else
		errorActive_b = TRUE;
		
	return errorActive_b;
}

bool handleDiag_iA_mV_GD( 	uint8 Diag_u8, bool *error_SCGND_OR_OPEN_Active_pb, bool *error_SCVCC_Active_pb, 
							uint8 location_u8, uint8 codeSCGND_OR_OPEN_u8, uint8 code_SCVCC_u8 )
{
	bool errorActive_b;
	
	if( Diag_u8 == GD_DIAG_SCGND_OR_OPEN && !*error_SCGND_OR_OPEN_Active_pb )
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, codeSCGND_OR_OPEN_u8, TRUE, GD_DIAG_OK);
	else if( Diag_u8 == GD_DIAG_SCVCC && !*error_SCVCC_Active_pb) 
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, code_SCVCC_u8, TRUE, GD_DIAG_OK);
	else if( Diag_u8 != GD_DIAG_SCGND_OR_OPEN && *error_SCGND_OR_OPEN_Active_pb ) 
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, codeSCGND_OR_OPEN_u8, FALSE, GD_DIAG_OK);
	else if( Diag_u8 != GD_DIAG_SCVCC && *error_SCVCC_Active_pb )
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, code_SCVCC_u8, FALSE, GD_DIAG_OK);
	
	if( Diag_u8 != GD_DIAG_SCGND_OR_OPEN && Diag_u8 != GD_DIAG_SCVCC )
		errorActive_b = FALSE;
	else
		errorActive_b = TRUE;
		
	return errorActive_b;
}

bool handleDiag_iA_mA_GD( 	uint8 Diag_u8, bool *error_SCGND_OR_OPEN_Active_pb, bool *error_SCVCC_Active_pb, 
							uint8 location_u8, uint8 codeSCGND_OR_OPEN_u8, uint8 code_SCVCC_u8 )
{
	bool errorActive_b;
	
	if( Diag_u8 == GD_DIAG_SCGND_OR_OPEN && !*error_SCGND_OR_OPEN_Active_pb )
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, codeSCGND_OR_OPEN_u8, TRUE, GD_DIAG_OK);
	else if( Diag_u8 == GD_DIAG_SCVCC && !*error_SCVCC_Active_pb) 
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, code_SCVCC_u8, TRUE, GD_DIAG_OK);
	else if( Diag_u8 != GD_DIAG_SCGND_OR_OPEN && *error_SCGND_OR_OPEN_Active_pb ) 
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, codeSCGND_OR_OPEN_u8, FALSE, GD_DIAG_OK);
	else if( Diag_u8 != GD_DIAG_SCVCC && *error_SCVCC_Active_pb )
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, code_SCVCC_u8, FALSE, GD_DIAG_OK);
	
	if( Diag_u8 != GD_DIAG_SCGND_OR_OPEN && Diag_u8 != GD_DIAG_SCVCC )
		errorActive_b = FALSE;
	else
		errorActive_b = TRUE;
		
	return errorActive_b;
}

bool handleDiag_iA_dutyCycle_GD( 	uint8 Diag_u8, bool *error_SCGND_Active_pb, bool *error_SCVCC_Active_pb, 
									uint8 location_u8, uint8 codeSCGND_u8, uint8 code_SCVCC_u8 )
{
	bool errorActive_b;
	
	if( Diag_u8 == GD_DIAG_SCGND && !*error_SCGND_Active_pb )
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, codeSCGND_u8, TRUE, GD_DIAG_OK);
	else if( Diag_u8 == GD_DIAG_SCVCC && !*error_SCVCC_Active_pb) 
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, code_SCVCC_u8, TRUE, GD_DIAG_OK);
	else if( Diag_u8 != GD_DIAG_SCGND && *error_SCGND_Active_pb ) 
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, codeSCGND_u8, FALSE, GD_DIAG_OK);
	else if( Diag_u8 != GD_DIAG_SCVCC && *error_SCVCC_Active_pb )
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, code_SCVCC_u8, FALSE, GD_DIAG_OK);
	
	if( Diag_u8 != GD_DIAG_SCGND && Diag_u8 != GD_DIAG_SCVCC )
		errorActive_b = FALSE;
	else
		errorActive_b = TRUE;
		
	return errorActive_b;
}

bool handleDiag_Out_GD( uint8 Diag_u8, bool *error_SCGND_Active_pb, bool *error_SCVCC_OR_OPEN_Active_pb, 
						uint8 location_u8, uint8 codeSCGND_u8, uint8 code_SCVCC_OR_OPEN_u8 )
{
	bool errorActive_b;
	
	if( Diag_u8 == GD_DIAG_SCGND && !*error_SCGND_Active_pb )
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, codeSCGND_u8, TRUE, GD_DIAG_OK);
	else if( Diag_u8 == GD_DIAG_SCVCC_OR_OPEN && !*error_SCVCC_OR_OPEN_Active_pb) 
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, code_SCVCC_OR_OPEN_u8, TRUE, GD_DIAG_OK);
	else if( Diag_u8 != GD_DIAG_SCGND && *error_SCGND_Active_pb ) 
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, codeSCGND_u8, FALSE, GD_DIAG_OK);
	else if( Diag_u8 != GD_DIAG_SCVCC_OR_OPEN && *error_SCVCC_OR_OPEN_Active_pb )
		gdSendImmediateWrite_s32 (location_u8, GD_LN_EMM*512 + location_u8, FALSE, code_SCVCC_OR_OPEN_u8, FALSE, GD_DIAG_OK);

	if( Diag_u8 != GD_DIAG_SCGND && Diag_u8 != GD_DIAG_SCVCC_OR_OPEN )
		errorActive_b = FALSE;
	else
		errorActive_b = TRUE;
		
	return errorActive_b;
}
#endif
bool triggerError_b( uint8 Diag_u8, uint16 *errorCounter_pu16, uint16 triggerTime_u16, uint16 tickTime_u16 )
{
	uint16 triggerCounter_u16 = triggerTime_u16 / tickTime_u16;

	if( !triggerCounter_u16 )
		return TRUE;

	if( Diag_u8 && *errorCounter_pu16 < 2*triggerCounter_u16 )
			(*errorCounter_pu16)++;
	else if( !Diag_u8 && *errorCounter_pu16 )
			(*errorCounter_pu16)--;

	bool trigger_b;

	if( *errorCounter_pu16 >= triggerCounter_u16 )
		trigger_b = TRUE;
	else
		trigger_b = FALSE;

	if( (trigger_b && Diag_u8)
		|| (!trigger_b && !Diag_u8) )
		return TRUE;
	else
		return FALSE;
}

GdData_ts checkGdXData( GdXRequestData_ts *GdXData_ps ) 
{
	GdData_ts tmpGdData_s = GdXData_ps->data_s;

	if(( GdXData_ps->timestamp_u32 == 0 ) || (GdXData_ps->timestamp_u32 == MAXUINT32))
	{
		tmpGdData_s.diag_u8 = GD_DIAG_CAN_ERROR;
	}

	return tmpGdData_s;
}

uint8 diagDutyCycleInput_u8( uint16 dutycycle_u16 )
{
	uint8 tmpError = GD_DIAG_OK;

	if( dutycycle_u16 < 500 || dutycycle_u16 > 9500 )
		tmpError = GD_DIAG_UNDEF;

	return tmpError;
}

/**
*  Returns the inputted index's logical node
*
*  @param volt_mV_u32      GD Index
*  @return                 GD Logical Node
*/
uint8 getLogicalNodeFromIndex( uint16 index_16 )
{
    return (uint8) ( index_16 / 0x0200 );
}

/**
*  Returns the state index's logical node
*
*  @param volt_mV_u32      GD Index
*  @return                 boolean - is that index's node alive
*/
uint8 isNodeAliveByIndex( uint16 index_16 )
{
	return gdIsAlive_b( getLogicalNodeFromIndex( index_16 ) );
}
