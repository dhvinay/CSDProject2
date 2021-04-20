/**
 * \file msgpool.h
 *
 * \brief Message pool - interface
 *
 * \par History
 *
 * 2000-09-28 / Latt
 * - created
 *
 * 2011-07-15 / florian.schwarz@euro-engineering.com
 * - doxygen format adjustments
 *
 */

#ifndef __msgpool__
#define __msgpool__

PxError_t CreateMsgPool(PxMbx_t *Poolmbx,
						PxUInt_t no,            /* Blockanzahl          */
						PxSize_t size,          /* Blockgroesse         */
						PxMc_t   srcmc,         /* Speicherquelle       */
						PxOpool_t srcopool);    /* Objektquelle         */

PxError_t DeleteMsgPool(PxMbx_t *Poolmbx);

#endif


