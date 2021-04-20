/**
 *  @file       eosHndOutp.h
 *
 *  @brief      Support functions for isr based current controller for hitch.
 *
 *  @section    history
 *
 *  2011-08-31 / Christian Pischulti
 *  - Created file to hide bosch core functions and to have a new header file
 *    for eos functions.
 *
 */
#ifndef __EOSHNDOUTP_H
    #define __EOSHNDOUTP_H

    // Interrupt enable and disable functions from bosch core
    uint32  eosSuspendInt_u32( void );          // stop isr handling
    void    eosResumeInt( uint32 );             // resume isr handling
    void    eosIntEnable( void );               // allow that other higher priority isrs can interrupt current isr

    // Eos functions for setting of outputs without mailbox
    sint32 eosSetAnyCoreOutput(EosOutName_te outname_e, sint16 setvalue_s16);

    // calculate current from latest adc value
    sint32 eosProcSpecificAnalogOutputCurrent_s32( EosOutName_te eosChNr_e, sint32 * curValuA_ps32 );

#endif // __EOSHNDOUTP_H
