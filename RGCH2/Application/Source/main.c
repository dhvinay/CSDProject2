/**
 *  \file   main.c
 *
 *  \brief
 *
 *  Copyright (c) 2014 by AGCO GmbH Marktoberdorf
 */

// --- PxROS include files
#include <pxdef.h>

// --- include files from EOS layer
#include "Eos.h"
#include "Eosmngmt.h"
#include "Eosinit.h"

// --- include files for support libraries
#include "kwp.h"

// --- include files from application
#include "init.h"
#include "flashcrc.h"
#include "Project.h"

// --- defines
#define MAIN_TICK                           10      // periodic timer for state machine in milli seconds
#define LIMIT_ZAEHLER_EXT_WD_INIT_USRMODUL  4       // Max. Zaehlerstand EXT WD damit Appliokation gestartet werden kann
#define FLASH_CRC_CHUNK_SIZE                64      // A larger value doesn't speed up the crc calculation.
#define DELAY_FOR_WAKE_DEBOUNCE_MS          150     // wait until debouncing of wake events is done
#define DELAY_FOR_FREQ_INPUTS_MS            200     // not a good value only for application framework TODO "Not a good value"???
#define ID_DEBUG							0x5FE	// ID used for state machine debug message

#ifdef DEBUG
    #define SYSMEMSIZE_IN_BYTES     70 * 1024           // system memory in bytes
#warning System size 70
#else
    #define SYSMEMSIZE_IN_BYTES     64 * 1024           // system memory in bytes
#warning System size 64
#endif

#define PX_SYSMEM_SECTION       __attribute__ ((section (".bss_dmuram")))       // Can be used to link sysmem to another location

#ifdef PXMON
    #define OBJ_NUMBER      250     // Objects with debugging data are bigger so we have to reduce the number of objects
#else
    #define OBJ_NUMBER      350     // Objects with monitor information are smalle so we can allocate more objects
#endif


//!< states of the application init process
typedef enum
{
    IDLE_NOINIT,                //! initial state
    IDLE_CHECK_EXT_WATCHDOG,    //! wait until the external watchdog has reached a smaller errorlevel than LIMIT_ZAEHLER...
    IDLE_CHECK_ECU,             //! check some things before starting application or just wait some time until something happens
	IDLE_CACHE_NVMEMORYS,		//! wait until whole eep is copied to RAM mirror (EOS)
    IDLE_START_APPLICATION,     //! Initialize application tasks.
    IDLE_APPLICATION_RUNNING,   //! application tasks are running. Now we are the real idle loop.
    IDLE_SHUTDOWN_DELAY,        //! delay until can fifos are empty uso.
    IDLE_ECU_OFF_RESTART        //! shutdown ecu powersupply if Kl.15 if of else do software reset to restart ecu
} IdleTaskStates_e;


// --- static data ---------------------------------------------------------------------------------
static PxAligned_t sysmem[(SYSMEMSIZE_IN_BYTES + sizeof(PxAligned_t) - 1)/sizeof(PxAligned_t)]  PX_SYSMEM_SECTION;

// --- function declarations -----------------------------------------------------------------------
sint32 _main(boolean ramTestFailure_b);

/**
 *  \brief  main function
 *
 *  Entry point from startup code
 *
 *  \param  ramTestFailure_b    TRUE: POST ramtest failed - FALSE: ram ok
 *
 *  \return 0
 */
sint32 _main(boolean ramTestFailure_b)
{
    bool       extWdEnabled_b;
    PxTask_t   idleTaskId_ps;         //  Initialization task ID

    IdleTaskStates_e currIdleTaskState_te = IDLE_NOINIT;     // stores the current state of the idle task
    uint16  idleTimestampExtWdOKmSec_u16 = 0;       // This timestamp is set when the external watchdog error counter
    uint32  shutdownDelayTicks_u32 = 0;             // has reached a value smaller than LIMIT_ZAEHLER_EXT_WD_INIT_USRMODUL.
    uint32  lastEvTick_u32 = 0;                     // timestamp of last state machine run (periodic timer)
    uint32  tick_u32;                               // local copy of current systick counter
    flashCrcAdmin_ts    flashCrc_s;                 // struct which holds the configuration and working values for crc calculation of flash content.
    uint32  errLevelExternalWatchdog_u32;           // Local for storing error level of external watchdog.

    uint32  writeTime_mS_u32;
    uint16  eepState_u16;
    uint8   canMsgData_au8[CAN_DATA_MAX];

	// Start Can controller
	EosCanSetBitrate_s32( CAN_1, CAN_BR_250 );
	EosCanSetBitrate_s32( CAN_2, CAN_BR_250 );
	EosCanSetBitrate_s32( CAN_3, CAN_BR_250 );
	EosCanSetBitrate_s32( CAN_4, CAN_BR_250 );

    PARAM_UNUSED(ramTestFailure_b);

    //  Alle Initialisierungen fuer BOSCH-Core
    EosInitPxrosBegin( &idleTaskId_ps, sysmem, sizeof(sysmem), OBJ_NUMBER );
    EosInitEos_s32();
    EosInitPxrosEnd( idleTaskId_ps );

    // Init checksum calculation over flash content. Checksum calculation can be done regardless from the rest of init process.
    flashCrcInit_v( &flashCrc_s );

    // Ram test is done for EXT and EXT-Light by bootloader. The result is stored in the IRAM struct.
    // Ram test for all other tricore ECUs is done by startup code (EOS).
    #if (defined EXT && !defined SRC36_20_31) || defined EXT_LIGHT
        ramTestFailure_b = kwpGetRamSelftestError_b( );
    #endif

    // Unlock powerlock
    // Core starts with enabled powerlock but we want that ECU turns off if KL15 is off
    // before application tasks are started.
    EosPwrEnDisableKl15AutoShutdown_b( TRUE );
    
    // Get initial tick values for selfmade periodic timers
    lastEvTick_u32 = PxTickGetCount();

    /*
    *   Idle task main loop
    */
    //{
    FOREVER
    {
        // Get current time stamp
        tick_u32 = PxTickGetCount();

        // Handle idle state machine if tick count is reached ( Substitute for PXROS PE )
        if ( (lastEvTick_u32 + MSEC(MAIN_TICK)) <= tick_u32  )
        {
            lastEvTick_u32 = tick_u32;

            /*
             * state machine for idle task
             */
            switch( currIdleTaskState_te )
            {
                case IDLE_NOINIT:
                    // Enable system reset by external Watchdog. The external watchdog should be active before
                    // the application tasks are started.
                    #ifdef PLS_DEBUG
                        #warning "define PLS_DEBUG is set"
                            currIdleTaskState_te = IDLE_CHECK_EXT_WATCHDOG;
                        #else
                        // Enable system reset by external Watchdog. The external watchdog should be active before
                        // any kind of power is applied to outputs. The next state is active with next PE event. This
                        // should give the Cy320_Proc() enough timt to read the external error counter. Proceed only to
                        // next state if enable call was accepted.
                        if( EosEnDisableExtWdReset_b( TRUE ) )
                            currIdleTaskState_te = IDLE_CHECK_EXT_WATCHDOG;
                    #endif // PLS_DEBUG
                    break;

                case IDLE_CHECK_EXT_WATCHDOG:
                    // Go to next state if the error level from external watchdog is below the define LIMIT_ZAEHLER and external Watchdog is enabled!
                    EosExtWDGetErrLevel(&errLevelExternalWatchdog_u32);    // Read the error counter value from a bosch core memory struct.

                    // Tricore cpu watchdog could be enabled because clock to watchdog module is stopped if CPU is halted with JTAG debugger.
                    if( EosCpuWatchdogEnable( ) == 0 )
                    {
                        #ifndef PLS_DEBUG
                            if( !EosGetExtWdResetStatus_b( &extWdEnabled_b )   )        // check enable state of external watchdog
                                extWdEnabled_b = FALSE;
                        #else
                            #warning "define PLS_DEBUG is set"
                            extWdEnabled_b = TRUE;
                        #endif
                    }
                    else
                    {
                        extWdEnabled_b  = FALSE;
                    }

                    if ( (errLevelExternalWatchdog_u32  <=  LIMIT_ZAEHLER_EXT_WD_INIT_USRMODUL) && extWdEnabled_b  )
                    {
						// Reset all diagnostic values influenced by power up sequence.
                        // Errors caused by turned off external powersupplies like 8,5V are
                        // reseted.
#if defined( SRC14_34_31 )
						eosIoDiagResetAll_s32();
#else
						EosInputResetDiags_s32();
#endif

                        // now its possible to turn on external power supplies and main relays
                        EosOutSetSwitch_s32( DOMR_01, TRUE );
                        EosOutSetSwitch_s32( DOMR_02, TRUE );
                        EosOutSetSwitch_s32( DOMR_03, TRUE );
						EosOutSetSwitch_s32( DO_PUDI, TRUE ); //Turn on pullup voltage for digital input DI_09 - DI_16 (DO_PUDI = on)
						EosOutSetSwitch_s32( DOPS_5V, TRUE );
						EosOutSetSwitch_s32( DOPS_8V5, TRUE );

						
						EosOutSetSwitch_s32( SENSOR_ENABLE_PDOH, 1 );

                        // Get timestamp. This timestamp shows when all external powersupplies have been released
                        // by the prewarn signal of the external watchdog. Pure hardware issue.
                        idleTimestampExtWdOKmSec_u16 = tick_u32 + DELAY_FOR_FREQ_INPUTS_MS;

                        // Go to next state.
                        currIdleTaskState_te = IDLE_CHECK_ECU;
                    }
                    break;

                case IDLE_CHECK_ECU:
                    // EXT: The 8.5V sensor power supply enable signal is connected to prewarn signal of external
                    // watchdog. If the error level of external watchdog rises above four the DOPS_8V5 is turned off
                    // and therefore the pullup voltage for frequency inputs. The result are some spurious pulses
                    // which cause a frequency signal that lasts for about 1.3 seconds. This won't happen if the 8.5V
                    // are stable before bosch core pcp init. If we know that the bootloader takes care to jump to
                    // application with an error level of 2 we can skip this delay here. Only EXT is affected.
                    if( idleTimestampExtWdOKmSec_u16 <= tick_u32 )
                    {
                            currIdleTaskState_te = IDLE_CACHE_NVMEMORYS;
                    }
                    break;

				case IDLE_CACHE_NVMEMORYS:
					memset( canMsgData_au8, 0x08, 4 );
					EosCanSend_s32( CAN_1, ID_DEBUG, &canMsgData_au8[0], 4 );
                    if( EosEepromGetState_s32( &eepState_u16 )  == 0 )      // wait until whole eep is copied to RAM mirror (EOS)
                    {
                        if( eepState_u16 == EOSEEP_CACHED )
                        {
                            currIdleTaskState_te = IDLE_START_APPLICATION;
                        }
                    }
					break;

                case IDLE_START_APPLICATION:
                    // Set powerlock as late as possible to reduce time between KL15 power lock
                    // and starting of application tasks.
                    EosPwrEnDisableKl15AutoShutdown_b(FALSE);
                    ignStart();
                    // Start application task and goto state running.
                    initApplicationTasks();
                    currIdleTaskState_te = IDLE_APPLICATION_RUNNING;
					memset(canMsgData_au8, 0x09, 4 );
					EosCanSend_s32( CAN_1, ID_DEBUG, &canMsgData_au8[0], 4);
                    break;

                case IDLE_APPLICATION_RUNNING:
                    // If all tasks has been suspended by ignitions handler we can start the
                    // shutdown sequence.
                    if( EosIgStateOff_b())
                    {
						memset(canMsgData_au8, 0xAA, 4 );
						EosCanSend_s32( CAN_1, ID_DEBUG, &canMsgData_au8[0], 4);

						EosEepromLock_s32 ();
						shutdownDelayTicks_u32 = tick_u32;
                        currIdleTaskState_te = IDLE_SHUTDOWN_DELAY;
                    }
                    break;

                case IDLE_SHUTDOWN_DELAY:
					// If eep is locked we can continue with shutdown.
					if( EosEepromGetState_s32 ( &eepState_u16 ) == EOSEEP_NO_ERROR )
					{
						if( eepState_u16 == EOSEEP_LOCKED )
						{
							//----------- DebugBotschaft ----------------------------------//TODO remove debug for production
							writeTime_mS_u32 = (tick_u32 - shutdownDelayTicks_u32) * PX_MS;
							memset(canMsgData_au8, 0xBB, 4 );
							canMsgData_au8[7] = (uint8)writeTime_mS_u32;
							canMsgData_au8[6] = (uint8)(writeTime_mS_u32>>8);
							canMsgData_au8[5] = (uint8)(writeTime_mS_u32>>16);
							canMsgData_au8[4] = (uint8)(writeTime_mS_u32>>24);
							EosCanSend_s32( CAN_1, ID_DEBUG, &canMsgData_au8[0], 8);
						}
					}				
					
                    // After the shutdown delay the ECU is brought down regardless of eep state and
                    // other things.
                    if( ((shutdownDelayTicks_u32 + MSEC(1000)) < tick_u32 ) || (eepState_u16 == EOSEEP_LOCKED) )
                    {
						memset(canMsgData_au8, 0xCC, 4 );
						EosCanSend_s32( CAN_1, ID_DEBUG, &canMsgData_au8[0], 4);
                        currIdleTaskState_te = IDLE_ECU_OFF_RESTART;
                    }
                    break;

                case IDLE_ECU_OFF_RESTART:
                    // Wait a while until CAN fifo has run empty
                    // Do last settings that are necessary to shutdown ecu.
                    // Enable automatic shutdown again. If Kl.15 is still removed ECU will be turned off.
                    // If Kl.15 was applied again we do a (hard) reset and start again.
					EosPwrEnDisableKl15AutoShutdown_b(TRUE);                    // Wait until ECU is turned off or reseted.
                    EosSystemReset_v( );
                    FOREVER{ }
                    break;

                default:          // We should never reach this point.
                    break;

            }// Idle state machine

        }  // periodic timer

        // Calculate checksum for a chunk of flash data until the end is reached.
        if( flashCrc_s.flashCrcState_e == FLASH_CRC_RUNNING )
        {
            flashCrcChunkCalc_v( &flashCrc_s, FLASH_CRC_CHUNK_SIZE );
        }
    } // FOREVER
    //} Idle task main loop.

    return   0; // just to prevent compiler warning
}
