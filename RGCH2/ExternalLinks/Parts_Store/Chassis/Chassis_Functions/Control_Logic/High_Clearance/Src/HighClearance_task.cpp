#include "HighClearance_task.h"
#include "HighClearance_enum.h"

extern "C"
{
#include "HighClearance_model.h"
#include "Eos.h"
#include "Project.h"
}

namespace HighClearance
{
	highClearanceTask::highClearanceTask()
	{
		ignitionOff				= FALSE;
		prevMfaUpTimestamp_u32  = 0xFFFFFFFF;
		prevMfaDnTimestamp_u32  = 0xFFFFFFFF;
		prevManOvrTimestamp_u32 = 0xFFFFFFFF;
		prevCalCmdTimestamp_u32 = 0xFFFFFFFF;
	}

	highClearanceTask::~highClearanceTask()
	{

	}

	void highClearanceTask::initialize( iTaskRegistrar* reg )
	{
		reg->registerGdApp( GD_LN_HC, &m_gdClient );

		//initErrorHandles();

		initPhysicalIO();

		initLogicParams();
	}

	int highClearanceTask::getStepTime( void )
	{
		return 10;
	}

	void highClearanceTask::step( void )
	{
		handleLogicInputs();

		HighClearance_model_step();		

		handleLogicOutputs();

	}

	bool highClearanceTask::initOk(void)
	{
		readEeprom();

		return hasHighClearanceOption;
	}
	
	void highClearanceTask::ignitionOffEvent( void )
	{
		ignitionOff = TRUE;
	}
	
	void highClearanceTask::ignitionOnEvent( void )
	{
		ignitionOff = FALSE;
		shutdownDelayTicks = 0;

		initLogicParams();

		initPhysicalIO();
	}
	
	bool highClearanceTask::shutdownOK( void )
	{
		if ( shutdownDelayTicks || ignitionOff )
		{
			shutdownDelayTicks++;	//Need to give GD enough time to send final messages before shutdown
		}
		return ( shutdownDelayTicks > 6 );
	}

	void highClearanceTask::readEeprom( void )
	{
		if ( m_eeprom.optionsEepromRead( &EepromData_Options_s ) )
		{
			hasHighClearanceOption = FALSE;

			signalError_s32( EMM_CLIENT_HC, 3, ERR_HC_OPTIONS_EEPROM_FAIL, 0, 0 );
		}
		else
		{
			hasHighClearanceOption = EepromData_Options_s.hasHighClearance;
		}

		if ( hasHighClearanceOption )
		{
			if ( m_eeprom.paramsEepromRead( &EepromData_Params_s ) )
			{
				signalError_s32( EMM_CLIENT_HC, 3, ERR_HC_PARAMS_EEPROM_FAIL, 0, 0 );
			}

			if ( m_eeprom.calsEepromRead( &EepromData_Cals_s ) )
			{
				signalError_s32( EMM_CLIENT_HC, 3, ERR_HC_CALS_EEPROM_FAIL, 0, 0 );
			}
		}
	}
	/* External EMM, doesn't use handles, just LN and Err Num
	void highClearanceTask::initErrorHandles(void)
	{
		uint8 errorIndex;

		for ( errorIndex = 0; errorIndex++; errorIndex < ERR_HC_ERROR_COUNT )
		{
			errorHandles[errorIndex] = getErrorHandle_s32( GD_LN_HC, errorIndex );
		}
	}
	*/
	void highClearanceTask::initLogicParams( void )
	{
		HighClearance_model_P.bangBang_maxOut 					= EepromData_Params_s.bangBang_maxOut;								// [%]    100	
		HighClearance_model_P.baseClearance 					= EepromData_Params_s.baseClearance / 10.0F;						// [mm]   1270	
		HighClearance_model_P.calSensorTolerance 				= EepromData_Params_s.calSensorTolerance / 1000.0F;					// [mA]   0.5	
		HighClearance_model_P.defaultPositionSensor_BrkPnts[0] 	= EepromData_Params_s.defaultPositionSensor_BrkPnts[0] / 1000.0F;	// [mA]   4		
		HighClearance_model_P.defaultPositionSensor_BrkPnts[1] 	= EepromData_Params_s.defaultPositionSensor_BrkPnts[1] / 1000.0F;	// [mA]   20	
		HighClearance_model_P.errDelay							= EepromData_Params_s.errDelay;										// [sec]  3
		HighClearance_model_P.errorMinSpd 						= EepromData_Params_s.errorMinSpd / 10.0F;							// [kph]  1.6	
		HighClearance_model_P.heightControlToleranceStart 		= EepromData_Params_s.heightControlToleranceStart / 10.0F;			// [mm]   4		
		HighClearance_model_P.heightControlToleranceStop 		= EepromData_Params_s.heightControlToleranceStop / 10.0F;			// [mm]   2		
		HighClearance_model_P.heightDiffTolerance 				= EepromData_Params_s.heightDiffTolerance / 10.0F;					// [mm]   26	
		//HighClearance_model_P.maxMedianWheelAngle 				= EepromData_Params_s.maxMedianWheelAngle;							// [deg]  10	
		HighClearance_model_P.maxTransitionMachineSpd 			= EepromData_Params_s.maxTransitionMachineSpd / 10.0F;				// [kph]  8		
		HighClearance_model_P.minDistanceMoving 				= EepromData_Params_s.minDistanceMoving / 10.0F;					// [mm]   1		
		HighClearance_model_P.minTransitionMachineSpd 			= EepromData_Params_s.minTransitionMachineSpd / 10.0F;				// [kph]  0.0
		HighClearance_model_P.movementTimeOut 					= EepromData_Params_s.movementTimeOut;								// [msec] 100	
		HighClearance_model_P.noMovementTimeOut 				= EepromData_Params_s.noMovementTimeOut;							// [msec] 250	
		HighClearance_model_P.positionSensor_tblData[0] 		= EepromData_Params_s.positionSensor_tblData[0] / 10.0F;			// [mm]   0		
		HighClearance_model_P.positionSensor_tblData[1] 		= EepromData_Params_s.positionSensor_tblData[1] / 10.0F;			// [mm]   500	
		HighClearance_model_P.trackWidthMax 					= EepromData_Params_s.trackWidthMax / 10.0F;						// [mm]   3657.6
		HighClearance_model_P.trackWidthMin 					= EepromData_Params_s.trackWidthMin / 10.0F;						// [mm]   3048	
		HighClearance_model_P.trackWidthTolerance 				= EepromData_Params_s.trackWidthTolerance / 10.0F;					// [mm]   6		
		HighClearance_model_P.calSettlingTime 					= EepromData_Params_s.calSettlingTime;								// [msec] 4000	
		HighClearance_model_P.calStepTimeOut 					= EepromData_Params_s.calStepTimeOut;								// [sec]  120	
		HighClearance_model_P.legMovingTimeout 					= EepromData_Params_s.legMovingTimeout;								// [msec] 1000
		HighClearance_model_P.sensorCutOffHz					= EepromData_Params_s.sensorCutOffHz / 1000.0F;						// [hz]   0.032
		HighClearance_model_P.ctrlWarningTime					= EepromData_Params_s.ctrlWarningTime / 1000.0F;					// [sec]  5
		HighClearance_model_P.heightTolerance					= EepromData_Params_s.heightTolerance / 10.0F;						// [mm]   4
		HighClearance_model_P.heightToleranceRoad				= EepromData_Params_s.heightToleranceRoad / 10.0F;					// [mm]   8
		HighClearance_model_P.plausiDistance					= EepromData_Params_s.plausiDistance / 10.0F;						// [mm]   5

		if ( EepromData_Params_s.sensorCutOffHz == 0 )
		{
			HighClearance_model_P.useSensorFilter = FALSE;
		}
		else
		{
			HighClearance_model_P.useSensorFilter = EepromData_Options_s.useSensorFilter;											// [bool] 0
		}
		

		HighClearance_model_P.positionSensorFL_BrkPnts[0] 		= EepromData_Cals_s.positionSensorFL_BrkPnts[0] / 1000.0;			// [mA]   4	
		HighClearance_model_P.positionSensorFL_BrkPnts[1] 		= EepromData_Cals_s.positionSensorFL_BrkPnts[1] / 1000.0;			// [mA]   20	
		HighClearance_model_P.positionSensorFR_BrkPnts[0] 		= EepromData_Cals_s.positionSensorFR_BrkPnts[0] / 1000.0;			// [mA]   4		
		HighClearance_model_P.positionSensorFR_BrkPnts[1] 		= EepromData_Cals_s.positionSensorFR_BrkPnts[1] / 1000.0;			// [mA]   20	
		HighClearance_model_P.positionSensorRL_BrkPnts[0] 		= EepromData_Cals_s.positionSensorRL_BrkPnts[0] / 1000.0;			// [mA]   4		
		HighClearance_model_P.positionSensorRL_BrkPnts[1] 		= EepromData_Cals_s.positionSensorRL_BrkPnts[1] / 1000.0;			// [mA]   20	
		HighClearance_model_P.positionSensorRR_BrkPnts[0] 		= EepromData_Cals_s.positionSensorRR_BrkPnts[0] / 1000.0;			// [mA]   4		
		HighClearance_model_P.positionSensorRR_BrkPnts[1] 		= EepromData_Cals_s.positionSensorRR_BrkPnts[1] / 1000.0;			// [mA]   20	

		HighClearance_model_initialize();
	}

	void highClearanceTask::initPhysicalIO( void )
	{
		EosOutPara_ts eosOutPara_s;
		eosOutPara_s.Pwfreq_Hz_u16		 = 100;      
		eosOutPara_s.PwOffs_u16			 = STD_PWM_DIAG_OFFSET;         
		eosOutPara_s.ResistMin_mOhm_u32	 = STD_MIN_RESISTOR_PWM_mOHM; 
		eosOutPara_s.ResistMax_mOhm_u32	 = STD_MAX_RESISTOR_PWM_mOHM; 
		eosOutPara_s.CurrentMax_uA_u32	 = STD_MAX_CURRENT_PWM_uA;  
		eosOutPara_s.Filtertime_MSek_u32 = STD_ERROR_TIME_PWM_MS;
		eosOutPara_s.SCD_Max_cnt_u16	 = STD_MAX_CNT_SCD;    

		EosOutSetPara_s32( HC_EXTEND_FL_POH, &eosOutPara_s );
		EosOutSetPara_s32( HC_EXTEND_FR_POH, &eosOutPara_s );
		EosOutSetPara_s32( HC_EXTEND_RL_POH, &eosOutPara_s );
		EosOutSetPara_s32( HC_EXTEND_RR_POH, &eosOutPara_s );
		EosOutSetPara_s32( HC_RETRACT_FL_POH, &eosOutPara_s );
		EosOutSetPara_s32( HC_RETRACT_FR_POH, &eosOutPara_s );
		EosOutSetPara_s32( HC_RETRACT_RL_POH, &eosOutPara_s );
		EosOutSetPara_s32( HC_RETRACT_RR_POH, &eosOutPara_s );

		//EosOutSetPara_s32( LADDER_EXTENTION_PDOH, &eosOutPara_s );

	}

	void highClearanceTask::handleLogicInputs( void )
	{
		readPhysicalIO();

		readGdClient();
	}

	void highClearanceTask::readPhysicalIO( void )
	{
		EosOutStatus_ts eosOutStatus_s;
		EosAiStatus_ts eosAiStatus_s;

		EosOutGetSt_s32( HC_EXTEND_FL_POH, &eosOutStatus_s );
		m_gdClient.setGdIdAmps( GD_ID_HC_COIL_RAW_EXTEND_FL, eosOutStatus_s.i_uA_s32 );
		HighClearance_model_U.cylCoilDiags.extend.FrontLeft = eosOutStatus_s.diag_e;

		EosOutGetSt_s32( HC_EXTEND_FR_POH, &eosOutStatus_s );
		m_gdClient.setGdIdAmps( GD_ID_HC_COIL_RAW_EXTEND_FR, eosOutStatus_s.i_uA_s32 );
		HighClearance_model_U.cylCoilDiags.extend.FrontRight = eosOutStatus_s.diag_e;

		EosOutGetSt_s32( HC_EXTEND_RL_POH, &eosOutStatus_s );
		m_gdClient.setGdIdAmps( GD_ID_HC_COIL_RAW_EXTEND_RL, eosOutStatus_s.i_uA_s32 );
		HighClearance_model_U.cylCoilDiags.extend.RearLeft = eosOutStatus_s.diag_e;

		EosOutGetSt_s32( HC_EXTEND_RR_POH, &eosOutStatus_s );
		m_gdClient.setGdIdAmps( GD_ID_HC_COIL_RAW_EXTEND_RR, eosOutStatus_s.i_uA_s32 );
		HighClearance_model_U.cylCoilDiags.extend.RearRight = eosOutStatus_s.diag_e;

		EosOutGetSt_s32( HC_RETRACT_FL_POH, &eosOutStatus_s );
		m_gdClient.setGdIdAmps( GD_ID_HC_COIL_RAW_RETRCT_FL, eosOutStatus_s.i_uA_s32 );
		HighClearance_model_U.cylCoilDiags.retract.FrontLeft = eosOutStatus_s.diag_e;

		EosOutGetSt_s32( HC_RETRACT_FR_POH, &eosOutStatus_s );
		m_gdClient.setGdIdAmps( GD_ID_HC_COIL_RAW_RETRCT_FR, eosOutStatus_s.i_uA_s32 );
		HighClearance_model_U.cylCoilDiags.retract.FrontRight = eosOutStatus_s.diag_e;

		EosOutGetSt_s32( HC_RETRACT_RL_POH, &eosOutStatus_s );
		m_gdClient.setGdIdAmps( GD_ID_HC_COIL_RAW_RETRCT_RL, eosOutStatus_s.i_uA_s32 );
		HighClearance_model_U.cylCoilDiags.retract.RearLeft = eosOutStatus_s.diag_e;

		EosOutGetSt_s32( HC_RETRACT_RR_POH, &eosOutStatus_s );
		m_gdClient.setGdIdAmps( GD_ID_HC_COIL_RAW_RETRCT_RR, eosOutStatus_s.i_uA_s32 );
		HighClearance_model_U.cylCoilDiags.retract.RearRight = eosOutStatus_s.diag_e;

		EosAiGetSt_s32( HC_POSITION_SENSOR_FL_CI, &eosAiStatus_s );
		HighClearance_model_U.heightPosSensors_mA.FrontLeft	  = eosAiStatus_s.curr_uA_u32 * 0.001;
		HighClearance_model_U.heightPosSensors_diag.FrontLeft = eosAiStatus_s.diag_e;

		EosAiGetSt_s32( HC_POSITION_SENSOR_FR_CI, &eosAiStatus_s );
		HighClearance_model_U.heightPosSensors_mA.FrontRight   = eosAiStatus_s.curr_uA_u32 * 0.001;
		HighClearance_model_U.heightPosSensors_diag.FrontRight = eosAiStatus_s.diag_e;

		EosAiGetSt_s32( HC_POSITION_SENSOR_RL_CI, &eosAiStatus_s );
		HighClearance_model_U.heightPosSensors_mA.RearLeft	 = eosAiStatus_s.curr_uA_u32 * 0.001;
		HighClearance_model_U.heightPosSensors_diag.RearLeft = eosAiStatus_s.diag_e;

		EosAiGetSt_s32( HC_POSITION_SENSOR_RR_CI, &eosAiStatus_s );
		HighClearance_model_U.heightPosSensors_mA.RearRight	  = eosAiStatus_s.curr_uA_u32 * 0.001;
		HighClearance_model_U.heightPosSensors_diag.RearRight = eosAiStatus_s.diag_e;
	}

	void highClearanceTask::readGdClient( void )
	{
		HighClearance_model_U.mfa.isAlive = gdIsAlive_b( GD_LN_HC_MFA );

		if ( m_gdClient.getImmWrtCalCmd()->data_s.diag_u8 == GD_DIAG_OK )
		{
			if ( m_gdClient.getImmWrtCalCmd()->timestamp_u32 != prevCalCmdTimestamp_u32 )
			{
				prevCalCmdTimestamp_u32 = m_gdClient.getImmWrtCalCmd()->timestamp_u32;
				HighClearance_model_U.calCmd = m_gdClient.getImmWrtCalCmd()->data_s.val_s16;
			}
		}

		if ( m_gdClient.getGdRequestData( m_gdClient.MFA_UP_BUTTON )->data_s.diag_u8 == GD_DIAG_OK )
		{
			HighClearance_model_U.mfa.upBtn = m_gdClient.getGdRequestData( m_gdClient.MFA_UP_BUTTON )->data_s.stbit_b;

			if( m_gdClient.getGdRequestData( m_gdClient.MFA_UP_BUTTON )->timestamp_u32 != prevMfaUpTimestamp_u32)
			{
				prevMfaUpTimestamp_u32 = m_gdClient.getGdRequestData( m_gdClient.MFA_UP_BUTTON )->timestamp_u32;
				HighClearance_model_U.manualOverride = 0;
			}			
		}

		HighClearance_model_U.mfa.downDiag = m_gdClient.getGdRequestData( m_gdClient.MFA_DOWN_BUTTON )->data_s.diag_u8;
		if ( m_gdClient.getGdRequestData( m_gdClient.MFA_DOWN_BUTTON )->data_s.diag_u8 == GD_DIAG_OK )
		{
			HighClearance_model_U.mfa.downBtn = m_gdClient.getGdRequestData( m_gdClient.MFA_DOWN_BUTTON )->data_s.stbit_b;

			if ( m_gdClient.getGdRequestData( m_gdClient.MFA_DOWN_BUTTON )->timestamp_u32 != prevMfaDnTimestamp_u32 )
			{
				prevMfaDnTimestamp_u32 = m_gdClient.getGdRequestData( m_gdClient.MFA_DOWN_BUTTON )->timestamp_u32;
				HighClearance_model_U.manualOverride = 0;
			}
		}

		if ( m_gdClient.getGdRequestData( m_gdClient.MFA_STOP_BUTTON )->data_s.diag_u8 == GD_DIAG_OK )
		{
			HighClearance_model_U.mfa.stopBtn = m_gdClient.getGdRequestData( m_gdClient.MFA_STOP_BUTTON )->data_s.stbit_b;
			if ( HighClearance_model_U.mfa.stopBtn )
			{
				HighClearance_model_U.calCmd = calABORT_e;
			}
		}

		if ( m_gdClient.getGdRequestData( m_gdClient.DRIVE_CAL )->data_s.diag_u8 == GD_DIAG_OK )
		{
			if ( m_gdClient.getGdRequestData( m_gdClient.DRIVE_CAL )->data_s.val_s16 != 0 ||
				 m_gdClient.getGdRequestData( m_gdClient.DRIVE_CAL )->data_s.val_s16 != 5 )
			{
				HighClearance_model_U.driveCalActive = TRUE;
			}
			else
			{
				HighClearance_model_U.driveCalActive = FALSE;
			}			
		}

		if ( m_gdClient.getGdRequestData( m_gdClient.EOI )->data_s.diag_u8 == GD_DIAG_OK )
		{
			if ( m_gdClient.getGdRequestData( m_gdClient.EOI )->data_s.val_s16 == 4 )
			{
				HighClearance_model_U.engRunning = TRUE;
			}
			else
			{
				HighClearance_model_U.engRunning = FALSE;
			}
		}

		if ( m_gdClient.getGdRequestData( m_gdClient.ROAD_FIELD_MODE )->data_s.diag_u8 == GD_DIAG_OK )
		{
			if ( m_gdClient.getGdRequestData( m_gdClient.ROAD_FIELD_MODE )->data_s.stbit_b == 0 )
			{
				HighClearance_model_U.fieldModeActive = TRUE;
			}
			else
			{
				HighClearance_model_U.fieldModeActive = FALSE;
			}
		}
		
		if ( m_gdClient.getGdRequestData( m_gdClient.MACHINE_SPEED )->data_s.diag_u8 == GD_DIAG_OK )
		{
			HighClearance_model_U.machineSpeedKph = (m_gdClient.getGdRequestData( m_gdClient.MACHINE_SPEED )->data_s.val_s16 * 0.0036 ); //mmps * 0.0036 = kph
		}

		if ( m_gdClient.getGdRequestData( m_gdClient.WHEEL_ANGLE )->data_s.diag_u8 == GD_DIAG_OK )
		{
			HighClearance_model_U.medianWheelAngle = m_gdClient.getGdRequestData( m_gdClient.WHEEL_ANGLE )->data_s.val_s16 / 100.0F;
		}
		else
		{
			HighClearance_model_U.medianWheelAngle = 0;
		}

		if ( m_gdClient.getGdRequestData( m_gdClient.SELECTED_GEAR )->data_s.diag_u8 == GD_DIAG_OK )
		{
			HighClearance_model_U.selectedGear = m_gdClient.getGdRequestData( m_gdClient.SELECTED_GEAR )->data_s.val_s16;
		}

		if ( m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_FL )->data_s.diag_u8 == GD_DIAG_OK )
		{
			HighClearance_model_U.actualTrackWidth_mm.FrontLeft = m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_FL )->data_s.val_s16;
		}

		if ( m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_FR )->data_s.diag_u8 == GD_DIAG_OK )
		{
			HighClearance_model_U.actualTrackWidth_mm.FrontRight = m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_FR )->data_s.val_s16;
		}

		if ( m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_RL )->data_s.diag_u8 == GD_DIAG_OK )
		{
			HighClearance_model_U.actualTrackWidth_mm.RearLeft = m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_RL )->data_s.val_s16;
		}

		if ( m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_RR )->data_s.diag_u8 == GD_DIAG_OK )
		{
			HighClearance_model_U.actualTrackWidth_mm.RearRight = m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_RR )->data_s.val_s16;
		}

		if ( m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_TARGET_FL )->data_s.diag_u8 == GD_DIAG_OK )
		{
			HighClearance_model_U.targetTrackWidth_mm.FrontLeft = m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_TARGET_FL )->data_s.val_s16;
		}

		if ( m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_TARGET_FR )->data_s.diag_u8 == GD_DIAG_OK )
		{
			HighClearance_model_U.targetTrackWidth_mm.FrontRight = m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_TARGET_FR )->data_s.val_s16;
		}

		if ( m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_TARGET_RL )->data_s.diag_u8 == GD_DIAG_OK )
		{
			HighClearance_model_U.targetTrackWidth_mm.RearLeft = m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_TARGET_RL )->data_s.val_s16;
		}

		if ( m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_TARGET_RR )->data_s.diag_u8 == GD_DIAG_OK )
		{
			HighClearance_model_U.targetTrackWidth_mm.RearRight = m_gdClient.getGdRequestData( m_gdClient.TRACKWIDTH_TARGET_RR )->data_s.val_s16;
		}

		HighClearance_model_U.ccoEnableDiag = translateGdDiag_u8( m_gdClient.getGdRequestData( m_gdClient.CCO_ENABLE )->data_s.diag_u8 );

		HighClearance_model_U.trackCylCoilDiags.extend.FrontLeft = translateGdDiag_u8( m_gdClient.getGdRequestData( m_gdClient.TRACK_EXTEND_FL )->data_s.diag_u8 );
		HighClearance_model_U.trackCylCoilDiags.extend.FrontRight = translateGdDiag_u8( m_gdClient.getGdRequestData( m_gdClient.TRACK_EXTEND_FR )->data_s.diag_u8 );
		HighClearance_model_U.trackCylCoilDiags.extend.RearLeft = translateGdDiag_u8( m_gdClient.getGdRequestData( m_gdClient.TRACK_EXTEND_RL )->data_s.diag_u8 );
		HighClearance_model_U.trackCylCoilDiags.extend.RearRight = translateGdDiag_u8( m_gdClient.getGdRequestData( m_gdClient.TRACK_EXTEND_RR )->data_s.diag_u8 );

		HighClearance_model_U.trackCylCoilDiags.retract.FrontLeft = translateGdDiag_u8( m_gdClient.getGdRequestData( m_gdClient.TRACK_RETRACT_FL )->data_s.diag_u8 );
		HighClearance_model_U.trackCylCoilDiags.retract.FrontRight = translateGdDiag_u8( m_gdClient.getGdRequestData( m_gdClient.TRACK_RETRACT_FR )->data_s.diag_u8 );
		HighClearance_model_U.trackCylCoilDiags.retract.RearLeft = translateGdDiag_u8( m_gdClient.getGdRequestData( m_gdClient.TRACK_RETRACT_RL )->data_s.diag_u8 );
		HighClearance_model_U.trackCylCoilDiags.retract.RearRight = translateGdDiag_u8( m_gdClient.getGdRequestData( m_gdClient.TRACK_RETRACT_RR )->data_s.diag_u8 );

		if ( m_gdClient.getImmWrtManOvr()->data_s.diag_u8 == GD_DIAG_OK )
		{
			if ( m_gdClient.getImmWrtManOvr()->timestamp_u32 != prevManOvrTimestamp_u32 )
			{
				prevManOvrTimestamp_u32 = m_gdClient.getImmWrtManOvr()->timestamp_u32;
				HighClearance_model_U.manualOverride = m_gdClient.getImmWrtManOvr()->data_s.val_s16;
			}
		}

	}

	void highClearanceTask::handleLogicOutputs( void )
	{
		sint16 dutyCycle;

		HighClearance_model_U.calCmd = 0; //clear input

		//EosOutSetSwitch_s32( LADDER_EXTENTION_PDOH, HighClearance_model_Y.extenedLadder );

		dutyCycle = EOSOUT_MAX_PW_RESOLUTION * (sint16)( HighClearance_model_Y.coilDutyCycle_pct.extend.FrontLeft / 100.0 );
		EosOutSetPw_s32( HC_EXTEND_FL_POH, dutyCycle );

		dutyCycle = EOSOUT_MAX_PW_RESOLUTION * (sint16)( HighClearance_model_Y.coilDutyCycle_pct.extend.FrontRight / 100.0 );
		EosOutSetPw_s32( HC_EXTEND_FR_POH, dutyCycle );

		dutyCycle = EOSOUT_MAX_PW_RESOLUTION * (sint16)( HighClearance_model_Y.coilDutyCycle_pct.extend.RearLeft / 100.0 );
		EosOutSetPw_s32( HC_EXTEND_RL_POH, dutyCycle );

		dutyCycle = EOSOUT_MAX_PW_RESOLUTION * (sint16)( HighClearance_model_Y.coilDutyCycle_pct.extend.RearRight / 100.0 );
		EosOutSetPw_s32( HC_EXTEND_RR_POH, dutyCycle );

		dutyCycle = EOSOUT_MAX_PW_RESOLUTION * (sint16)( HighClearance_model_Y.coilDutyCycle_pct.retract.FrontLeft / 100.0 );
		EosOutSetPw_s32( HC_RETRACT_FL_POH, dutyCycle );

		dutyCycle = EOSOUT_MAX_PW_RESOLUTION * (sint16)( HighClearance_model_Y.coilDutyCycle_pct.retract.FrontRight / 100.0 );
		EosOutSetPw_s32( HC_RETRACT_FR_POH, dutyCycle );

		dutyCycle = EOSOUT_MAX_PW_RESOLUTION * (sint16)( HighClearance_model_Y.coilDutyCycle_pct.retract.RearLeft / 100.0 );
		EosOutSetPw_s32( HC_RETRACT_RL_POH, dutyCycle );

		dutyCycle = EOSOUT_MAX_PW_RESOLUTION * (sint16)( HighClearance_model_Y.coilDutyCycle_pct.retract.RearRight / 100.0 );
		EosOutSetPw_s32( HC_RETRACT_RR_POH, dutyCycle );

		sendImmWritesToDrive();

		sendImmWritesToMFA();

		updateCalibrationValues();

		handleErrors();
	}

	void highClearanceTask::sendImmWritesToDrive( void )
	{
		static sint32 sendError = -1;
		static boolean prev_ccoReqOff;

		if ( gdIsAlive_b( GD_LN_HC_DRIVE ) )
		{
			if ( (sendError != 0) || (HighClearance_model_Y.ccoReqOff != prev_ccoReqOff) )
			{
				prev_ccoReqOff = HighClearance_model_Y.ccoReqOff;
				sendError = gdSendImmediateWrite_s32( GD_LN_HC, HC_GD_ID_HYD_CCO_REQ_OFF, FALSE, 0, prev_ccoReqOff, GD_DIAG_OK );
			}
		}
		else
		{
			sendError = -1;
		}
		
	}

	void highClearanceTask::sendImmWritesToMFA( void )
	{
		static sint32 sendError = -1;
		static uint8 prev_ledUpCmd;
		static uint8 prev_ledDownCmd;

		if ( gdIsAlive_b( GD_LN_HC_MFA ) )
		{
			if ( sendError != 0 ||
				 HighClearance_model_Y.mfaLeds.upBtn != prev_ledUpCmd ||
				 HighClearance_model_Y.mfaLeds.downBtn != prev_ledDownCmd
				 )
			{
				sendError = 0;
				prev_ledUpCmd = HighClearance_model_Y.mfaLeds.upBtn;
				prev_ledDownCmd = HighClearance_model_Y.mfaLeds.downBtn;

				sendError |= gdSendImmediateWrite_s32( GD_LN_HC, HC_GD_ID_MFA_UP_BUTTON_LED, FALSE, prev_ledUpCmd, 0, GD_DIAG_OK );
				sendError |= gdSendImmediateWrite_s32( GD_LN_HC, HC_GD_ID_MFA_DOWN_BUTTON_LED, FALSE, prev_ledDownCmd, 0, GD_DIAG_OK );
			}
		}
		else
		{
			sendError = -1;
		}		
	}

	void highClearanceTask::updateCalibrationValues( void )
	{
		static uint8 eepromWriteCounter = 0;

		if ( HighClearance_model_Y.calState == calSTEP5_e )
		{
			EepromData_Cals_s.positionSensorFL_BrkPnts[0] = (uint16)(1000 * HighClearance_model_Y.calValues.retract.FrontLeft);
			EepromData_Cals_s.positionSensorFL_BrkPnts[1] = (uint16)(1000 * HighClearance_model_Y.calValues.extend.FrontLeft);
			EepromData_Cals_s.positionSensorFR_BrkPnts[0] = (uint16)(1000 * HighClearance_model_Y.calValues.retract.FrontRight);
			EepromData_Cals_s.positionSensorFR_BrkPnts[1] = (uint16)(1000 * HighClearance_model_Y.calValues.extend.FrontRight);
			EepromData_Cals_s.positionSensorRL_BrkPnts[0] = (uint16)(1000 * HighClearance_model_Y.calValues.retract.RearLeft);
			EepromData_Cals_s.positionSensorRL_BrkPnts[1] = (uint16)(1000 * HighClearance_model_Y.calValues.extend.RearLeft);
			EepromData_Cals_s.positionSensorRR_BrkPnts[0] = (uint16)(1000 * HighClearance_model_Y.calValues.retract.RearRight);
			EepromData_Cals_s.positionSensorRR_BrkPnts[1] = (uint16)(1000 * HighClearance_model_Y.calValues.extend.RearRight);

			HighClearance_model_P.positionSensorFL_BrkPnts[0] = EepromData_Cals_s.positionSensorFL_BrkPnts[0] / 1000.0;
			HighClearance_model_P.positionSensorFL_BrkPnts[1] = EepromData_Cals_s.positionSensorFL_BrkPnts[1] / 1000.0;
			HighClearance_model_P.positionSensorFR_BrkPnts[0] = EepromData_Cals_s.positionSensorFR_BrkPnts[0] / 1000.0;
			HighClearance_model_P.positionSensorFR_BrkPnts[1] = EepromData_Cals_s.positionSensorFR_BrkPnts[1] / 1000.0;
			HighClearance_model_P.positionSensorRL_BrkPnts[0] = EepromData_Cals_s.positionSensorRL_BrkPnts[0] / 1000.0;
			HighClearance_model_P.positionSensorRL_BrkPnts[1] = EepromData_Cals_s.positionSensorRL_BrkPnts[1] / 1000.0;
			HighClearance_model_P.positionSensorRR_BrkPnts[0] = EepromData_Cals_s.positionSensorRR_BrkPnts[0] / 1000.0;
			HighClearance_model_P.positionSensorRR_BrkPnts[1] = EepromData_Cals_s.positionSensorRR_BrkPnts[1] / 1000.0;

			if ( eepromWriteCounter == 0 )
			{
				m_eeprom.calsEepromWrite( &EepromData_Cals_s );
				eepromWriteCounter++;
			}
		}
		else
		{
			eepromWriteCounter = 0;
		}
	}

	void highClearanceTask::handleErrors( void )
	{
		//Position Sensors
		eosIOErrorHandler( ERR_HC_SENSOR_FL_OPEN, ERR_HC_SENSOR_FL_HIGH, ERR_HC_SENSOR_FL_LOW,
						   HighClearance_model_Y.heightPosDiagsLatched.FrontLeft );
		eosIOErrorHandler( ERR_HC_SENSOR_FR_OPEN, ERR_HC_SENSOR_FR_HIGH, ERR_HC_SENSOR_FR_LOW,
						   HighClearance_model_Y.heightPosDiagsLatched.FrontRight );
		eosIOErrorHandler( ERR_HC_SENSOR_RL_OPEN, ERR_HC_SENSOR_RL_HIGH, ERR_HC_SENSOR_RL_LOW,
						   HighClearance_model_Y.heightPosDiagsLatched.RearLeft );
		eosIOErrorHandler( ERR_HC_SENSOR_RR_OPEN, ERR_HC_SENSOR_RR_HIGH, ERR_HC_SENSOR_RR_LOW,
						   HighClearance_model_Y.heightPosDiagsLatched.RearRight );
		//Retract Coils
		eosIOErrorHandler( ERR_HC_RETRACT_COIL_FL_OPEN, ERR_HC_RETRACT_COIL_FL_HIGH, ERR_HC_RETRACT_COIL_FL_LOW,
						   HighClearance_model_Y.cylCoilDiagsLatched.retract.FrontLeft );
		eosIOErrorHandler( ERR_HC_RETRACT_COIL_FR_OPEN, ERR_HC_RETRACT_COIL_FR_HIGH, ERR_HC_RETRACT_COIL_FR_LOW,
						   HighClearance_model_Y.cylCoilDiagsLatched.retract.FrontRight );
		eosIOErrorHandler( ERR_HC_RETRACT_COIL_RL_OPEN, ERR_HC_RETRACT_COIL_RL_HIGH, ERR_HC_RETRACT_COIL_RL_LOW,
						   HighClearance_model_Y.cylCoilDiagsLatched.retract.RearLeft );
		eosIOErrorHandler( ERR_HC_RETRACT_COIL_RR_OPEN, ERR_HC_RETRACT_COIL_RR_HIGH, ERR_HC_RETRACT_COIL_RR_LOW,
						   HighClearance_model_Y.cylCoilDiagsLatched.retract.RearRight );
		//Extend Coils
		eosIOErrorHandler( ERR_HC_EXTEND_COIL_FL_OPEN, ERR_HC_EXTEND_COIL_FL_HIGH, ERR_HC_EXTEND_COIL_FL_LOW,
						   HighClearance_model_Y.cylCoilDiagsLatched.extend.FrontLeft );
		eosIOErrorHandler( ERR_HC_EXTEND_COIL_FR_OPEN, ERR_HC_EXTEND_COIL_FR_HIGH, ERR_HC_EXTEND_COIL_FR_LOW,
						   HighClearance_model_Y.cylCoilDiagsLatched.extend.FrontRight );
		eosIOErrorHandler( ERR_HC_EXTEND_COIL_RL_OPEN, ERR_HC_EXTEND_COIL_RL_HIGH, ERR_HC_EXTEND_COIL_RL_LOW,
						   HighClearance_model_Y.cylCoilDiagsLatched.extend.RearLeft );
		eosIOErrorHandler( ERR_HC_EXTEND_COIL_RR_OPEN, ERR_HC_EXTEND_COIL_RR_HIGH, ERR_HC_EXTEND_COIL_RR_LOW,
						   HighClearance_model_Y.cylCoilDiagsLatched.extend.RearRight );
		//Movement Errors
		signalErrors( HighClearance_model_Y.legErrors.FrontLeft.movementErr1 ||
					  HighClearance_model_Y.legErrors.FrontLeft.movementErr2, ERR_HC_FL_MOVEMENT );
		signalErrors( HighClearance_model_Y.legErrors.FrontLeft.noMovementErr, ERR_HC_FL_NO_MOVEMENT );
		signalErrors( HighClearance_model_Y.legErrors.FrontRight.movementErr1 ||
					  HighClearance_model_Y.legErrors.FrontRight.movementErr2, ERR_HC_FR_MOVEMENT );
		signalErrors( HighClearance_model_Y.legErrors.FrontRight.noMovementErr, ERR_HC_FR_NO_MOVEMENT );
		signalErrors( HighClearance_model_Y.legErrors.RearLeft.movementErr1 ||
					  HighClearance_model_Y.legErrors.RearLeft.movementErr2, ERR_HC_RL_MOVEMENT );
		signalErrors( HighClearance_model_Y.legErrors.RearLeft.noMovementErr, ERR_HC_RL_NO_MOVEMENT );
		signalErrors( HighClearance_model_Y.legErrors.RearRight.movementErr1 ||
					  HighClearance_model_Y.legErrors.RearRight.movementErr2, ERR_HC_RR_MOVEMENT );
		signalErrors( HighClearance_model_Y.legErrors.RearRight.noMovementErr, ERR_HC_RR_NOMOVEMENT );

		//Position Plausibitly Errors
		signalErrors( HighClearance_model_Y.heightPosDiagsLatched.FrontLeft,	ERR_HC_SENSOR_PLAUSI_FL );
		signalErrors( HighClearance_model_Y.heightPosDiagsLatched.FrontRight,	ERR_HC_SENSOR_PLAUSI_FR );
		signalErrors( HighClearance_model_Y.heightPosDiagsLatched.RearLeft,		ERR_HC_SENSOR_PLAUSI_RL );
		signalErrors( HighClearance_model_Y.heightPosDiagsLatched.RearRight,	ERR_HC_SENSOR_PLAUSI_RR );

		//Warnings
		signalErrors( HighClearance_model_Y.userWarnings.trackWidth, ERR_HC_WARNING_TRACKWIDTH );
		signalErrors( HighClearance_model_Y.userWarnings.speed, ERR_HC_WARNING_SPEED );
		signalErrors( HighClearance_model_Y.userWarnings.guide, ERR_HC_WARNING_GUIDANCE );
		signalErrors( HighClearance_model_Y.userWarnings.was, ERR_HC_WARNING_WAS );
		signalErrors( HighClearance_model_Y.userWarnings.fws, ERR_HC_WARNING_FWS );
		signalErrors( HighClearance_model_Y.userWarnings.fieldRoad, ERR_HC_WARNING_ROAD );
		signalErrors( HighClearance_model_Y.userWarnings.cal, ERR_HC_WARNING_CAL );
		signalErrors( HighClearance_model_Y.userWarnings.parkBrake, ERR_HC_WARNING_PARKBRAKE );
		signalErrors( HighClearance_model_Y.controlWarnings.track.FrontLeft, ERR_HC_WARNING_TOLERANCE_TA_FL );
		signalErrors( HighClearance_model_Y.controlWarnings.track.FrontRight, ERR_HC_WARNING_TOLERANCE_TA_FR );
		signalErrors( HighClearance_model_Y.controlWarnings.track.RearLeft, ERR_HC_WARNING_TOLERANCE_TA_RL );
		signalErrors( HighClearance_model_Y.controlWarnings.track.RearRight, ERR_HC_WARNING_TOLERANCE_TA_RR );
		signalErrors( HighClearance_model_Y.controlWarnings.height.FrontLeft, ERR_HC_WARNING_TOLERANCE_HC_FL );
		signalErrors( HighClearance_model_Y.controlWarnings.height.FrontRight, ERR_HC_WARNING_TOLERANCE_HC_FR );
		signalErrors( HighClearance_model_Y.controlWarnings.height.RearLeft, ERR_HC_WARNING_TOLERANCE_HC_RL );
		signalErrors( HighClearance_model_Y.controlWarnings.height.RearRight, ERR_HC_WARNING_TOLERANCE_HC_RR );
	}

	void highClearanceTask::eosIOErrorHandler( uint8 openCode, uint8 highCode , uint8 lowCode, uint8 diag_e )
	{
		if ( ( diag_e != IOD_OK ) && ( diag_e != 0xFF ) )
		{
			if ( ( diag_e & IOD_Open ) == IOD_Open )
			{
				signalErrors( TRUE, openCode );
			}
			else if ( ( diag_e & IOD_ScHigh ) == IOD_ScHigh )
			{
				signalErrors( TRUE, highCode );
			}
			else if ( ( diag_e & IOD_ScGnd ) == IOD_ScGnd )
			{
				signalErrors( TRUE, lowCode );
			}
		}
		else
		{
			signalErrors( FALSE, openCode );
			signalErrors( FALSE, highCode );
			signalErrors( FALSE, lowCode );
		}
	}

	void highClearanceTask::signalErrors( bool active, sint32 handle )
	{
		//uint8 myHandleLocal = handle;
		if ( active && !isErrorActive_b( EMM_CLIENT_HC, handle ) )
		{
			signalError_s32( EMM_CLIENT_HC, 3, handle, 0, 0 );
		}
		else if ( !active && isErrorActive_b( EMM_CLIENT_HC, handle ) && isErrorQuitted_b( EMM_CLIENT_HC, handle ) )
		{
			signalError_s32( EMM_CLIENT_HC, FALSE, handle, 0, 0 );
		}
	}
}
