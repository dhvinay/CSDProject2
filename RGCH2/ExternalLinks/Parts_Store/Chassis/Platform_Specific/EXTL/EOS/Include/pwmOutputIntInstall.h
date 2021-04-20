/**
 *  \file pwmOutputIntInstall.h
 *
 *  \brief Header file for applications which need a interrupt handler at the edges
 *         of a pwm output.
 *
 *
 *  \section History
 *
 *  2008-02-25 / Christian.Pischulti@xfendt.de
 *  - initial release
 *
 *  2008-05-21 / Christian.Pischulti@xfende.de
 *  - Fixed type mismatch of function pointer in declaration of EosInstallPwmIntHandler_s32.
 *
 *  2012-10-01 / florian.schwarz@euro-engineering.net
 *  - added to EOS
 */

#include "eos.h"

#ifndef _PWMOUTPUTINTINSTALL_H
#define  _PWMOUTPUTINTINSTALL_H

/*!< the inthandler can be called at leading or trailing edge */
typedef enum
{
    LEADING_EDGE,
    TRAILING_EDGE
} pwmEdgeInt_te;

/*!< enable or disable interrupt for pwm edges */
typedef enum
{
    PWM_INT_DISABLE,
    PWM_INT_ENABLE
} pwmIntState_te;

/*
*     Functions to install, remove and en/disable a PWM output handler
*/

/*! EosInstallPwmIntHandle -install a int handler on requested edge of a pwm output */
sint32  EosInstallPwmIntHandler_s32( EosOutName_te chName_e,        /**< pwm output name from eos.h */
                                     pwmEdgeInt_te pwmedge_e,       /**< install int handler on leading or trailing edge of PWM output signal */
                                     void (intHandler_pf)(void)  ); /**< pointer to handler of type  void ....(sint16 callParam_s16) */

/*! EosRemovePmwIntHandle - remove int handler for given edge of a pmw output */
sint32  EosRemovePwmIntHandler_s32( EosOutName_te chName_e,     /**< pwm output name from eos.h */
                                    pwmEdgeInt_te pwmedge_e );  /**< remove int handler from the leading or trailing edge */

/*! EosEnDisablePwmIntHandler - enable the interrupt for the given pwm output */
sint32  EosEnDisablePwmIntHandler_s32( EosOutName_te    chName_e,   /**< pwm output name from eos.h */
                                       pwmIntState_te   intState_e, /**< enable or disable the pwm interrupt */
                                       pwmEdgeInt_te    pwmedge_e);

/*! EosTriggerPwmIntHandler - software trigger for pwm int handler */
sint32  EosTriggerPwmIntHandler_s32( EosOutName_te chName_e,        /**< pwm output name from eos.h */
                                     pwmEdgeInt_te pwmedge_e);      /**< trigger int handler for leading or trailing edge */

#endif   // _PWMOUTPUTINTINSTALL_H
