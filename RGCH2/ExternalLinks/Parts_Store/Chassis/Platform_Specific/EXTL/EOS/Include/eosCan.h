/**
 * \file eosCan.h
 *
 * \brief CAN bus related functions and types
 *
 * Copyright 2014 (c) AGCO GmbH, Marktoberdorf
 *
 * \par History
 *
 * 2013-11-07 / florian.schwarz@euro-engineering.com
 * - [PB-5211] Moved all CAN related functions from eos.h to
 *   own header file. Added function eosCanSendBufferFreeCnt_s32()
 *   to read number of free CAN send fifo messages. Added
 *   function eosCanState_e() and can states enum for reading
 *   of current CAN state.
 *
 * 2014-11-18 / Mattis.Kornelius@AGCOcorp.com
 * - [PB-9026] added message envelope functionality to CAN task
 *
 * 2015-07-03 / Christian.Pischulti@AGCOcorp.com
 * - [PB-9026] Changed MSG_ENV_TYPE_CAN from 0x01 to 0x20 (ARM EOS).
 */

#ifndef EOSCAN_H
#define EOSCAN_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup _can CAN
 * \{
 */

typedef struct _eoscanadmin_ *EosCanAdmin_pts; ///< \brief special type to administrate a request to CAN (used like a handle) just pointer is needed here

/**
 * \brief  CAN port identifiers
 */
typedef enum
{
    CAN_1,  ///< \brief node 1
    CAN_2,  ///< \brief node 2
    CAN_3,  ///< \brief node 3
    CAN_4,  ///< \brief node 4
    /// not actually the "last" CAN node, but the lowest ID that is NOT a valid CAN node - useful in loops and for range checks
    CAN_Last
} EosCan_te;

#define MSG_ENV_TYPE_CAN    (0x20u) ///< \brief CAN Message envelope type (EosCanInstallReqMailEnv_s32())

/**
 * \brief  CAN message sub types
 */
typedef enum
{
    MSG_ENV_CAN1_RX,                ///< \brief received CAN message from CAN_1
    MSG_ENV_CAN2_RX,                ///< \brief received CAN message from CAN_2
    MSG_ENV_CAN3_RX,                ///< \brief received CAN message from CAN_3
    MSG_ENV_CAN4_RX                 ///< \brief received CAN message from CAN_4
} MsgEnvSubCAN_te;

#define CAN_DATA_MAX    8u          ///< \brief maximum data bytes in a CAN message
#define CAN_STD_ID_MAX  0x7FFu      ///< \brief highest possible CAN ID
#define CAN_EXT_ID_MAX  0x1FFFFFFFu ///< \brief highest possible extended CAN ID

/**
 * \brief data struct that is received by application-task from CAN-task containing CAN-data
 */
typedef struct
{
    uint32   id_u32;                ///< \brief identifier of the message
    boolean  isXformat_b;           ///< \brief TRUE if extended CAN message (29-bit id)
    uint16   dlc_u16;               ///< \brief data length code; amount of data-bytes
    uint8    data_u8[CAN_DATA_MAX]; ///< \brief the message data itself
    uint32   timestamp_u32;         ///< \brief time [ms] when this message was received
} EosCanRcv_ts;
typedef  EosCanRcv_ts* EosCanRcv_pts;   ///< \brief  special type for pointer to CAN-receive-data

/**
 * \brief  data struct used by application tasks to specify which CAN messages they want to receive
 *
 * If a task wants to receive specific CAN-messages it has to set up this struct.
 * Filtering of CAN messages is done with a simple AND mask in the following way:
 * If (IdMask_u32 & IdSet_u32) equals (IdMask_u32 & can_id), the message is sent
 * to the application task. This means that the a bit of the received CAN ID at a
 * position where there is a set bit in iDMask_u32 must match the bit at the same
 * position in IdSet_u32. Bit positions that have a zero bit in IdMask_u32 may
 * have any value.
 */
typedef struct
{
    uint32   IdMask_u32;    ///< \brief Identifier mask for receive-message
    uint32   IdSet_u32;     ///< \brief identifier of the message
    boolean  isXformat_b;   ///< \brief TRUE if extended CAN message (29-bit id)
    uint16   dlc_u16;       ///< \brief data length code; set it > CAN_DATA_MAX to say "don't care"
} EosCanReq_ts;
typedef EosCanReq_ts *EosCanReq_pts;    ///< \brief special type for pointer to CAN-receive-data

/**
 * \brief CAN bitrates
 */
typedef enum
{
    CAN_BR_100,     ///< \brief  100 kbit/s
    CAN_BR_125,     ///< \brief  125 kbit/s
    CAN_BR_250,     ///< \brief  250 kbit/s
    CAN_BR_500,     ///< \brief  500 kbit/s
    CAN_BR_1000,    ///< \brief 1000 kbit/s
    CAN_OFF         ///< \brief switch off
}   EosCanBr_te;

/**
 * \brief state of a CAN node - used by function eosCanNodeState_s32
 */
typedef enum
{
    CAN_NODE_ST_DISABLED,       ///< \brief CAN node is disabled/turned off
    CAN_NODE_ST_ACTIVE,         ///< \brief node is running
    CAN_NODE_ST_ERRPASSIVE,     ///< \brief error-passive state (highest error counter >= 128)
    CAN_NODE_ST_ERRBUSOFF,      ///< \brief bus-off state (highest error counter >= 256)
    CAN_NODE_ST_ERRUNREC,       ///< \brief unrecoverable error
} EosCanNodeSt_te;

sint32 EosCanSetBitrate_s32( EosCan_te canNode_e, EosCanBr_te baudrate_e);

sint32 EosCanInstallReqMail_s32( EosCan_te canNode_e, EosCanAdmin_pts *canAdmin_pps,
                                 EosCanReq_ts const *canReqSpec_ps, PxMbx_t *rcvMbx_pt );

sint32 EosCanInstallReqMailEnv_s32( EosCan_te canNode_e, EosCanAdmin_pts *canAdmin_pps,
                                    EosCanReq_ts const *canReqSpec_ps, PxMbx_t *rcvMbx_pt );

sint32 EosCanRemoveReq_s32( EosCan_te CanName_ce, EosCanAdmin_pts *CanAdmin_cpps, PxMbx_t *RcvMbx_cpt );

sint32 EosCanPutMsg_s32( EosCan_te CanName_ce, uint8 const *RawData_cau8 );

sint32 EosCanSend_s32( EosCan_te CanName_ce, uint16 Id_cu16, uint8 const *Data_cau8, uint32 Dlength_cu32 );

sint32 EosCanSendExt_s32( EosCan_te CanName_ce,
                          uint32 Id_cu32, uint8 const *Data_cau8, uint32 Dlength_cu32 );

typedef struct _eoscanbosig_ *EosCanBoSig_pts; ///< \brief special type to administrate Busoff signaling. Just pointer is needed here

sint32 EosCanInstallBoSignal_s32( EosCan_te CanName_ce, EosCanBoSig_pts *BoSignal_cpps,
                                  PxEvents_t BoStartEv_ct, PxEvents_t BoClearEv_ct );

sint32 EosCanRemoveBoSignal_s32( EosCan_te CanName_ce, EosCanBoSig_pts *BoSignal_cpps );

boolean EosCanSend_Hnd_b( EosCan_te canNode_e, uint16 ident_u16, uint8 const *data_pu8, uint8 dlc_u8);
boolean EosCanSendExt_Hnd_b( EosCan_te canNode_e, uint32 identExt_u32, uint8 const *data_pu8, uint8 dlc_u8);

sint32  eosCanSendBufferFreeCnt_s32(EosCan_te canNode_e);

EosCanNodeSt_te eosCanState_e(EosCan_te canNode_e);

/**
 * \}
 */

#ifdef __cplusplus
} // extern "C"
#endif

#endif  // EOSCAN_H
