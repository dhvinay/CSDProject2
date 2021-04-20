#ifndef HIGHCLEARNACE_LOGIC_H
	#define HIGHCLEARNACE_LOGIC_H

extern "C"
{
#include "Eos.h"
#include "HighClearance_model.h"
}

namespace HighClearance
{
	class highClearanceLogic
	{
		public:
			typedef enum
			{
				heightDown_e,
				heightUp_e,
				heightMovingUp_e,
				heightMovingDown_e,
				heightCalibrating_e,
				heightError_e,
				heightUnknown_e,	
			} heightStates_te; 

			typedef enum
			{
				calOKAY_e			= 0x0000,
				calSTART_e 			= 0xCC00,
				calSTEP1_e			= 0x0001,
				calSTEP2_e			= 0x0002,
				calCONFIRM2_e		= 0xCC02,
				calSTEP3_e			= 0x0003,
				calSTEP4_e			= 0x0004,
				calCONFIRM4_e		= 0xCC04,
				calABORT_e 			= 0x00DD,
				calDECLINE_e 		= 0x00EE,
				calERROR0_e 		= 0xFF00,	//Error with start conditions
				calERROR1_e 		= 0xFF01,	//Error while moving down
				calERROR2_e 		= 0xFF02,	//Error with down cal values
				calERROR3_e 		= 0xFF03,	//Error while moving up
				calERROR4_e 		= 0xFF04,	//Error with up cal values
				calBAD_e 			= 0xFFFF,	//Bad cal
			} calStates_te;

		public:
			void resetVariables( void );
			void timeEvent( void );

			//Set functions

			//Get functions

		private:

	};
}

#endif // HIGHCLEARNACE_LOGIC_H
