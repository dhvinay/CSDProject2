/**
 *  @file       gd.h
 *
 *  @brief      Access to GENERIC DRIVER (GD).
 *
 *
 *  @section    History
 *
 *  2009-07-03 / werner.unsinn@xfendt.de
 *  - erstellt
 *
 *  2010-06-07 / Christian.Pischulti@xfendt.de
 *  - New parameter canNode_u8 for config struct GdInit_ts.
 *  - Parameter ecuNumber_u8 extended with segment number (strang).
 *    Unused upper four bits are used to tell gd the segment number.
 *
 *  2012-07-05 / werner.unsinn@agcocorp.com
 *  - Funktion zur Abfrage des Diagnosestatus (GD) [PB-3971]
 *  - Typedefs fuer Pointer auf Strukturen entfernt
 *
 *  2012-10-12 / werner.unsinn@agcocorp.com
 *  - Diagnosestatus um "Tabellen voll Index" erweitert [PB-3423]
 *
 *  2013-02-15 / werner.unsinn@agcocorp.com
 *  - Define GD_DIAG_DISABLED fuer nicht verfuegbaren Index definiert
 *
 *  2013-07-23 / mattis.kornelius.euroeng@agcocorp.com
 *  - [PB-6278] prepared code for message envelope
 *
 *  2013-10-01 / rainer.eberhardt@agcocorp.com
 *  - comments translated to English
 *
 *  2014-01-24 / werner.unsinn@agcocorp.com
 *  - Funktionen fuer ECRR Requests mit absoluter Hysterese hinzugefuegt [PB-6108]
 *
 *  2014-01-28 / mattis.kornelius.auroeng@agcocorp.com
 *  - [PB-7043] added envelope identifier for blocktransfer
 *
 * 	2015-05-04 / florian.koppers.ruecker@agcocorp.com
 *	- [BUG-6223] elimate local definition of req/resp-variables.
 *
 *	2015-10-09 / mattis.kornelius@agcocorp.com
 *	- [PB-10478] replaced FreeRTOS by OsWrapper.
 *	  Replaced bool by boolean.
 *
 *  2015-12-17 / florian.koppers.ruecker@agcocorp.com
 *  - [PB-11396] added parameter in init structure for GD-mirroring.
 *  2016-03-04 / florian.koppers.ruecker@agcocorp.com					    
 *  - [PB-12063] change in alive detection, behavior after Kl15 off can  
 *     be influenced by added init variable          					
 *
 *  2016-04-12 / mattis.kornelius@agcocorp.com
 *  - [Misc] changed MSG_ENV_TYPE_GD from 0x31 to 0x41 (for message envelope/header).
 */

#ifndef __GD_H
#define __GD_H

//Note: Define message type Id according to this table:
// 0x01 - 0x1F: RTOS specific
// 0x20 - 0x3F: EOS
// 0x40 - 0x4F: Services (common libs like KWP, GD.. )
// 0x50 - 0x9F: application tasks
// 0xAF - 0xFF: reserved for future use
/// MSG envelope type
#define MSG_ENV_TYPE_GD     0x41

#ifdef RTOS_PXROS
    #define SIZEOF_RESP_REQ_TABLE_ENTRY 24	// number of bytes, one entry in response / request table uses
#else
    #define SIZEOF_RESP_REQ_TABLE_ENTRY 28  // there is an additional queue pointer needed in AL2GD struct
#endif

/// Identifier for Envelope
typedef enum
{                                           // message envelope identifier for
    MSG_ENV_SUBTYPE_GD_INIT,                // configuration message at startup
    MSG_ENV_SUBTYPE_GD_LOGONOFF,            // logon or logoff message
    MSG_ENV_SUBTYPE_GD_REQUEST,             // request a GD-ID
    MSG_ENV_SUBTYPE_GD_RESPONSE,            // send a response to GD-Task
    MSG_ENV_SUBTYPE_GD_INDEXNEWDATA,        // send a response to GD-Task
    MSG_ENV_SUBTYPE_GD_REQUIREMENT,         // GD-Task send a requirement to appl-task
    MSG_ENV_SUBTYPE_GD_BLOCKTRANSFER        // request / serve a gd-blocktransfer
}  MsgEnvSubGD_te;


// Data structure for GD
typedef struct
{
    sint16  val_s16;                ///< Data bytes (discrete value)
    boolean stbit_b;                ///< Status bit (Status of/off)
    uint8   diag_u8;                ///< Diagnostic byte
} GdData_ts;


///> Initialisation structure for GD
/* Further explanation to members of struct GdInit_ts:
 *
 * gdRequestResponseTable_p must point to a memory-location where enough memory is reserved for the request/response-tables of GD.
 *                          You just provide GD an array of uint32-fields of the right size. Don't touch that memory! It is used by GD internally.
 *                          To calculate the size of array: (number of requests + number of responses) * SIZEOF_RESP_REQ_TABLE_ENTRY / sizeof(uint32)
 *                          								(note: SIZEOF_RESP_REQ_TABLE_ENTRY is the size in bytes of the internal used management-structure)
 *
 * sizeOfRequestResponseTable_u32 provides GD an information how long the reserved memory is. Should be filled by sizeof()-function.
 *
 * entriesResponseTable_u16 / entriesRequestTable_u16: How many requests/responses your GD has to handle at the same time
 */
typedef struct
{
    uint8   rootingData_au8[64];            ///< Routing table
    uint8   ecuNumber_u8;                   ///< (( segment << 4 ) | phy. node number )
    uint16  aliveTime_u16;                  ///< Time for alive messages
    uint8   diagInterval_u8;                ///< Activate the diagnostic
    uint8   canNode_u8;                     ///< CAN node of ECU which is used for GD ( 0 - CAN_1, 1 - CAN_2, ... )
    uint16  entriesResponseTable_u16;  		///< how many entries the response table has
    uint16  entriesRequestTable_u16;   		///< how many entries the request table has
    uint32  *gdRequestResponseTable_p;	  	///< pointer to reserved memory for GDs request/response-table
    uint32  sizeOfRequestResponseTable_u32; ///< size in bytes of reserved memory (where gdRequestResponseTable_p points to)
    uint8 	*ptrToMirrorStruct_ps;     	    ///< pointer to GD mirror structure (allocated and filled outside)
    bool keepAliveDetectionOnAfterKl15off_b; ///< should alive detection keep on working after Kl15 off (set TRUE), else last state is freezed (FALSE)
#ifndef RTOS_PXROS
    osQueue_t answQueue_t;          ///< Answer queue of calling task (will be filled automatically // reqsyn mechanism)
#endif
} GdInit_ts;


// Diagnostic status for GD
typedef struct
{
    uint16  numReqEntries_u16;      ///< Number of items in the request table
    uint16  maxReqEntries_u16;      ///< maximum number of items in the request table
    uint16  idxReqEntries_u16;      ///< Index where the request table was full
    uint16  numRespEntries_u16;     ///< Number of items in the response table
    uint16  maxRespEntries_u16;     ///< maximum number of items in the response table
    uint16  idxRespEntries_u16;     ///< Index where the response table was full
} GdDiagStatus_ts;


/**
 *  @brief Initialize the GD task.
 *
 *  @param init_ps      Pointer to initialization structure
 *  @return             0 if init was successful, -1 or -2 if init failed due to intern reasons,
 *                      -4 if pointer gdRequestResponseTable_p in init-struct is null-pointer,  > 0 if reserved memory at gdRequestResponseTable_p is too small (responding the minimum size)
 */
sint32 gdInitTask_s32 (GdInit_ts *init_ps);

/**
 *  @brief Initialize the GD for a single participant.
 *
 *  @param tn_u8        Own participant number
 *  @param response_mbx Mailbox to receive requests from other GD participants
 *  @param request_mbx  Mailbox to receive answers of previous requests
 *  @return             0 if initialization was successful transmitted
 */
sint32 gdInit_s32 (uint8 tn_u8, PxMbx_t response_mbx, PxMbx_t request_mbx);

/**
 *  @brief Send registration to GD
 *
 *  @param tn_u8        Own participant number
 *  @return             0 if registration was successful transmitted
 */
sint32 gdLogon_s32 (uint8 tn_u8);

/**
 *  @brief Send deregistration to GD.
 *
 *  @param tn_u8        Own participant number
 *  @return             0 if deregistration was successful transmitted
 */
sint32 gdLogoff_s32 (uint8 tn_u8);

/**
 *  @brief Returns the information if the participant is still alive.
 *
 *  @param tn_u8        Number of the participant
 *  @return             TRUE if the participant is still alive, otherwise FALSE
 */
boolean gdIsAlive_b (uint8 tn_u8);


/**
 *  @brief Send a SRR Request.
 *
 *  @param tn_u8        Own participant number
 *  @param index_u16    Index of the request
 *  @param hs_b         Flag for handshake
 *  @return             0 if the request was successful transmitted
 */
sint32 gdSendRequestSRR_s32 (uint8 tn_u8, uint16 index_u16, boolean hs_b);

/**
 *  @brief Send an ECRR Request with relativ hysteresis.
 *
 *  @param tn_u8                Own participant number
 *  @param index_u16            Index of the request
 *  @param hs_b                 Flag for handshake
 *  @param hysteresisUp_u16     Upper hysteresis for event control
 *  @param hysteresisDown_u16   Lower hysteresis for event control
 *  @return                     0 if the request was successful transmitted
 */
sint32 gdSendRequestECRR_s32 (uint8 tn_u8, uint16 index_u16, boolean hs_b, uint16 hysteresisUp_u16, uint16 hysteresisDown_u16);

/**
 *  @brief Send an ECRR Request with absolut hysteresis.
 *
 *  @param tn_u8                Own participant number
 *  @param index_u16            Index of the request
 *  @param hs_b                 Flag for handshake
 *  @param hysteresisUp_u16     Upper hysteresis for event control
 *  @param hysteresisDown_u16   Lower hysteresis for event control
 *  @return                     0 if the request was successful transmitted
 */
sint32 gdSendRequestAbsECRR_s32 (uint8 tn_u8, uint16 index_u16, boolean hs_b, uint16 hysteresisUp_u16, uint16 hysteresisDown_u16);

/**
 *  @brief Send an AECRR Request with relativ hysteresis.
 *
 *  @param tn_u8                Own participant number
 *  @param index_u16            Index of the request
 *  @param period_u16           cycle time
 *  @param hysteresisUp_u16     Upper hysteresis for event control
 *  @param hysteresisDown_u16   Lower hysteresis for event control
 *  @return                     0 if the request was successful transmitted
 */
sint32 gdSendRequestAECRR_s32 (uint8 tn_u8, uint16 index_u16, uint16 period_u16, uint16 hysteresisUp_u16, uint16 hysteresisDown_u16);

/**
 *  @brief Send an AECRR Request with absolut hysteresis.
 *
 *  @param tn_u8                Own participant number
 *  @param index_u16            Index of the request
 *  @param period_u16           cycle time
 *  @param hysteresisUp_u16     Upper hysteresis for event control
 *  @param hysteresisDown_u16   Lower hysteresis for event control
 *  @return                     0 if the request was successful transmitted
 */
sint32 gdSendRequestAbsAECRR_s32 (uint8 tn_u8, uint16 index_u16, uint16 period_u16, uint16 hysteresisUp_u16, uint16 hysteresisDown_u16);

/**
 *  @brief Send a TCRR Request.
 *
 *  @param tn_u8        Own participant number
 *  @param index_u16    Index of the request
 *  @param period_u16   cycle time
 *  @return             0 if the request was successful transmitted
 */
sint32 gdSendRequestTCRR_s32 (uint8 tn_u8, uint16 index_u16, uint16 period_u16);

/**
 *  @brief Cancel a request.
 *
 *  @param tn_u8        Own participant number
 *  @param index_u16    Index of the request to be canceled
 *  @return             0 if the cancelation was successful transmitted
 */
sint32 gdKillRequest_s32 (uint8 tn_u8, uint16 index_u16);

/**
 *  @brief Cancel all requests.
 *
 *  @param tn_u8        Own participant number
 *  @return             0 if the cancelation was successful transmitted
 */
sint32 gdKillAllRequests_s32    (uint8 tn_u8);

/**
 *  @brief Send an immediate write.
 *
 *  @param tn_u8        Own participant number
 *  @param index_u16    Index to do the immediate write
 *  @param hs_b         Flag for handshake
 *  @param data_s16     Data bytes
 *  @param stbit_b      Status bit
 *  @param diag_u8      Diagnostic bytes
 *  @return             0 if the immediate write was successful transmitted
 */
sint32 gdSendImmediateWrite_s32 (uint8 tn_u8, uint16 index_u16, boolean hs_b, sint16 data_s16, boolean stbit_b, uint8 diag_u8);



#define GD_DIAG_OK              0x00u  // FEHLER_FREI (without error)
#define GD_DIAG_SCGND           0x01u  // KS_MASSE (KS GND)
#define GD_DIAG_SCVCC           0x02u  // KS_UB (KS +UB)
#define GD_DIAG_OPEN            0x03u  // LU (LU)
#define GD_DIAG_SCGND_OR_OPEN   0x04u  // KS_MASSE_ODER_LU (KS GND or LU)
#define GD_DIAG_SCVCC_OR_OPEN   0x05u  // KS_UB_ODER_LU (KS UB or LU)
#define GD_DIAG_UNDEF           0x06u  // UNDEF_FEHLER (undefined error)
#define GD_DIAG_DISABLED        0x07u  // NICHT_VERFUEGBAR (not available)
#define GD_DIAG_PLAUSI          0x08u  // FEHLER_PLAUSI (Plausibility error)
#define GD_DIAG_CAN_ERROR       0x10u  // FEHLER_CAN_GD (CAN GD error)
#define GD_DIAG_CALIB_ERROR     0x20u  // FEHLER_CALIB (Calibration error)

/**
 *  @brief Transforms the EOL diagnostic value into GD diagnostic value.
 *
 *  GD-Diagnostic value:
 *  -   0x00 => no error
 *  -   0x01 => short circuit to ground
 *  -   0x02 => short circuit to power supply
 *  -   0x03 => wire broken
 *  -   0x04 => short circuit to ground or wire broken
 *  -   0x05 => short circuit to power supply or wire broken
 *  -   0x06 => undefined error
 *  -  (0x08 => plausibility error)
 *  -  (0x10 => CAN/GD error)
 *  -  (0x20 => calibration error)
 *
 *  @param diag_e       Diagnostic value (EOL)
 *  @return             GD diagnostic value
 */
uint8 gdTranslateDiag_u8 (IODiag_te diag_e);


/**
 *  @brief Returns the diagnostic status of GD.
 *
 *  @param status_ps    Pointer to a structure for diagnostic status
 */
void gdGetDiagStatus (GdDiagStatus_ts* status_ps);

/**
 *  @brief Returns the version number of the GD library.
 *
 *  @return             Version number
 */
uint16 gdGetVersion_u16 (void);

#endif // __GD_H
