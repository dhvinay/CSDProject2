/**
 *  \file       EosStdTypeTC.h
 *
 *  \brief      This file contains the standard typedefs for the Tricore platform
 *
 *              Copyright 2011 (c) AGCO/Fendt GmbH & Co
 *
 *  \section    history
 *
 *  2008-08-07 / Christian.Pischulti@xfendt.de
 *  - created
 *
 *  2011-03-11 / Christian.Pischulti@xfendt.de
 *  - New typedef boolean to replace bool in c files.
 *  - bool is no longer defined for c++ builds.
 *  - New typedefs uint64 and sint64
 *
 *  2012-04-18 / Christian.Pischulti@xfendt.de
 *  - Added unsigned attribute to define values for MAXUINT8 and
 *    MAXUINT16 to comply to MISRA rules.
 *  - Don't define boolean type if bosch core plattform_types.h
 *    was included before.
 *  - Added attribute unsigned to define FALSE.
 *
 *  2012-09-06 / florian.schwarz@euro-engineering.com
 *  - define _STD_TYPE_H to prevent Bosch std_type.h from being included
 */
#ifndef _EOSSTDTYPETC_H
#define _EOSSTDTYPETC_H

#ifndef _STD_TYPE_H

/*
 *          Standard datatypes for tricore platforms based on
 *          hightecs gnu compiler integrated types.
 */

    // TRUE/FALSE define
    // Notice: C++ defines true and false ( lower case )
    #define FALSE           (0u)
    #define TRUE            (!FALSE)


    // NULL pointer
    #ifndef NULL
        #define NULL        ((void*)0)
    #endif

    // limits of data types
    #define MAXUINT8        (0xffu)
    #define MAXSINT8        (0x7f)
    #define MINSINT8        (-(MAXSINT8) - 1)
    #define MAXUINT16       (0xffffu)
    #define MAXSINT16       (0x7fff)
    #define MINSINT16       (-(MAXSINT16) - 1)
    #define MAXUINT32       (0xfffffffful)
    #define MAXSINT32       (0x7fffffffl)
    #define MINSINT32       (-(MAXSINT32) - 1l)
    #define MAXUINT64       (0xffffffffffffffffull)
    #define MAXSINT64       (0x7fffffffffffffffll)
    #define MAXREAL32       (3.40282347E38F)
    #define MINREAL32       (1.17549435E-38F)
    #define MAXREAL64       (1.7976931348623157E308)
    #define MINREAL64       (2.2250738585072016E-308)

    #ifndef __cplusplus
        // bool is a keyword in c++. Type bool can't be used in header files to be
        // included in c++ files.
        typedef unsigned char  bool; // __attribute__ ((deprecated));
    #endif // __cplusplus

    typedef unsigned char       uint8;
    typedef signed char         sint8;
    typedef unsigned short      uint16;
    typedef signed short        sint16;
    typedef unsigned long       uint32;
    typedef signed long         sint32;
    typedef unsigned long long  uint64;
    typedef signed long long    sint64;
    typedef float               real32;
    typedef double              real64;

#endif  // _STD_TYPE_H

// Type boolean is not defined in bosch core std_type.h
// but sometimes in platform_types.h
#ifndef  _BOOLEAN_DEFINED_
    #define _BOOLEAN_DEFINED_

    #ifndef _PLATFORM_TYPES_H
        typedef unsigned char       boolean;
    #endif
#endif

#endif  // _EOSSTDTYPETC_H
