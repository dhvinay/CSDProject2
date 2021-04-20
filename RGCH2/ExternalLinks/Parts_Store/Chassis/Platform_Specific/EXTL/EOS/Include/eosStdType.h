/**
 *  \file       eosStdType.h
 *
 *  \brief      This file pulls in the typedefs for the
 *              different micro controllers.
 *
 *
 *              Copyright 2012 (c) AGCO/Fendt GmbH & Co
 *
 *  \par    History
 *
 *  2012-02-01 / Christian.Pischulti@xfendt.de
 *  - created
 *
 */
#ifndef _EOSSTDTYPE_H_
    #define _EOSSTDTYPE_H_

    #if defined __tricore__
        #include "EosStdTypeTC.h"       // Infineon tricores with gnu compiler
    #elif defined __ARM_ARCH_4T__
        #include "EosStdTypeARM.h"      // ARM7-TDMI-S with gnu compiler (NXP LPC22XX and LPC23XX)
    #else
        #error  unknown micro controller family
    #endif

#endif  // _EOSSTDTYPE_H_


