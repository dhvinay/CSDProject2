/**
 * \file stdtask.h
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
 * 2014-10-08 / Christian.Pischulti@AGCOcorp.com
 * - [PB-8554] Removed function CreateStdTask() from EOS-API header file.
 *
 * 2014-11-18 / Mattis.Kornelius@AGCOcorp.com
 * - [PB-9026] Declared header file as deprecated, please use eosRtos.h instead
 */
#ifndef STDTASK_H
#define STDTASK_H

//#warning deprecated header file, please use new header file eosRtos.h
#include "eosRtos.h"

#endif // STDTASK_H
