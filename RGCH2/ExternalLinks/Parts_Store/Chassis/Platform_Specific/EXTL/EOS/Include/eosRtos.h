/**
 * \file eosRtos.h
 *
 * \brief Task creation - interface
 *
 * \par History
 *
 * 2004-07-11 / Latt
 * - created
 *
 * 2009-07-29 / Ch. Pischulti
 * - Added function CreateStdtaskwTbLim for application/service tasks
 *   which need adjustable transfer buffer size.
 *
 * 2009-11-10 / Ch. Pischulti
 * - Renamed CreateStdtaskwTbLim() to CreatedUsrtaskwTbLim().
 *   The task priority is located in the user range.
 *
 * 2011-07-18 / florian.schwarz@euro-engineering.com
 * - doxygen format adjustments
 *
 * 2011-12-02 / florian.schwarz@euro-engineering.com
 * - added const qualifier to string arguments
 * - added preprocessor directives to prevent conflicts on multiple includes
 *
 * 2014-11-18 / Mattis Kornelius
 * - [Misc] moved function prototype "CreateStdtask" to EOS internal header file
 *   to avoid non-Eos task creation in EOS priority range.
 *
 * 2015-07-03 / Christian.Pischulti@AGCOcorp.com
 * - [PB-9026] Update of can message ids from latest ARM EOS.
 * 
 * 2016-04-19 / Christian.Pischulti@AGCOcorp.com
 * - [PB-12141] Added header file pxpe.h and fixed typo in message id table.
 */
#ifndef EOSRTOS_H
#define EOSRTOS_H

#ifdef __cplusplus
extern "C" {
#endif

#define RTOS_PXROS      ///< Tell libs and other codes that we are using PXROS

#include <pxdef.h>      // Pxros RTOS header file
#include <pxpe.h>

/**
 * \defgroup _utility Utility macros
 * \{
 */

// PARAM_UNUSED and FOREVER are not compliant to MISRA rule 19.4
#define PARAM_UNUSED(param) if ((param) != 0) {}        ///< \brief macro to suppress compiler warnings about unused parameters
#define FOREVER             for (;;)                    ///< \brief for endless loop in tasks
#define EVENT(no)           (1ul << (no))               ///< \brief macro to make PXROS-signal definitions easier

#define PXTASK_PRIOAPPL_HIGHEST     ((PxUChar_t)1u)     ///< \brief highest priority for application tasks
#define PXTASK_PRIOAPPL_LOWEST      ((PxUChar_t)15u)    ///< \brief lowest priority for application tasks

#define PX_MS           1u      ///< \brief PXROS tick interval [ms]
#define SYSTICK_MS      PX_MS   ///< \brief System timer tick period in milli seconds [ms]

#define MSEC(ms)        (((PxTicks_t)(ms) + (PX_MS/2u)) / PX_MS)    ///< \brief calculate the number of PXROS ticks resulting in the given duration (in ms)
#define MS2SYSTICKS(ms) (((PxTicks_t)(ms) + (PX_MS/2u)) / PX_MS)    ///< \brief calculate the number of PXROS ticks resulting in the given duration (in ms)

/**
 * \}
 */

// MESSAGE ENVELOPE IS DEFINED IN OS_WRAPPER AS FOLLOWS:
// Note: Define message type Id according to this table:
// 0x01 - 0x1F: RTOS specific
// 0x20 - 0x3F: EOS
// 0x40 - 0x4F: Services (common libs like KWP, GD.. )
// 0x50 - 0x9F: application tasks
// 0xAF - 0xFF: reserved for future use

///\brief Message envelope struct. The type and subtype is defined in the header file of the module like CAN, GD, KWP ...
typedef struct
{
    uint8    msgType_u8;        ///< MSG type like CAN, KWP ....
    uint8    msgSubType_u8;     ///< MSG subtype like can message received on CAN 1
    uint16   msgSize_u16;       ///< Size of message in bytes (envelope and data)
} MsgEnvelope_ts __attribute__((aligned(4))); // specify 32-bit alignment to ensure the correct envelope size on ARM and TriCore


// Notice:  The task priority is translated to a different value to avoid that service or application
//          tasks can get a higher priority than eos tasks.
PxError_t CreateUsrtask (   PxTask_t        *Task,                              // created Task's Taskid
                            const char      *name,                              // Task Name
                            void (*fun)(PxTask_t, PxMbx_t, PxEvents_t),         // Task Executed Function
                            PxUInt_t        stksize,                            // Stack Size in Integers
                            PxUChar_t       prio);                              // Task Priority

// Same as CreateUsrTask but the pxros limit for message transfer buffer can be adjusted.
PxError_t CreateUsrtaskwTbLim ( PxTask_t    *Task,                              // created task's Taskid
                            const char      *name,                              // Task Name
                            void (*fun)(PxTask_t, PxMbx_t, PxEvents_t),         // Task Executed Function
                            PxUInt_t        stksize,                            // Stack Size in Integers
                            PxUChar_t       prio,                               // Task Priority
                            PxUInt_t        tblimit);                           // Task's TBLimit

#ifdef __cplusplus
} // extern "C"
#endif

#endif // EOSRTOS_H
