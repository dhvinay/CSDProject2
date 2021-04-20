/**
 *  \file iosymbdefault.h
 *
 *  \brief symbol definitions for inputs/outputs
 *
 *  This file simply defines all the enums to identify inputs and outputs,
 *  the actual I/O symbol definitions can be found in the ECU specific header files.
 *
 *  \par    History
 *
 *  2009-07-01 / werner.unsinn@xfendt.de
 *  - created
 *
 *  2012-03-27 / werner.unsinn@agcocorp.com
 *  - added empty enum for ECU internal temperature sensors
 *
 */

#ifndef __IOSYMBDEFAULT_H
    #define  __IOSYMBDEFAULT_H


    /// \brief names of all digital and PWM outputs
    typedef enum
    {
        OUT_MAX
    } EosOutName_te;

    /// \brief names of all analog inputs
    typedef enum
    {
        AI_MAX
    } EosAiName_te;

    /// names of all digital inputs
    typedef enum
    {
        DI_MAX
    } EosDiName_te;

    /// names of all temperature inputs
    typedef enum
    {
        TI_MAX
    } EosTiName_te;

#endif // __IOSYMBDEFAULT_H
