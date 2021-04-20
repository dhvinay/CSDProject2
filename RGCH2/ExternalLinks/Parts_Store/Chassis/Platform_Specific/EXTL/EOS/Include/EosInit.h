/**
 *  \file       EosInit.h
 *
 *  \brief      Header file for eos and PxROS init functions
 *
 *  Copyright 2011 (c) AGCO/Fendt GmbH & Co
 *
 *  \par    History
 *
 *  2004-10-11 / W. Zaremba
 *  - created
 *
 *  2006-11-20 / E. Kemmler
 *  - Core initialisation divided into 2 parts
 *
 *  2008-05-09 / Ch. Pischulti
 *  - removed unnecessary externs
 *  - removed easycode tags
 *  - changed comment style for doxygen
 *
 *  2011-11-02 / Florian Schwarz
 *  - Removed function EosInitCoreBegin/End.
 *
 *  2012-04-25 / Christian.Pischulti@AGCOcorp.com
 *  - Added new parameters to init function to be able to set
 *    address and size of system memory block and size of object
 *    pool from application.
 *  - Idle task id is no longer stored in EOS.
 *
 */
#ifndef EOSINIT_H
#define EOSINIT_H

void    EosInitPxrosBegin( PxTask_t * idleTaskId_pps, PxAligned_t * sysmem_pa, uint32 sysmemInBytes_u32, uint32 objNum_u32 );
sint32  EosInitEos_s32( void );
void    EosInitPxrosEnd( PxTask_t idleTaskId_ps);

#endif   // EOSINIT_H
