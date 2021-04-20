/**
 *  \file       EosStdTypeARM.h
 *
 *  \brief      This file contains the standard typedefs for the ARM platform
 *
 *
 *  \section    History
 *
 *  2008-08-07 / Christian.Pischulti@xfendt.de
 *  - created
 *
 *  2011-03-11 / Christian.Pischulti@xfendt.de
 *  - New typedef boolean to replace bool in c files.
 *  - bool is no longer defined for c++ builds.
 */

#ifndef __EOSSTDTYPEARM_H
    #define __EOSSTDTYPEARM_H


    // TRUE/FALSE define
    #define FALSE           (0u)
    #define TRUE            (!FALSE)

    // NULL pointer
    #ifndef NULL
    #define NULL            (0)
    #endif

    // limits of data types
    #define MAXUINT8        (0xFFu)
    #define MAXSINT8        (0x7F)
    #define MINSINT8        (-(MAXSINT8) - 1)
    #define MAXUINT16       (0xFFFFu)
    #define MAXSINT16       (0x7FFF)
    #define MINSINT16       (-(MAXSINT16) - 1)
    #define MAXUINT32       (0xFFFFFFFFul)
    #define MAXSINT32       (0x7FFFFFFFl)
    #define MINSINT32       (-(MAXSINT32) - 1l)
    #define MAXREAL32       (3.40282347E38F)
    #define MINREAL32       (1.17549435E-38F)
    #define MAXREAL64       (1.7976931348623157E308)
    #define MINREAL64       (2.2250738585072016E-308)

    #ifndef __cplusplus
        // bool is a keyword in c++. Type bool can't be used in header files to be
        // included in c++ files.
        typedef unsigned char  bool; // __attribute__ ((deprecated));
    #endif // __cplusplus


    typedef unsigned char   boolean;

    typedef unsigned char   uint8;
    typedef signed char     sint8;
    typedef unsigned short  uint16;
    typedef signed short    sint16;
    typedef unsigned long   uint32;
    typedef signed int      sint32;

    typedef float           real32;
    typedef double          real64;

#endif // __EOSSTDTYPEARM_H
