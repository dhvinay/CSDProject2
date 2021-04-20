/**
 * \file mbxinf.h
 *
 * \brief Mailbox event notification - interface
 *
 * With this module, tasks can be notified via a PXROS event if
 * a message is received on a mailbox.
 *
 * Copyright 2000 (c) AGCO GmbH, Marktoberdorf
 *
 * \par History
 *
 * 2000-09-28 / Latt
 * - created
 *
 * 2011-07-15 / florian.schwarz@euro-engineering.com
 * - doxygen format adjustments
 *
 * 2014-10-09 / Christian.Pischulti@AGCOcorp.com
 * - [PB-8563] Improved comments for doxygen.
 *
 */

#ifndef __mbxinf__
#define __mbxinf__

/**
 * \brief Data structure to hold information for event generation
 */
typedef struct
{
    PxUInt_t mbxi_state;        ///< State of structure (empty, initialized, event generation running)
    PxMbx_t mbxi_mbx;           ///< PXROS mailbox
    PxMsgType_t mbxi_msgtype;   ///< PXROS message type
    PxEvents_t mbxi_events;     ///< PXROS events to generate
    PxTask_t mbxi_task;         ///< Task which gets notified
} MbxInf_T;
typedef MbxInf_T* MbxInf_t;     ///< pointer typedef for MbxInf_T

PxError_t MbxInfInit(MbxInf_t mbxi,
                        PxMbx_t mbx,
                        PxMsgType_t msgtype,
                        PxEvents_t events);

PxError_t MbxInfClear  (MbxInf_t mbxi);

PxError_t MbxInfStart  (MbxInf_t mbxi);

PxError_t MbxInfStop   (MbxInf_t mbxi);

PxError_t MbxInfChange (MbxInf_t mbxi,
                            PxMbx_t mbx,
                            PxMsgType_t msgtype,
                            PxEvents_t  events);

#endif
