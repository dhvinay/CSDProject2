/**
 *  @file   init.c
 */

#include "eos.h"
#include "kwp.h"
#include "gd.h"
#include "gdblk.h"
#include "gd_mirror.h"
#include "stdtask.h"

#include "init.h"
// Project specific header
#include "Project.h"

#include "..\..\ExternalLinks\Parts_Store\Chassis\Chassis_Functions\Control_Logic\External_Error_Handler\Src\Eemm_Task.h"
#include "TaskManager.h"

// specify the size of response / request tables. These values limit the amount of active requests / responses
#define NUMBER_MAX_RESPONSE_ENTRIES  455
#define NUMBER_MAX_REQUEST_ENTRIES   170

#define GD_MIRROR_ENTRIES_RAM		10
#define GD_MIRROR_ENTRIES_EEPROM	10
//#define GD_MIRROR_EEPROM_ADRESS		EEPR_GD_MIRROR_INDEXLIST
#define GD_MIRROR_DEFAULT_IN_ID		0x7A0
#define GD_MIRROR_DEFAULT_OUT_ID	0x7A2
#define GD_MIRROR_DEFAULT_CAN_NO	0x00

#define DEFAULT_AI_SHORT_LOW_MV 100
#define DEFAULT_AI_SHORT_HIGH_MV 7900

// here, the size of the uint32-array is calculated, needed for GDs request/response-tables
#define GD_SIZEOF_MEMORYARRAY 	SIZEOF_RESP_REQ_TABLE_ENTRY * (NUMBER_MAX_REQUEST_ENTRIES + NUMBER_MAX_RESPONSE_ENTRIES) / sizeof(uint32)

static void myErrorMessageFunc (PxMessageClass_t class, PxError_t err, ...);

static void initIO( void );

static uint32 blkTrfMem_au32[( ( 2 * 1024 ) + sizeof( PxAligned_t ) - 1 ) / sizeof( PxAligned_t )] __attribute__( ( asection( ".bss_ext_ram", "f=aw" ) ) );

/* GD needs memory for the request/response-tables. This memory is reserved here (as an uint32-array).
 * The size of the array is depending on the number of entries to be hold in GD.  */
#ifdef ALLOCATE_VAR_TO_DMU_SRAM
#pragma section .bss_dmuram aw
#endif
	static uint32 gdRequestResponseTable_au32[GD_SIZEOF_MEMORYARRAY];
#ifdef ALLOCATE_VAR_TO_DMU_SRAM
#pragma section
#endif


	// for GD mirroring
#pragma section .bss_ext_ram aw
	static gdMirrorEntry_ts gdMirrorEntries_as[(GD_MIRROR_ENTRIES_EEPROM + GD_MIRROR_ENTRIES_RAM)];
#pragma section
static gdMirrorManagement_ts gdMirrorManagement_s;

/**
 *  Initialise the application tasks.
 */
void initApplicationTasks (void)
{
    PxCtrl(PXCtrlSetMessageFun, &myErrorMessageFunc);

	// init gd task
	{
		GdInit_ts GdInit_s;

		uint8 i_u8;
		for ( i_u8 = 0; i_u8 < 64; i_u8++ )
		{
			GdInit_s.rootingData_au8[i_u8] = 0xFF;
		}

		GdInit_s.rootingData_au8[GD_LN_ES] 			            = GD_PN_CHS;
		GdInit_s.rootingData_au8[GD_LN_NT01] 				    = GD_PN_NT01;
		GdInit_s.rootingData_au8[GD_LN_MFA] 				    = GD_PN_MFA;
		GdInit_s.rootingData_au8[GD_LN_DRIVE] 		            = GD_PN_CHS;
		GdInit_s.rootingData_au8[GD_LN_TI]			            = GD_PN_CHS;
		GdInit_s.rootingData_au8[GD_LN_TELEM]				    = GD_PN_VD03;
		GdInit_s.rootingData_au8[GD_LN_ZE] 		                = GD_PN_ZE;
		GdInit_s.rootingData_au8[GD_LN_LCP]						= GD_PN_LCP;
		GdInit_s.rootingData_au8[GD_LN_INFO] 					= GD_PN_CHS;
		GdInit_s.rootingData_au8[GD_LN_SCT]				 		= GD_PN_CHS;
		GdInit_s.rootingData_au8[GD_LN_WBZ] 					= GD_PN_CHS;
		GdInit_s.rootingData_au8[GD_LN_SBL]						= GD_PN_CHS;
		GdInit_s.rootingData_au8[GD_LN_TA] 			            = GD_PN_CHS;
		GdInit_s.rootingData_au8[GD_LN_EMM] 					= GD_PN_CHS;
		GdInit_s.rootingData_au8[GD_LN_CEAG]	 			    = GD_PN_VD03;
		GdInit_s.rootingData_au8[GD_LN_PICTO]	 		        = GD_PN_CHS;
		GdInit_s.rootingData_au8[GD_LN_EFC]	 		            = GD_PN_CHS;
		GdInit_s.rootingData_au8[GD_LN_HC]	 					= GD_PN_CHS2;
		GdInit_s.rootingData_au8[GD_LN_4WS]	 					= GD_PN_CHS;
		GdInit_s.rootingData_au8[GD_LN_DASH]					= GD_PN_DASH;
		GdInit_s.rootingData_au8[GD_LN_ACM]	 					= GD_PN_ACM;

		GdInit_s.aliveTime_u16 = 200;
		GdInit_s.diagInterval_u8 = 0;

		GdInit_s.ecuNumber_u8 = GD_PN_CHS2; // physical node number
		GdInit_s.canNode_u8 = CAN_GD;

		GdInit_s.entriesRequestTable_u16 = NUMBER_MAX_REQUEST_ENTRIES;		// tell GD how many request-entries my request-table has
        GdInit_s.entriesResponseTable_u16 = NUMBER_MAX_RESPONSE_ENTRIES;
        GdInit_s.gdRequestResponseTable_p = gdRequestResponseTable_au32;	// give GD an allocated memory for these tables
        GdInit_s.sizeOfRequestResponseTable_u32 = sizeof(gdRequestResponseTable_au32);	// tell GD the overall size of the allocated memory (in bytes)
		GdInit_s.ptrToMirrorStruct_ps = (void*)&gdMirrorManagement_s;
		GdInit_s.keepAliveDetectionOnAfterKl15off_b = TRUE;

		gdBlkInitTask_s32( &GdInit_s, &blkTrfMem_au32[0], sizeof( blkTrfMem_au32 ) );
	}

	    // start diagnostic task
    {
        KwpInit_ts KwpInit_s;
        sint32 err_s32;

        // Set KWP ID
        #ifdef SRC9_34
            KwpInit_s.addr_u8 = 0x1D;
            KwpInit_s.type_u8 = KWP_ECU_TYPE_EXTLT;
        #elif defined SRC36_20_30
            KwpInit_s.addr_u8 = 0x1E;
            KwpInit_s.type_u8 = KWP_ECU_TYPE_EXT;
        #elif defined SRC36_20_31
            KwpInit_s.addr_u8 = 0x1E;
            KwpInit_s.type_u8 = KWP_ECU_TYPE_SRC36_20_31;
		#elif defined SRC14_34_31
            KwpInit_s.addr_u8 = 0x1D;
            KwpInit_s.type_u8 = KWP_ECU_TYPE_SRC14_34_31;
        #else
            #error Unknown ECU. Add configuration for KWP task.
        #endif

	 
       err_s32 = EosEepromRead_s32(EEP_ADDR_KWP_HW_VERSION, &KwpInit_s.hwVersion_au8[0], KWP_HW_VERSION_MAX);
       if (err_s32 != 0)
       {
           PxBzero(&KwpInit_s.hwVersion_au8[0], KWP_HW_VERSION_MAX);
       }
	 
       err_s32 = EosEepromRead_s32(EEP_ADDR_KWP_HW_NUMBER, &KwpInit_s.hwNumber_au8[0], KWP_AGCO_ORDNUM_HDR_STRING_LENGTH);
       if (err_s32 != 0)
       {
           PxBzero(&KwpInit_s.hwNumber_au8[0], KWP_AGCO_ORDNUM_HDR_STRING_LENGTH);
       }

        kwpInitTask_s32(&KwpInit_s);
    }

	eosDfiStartAll_s32();

	initIO();

	// start application tasks
	//GD Task is priority 2
	//NOTE EMM task must be started first to catch init errors in other tasks!!
	initEmmTask();			//prio 6,  100ms
	initTaskManager();		//C++ inits

}


static void myErrorMessageFunc (PxMessageClass_t class, PxError_t err, ...)
{
////////////////////////////////////
	uint8  canMsgData_au8[3];

	canMsgData_au8[0] = class;
	canMsgData_au8[1] = (err >> 8);
	canMsgData_au8[2] = (err);

	// Here it’s possible to send a CAN message….
	EosCanSend_Hnd_b(CAN_1, 0x504, (uint8*)canMsgData_au8, sizeof(canMsgData_au8));
////////////////////////////////////////////

    if( class == PXFatal)
    {
		while (1);
		PxPanic();
    }
}

static void initIO( void )
{
	//EosViConfig_ts viConfig_s;
	//
	//EosAiReadConfig_s32( WHEEL_ANGLE_FRONT_AI, &viConfig_s );
	//viConfig_s.diagLowBorder_mV_s32 = DEFAULT_AI_SHORT_LOW_MV;
	//viConfig_s.diagUpperBorder_mV_s32 = DEFAULT_AI_SHORT_HIGH_MV;
	//EosAiSetConfig_s32( WHEEL_ANGLE_FRONT_AI, &viConfig_s );

}

