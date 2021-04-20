#ifndef HIGHCLEARNACE_TASK_H
	#define HIGHCLEARNACE_TASK_H

#include "HighClearance_gd.h"
#include "HighClearance_eeprom.h"

#include "iTask.h"
#include "iTaskRegistrar.h"

extern "C"
{
#include "Project.h"
}

namespace HighClearance
{
	class highClearanceTask : public iTask
	{
		public:
			highClearanceTask();
			virtual ~highClearanceTask();

			void initialize( iTaskRegistrar* reg );
			int getStepTime( void );
			void step( void );
			bool initOk( void );
			void ignitionOffEvent( void );
			void ignitionOnEvent( void );
			bool shutdownOK( void );

		private:
			highClearanceGd m_gdClient;
			highClearanceEeprom m_eeprom;
			bool ignitionOff;
			uint8 shutdownDelayTicks;
			highClearanceEeprom::EepromData_Params_ts EepromData_Params_s;
			highClearanceEeprom::EepromData_Cals_ts EepromData_Cals_s;
			highClearanceEeprom::EepromData_Options_ts EepromData_Options_s;
			bool hasHighClearanceOption;
			sint32 errorHandles[ERR_HC_ERROR_COUNT];

		private:
			void readEeprom( void );
			//void writeEeprom( void );
			//void initErrorHandles( void ); //External EMM, doesn't use handles, just LN and Err Num
			void initLogicParams( void );
			void initPhysicalIO( void );
			void handleLogicInputs( void );
			void handleLogicOutputs( void );			
			void readPhysicalIO( void );
			void readGdClient( void );
			void sendImmWritesToDrive( void );
			void sendImmWritesToMFA( void );
			void updateCalibrationValues( void );
			void handleErrors( void );
			void eosIOErrorHandler( uint8 openCode, uint8 highCode, uint8 lowCode, uint8 diag_e );
			void signalErrors( bool active, sint32 handle );

			uint32 prevMfaUpTimestamp_u32;
			uint32 prevMfaDnTimestamp_u32;
			uint32 prevManOvrTimestamp_u32;
			uint32 prevCalCmdTimestamp_u32;
	};
}

#endif // HIGHCLEARNACE_TASK_H
