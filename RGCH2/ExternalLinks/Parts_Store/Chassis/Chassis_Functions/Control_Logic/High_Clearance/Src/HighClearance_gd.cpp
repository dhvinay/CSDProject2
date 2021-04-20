#include "HighClearance_gd.h"

extern "C"
{
#include "HighClearance_model.h"
#include "Eos.h"
}

namespace HighClearance
{
	highClearanceGd::highClearanceGd()
	{
		uint16 i;

		GdRequests_ts resetGdRequests_s = { MAXUINT16, { { 0, 0, 0 }, 0 }, FALSE, ECRR };
		GdData_ts tmpGdData_UNAVAL_s = { 0, FALSE, GD_DIAG_DISABLED };
		GdXRequestData_ts tmpGdXData_UNAVAL_s = { tmpGdData_UNAVAL_s, 0 };

		for ( i = 0; i < NUM_OF_REQUESTS; i++ )
		{
			requests_s[i] = resetGdRequests_s;
		}

		requests_s[MFA_UP_BUTTON		].IndexToRequest = HC_GD_ID_MFA_UP_BUTTON;	
		requests_s[MFA_DOWN_BUTTON		].IndexToRequest = HC_GD_ID_MFA_DOWN_BUTTON;
		requests_s[MFA_STOP_BUTTON		].IndexToRequest = HC_GD_ID_MFA_STOP_BUTTON;		
		requests_s[EOI					].IndexToRequest = HC_GD_ID_EOI;				
		requests_s[ROAD_FIELD_MODE		].IndexToRequest = HC_GD_ID_ROAD_FIELD_MODE;		
		requests_s[TRACKWIDTH_FL		].IndexToRequest = HC_GD_ID_TRACKWIDTH_FL;			
		requests_s[TRACKWIDTH_FR		].IndexToRequest = HC_GD_ID_TRACKWIDTH_FR;			
		requests_s[TRACKWIDTH_RL		].IndexToRequest = HC_GD_ID_TRACKWIDTH_RL;			
		requests_s[TRACKWIDTH_RR		].IndexToRequest = HC_GD_ID_TRACKWIDTH_RR;			
		requests_s[TRACKWIDTH_TARGET_FL	].IndexToRequest = HC_GD_ID_TRACKWIDTH_TARGET_FL;	
		requests_s[TRACKWIDTH_TARGET_FR	].IndexToRequest = HC_GD_ID_TRACKWIDTH_TARGET_FR;	
		requests_s[TRACKWIDTH_TARGET_RL	].IndexToRequest = HC_GD_ID_TRACKWIDTH_TARGET_RL;	
		requests_s[TRACKWIDTH_TARGET_RR	].IndexToRequest = HC_GD_ID_TRACKWIDTH_TARGET_RR;	
		requests_s[TRACK_EXTEND_FL		].IndexToRequest = HC_GD_ID_TRACK_EXTEND_FL;
		requests_s[TRACK_EXTEND_FR		].IndexToRequest = HC_GD_ID_TRACK_EXTEND_FR;		
		requests_s[TRACK_EXTEND_RL		].IndexToRequest = HC_GD_ID_TRACK_EXTEND_RL;		
		requests_s[TRACK_EXTEND_RR		].IndexToRequest = HC_GD_ID_TRACK_EXTEND_RR;		
		requests_s[TRACK_RETRACT_FL		].IndexToRequest = HC_GD_ID_TRACK_RETRACT_FL;		
		requests_s[TRACK_RETRACT_FR		].IndexToRequest = HC_GD_ID_TRACK_RETRACT_FR;		
		requests_s[TRACK_RETRACT_RL		].IndexToRequest = HC_GD_ID_TRACK_RETRACT_RL;		
		requests_s[TRACK_RETRACT_RR		].IndexToRequest = HC_GD_ID_TRACK_RETRACT_RR;		
		requests_s[MACHINE_SPEED		].IndexToRequest = HC_GD_ID_MACHINE_SPEED;			
		requests_s[WHEEL_ANGLE			].IndexToRequest = HC_GD_ID_WHEEL_ANGLE;			
		requests_s[SELECTED_GEAR		].IndexToRequest = HC_GD_ID_SELECTED_GEAR;			
		requests_s[CCO_ENABLE			].IndexToRequest = HC_GD_ID_HYD_CCO_ENABLE;
		requests_s[DRIVE_CAL			].IndexToRequest = HC_GD_ID_DRIVE_HYDRO_CAL_STATE;

		for (i = 0; i < ARRAY_SIZE(IndexList); i++)
		{
			gdLoclist_s[i].index_u16 = IndexList[i];
		}

		gdXImmWrtCalCmd = tmpGdXData_UNAVAL_s;
		gdXImmWrtManOvr = tmpGdXData_UNAVAL_s;

		immWrtCount = 0;
	}

	highClearanceGd::~highClearanceGd()
	{

	}

	void highClearanceGd::getMyLocList(GdLocList_ts* locList[], uint16* count)
	{
		*locList = gdLoclist_s;
		*count = ARRAY_SIZE(IndexList);
	}

	void highClearanceGd::getMyLocListBlk( GdBlkIndex_ts* locList[], uint16* count )
	{
		PARAM_UNUSED( locList[0] );
		PARAM_UNUSED( count );
	}

	void highClearanceGd::getRequestGdList(GdRequests_ts* requestList[], uint16* count)
	{
		*requestList = requests_s;
		*count = NUM_OF_REQUESTS;
	}

	sint16 highClearanceGd::gdBlkIdxRead_s16( uint16 arrayIdx, uint8 * rdData_p, uint16 rdSize )
	{
		PARAM_UNUSED( arrayIdx );
		PARAM_UNUSED( rdData_p );
		PARAM_UNUSED( rdSize );

		return -1;
	}

	sint16 highClearanceGd::gdBlkIdxWrite_s16( uint16 arrayIdx, uint8 * wData_p, uint16 wSize )
	{
		PARAM_UNUSED( arrayIdx );
		PARAM_UNUSED( wData_p );
		PARAM_UNUSED( wSize );

		return -1;
	}

	bool highClearanceGd::getIndexData(uint16 index, GdData_ts *Data_ps)
	{
		boolean Available = TRUE;
	
		if (!Data_ps) //NULL Pointer Check
		{
			return FALSE;
		}
	
		switch (index)
		{
			case GD_ID_HC_TARGET_STATE:
				Data_ps->val_s16 = HighClearance_model_Y.targetState;
				Data_ps->stbit_b = HighClearance_model_Y.controlEnable;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_MACHINE_STATE:
				Data_ps->val_s16 = HighClearance_model_Y.machineState;
				Data_ps->stbit_b = HighClearance_model_Y.controlActive;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_LEG_STATE_FRONTLEFT:
				Data_ps->val_s16 = HighClearance_model_Y.legState.FrontLeft;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_LEG_STATE_FRONTRIGHT:
				Data_ps->val_s16 = HighClearance_model_Y.legState.FrontRight;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_LEG_STATE_REARLEFT:
				Data_ps->val_s16 = HighClearance_model_Y.legState.RearLeft;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_LEG_STATE_REARRIGHT:
				Data_ps->val_s16 = HighClearance_model_Y.legState.RearRight;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_TARGET_CLEARANCE_FL:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.postionTargets.FrontLeft;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_TARGET_CLEARANCE_FR:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.postionTargets.FrontRight;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_TARGET_CLEARANCE_RL:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.postionTargets.RearLeft;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_TARGET_CLEARANCE_RR:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.postionTargets.RearRight;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_ACTUAL_CLEARANCE_FL:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.legClearnace_mm.FrontLeft;
				Data_ps->stbit_b = HighClearance_model_Y.legEnable.FrontLeft;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_Y.heightPosDiagsLatched.FrontLeft );
				if ( HighClearance_model_Y.calState != (uint16)calOKAY_e )
				{
					Data_ps->diag_u8 |= GD_DIAG_CALIB_ERROR;
				}
				if ( HighClearance_model_Y.heightPosDiagsLatched.FrontLeft == 0xFF )
				{
					Data_ps->diag_u8 |= GD_DIAG_PLAUSI;
				}
			break;

			case GD_ID_HC_ACTUAL_CLEARANCE_FR:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.legClearnace_mm.FrontRight;
				Data_ps->stbit_b = HighClearance_model_Y.legEnable.FrontRight;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_Y.heightPosDiagsLatched.FrontRight );
				if ( HighClearance_model_Y.calState != (uint16)calOKAY_e )
				{
					Data_ps->diag_u8 |= GD_DIAG_CALIB_ERROR;
				}
				if ( HighClearance_model_Y.heightPosDiagsLatched.FrontRight == 0xFF )
				{
					Data_ps->diag_u8 |= GD_DIAG_PLAUSI;
				}
			break;

			case GD_ID_HC_ACTUAL_CLEARANCE_RL:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.legClearnace_mm.RearLeft;
				Data_ps->stbit_b = HighClearance_model_Y.legEnable.RearLeft;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_Y.heightPosDiagsLatched.RearLeft );
				if ( HighClearance_model_Y.calState != (uint16)calOKAY_e )
				{
					Data_ps->diag_u8 |= GD_DIAG_CALIB_ERROR;
				}
				if ( HighClearance_model_Y.heightPosDiagsLatched.RearLeft == 0xFF )
				{
					Data_ps->diag_u8 |= GD_DIAG_PLAUSI;
				}
			break;

			case GD_ID_HC_ACTUAL_CLEARANCE_RR:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.legClearnace_mm.RearRight;
				Data_ps->stbit_b = HighClearance_model_Y.legEnable.RearRight;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_Y.heightPosDiagsLatched.RearRight );
				if ( HighClearance_model_Y.calState != (uint16)calOKAY_e )
				{
					Data_ps->diag_u8 |= GD_DIAG_CALIB_ERROR;
				}
				if ( HighClearance_model_Y.heightPosDiagsLatched.RearRight == 0xFF )
				{
					Data_ps->diag_u8 |= GD_DIAG_PLAUSI;
				}
			break;

			case GD_ID_HC_STROKE_LEGNTH_RAW_FL:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.strokeLegnthRaw_mm.FrontLeft;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.heightPosSensors_diag.FrontLeft );
				if ( HighClearance_model_Y.calState != (uint16)calOKAY_e )
				{
					Data_ps->diag_u8 |= GD_DIAG_CALIB_ERROR;
				}
				if ( HighClearance_model_Y.heightPosDiagsLatched.FrontLeft == 0xFF )
				{
					Data_ps->diag_u8 |= GD_DIAG_PLAUSI;
				}
			break;

			case GD_ID_HC_STROKE_LEGNTH_RAW_FR:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.strokeLegnthRaw_mm.FrontRight;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.heightPosSensors_diag.FrontRight );
				if ( HighClearance_model_Y.calState != (uint16)calOKAY_e )
				{
					Data_ps->diag_u8 |= GD_DIAG_CALIB_ERROR;
				}
				if ( HighClearance_model_Y.heightPosDiagsLatched.FrontRight == 0xFF )
				{
					Data_ps->diag_u8 |= GD_DIAG_PLAUSI;
				}
			break;

			case GD_ID_HC_STROKE_LEGNTH_RAW_RL:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.strokeLegnthRaw_mm.RearLeft;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.heightPosSensors_diag.RearLeft );
				if ( HighClearance_model_Y.calState != (uint16)calOKAY_e )
				{
					Data_ps->diag_u8 |= GD_DIAG_CALIB_ERROR;
				}
				if ( HighClearance_model_Y.heightPosDiagsLatched.RearLeft == 0xFF )
				{
					Data_ps->diag_u8 |= GD_DIAG_PLAUSI;
				}
			break;

			case GD_ID_HC_STROKE_LEGNTH_RAW_RR:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.strokeLegnthRaw_mm.RearRight;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.heightPosSensors_diag.RearRight );
				if ( HighClearance_model_Y.calState != (uint16)calOKAY_e )
				{
					Data_ps->diag_u8 |= GD_DIAG_CALIB_ERROR;
				}
				if ( HighClearance_model_Y.heightPosDiagsLatched.RearRight == 0xFF )
				{
					Data_ps->diag_u8 |= GD_DIAG_PLAUSI;
				}
			break;

			case GD_ID_HC_OKAY_TO_TRANSITION:
				Data_ps->val_s16 = ((uint8)HighClearance_model_Y.okayToRaise | ( (uint8)HighClearance_model_Y.okayToLower << 1 ));
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_CYLINDER_PWM_EXTEND_FL:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.coilDutyCycle_pct.extend.FrontLeft;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8(HighClearance_model_U.cylCoilDiags.extend.FrontLeft);
			break;

			case GD_ID_HC_CYLINDER_PWM_EXTEND_FR:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.coilDutyCycle_pct.extend.FrontRight;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8(HighClearance_model_U.cylCoilDiags.extend.FrontRight);
			break;

			case GD_ID_HC_CYLINDER_PWM_EXTEND_RL:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.coilDutyCycle_pct.extend.RearLeft;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8(HighClearance_model_U.cylCoilDiags.extend.RearLeft);
			break;

			case GD_ID_HC_CYLINDER_PWM_EXTEND_RR:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.coilDutyCycle_pct.extend.RearRight;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8(HighClearance_model_U.cylCoilDiags.extend.RearRight);
			break;

			case GD_ID_HC_CYLINDER_PWM_RETRCT_FL:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.coilDutyCycle_pct.retract.FrontLeft;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8(HighClearance_model_U.cylCoilDiags.retract.FrontLeft);
			break;

			case GD_ID_HC_CYLINDER_PWM_RETRCT_FR:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.coilDutyCycle_pct.retract.FrontRight;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8(HighClearance_model_U.cylCoilDiags.retract.FrontRight);
			break;

			case GD_ID_HC_CYLINDER_PWM_RETRCT_RL:
				Data_ps->val_s16 =  (uint16)HighClearance_model_Y.coilDutyCycle_pct.retract.RearLeft;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8(HighClearance_model_U.cylCoilDiags.retract.RearLeft);
			break;

			case GD_ID_HC_CYLINDER_PWM_RETRCT_RR:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.coilDutyCycle_pct.retract.RearRight;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8(HighClearance_model_U.cylCoilDiags.retract.RearRight);
			break;

			case GD_ID_HC_LADDER_EXTEND:
				Data_ps->val_s16 = 0;
				Data_ps->stbit_b = HighClearance_model_Y.extenedLadder;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_REQUEST_CCO_OFF:
				Data_ps->val_s16 = 0;
				Data_ps->stbit_b = HighClearance_model_Y.ccoReqOff;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.ccoEnableDiag );
			break;

			case GD_ID_HC_USER_WARNINGS:
			Data_ps->val_s16 = (
					( (uint8)HighClearance_model_Y.userWarnings.trackWidth		 ) |
					( (uint8)HighClearance_model_Y.userWarnings.speed		<< 1 ) |
					( (uint8)HighClearance_model_Y.userWarnings.guide		<< 2 ) |
					( (uint8)HighClearance_model_Y.userWarnings.was			<< 3 ) |
					( (uint8)HighClearance_model_Y.userWarnings.fws			<< 4 ) |
					( (uint8)HighClearance_model_Y.userWarnings.fieldRoad	<< 5 ) |
					( (uint8)HighClearance_model_Y.userWarnings.cal			<< 6 ) |
					( (uint8)HighClearance_model_Y.userWarnings.parkBrake	<< 7 )
					);
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_MOVEMENT_ERROR_FL:
				Data_ps->val_s16 = (
					( (uint8)HighClearance_model_Y.legErrors.FrontLeft.movementErr1 ) &
					( (uint8)HighClearance_model_Y.legErrors.FrontLeft.movementErr2 << 1 ) &
					( (uint8)HighClearance_model_Y.legErrors.FrontLeft.noMovementErr << 2 )
					);
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_MOVEMENT_ERROR_FR:
				Data_ps->val_s16 = (
					( (uint8)HighClearance_model_Y.legErrors.FrontRight.movementErr1 ) &
					( (uint8)HighClearance_model_Y.legErrors.FrontRight.movementErr2 << 1 ) &
					( (uint8)HighClearance_model_Y.legErrors.FrontRight.noMovementErr << 2 )
					);
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_MOVEMENT_ERROR_RL:
				Data_ps->val_s16 = (
					( (uint8)HighClearance_model_Y.legErrors.RearLeft.movementErr1 ) &
					( (uint8)HighClearance_model_Y.legErrors.RearLeft.movementErr2 << 1 ) &
					( (uint8)HighClearance_model_Y.legErrors.RearLeft.noMovementErr << 2 )
					);
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_MOVEMENT_ERROR_RR:
				Data_ps->val_s16 = (
					( (uint8)HighClearance_model_Y.legErrors.RearRight.movementErr1 ) &
					( (uint8)HighClearance_model_Y.legErrors.RearRight.movementErr2 << 1 ) &
					( (uint8)HighClearance_model_Y.legErrors.RearRight.noMovementErr << 2 )
					);
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_MANUAL_OVERRIDE:
				Data_ps->val_s16 = HighClearance_model_U.manualOverride;
				Data_ps->stbit_b = HighClearance_model_Y.manualOverrideEnable;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_CAL_STATE:
				Data_ps->val_s16 = HighClearance_model_Y.calState;
				Data_ps->stbit_b = HighClearance_model_Y.calOverride;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_CAL_CMD:
				Data_ps->val_s16 = 0;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = GD_DIAG_OK;
			break;

			case GD_ID_HC_SENSOR_RAW_FL:
				Data_ps->val_s16 = (uint16)(HighClearance_model_U.heightPosSensors_mA.FrontLeft * 1000);
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.heightPosSensors_diag.FrontLeft );
			break;

			case GD_ID_HC_SENSOR_RAW_FR:
				Data_ps->val_s16 = (uint16)(HighClearance_model_U.heightPosSensors_mA.FrontRight * 1000);
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.heightPosSensors_diag.FrontRight );
			break;

			case GD_ID_HC_SENSOR_RAW_RL:
				Data_ps->val_s16 = (uint16)(HighClearance_model_U.heightPosSensors_mA.RearLeft * 1000);
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.heightPosSensors_diag.RearLeft );
			break;

			case GD_ID_HC_SENSOR_RAW_RR:
				Data_ps->val_s16 = (uint16)(HighClearance_model_U.heightPosSensors_mA.RearRight * 1000);
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.heightPosSensors_diag.RearRight );
			break;

			case GD_ID_HC_COIL_RAW_EXTEND_FL:
				Data_ps->val_s16 = coilExAmps_FL;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.cylCoilDiags.extend.FrontLeft );
			break;

			case GD_ID_HC_COIL_RAW_RETRCT_FL:
				Data_ps->val_s16 = coilRtAmps_FL;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.cylCoilDiags.retract.FrontLeft );
			break;

			case GD_ID_HC_COIL_RAW_EXTEND_FR:
				Data_ps->val_s16 = coilExAmps_FR;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.cylCoilDiags.extend.FrontRight );
			break;

			case GD_ID_HC_COIL_RAW_RETRCT_FR:
				Data_ps->val_s16 = coilRtAmps_FR;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.cylCoilDiags.retract.FrontRight );
			break;

			case GD_ID_HC_COIL_RAW_EXTEND_RL:
				Data_ps->val_s16 = coilExAmps_RL;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.cylCoilDiags.extend.RearLeft );
			break;

			case GD_ID_HC_COIL_RAW_RETRCT_RL:
				Data_ps->val_s16 = coilRtAmps_RL;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.cylCoilDiags.retract.RearLeft );
			break;

			case GD_ID_HC_COIL_RAW_EXTEND_RR:
				Data_ps->val_s16 = coilExAmps_RR;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.cylCoilDiags.extend.RearRight );
			break;

			case GD_ID_HC_COIL_RAW_RETRCT_RR:
				Data_ps->val_s16 = coilRtAmps_RR;
				Data_ps->stbit_b = FALSE;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.cylCoilDiags.retract.RearRight );
			break;

			case GD_ID_HC_STROKE_LEGNTH_FILTER_FL:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.strokeLegnthFlt_mm.FrontLeft;
				Data_ps->stbit_b = HighClearance_model_P.useSensorFilter;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.heightPosSensors_diag.FrontLeft );
				if ( HighClearance_model_Y.calState != (uint16)calOKAY_e )
				{
					Data_ps->diag_u8 |= GD_DIAG_CALIB_ERROR;
				}
				if ( HighClearance_model_Y.heightPosDiagsLatched.FrontLeft == 0xFF )
				{
					Data_ps->diag_u8 |= GD_DIAG_PLAUSI;
				}
			break;

			case GD_ID_HC_STROKE_LEGNTH_FILTER_FR:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.strokeLegnthFlt_mm.FrontRight;
				Data_ps->stbit_b = HighClearance_model_P.useSensorFilter;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.heightPosSensors_diag.FrontRight );
				if ( HighClearance_model_Y.calState != (uint16)calOKAY_e )
				{
					Data_ps->diag_u8 |= GD_DIAG_CALIB_ERROR;
				}
				if ( HighClearance_model_Y.heightPosDiagsLatched.FrontRight == 0xFF )
				{
					Data_ps->diag_u8 |= GD_DIAG_PLAUSI;
				}
			break;

			case GD_ID_HC_STROKE_LEGNTH_FILTER_RL:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.strokeLegnthFlt_mm.RearLeft;
				Data_ps->stbit_b = HighClearance_model_P.useSensorFilter;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.heightPosSensors_diag.RearLeft );
				if ( HighClearance_model_Y.calState != (uint16)calOKAY_e )
				{
					Data_ps->diag_u8 |= GD_DIAG_CALIB_ERROR;
				}
				if ( HighClearance_model_Y.heightPosDiagsLatched.RearLeft == 0xFF )
				{
					Data_ps->diag_u8 |= GD_DIAG_PLAUSI;
				}
			break;

			case GD_ID_HC_STROKE_LEGNTH_FILTER_RR:
				Data_ps->val_s16 = (uint16)HighClearance_model_Y.strokeLegnthFlt_mm.RearRight;
				Data_ps->stbit_b = HighClearance_model_P.useSensorFilter;
				Data_ps->diag_u8 = translateDiag_u8( HighClearance_model_U.heightPosSensors_diag.RearRight );
				if ( HighClearance_model_Y.calState != (uint16)calOKAY_e )
				{
					Data_ps->diag_u8 |= GD_DIAG_CALIB_ERROR;
				}
				if ( HighClearance_model_Y.heightPosDiagsLatched.RearRight == 0xFF )
				{
					Data_ps->diag_u8 |= GD_DIAG_PLAUSI;
				}
			break;

			default:
				Available = FALSE;
			break;
		}

		return Available;
	}

	void highClearanceGd::signalImmediateWrite(uint16 index, GdData_ts *data_ps, uint8 senderLN)
	{
		PARAM_UNUSED( senderLN );

		immWrtCount += 1;

		switch ( index )
		{
			case GD_ID_HC_CAL_CMD:
				gdXImmWrtCalCmd.data_s = *data_ps;
				gdXImmWrtCalCmd.timestamp_u32 = immWrtCount;
			break;

			case GD_ID_HC_MANUAL_OVERRIDE:
				gdXImmWrtManOvr.data_s = *data_ps;
				gdXImmWrtManOvr.timestamp_u32 = immWrtCount;
			break;

			case GD_ID_HC_ErrorManagement:
				signalEmmGdQuittance( EMM_CLIENT_HC, data_ps );
			break;

		}
	}

	void highClearanceGd::signalHandshake( uint16 index, GdData_ts * data_ps )
	{
		switch ( index )
		{
			case HC_GD_ID_EMM_SIGNAL_HC_ERROR_W:
				signalEmmGdHandshake( EMM_CLIENT_HC, data_ps );
			break;

			default:
			break;
		}
	}

	void highClearanceGd::signalImmediateWriteError( uint16 index )
	{
		switch ( index )
		{
			case HC_GD_ID_EMM_SIGNAL_HC_ERROR_W:
				signalEmmGdWriteError( EMM_CLIENT_HC );
			break;

			default:
			break;
		}
	}

	void highClearanceGd::signalDataResponse(uint16 index, GdData_ts* data_ps)  
	{
		PARAM_UNUSED( data_ps );

		switch ( index )
		{		
			default:
			break;
		}
	}

    void highClearanceGd::step( void )
    {}

	void highClearanceGd::setGdIdAmps( uint16 index, uint32 uAmps )
	{
		switch ( index )
		{
			case GD_ID_HC_COIL_RAW_EXTEND_FL:
				coilExAmps_FL = uAmps / 100;
			break;

			case GD_ID_HC_COIL_RAW_RETRCT_FL:
				coilRtAmps_FL = uAmps / 100;
			break;

			case GD_ID_HC_COIL_RAW_EXTEND_FR:
				coilExAmps_FR = uAmps / 100;
			break;

			case GD_ID_HC_COIL_RAW_RETRCT_FR:
				coilRtAmps_FR = uAmps / 100;
			break;

			case GD_ID_HC_COIL_RAW_EXTEND_RL:
				coilExAmps_RL = uAmps / 100;
			break;

			case GD_ID_HC_COIL_RAW_RETRCT_RL:
				coilRtAmps_RL = uAmps / 100;
			break;

			case GD_ID_HC_COIL_RAW_EXTEND_RR:
				coilExAmps_RR = uAmps / 100;
			break;

			case GD_ID_HC_COIL_RAW_RETRCT_RR:
				coilRtAmps_RR = uAmps / 100;
			break;

			default:
			break;
		}
	}

	GdXRequestData_ts* highClearanceGd::getGdRequestData( GdRequests_te index_e )
	{
		return &requests_s[index_e].RequestData;
	}

	GdXRequestData_ts* highClearanceGd::getImmWrtCalCmd( void )
	{
		return &gdXImmWrtCalCmd;
	}

	GdXRequestData_ts* highClearanceGd::getImmWrtManOvr( void )
	{
		return &gdXImmWrtManOvr;
	}
}
