#ifndef __HIGH_CLEARANCE_EEPROM_H
	#define __HIGH_CLEARANCE_EEPROM_H

extern "C"
{
#include "Eos.h" //For types
}

namespace HighClearance
{
	class highClearanceEeprom
	{
		public:
			typedef struct
			{
//EEPROM_HIGH_CLEARANCE_PARAMS_START
				uint16 bangBang_maxOut;                 		// [%]		Percent for fully ON
				uint16 baseClearance;                   		// [0.1mm]	Machine clearance when down
				uint16 calSensorTolerance;              		// [uA]		How close cal values must be to default values
				uint16 defaultPositionSensor_BrkPnts[2];		// [uA]		Default sensor values for down and up
				uint16 errorMinSpd;                     		// [0.1kph]	Alternative min speed required to transition when in error/cal state (>)	
				uint8  heightControlToleranceStart;          	// [0.1mm]	Min error needed to start closed loop height control. Should be greater than stop 	
				uint8  heightControlToleranceStop;          	// [0.1mm]	Max error needed to stop closed loop height control. Should be less than start
				uint16 heightDiffTolerance;             		// [0.1mm]	Max difference allowed between highest and lowest leg while transitioning
				uint16 maxMedianWheelAngle;             		// [deg]	Max median wheel angle allowed while transitioning
				uint16 maxTransitionMachineSpd;         		// [0.1kph]	Max speed allowed during transition (<=)
				uint16 minDistanceMoving;               		// [0.1mm]	Min distance traveled for leg to be considered moving
				uint16 minTransitionMachineSpd;         		// [0.1kph]	Normal condition min speed required for transition (>=)
				uint16 movementTimeOut;                 		// [msec]	Error time out for when no leg movemnet is commanded but it is moving
				uint16 noMovementTimeOut;               		// [msec]	Error time out for when leg movement is commanded but it is not moving
				uint16 positionSensor_tblData[2];       		// [0.1mm]	Min/Max stroke length
				uint16 trackWidthMax;                   		// [0.1mm]	Max trackWidth when raised/transitioning
				uint16 trackWidthMin;                   		// [0.1mm]	Min trackWidth
				uint16 trackWidthTolerance;             		// [0.1mm]	How close actual track width must stay to expect to keep leg transitioning
				uint16 calSettlingTime;                 		// [msec]	Time all legs must be in position before advancing
				uint16 calStepTimeOut;                  		// [sec]	Time transtioning steps have before erroring out 
				uint16 legMovingTimeout;                		// [msec]	Unknown state time out for when leg is transitioning but has not moved "minDistanceMoving"
				uint16 sensorCutOffHz;							// [mHz]	Cutoff frequency for postion sensor filter
				uint16 ctrlWarningTime;							// [msec]	Time control must be paused for while waiting for track or height tolerances to issue warning
				uint16 heightTolerance;          				// [0.1mm]	Tolerance to be concidered fully up/down while in field mode/drive calibration
				uint16 heightToleranceRoad;          			// [0.1mm]	Tolerance to be concidered fully up/down while in road mode
				uint8  errDelay;								// [sec]    Time delay before checking for I/O errors
				uint8  plausiDistance;							// [0.1mm]	Minimum distance leg must move in 30ms to not be a plausible change

				uint16	checksum;								//checksum
//EEPROM_HIGH_CLEARANCE_PARAMS_END
			}
#ifdef __GNUC__
__attribute__( ( __packed__ ) ) 
#endif
				EepromData_Params_ts, *EepromData_Params_pts;

			typedef struct
			{
//EEPROM_HIGH_CLEARANCE_OPTIONS_START
				uint8   hasHighClearance;							//[bool] High clearance option enabled, True/False
				boolean useSensorFilter;							//[bool] Position sensor filter enabled, True/False

				uint16	checksum;								//checksum
//EEPROM_HIGH_CLEARANCE_OPTIONS_END
			}
#ifdef __GNUC__
__attribute__( ( __packed__ ) ) 
#endif
				EepromData_Options_ts, *EepromData_Options_pts;

			typedef struct
			{
//EEPROM_HIGH_CLEARANCE_CALS_START
				uint16 positionSensorFL_BrkPnts[2];     		// [uA] Front Left postion sensor values for down [0] and up [1]
				uint16 positionSensorFR_BrkPnts[2];     		// [uA] Front Right postion sensor values for down [0] and up [1]
				uint16 positionSensorRL_BrkPnts[2];     		// [uA] Rear Left postion sensor values for down [0] and up [1]
				uint16 positionSensorRR_BrkPnts[2];     		// [uA] Rear Right postion sensor values for down [0] and up [1]

				uint16	checksum;								//checksum
//EEPROM_HIGH_CLEARANCE_CALS_END
			}
#ifdef __GNUC__
__attribute__( ( __packed__ ) ) 
#endif
				EepromData_Cals_ts, *EepromData_Cals_pts;

		public:
			sint32	paramsEepromRead( EepromData_Params_pts EepromData_Params_ps );
			//sint32	paramsEepromWrite( EepromData_Params_pts EepromData_Params_ps );

			sint32	optionsEepromRead( EepromData_Options_pts EepromData_Options_ps );
			sint32	optionsEepromWrite( EepromData_Options_pts EepromData_Options_ps );

			sint32	calsEepromRead( EepromData_Cals_pts EepromData_Cals_ps );
			sint32	calsEepromWrite( EepromData_Cals_pts EepromData_Cals_ps );
	};
}

#endif // __HIGH_CLEARANCE_EEPROM_H
