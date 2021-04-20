#ifndef HIGHCLEARNACE_ENUM_H
	#define HIGHCLEARNACE_ENUM_H

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
		calSTEP5_e			= 0x0005,
		calPAUSED_e			= 0xBB00,
		calABORT_e 			= 0xDD00,
		calDECLINE_e 		= 0xEE00,
		calERROR0_e 		= 0xFF00,	//Error with start conditions
		calERROR1_e 		= 0xFF01,	//Error while moving down
		calERROR2_e 		= 0xFF02,	//Error with down cal values
		calERROR3_e 		= 0xFF03,	//Error while moving up
		calERROR4_e 		= 0xFF04,	//Error with up cal values
		calBAD_e 			= 0xFFFF,	//Bad cal
	} calStates_te;

#endif // HIGHCLEARNACE_ENUM_H
