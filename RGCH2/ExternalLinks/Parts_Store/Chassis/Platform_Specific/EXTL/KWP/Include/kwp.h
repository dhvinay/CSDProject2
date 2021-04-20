/**
 * \file       kwp.h
 *
 * \brief      KWP interface
 *
 * Copyright 2009 (c) Dept. ES-SWE AGCO GmbH, Marktoberdorf
 *
 * \section    History
 *
 * 2009-07-01 / werner-unsinn@xfendt.de
 * - erstellt
 *
 * 2009-12-10 / werner.unsinn@xfendt.de
 * - KWP-Task wird mit Parametern initialisiert
 *
 * 2011-02-21 / Christian.Pischulti@xfendt.de
 * - New function kwpGetRamSelftestError_b( ) for tricore ECUs.
 *
 * 2011-06-21 / florian.schwarz@euro-engineering.com
 * - handler functionality [PB-1705]
 * - moved KWP_RESPONSE_* (from kwp_2000.h) here
 * - doxygen structure
 *
 * 2011-10-20 / florian.schwarz@euro-engineering.com
 * - changed type names to be consistent with EOS types
 * - changed wrong suffix of KwpResponse_ts.type_u8 to type_e
 *
 * 2012-06-20 / florian.schwarz@euro-engineering.com
 * - Added SRC4_5 and SRC36_20_31.
 *
 * 2012-12-14 / Christian.Pischulti@AGCOcorp.com
 * - [PB-4979] Added ECU EBK (light and HVAC control panel).
 *
 * 2013-02-19 / Christian.Pischulti@AGCOcorp.com
 * - [PB-4122] Added ECU ZEK (X5 cabine central electric).
 * - [PB-4122] Added support for messages with envelope (Mattis Kornelius).
 *
 * 2013-02-19 / Meinrad.Hefele@AGCOcorp.com
 * - [PB-5538] Added ECU MFC.
 *
 * 2014-09-25 / Christian.Pischulti@AGCOcorp.com
 * - [PB-8552] Added ECU SRC14-34/31 (new EXT light).
 *
 * 2015-10-12 / Mattis.Kornelius@AGCOcorp.com
 * - [PB-10481] added an answer queue for OsWrapper inter-task-communication in
 *   communication structures (KwpInit_ts, KwpRequest_ts).
 *
 * 2015-10-21 / Mattis.Kornelius@AGCOcorp.com
 * - [PB-10481] changed define RTOS_PXROS in to compiler define __tricore__.
 *
 * 2016-03-11 / Christian.Pischulti@AGCOcorp.com
 * - [PB-12073] Changed init structure for AGCO part/order number and Fendt G number.
 *   Moved function isKwpExtendedDiagMode_b from kwpx.h to kwp.h.
 *   Changed MSG_ENV_TYPE_KWP from 0x10 to 0x40 (for message envelope/header).
 *
 * 2016-05-11 / Mattis.Kornelius@AGCOcorp.com
 * - [PB-11740] Added ECU ZE7R2 (replacement for ZEL).
 *
 * 2016-09-19 / Mattis.Kornelius@AGCOcorp.com
 * - [PB-11734] Added ECU FLB.
 */

#ifndef __KWP_H
#define __KWP_H

/**
 * \page _kwp_usage Interface Description
 *
 * The KWP interface is used to register handler mailboxes which
 * shall receive KWP requests.
 *
 * \section _kwp_initialization Initialization
 *
 * The KWP task is started with the Function kwpInitTask_s32().
 * Unless the KWP task is running, handlers can't be registered.
 *
 * \section _kwp_handler_register Registering/Unregistering a Handler
 *
 * To register a handler, us the function kwpHandlerRegister_s32().
 * Handlers can be registered for a number of "Request Groups"
 * (see \ref KwpReqGroup_te). A Handler will receive all
 * KWP messages belonging to the specified group.
 *
 * Multiple handlers can be installed for a single Request Group.
 * If this is the case, all registered handlers will receive
 * an incoming KWP request of their group in turn until one of
 * them responds to the request.
 *
 * Already registered handlers can be unregistered via
 * kwpHandlerUnregister_s32().
 *
 * \section _kwp_message_handling Message Handling and Responses
 *
 * After a handler has been registered, the corresponding mailbox will receive
 * KWP requests. A registered handler has to handle all incoming requests,
 * i.e. for every received message in the handler mailbox, either
 * kwpHandlerRespond_s32() or kwpHandlerReject_s32() has to be called.
 *
 * \section _see_also See also
 *
 * \ref _kwp_interface
 */

/**
 * \defgroup _kwp_interface KWP Interface
 * \{
 */

#define KWP_HW_VERSION_MAX  8u   /**< \brief maximum length of hardware version string */

// 13 ASCII signs for order number according to 2016-02-23_Common AGCO EBOM Structure_FINAL-VERSION.xlsx
// (without zero termination)
#define KWP_AGCO_ORDNUM_STRING_LENGTH       (13u)
// Part/Ordernumber is sent with four bytes before order number
// AGCO order number: 2 bytes for 0x5AA5, 2 bytes for property field 0x01 and string length 0x0D
#define KWP_AGCO_ORDNUM_HDR_STRING_LENGTH   (4u + KWP_AGCO_ORDNUM_STRING_LENGTH)
// Fendt G number: 2 bytes for 0x5AA5, 2 bytes 0x0000, 6 bytes for BCD coded G number (no dots)
#define KWP_G_ODRNUM_HDR_STRING_LENGHT      (4u + 6u)

/**
 * \name Response Codes
 *
 * \anchor _kwp_response_codes
 *
 * Response Codes as defined by ISO 14230-3 except
 * KWP_RESPONSE_NONE which is used to indicate that no
 * response should be sent.
 *
 */
/**\{*/
#define KWP_RESPONSE_GENERAL_REJECT             0x10u
#define KWP_RESPONSE_SERVICE_NOT_SUPPORTED      0x11u
#define KWP_RESPONSE_FUNCTION_NOT_SUPPORTED     0x12u
#define KWP_RESPONSE_BUSY_REPEAT_REQUEST        0x21u
#define KWP_RESPONSE_INCORRECT_CONDITIONS       0x22u
#define KWP_RESPONSE_CALCULATION_STILL_RUNNING  0x23u
#define KWP_RESPONSE_REQUEST_OUT_OF_RANGE       0x31u
#define KWP_RESPONSE_SECURITY_ACCESS_DENIED     0x33u
#define KWP_RESPONSE_FINISHED_DOWNLOAD          0x40u
#define KWP_RESPONSE_CANNOT_DOWNLOAD_DATA       0x43u
#define KWP_RESPONSE_CHECKSUM_ERROR             0xFAu
#define KWP_RESPONSE_ERASING_STILL_RUNNING      0xFBu
#define KWP_RESPONSE_ERROR_ON_ERASING           0xFDu
#define KWP_RESPONSE_NONE                       0xFFu
/**\}*/

/**
 * \brief initialization data for KWP task
 *
 * This struct is used to pass initialization information
 * to the KWP task, see kwpInitTask_s32().
 */
typedef struct
{
    uint8   addr_u8;                                        	///< \brief KWP-ID --> CAN-ID = 0x500 + (KWP-ID << 1) + 1
    uint8   type_u8;                                        	///< \brief ECU type (see \ref _kwp_ecu_types_tricore, \ref _kwp_ecu_types_arm, \ref _kwp_ecu_types_cortexM3)
    uint8   hwVersion_au8[KWP_HW_VERSION_MAX];              	///< \brief hardware version (see doucement ECU-Identifikation for definition of data)
    uint8   hwNumber_au8[KWP_AGCO_ORDNUM_HDR_STRING_LENGTH]; 	///< \brief hardware number (see doucement ECU-Identifikation for definition of data)
} KwpInit_ts;

/**
 * \name TriCore ECU Types
 * \anchor _kwp_ecu_types_tricore
 * \{
 */
#define KWP_ECU_TYPE_EXT            0
#define KWP_ECU_TYPE_EXTLT          1
#define KWP_ECU_TYPE_SRC4_5         2
#define KWP_ECU_TYPE_SRC36_20_31    3
#define KWP_ECU_TYPE_SRC14_34_31    4

/**
 * \}
 */

/**
 * \name  ARM ECU Types
 * \anchor _kwp_ecu_types_arm
 * \{
 */
#define KWP_ECU_TYPE_MRC        0x3
#define KWP_ECU_TYPE_ZEFH       0x6
#define KWP_ECU_TYPE_EBT_SPFH   0x7
#define KWP_ECU_TYPE_MFB        0x9
#define KWP_ECU_TYPE_EBT        0xb
#define KWP_ECU_TYPE_MFA        0xc
#define KWP_ECU_TYPE_ZEL        0xd
#define KWP_ECU_TYPE_RDRA       0xe
#define KWP_ECU_TYPE_EBK        0x4

/**
 * \name  CortexM3 ECU Types
 * \anchor _kwp_ecu_types_cortexM3
 * \{
 */
#define KWP_ECU_TYPE_ZEK        0x1
#define KWP_ECU_TYPE_MFC        0xa
#define KWP_ECU_TYPE_ZE7R2      0xd
#define KWP_ECU_TYPE_FLB        0x5

/**
 * \}
 */

/**
 * \name KWP Status Flags
 *
 * \anchor _kwp_status_flags
 *
 * These flags are passed to handlers to indicate the current KWP state (see kwpRequest_ts)
 */
/**\{*/
#define KWP_HANDLER_FLAG_DIAGMODE   0x01    /**< \brief diagnose mode active */
#define KWP_HANDLER_FLAG_AUTH       0x02    /**< \brief client authenticated */
#define KWP_HANDLER_FLAG_EEPROM     0x04    /**< \brief EEPROM access active */
/**\}*/

/**
 * \brief Request Groups
 *
 * \anchor _kwp_request_groups
 *
 * "Request Groups" identify groups of KWP requests on
 * which a task can install a handler.
 */
typedef enum
{
    KWP_REQGROUP_TROUBLECODES=0,    /**< \brief read/clear trouble codes */
    KWP_REQGROUP_RWDATALOCAL,       /**< \brief read/write data by local identifier */
    KWP_REQGROUP_ROUTINE,           /**< \brief start/stop routine; get routine results */
    KWP_REQGROUP_COUNT              /**< \brief number of valid elements in this enum */
} KwpReqGroup_te;

/**
 * \brief message type (handler->kwp task)
 *
 * This enum is used in the kwpResponse_ts struct to specify the
 * type of response.
 */
typedef enum
{
    KWP_RSPTYPE_REJECT, /**< KWP message is rejected (not handled (by this handler)) */
    KWP_RSPTYPE_POS,    /**< positive response */
    KWP_RSPTYPE_NEG     /**< negative response */
} KwpRspType_te;

/**
 * \brief structure describing a KWP response message
 *
 * This structure is used by kwpHandlerRespond_s32() and
 * kwpHandlerReject_s32() to pass KWP responses from the handler
 * to the KWP task. It does not contain the actual response
 * data (if any) like EEPROM data, sensor values, etc. These
 * are stored in the same buffer the KWP request was stored in.
 */
typedef struct
{
    KwpRspType_te type_e;   /**< \ref KwpRspType_te "type of response" (positive/negative/...) */
    uint8 negRspCode_u8;    /**< negative \ref _kwp_response_codes "response code" (ignored for other responses) */
    uint16 payload_u16;     /**< number of data bytes in response (ignored for negative and reject responses) */
} KwpResponse_ts;

/**
 * \brief Description of a KWP request
 *
 * This struct is sent in form of a PXROS message to
 * a registered handler mailbox upon reception of
 * a KWP message. data_p points to a buffer containing
 * the actual data bytes of the KWP message (without the
 * request ID). Since this buffer is also used to store
 * response data, KwpRequest_ts contains two sizes:
 * msgSize_u16 which contains the size of the request
 * message and bufSize_u16 which contains the maximum
 * number of bytes usable for the response message.
 */
typedef struct
{
    uint8 id_u8;                /**< \brief KWP Request ID */
    uint8 flags_u8;             /**< \brief \ref _kwp_status_flags "flags describing the KWP state" */
    uint16 msgSize_u16;         /**< \brief number of data bytes in this message */
    uint16 bufSize_u16;         /**< \brief size of data area */
    void *data_p;               /**< \brief pointer to data area. Buffer starts with byte after kwp request code. */
    KwpResponse_ts response_s;  /**< \brief response data (filled by handler) */
#ifndef __tricore__
    osQueue_t answQueue_t;      /**< queue of the calling task (kwp) */
#endif
} KwpRequest_ts;

/**
 * \brief Defines for message envelope type
 */
//Note: Define message type Id according to this table:
// 0x01 - 0x1F: RTOS specific
// 0x20 - 0x3F: EOS
// 0x40 - 0x4F: Services (common libs like KWP, GD.. )
// 0x50 - 0x9F: application tasks
// 0xAF - 0xFF: reserved for future use
#define  MSG_ENV_TYPE_KWP 0x40u /**< \brief KWP message envelope id */

/**
 * \brief Enum for different KWP message subtypes
 */
enum
{
    MSG_ENV_SUBTYPE_KWP_INIT,           /**< \brief kwp initial configuration */
    MSG_ENV_SUBTYPE_KWP_REGISTER,       /**< \brief Register for specific KWP service group */
    MSG_ENV_SUBTYPE_KWP_DISPATCH        /**< \brief kwp request dispatcher */
};

sint32 kwpInitTask_s32 (const KwpInit_ts* init_ps);

uint16 kwpGetVersion_u16 (void);

#ifdef __TC13__
// Get result of RAM selftest done by bootloader. ( Tricore ECUs only)
// FALSE: no ram error; TRUE: ram test failed.
boolean kwpGetRamSelftestError_b( void );
#endif

sint32 kwpHandlerRegister_s32(KwpReqGroup_te reqGroup_e, PxMbx_t mbx_ps);
sint32 kwpHandlerRegisterEnv_s32(KwpReqGroup_te reqGroup_e, PxMbx_t mbx_ps);

sint32 kwpHandlerUnregister_s32(KwpReqGroup_te reqGroup_e, PxMbx_t mbx_ps);

void kwpHandlerReject(KwpRequest_ts *request_ps);

void kwpHandlerRespond(KwpRequest_ts *request_ps, uint8 negRspCode_u8, uint16 payload_u16);

// If this function returns TRUE the extended diagnostic session is active
boolean isKwpExtendedDiagMode_b(void);

/**
 * \}
 */

#endif // __KWP_H
