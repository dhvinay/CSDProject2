/* File: HighClearance_model.c */

#include "HighClearance_model.h"
#include "look1_iflf_binlca.h"

/* Named constants for Chart: '<S5>/legState_FrontLeft' */
#define HighClearance_model_IN_Down    ((uint8_T)1U)
#define HighClearance_model_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define HighClearance_model_IN_Unknown ((uint8_T)2U)
#define HighClearance_model_IN_Up      ((uint8_T)3U)
#define HighClearance_model_IN_error   ((uint8_T)1U)
#define HighClearance_model_IN_moving  ((uint8_T)1U)
#define HighClearance_model_IN_movingDown ((uint8_T)1U)
#define HighClearance_model_IN_movingUp ((uint8_T)2U)
#define HighClearance_model_IN_normalOperaion ((uint8_T)2U)
#define HighClearance_model_IN_stopped ((uint8_T)2U)

/* Named constants for Chart: '<S69>/diagLatch1' */
#define HighClearance_model_IN_IoErr   ((uint8_T)1U)
#define HighClearance_model_IN_NO_ACTIVE_CHILD_m ((uint8_T)0U)
#define HighClearance_model_IN_noError ((uint8_T)2U)
#define HighClearance_model_IN_plausiErr ((uint8_T)3U)

/* Named constants for Chart: '<S143>/extendRetractLogic' */
#define HighClearance_model_IN_NO_ACTIVE_CHILD_mw ((uint8_T)0U)
#define HighClearance_model_IN_extend  ((uint8_T)1U)
#define HighClearance_model_IN_retract ((uint8_T)2U)
#define HighClearance_model_IN_stop    ((uint8_T)3U)

/* Named constants for Chart: '<S129>/errorCheckFL' */
#define HighClearance_model_IN_NO_ACTIVE_CHILD_p ((uint8_T)0U)
#define HighClearance_model_IN_downs   ((uint8_T)1U)
#define HighClearance_model_IN_errorChecking ((uint8_T)1U)
#define HighClearance_model_IN_errorWithCommand ((uint8_T)2U)
#define HighClearance_model_IN_errorWithNoCmdStep1 ((uint8_T)3U)
#define HighClearance_model_IN_errorWithNoCmdStep2 ((uint8_T)4U)
#define HighClearance_model_IN_error_e ((uint8_T)1U)
#define HighClearance_model_IN_expectedToMove ((uint8_T)1U)
#define HighClearance_model_IN_moving_g ((uint8_T)1U)
#define HighClearance_model_IN_noChecking ((uint8_T)5U)
#define HighClearance_model_IN_notExpectedToMove ((uint8_T)2U)
#define HighClearance_model_IN_okay    ((uint8_T)2U)
#define HighClearance_model_IN_other   ((uint8_T)2U)
#define HighClearance_model_IN_stationary ((uint8_T)2U)
#define HighClearance_model_IN_up      ((uint8_T)3U)

/* Named constants for Chart: '<S181>/enableLogic' */
#define HighClearance_model_IN_NO_ACTIVE_CHILD_ao ((uint8_T)0U)
#define HighClearance_model_IN_NotTransitioning ((uint8_T)1U)
#define HighClearance_model_IN_badHeight ((uint8_T)1U)
#define HighClearance_model_IN_badTrack ((uint8_T)2U)
#define HighClearance_model_IN_disabled ((uint8_T)1U)
#define HighClearance_model_IN_enabled ((uint8_T)2U)
#define HighClearance_model_IN_okay_o  ((uint8_T)3U)
#define HighClearance_model_IN_transitioning ((uint8_T)2U)
#define HighClearance_model_IN_wait    ((uint8_T)1U)
#define HighClearance_model_IN_warning ((uint8_T)2U)

/* Named constants for Chart: '<S211>/diagLatch' */
#define HighClearance_model_IN_NO_ACTIVE_CHILD_l ((uint8_T)0U)
#define HighClearance_model_IN_error_p ((uint8_T)1U)
#define HighClearance_model_IN_noError_f ((uint8_T)2U)

/* Named constants for Chart: '<S246>/plausiCheck' */
#define HighClearance_model_IN_NO_ACTIVE_CHILD_d ((uint8_T)0U)
#define HighClearance_model_IN_checking ((uint8_T)1U)
#define HighClearance_model_IN_disable ((uint8_T)1U)
#define HighClearance_model_IN_enable  ((uint8_T)2U)
#define HighClearance_model_IN_plausiCheck ((uint8_T)1U)
#define HighClearance_model_IN_plausiError ((uint8_T)2U)
#define HighClearance_model_IN_waitToCheck ((uint8_T)2U)

/* Named constants for Chart: '<S5>/actualMachineState' */
#define HighClearance_model_IN_NO_ACTIVE_CHILD_jn ((uint8_T)0U)
#define HighClearance_model_IN_calibrating ((uint8_T)1U)
#define HighClearance_model_IN_down    ((uint8_T)2U)
#define HighClearance_model_IN_error_i ((uint8_T)3U)
#define HighClearance_model_IN_movingDown_a ((uint8_T)4U)
#define HighClearance_model_IN_movingUp_d ((uint8_T)5U)
#define HighClearance_model_IN_unKnown ((uint8_T)6U)
#define HighClearance_model_IN_up_m    ((uint8_T)7U)

/* Named constants for Chart: '<S6>/TargetPosition' */
#define HighClearance_model_IN_down_h  ((uint8_T)1U)
#define HighClearance_model_IN_stop_h  ((uint8_T)2U)
#define HighClearance_model_IN_up_f    ((uint8_T)3U)

/* Named constants for Chart: '<S1>/TargetStateArbitration' */
#define HighClearance_model_IN_active  ((uint8_T)1U)
#define HighClearance_model_IN_doNothing ((uint8_T)2U)
#define HighClearance_model_IN_holdDown ((uint8_T)1U)
#define HighClearance_model_IN_holdUp  ((uint8_T)2U)
#define HighClearance_model_IN_paused  ((uint8_T)3U)
#define HighClearance_model_IN_transitioning_n ((uint8_T)4U)
#define HighClearance_model_IN_up_mf   ((uint8_T)2U)
#define HighClearance_model_IN_updateWarningsDown ((uint8_T)3U)
#define HighClearance_model_IN_updateWarningsUp ((uint8_T)4U)
#define HighClearance_model_IN_waitForEngineRunning ((uint8_T)5U)
#define HighClearance_model_IN_wait_e  ((uint8_T)5U)

/* Named constants for Chart: '<S1>/ladderExtendLogic' */
#define HighClearance_model_IN_extend_h ((uint8_T)1U)
#define HighClearance_model_IN_retract_n ((uint8_T)2U)

/* Named constants for Chart: '<S1>/latch' */
#define HighClearance_model_IN_isAlive ((uint8_T)1U)
#define HighClearance_model_IN_notAlive ((uint8_T)2U)

/* Named constants for Chart: '<S1>/latch1' */
#define HighClearance_model_IN_notOkay ((uint8_T)1U)
#define HighClearance_model_IN_okay_p  ((uint8_T)2U)

/* Named constants for Chart: '<S25>/calState2TargetState' */
#define HighClearance_model_IN_Down_k  ((uint8_T)1U)
#define HighClearance_model_IN_Up_d    ((uint8_T)2U)
#define HighClearance_model_IN_stop_ht ((uint8_T)3U)

/* Named constants for Chart: '<S23>/calibrationLogic' */
#define HighClearance_model_IN_UpdateValues ((uint8_T)1U)
#define HighClearance_model_IN_calCommanded ((uint8_T)2U)
#define HighClearance_model_IN_checkDownCalValues ((uint8_T)1U)
#define HighClearance_model_IN_checkUpCalValues ((uint8_T)2U)
#define HighClearance_model_IN_inactive ((uint8_T)3U)
#define HighClearance_model_IN_moving_j ((uint8_T)1U)
#define HighClearance_model_IN_paused_a ((uint8_T)2U)
#define HighClearance_model_IN_startConditionsFailed ((uint8_T)2U)
#define HighClearance_model_IN_step1   ((uint8_T)4U)
#define HighClearance_model_IN_step2   ((uint8_T)5U)
#define HighClearance_model_IN_step3   ((uint8_T)6U)
#define HighClearance_model_IN_step4   ((uint8_T)7U)
#define HighClearance_model_IN_stopped_l ((uint8_T)2U)

/* Named constants for Chart: '<S3>/controlEnableLogic' */
#define HighClearance_model_IN_disabled_p ((uint8_T)1U)
#define HighClearance_model_IN_enabled_e ((uint8_T)2U)

/* Named constants for Chart: '<S131>/manualOverrides' */
#define HighClearance_model_IN_normal  ((uint8_T)1U)
#define HighClearance_model_IN_overRided ((uint8_T)2U)

const CoilBus HighClearance_model_rtZCoilBus =
{
  {
    0.0F,                              /* FrontLeft */
    0.0F,                              /* FrontRight */
    0.0F,                              /* RearLeft */
    0.0F                               /* RearRight */
  },                                   /* extend */

  {
    0.0F,                              /* FrontLeft */
    0.0F,                              /* FrontRight */
    0.0F,                              /* RearLeft */
    0.0F                               /* RearRight */
  }                                    /* retract */
} ;                                    /* CoilBus ground */

/* Block parameters (default storage) */
P_HighClearance_model_T HighClearance_model_P =
{
  /* Variable: bangBang_maxOut
   * Referenced by:
   *   '<S23>/calibrationLogic'
   *   '<S129>/errorCheckFL'
   *   '<S129>/errorCheckFR'
   *   '<S129>/errorCheckRL'
   *   '<S129>/errorCheckRR'
   *   '<S131>/manualOverrides'
   *   '<S143>/extendRetractLogic'
   *   '<S144>/extendRetractLogic'
   *   '<S145>/extendRetractLogic'
   *   '<S146>/extendRetractLogic'
   */
  100.0F,

  /* Variable: baseClearance
   * Referenced by:
   *   '<S5>/legState_FrontLeft'
   *   '<S5>/legState_FrontRight'
   *   '<S5>/legState_RearLeft'
   *   '<S5>/legState_RearRight'
   *   '<S6>/TargetPosition'
   *   '<S69>/Constant'
   *   '<S70>/Constant'
   *   '<S71>/Constant'
   *   '<S72>/Constant'
   *   '<S260>/Constant'
   *   '<S261>/Constant'
   *   '<S262>/Constant'
   *   '<S263>/Constant'
   */
  1270.0F,

  /* Variable: calSensorTolerance
   * Referenced by: '<S23>/calibrationLogic'
   */
  0.5F,

  /* Variable: calTolMultiplier
   * Referenced by: '<S34>/Gain'
   */
  5.0F,

  /* Variable: ctrlWarningTime
   * Referenced by:
   *   '<S181>/enableLogic'
   *   '<S182>/enableLogic'
   *   '<S183>/enableLogic'
   *   '<S184>/enableLogic'
   */
  5.0F,

  /* Variable: defaultPositionSensor_BrkPnts
   * Referenced by:
   *   '<S23>/calibrationLogic'
   *   '<S35>/1-D Lookup Table'
   *   '<S35>/1-D Lookup Table1'
   *   '<S35>/1-D Lookup Table2'
   *   '<S35>/1-D Lookup Table3'
   *   '<S229>/1-D Lookup Table'
   *   '<S229>/1-D Lookup Table1'
   *   '<S229>/1-D Lookup Table2'
   *   '<S229>/1-D Lookup Table3'
   */
  {
    4.0F, 20.0F
  },

  /* Variable: errorMinSpd
   * Referenced by: '<S1>/TargetStateArbitration'
   */
  1.6F,

  /* Variable: heightControlToleranceStart
   * Referenced by:
   *   '<S143>/extendRetractLogic'
   *   '<S144>/extendRetractLogic'
   *   '<S145>/extendRetractLogic'
   *   '<S146>/extendRetractLogic'
   */
  2.0F,

  /* Variable: heightControlToleranceStop
   * Referenced by:
   *   '<S143>/extendRetractLogic'
   *   '<S144>/extendRetractLogic'
   *   '<S145>/extendRetractLogic'
   *   '<S146>/extendRetractLogic'
   */
  1.0F,

  /* Variable: heightDiffTolerance
   * Referenced by:
   *   '<S125>/Constant'
   *   '<S34>/Constant'
   *   '<S181>/enableLogic'
   *   '<S182>/enableLogic'
   *   '<S183>/enableLogic'
   *   '<S184>/enableLogic'
   */
  26.0F,

  /* Variable: heightTolerance
   * Referenced by:
   *   '<S5>/legState_FrontLeft'
   *   '<S5>/legState_FrontRight'
   *   '<S5>/legState_RearLeft'
   *   '<S5>/legState_RearRight'
   */
  2.0F,

  /* Variable: heightToleranceRoad
   * Referenced by:
   *   '<S5>/legState_FrontLeft'
   *   '<S5>/legState_FrontRight'
   *   '<S5>/legState_RearLeft'
   *   '<S5>/legState_RearRight'
   */
  4.0F,

  /* Variable: maxTransitionMachineSpd
   * Referenced by: '<S1>/TargetStateArbitration'
   */
  8.0F,

  /* Variable: minDistanceMoving
   * Referenced by:
   *   '<S5>/legState_FrontLeft'
   *   '<S5>/legState_FrontRight'
   *   '<S5>/legState_RearLeft'
   *   '<S5>/legState_RearRight'
   */
  1.0F,

  /* Variable: minTransitionMachineSpd
   * Referenced by: '<S1>/TargetStateArbitration'
   */
  0.0F,

  /* Variable: movementTimeOut
   * Referenced by:
   *   '<S129>/errorCheckFL'
   *   '<S129>/errorCheckFR'
   *   '<S129>/errorCheckRL'
   *   '<S129>/errorCheckRR'
   */
  100.0F,

  /* Variable: noMovementTimeOut
   * Referenced by:
   *   '<S129>/errorCheckFL'
   *   '<S129>/errorCheckFR'
   *   '<S129>/errorCheckRL'
   *   '<S129>/errorCheckRR'
   */
  250.0F,

  /* Variable: plausiDistance
   * Referenced by:
   *   '<S246>/plausiCheck'
   *   '<S247>/plausiCheck'
   *   '<S248>/plausiCheck'
   *   '<S249>/plausiCheck'
   */
  5.0F,

  /* Variable: positionSensorFL_BrkPnts
   * Referenced by:
   *   '<S23>/calibrationLogic'
   *   '<S232>/1-D Lookup Table'
   */
  {
    4.0F, 20.0F
  },

  /* Variable: positionSensorFR_BrkPnts
   * Referenced by:
   *   '<S23>/calibrationLogic'
   *   '<S232>/1-D Lookup Table1'
   */
  {
    4.0F, 20.0F
  },

  /* Variable: positionSensorRL_BrkPnts
   * Referenced by:
   *   '<S23>/calibrationLogic'
   *   '<S232>/1-D Lookup Table2'
   */
  {
    4.0F, 20.0F
  },

  /* Variable: positionSensorRR_BrkPnts
   * Referenced by:
   *   '<S23>/calibrationLogic'
   *   '<S232>/1-D Lookup Table3'
   */
  {
    4.0F, 20.0F
  },

  /* Variable: positionSensor_tblData
   * Referenced by:
   *   '<S5>/legState_FrontLeft'
   *   '<S5>/legState_FrontRight'
   *   '<S5>/legState_RearLeft'
   *   '<S5>/legState_RearRight'
   *   '<S6>/TargetPosition'
   *   '<S35>/1-D Lookup Table'
   *   '<S35>/1-D Lookup Table1'
   *   '<S35>/1-D Lookup Table2'
   *   '<S35>/1-D Lookup Table3'
   *   '<S229>/1-D Lookup Table'
   *   '<S229>/1-D Lookup Table1'
   *   '<S229>/1-D Lookup Table2'
   *   '<S229>/1-D Lookup Table3'
   *   '<S232>/1-D Lookup Table'
   *   '<S232>/1-D Lookup Table1'
   *   '<S232>/1-D Lookup Table2'
   *   '<S232>/1-D Lookup Table3'
   */
  {
    0.0F, 500.0F
  },

  /* Variable: sensorCutOffHz
   * Referenced by:
   *   '<S107>/cutoffFreq'
   *   '<S108>/cutoffFreq'
   *   '<S109>/cutoffFreq'
   *   '<S110>/cutoffFreq'
   *   '<S56>/cutoffFreq'
   *   '<S57>/cutoffFreq'
   *   '<S58>/cutoffFreq'
   *   '<S59>/cutoffFreq'
   *   '<S236>/cutoffFreq'
   *   '<S237>/cutoffFreq'
   *   '<S238>/cutoffFreq'
   *   '<S239>/cutoffFreq'
   */
  0.0318309888F,

  /* Variable: trackWidthMax
   * Referenced by: '<S1>/TargetStateArbitration'
   */
  3657.6F,

  /* Variable: trackWidthMin
   * Referenced by: '<S1>/TargetStateArbitration'
   */
  3048.0F,

  /* Variable: trackWidthTolerance
   * Referenced by:
   *   '<S1>/TargetStateArbitration'
   *   '<S181>/enableLogic'
   *   '<S181>/trackWidthOkay'
   *   '<S182>/enableLogic'
   *   '<S182>/trackWidthOkay'
   *   '<S183>/enableLogic'
   *   '<S183>/trackWidthOkay'
   *   '<S184>/enableLogic'
   *   '<S184>/trackWidthOkay'
   */
  6.0F,

  /* Variable: calSettlingTime
   * Referenced by: '<S23>/calibrationLogic'
   */
  4000U,

  /* Variable: calStepTimeOut
   * Referenced by: '<S23>/calibrationLogic'
   */
  120U,

  /* Variable: legMovingTimeout
   * Referenced by:
   *   '<S5>/legState_FrontLeft'
   *   '<S5>/legState_FrontRight'
   *   '<S5>/legState_RearLeft'
   *   '<S5>/legState_RearRight'
   */
  1000U,

  /* Variable: useSensorFilter
   * Referenced by:
   *   '<S107>/useSensorFilter'
   *   '<S108>/useSensorFilter'
   *   '<S109>/useSensorFilter'
   *   '<S110>/useSensorFilter'
   *   '<S56>/useSensorFilter'
   *   '<S57>/useSensorFilter'
   *   '<S58>/useSensorFilter'
   *   '<S59>/useSensorFilter'
   *   '<S236>/useSensorFilter'
   *   '<S237>/useSensorFilter'
   *   '<S238>/useSensorFilter'
   *   '<S239>/useSensorFilter'
   */
  0,

  /* Variable: IOD_OK
   * Referenced by:
   *   '<S1>/TargetStateArbitration'
   *   '<S23>/calibrationLogic'
   *   '<S211>/diagLatch'
   *   '<S211>/diagLatch1'
   *   '<S211>/diagLatch2'
   *   '<S211>/diagLatch3'
   *   '<S211>/diagLatch4'
   *   '<S211>/diagLatch5'
   *   '<S211>/diagLatch6'
   *   '<S211>/diagLatch7'
   *   '<S213>/diagLatch'
   *   '<S213>/diagLatch1'
   *   '<S213>/diagLatch2'
   *   '<S213>/diagLatch3'
   *   '<S213>/diagLatch4'
   *   '<S213>/diagLatch5'
   *   '<S213>/diagLatch6'
   *   '<S213>/diagLatch7'
   *   '<S94>/Constant'
   *   '<S95>/Constant'
   *   '<S96>/Constant'
   *   '<S97>/Constant'
   *   '<S98>/Constant'
   *   '<S99>/Constant'
   *   '<S100>/Constant'
   *   '<S101>/Constant'
   *   '<S102>/Constant'
   *   '<S202>/Constant'
   *   '<S203>/Constant'
   *   '<S204>/Constant'
   *   '<S205>/Constant'
   *   '<S206>/Constant'
   *   '<S207>/Constant'
   *   '<S208>/Constant'
   *   '<S209>/Constant'
   *   '<S69>/diagLatch1'
   *   '<S70>/diagLatch1'
   *   '<S71>/diagLatch1'
   *   '<S72>/diagLatch1'
   *   '<S260>/diagLatch1'
   *   '<S261>/diagLatch1'
   *   '<S262>/diagLatch1'
   *   '<S263>/diagLatch1'
   *   '<S82>/Constant'
   *   '<S84>/Constant'
   *   '<S86>/Constant'
   *   '<S88>/Constant'
   *   '<S273>/Constant'
   *   '<S275>/Constant'
   *   '<S277>/Constant'
   *   '<S279>/Constant'
   */
  0U,

  /* Variable: errDelay
   * Referenced by:
   *   '<S211>/diagLatch'
   *   '<S211>/diagLatch1'
   *   '<S211>/diagLatch2'
   *   '<S211>/diagLatch3'
   *   '<S211>/diagLatch4'
   *   '<S211>/diagLatch5'
   *   '<S211>/diagLatch6'
   *   '<S211>/diagLatch7'
   *   '<S213>/diagLatch'
   *   '<S213>/diagLatch1'
   *   '<S213>/diagLatch2'
   *   '<S213>/diagLatch3'
   *   '<S213>/diagLatch4'
   *   '<S213>/diagLatch5'
   *   '<S213>/diagLatch6'
   *   '<S213>/diagLatch7'
   *   '<S69>/diagLatch1'
   *   '<S70>/diagLatch1'
   *   '<S71>/diagLatch1'
   *   '<S72>/diagLatch1'
   *   '<S246>/plausiCheck'
   *   '<S247>/plausiCheck'
   *   '<S248>/plausiCheck'
   *   '<S249>/plausiCheck'
   *   '<S260>/diagLatch1'
   *   '<S261>/diagLatch1'
   *   '<S262>/diagLatch1'
   *   '<S263>/diagLatch1'
   */
  3U
};

/* Internal Data Grouped For Same Function */
FuncInternalData0_HighClearance_model_T HighClearance_model_FuncInternalData0;

/* External inputs (root inport signals with default storage) */
ExtU_HighClearance_model_T HighClearance_model_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_HighClearance_model_T HighClearance_model_Y;
static void HighClearance_model_legState_FrontLeft_Init
  (FuncInternalData0_legState_FrontLeft_HighClearance_model_T
   *HighClearance_model_FuncGroup0);
static void HighClearance_model_legState_FrontLeft(real32_T rtu_cylPos,
  boolean_T rtu_fieldModeActive, boolean_T rtu_driveCalActive,
  FuncInternalData0_legState_FrontLeft_HighClearance_model_T
  *HighClearance_model_FuncGroup0);
static void HighClearance_model_heightOkayFL_Init
  (FuncInternalData0_heightOkayFL_HighClearance_model_T
   *HighClearance_model_FuncGroup0);
static void HighClearance_model_heightOkayFL(uint8_T rtu_targetState, real32_T
  rtu_legHeightSubject, real32_T rtu_legHeightRef1, real32_T rtu_legHeightRef2,
  real32_T rtu_legHeightRef3, real32_T rtu_tolerance,
  FuncInternalData0_heightOkayFL_HighClearance_model_T
  *HighClearance_model_FuncGroup0);
static void HighClearance_model_diagLatch1_Init
  (FuncInternalData0_diagLatch1_HighClearance_model_T
   *HighClearance_model_FuncGroup0);
static void HighClearance_model_diagLatch1(uint8_T rtu_diagIn, uint8_T
  rtu_plausi, FuncInternalData0_diagLatch1_HighClearance_model_T
  *HighClearance_model_FuncGroup0);
static void HighClearance_model_bangbangPositionControl_FL_Init
  (FuncInternalData0_bangbangPositionControl_FL_HighClearance_model_T
   *HighClearance_model_FuncGroup0);
static void HighClearance_model_bangbangPositionControl_FL_Reset
  (FuncInternalData0_bangbangPositionControl_FL_HighClearance_model_T
   *HighClearance_model_FuncGroup0);
static void HighClearance_model_bangbangPositionControl_FL_Disable
  (FuncInternalData0_bangbangPositionControl_FL_HighClearance_model_T
   *HighClearance_model_FuncGroup0);
static void HighClearance_model_bangbangPositionControl_FL(uint8_T rtu_Enable,
  real32_T rtu_setpoint_mm, real32_T rtu_feedback_mm,
  FuncInternalData0_bangbangPositionControl_FL_HighClearance_model_T
  *HighClearance_model_FuncGroup0);
static void HighClearance_model_errorCheckFL_Init
  (FuncInternalData0_errorCheckFL_HighClearance_model_T
   *HighClearance_model_FuncGroup0);
static void HighClearance_model_errorCheckFL(uint8_T rtu_machineState, uint8_T
  rtu_targetState, uint8_T rtu_legState, real32_T rtu_pwmIn_ex, real32_T
  rtu_pwmIn_rt, boolean_T rtu_override,
  FuncInternalData0_errorCheckFL_HighClearance_model_T
  *HighClearance_model_FuncGroup0);
static void HighClearance_model_enableLogic_Init
  (FuncInternalData0_enableLogic_HighClearance_model_T
   *HighClearance_model_FuncGroup0);
static void HighClearance_model_enableLogic(uint8_T rtu_targetState, uint8_T
  rtu_trackWidthInTolerance, uint8_T rtu_heightInTolerance,
  FuncInternalData0_enableLogic_HighClearance_model_T
  *HighClearance_model_FuncGroup0);
static void HighClearance_model_heightOkay_Init
  (FuncInternalData0_heightOkay_HighClearance_model_T
   *HighClearance_model_FuncGroup0);
static void HighClearance_model_heightOkay(uint8_T rtu_targetState, real32_T
  rtu_legHeightSubject, real32_T rtu_legHeightRef1, real32_T rtu_legHeightRef2,
  real32_T rtu_legHeightRef3, real32_T rtu_tolerance,
  FuncInternalData0_heightOkay_HighClearance_model_T
  *HighClearance_model_FuncGroup0);
static void HighClearance_model_trackWidthOkay_Init
  (FuncInternalData0_trackWidthOkay_HighClearance_model_T
   *HighClearance_model_FuncGroup0);
static void HighClearance_model_trackWidthOkay(real32_T rtu_targetTrackPos,
  real32_T rtu_actualTrackPos, boolean_T rtu_trackCoilErr,
  FuncInternalData0_trackWidthOkay_HighClearance_model_T
  *HighClearance_model_FuncGroup0);
static void HighClearance_model_diagLatch_Init
  (FuncInternalData0_diagLatch_HighClearance_model_T
   *HighClearance_model_FuncGroup0);
static void HighClearance_model_diagLatch(uint8_T rtu_diagIn,
  FuncInternalData0_diagLatch_HighClearance_model_T
  *HighClearance_model_FuncGroup0);
static void HighClearance_model_plausiCheck_Init
  (FuncInternalData0_plausiCheck_HighClearance_model_T
   *HighClearance_model_FuncGroup0);
static void HighClearance_model_plausiCheck(real32_T rtu_positionIn, real32_T
  rtu_positionDelay, boolean_T rtu_enableCheck,
  FuncInternalData0_plausiCheck_HighClearance_model_T
  *HighClearance_model_FuncGroup0);

/* Forward declaration for local functions */
static uint8_T HighClearance_model_checkUpOrDown(real32_T legPos, boolean_T
  rtu_fieldModeActive, boolean_T rtu_driveCalActive);
static void HighClearance_model_enter_internal_normalOperaion(real32_T
  rtu_cylPos, boolean_T rtu_fieldModeActive, boolean_T rtu_driveCalActive,
  FuncInternalData0_legState_FrontLeft_HighClearance_model_T
  *HighClearance_model_FuncGroup0);

/* Forward declaration for local functions */
static uint8_T HighClearance_model_heightInTolerance(uint8_T rtu_targetState,
  real32_T rtu_legHeightSubject, real32_T rtu_legHeightRef1, real32_T
  rtu_legHeightRef2, real32_T rtu_legHeightRef3, real32_T rtu_tolerance);

/* Forward declaration for local functions */
static boolean_T HighClearance_model_movingUpOrDown(uint8_T rtu_legState);
static void HighClearance_model_exit_internal_errorChecking
  (FuncInternalData0_errorCheckFL_HighClearance_model_T
   *HighClearance_model_FuncGroup0);
static void HighClearance_model_resetErrors
  (FuncInternalData0_errorCheckFL_HighClearance_model_T
   *HighClearance_model_FuncGroup0);
static void HighClearance_model_enter_internal_error(uint8_T rtu_targetState,
  FuncInternalData0_errorCheckFL_HighClearance_model_T
  *HighClearance_model_FuncGroup0);

/* Forward declaration for local functions */
static void HighClearance_model_exit_internal_transitioning
  (FuncInternalData0_enableLogic_HighClearance_model_T
   *HighClearance_model_FuncGroup0);

/* Forward declaration for local functions */
static uint8_T HighClearance_model_heightInTolerance_c(uint8_T rtu_targetState,
  real32_T rtu_legHeightSubject, real32_T rtu_legHeightRef1, real32_T
  rtu_legHeightRef2, real32_T rtu_legHeightRef3, real32_T rtu_tolerance);

/* Forward declaration for local functions */
static boolean_T HighClearance_model_trackWidthInTolerance(real32_T
  rtu_targetTrackPos, real32_T rtu_actualTrackPos, boolean_T rtu_trackCoilErr);

/* Forward declaration for local functions */
static void HighClearance_model_setIO(void);
static uint16_T HighClearance_model_checkCalValues(void);
static boolean_T HighClearance_model_checkCalOkay(void);
static boolean_T HighClearance_model_sensorsOkay(void);
static void HighClearance_model_heightDown(void);
static void HighClearance_model_heightStop(void);
static void HighClearance_model_clearCalValues(void);
static boolean_T HighClearance_model_pauseCal(void);
static void HighClearance_model_heightUp(void);
static void HighClearance_model_updateCalUpValues(const real32_T *Switch_a,
  const real32_T *Switch_j, const real32_T *Switch_i, const real32_T *Switch_f);
static uint16_T HighClearance_model_checkDownValues(real32_T FL, real32_T FR,
  real32_T RL, real32_T RR);
static uint16_T HighClearance_model_checkCalDownValues(void);
static uint16_T HighClearance_model_checkUpValues(real32_T FL, real32_T FR,
  real32_T RL, real32_T RR);
static uint16_T HighClearance_model_checkCalUpValues(void);
static void HighClearance_model_updateCalDownValues(const real32_T *Switch_a,
  const real32_T *Switch_j, const real32_T *Switch_i, const real32_T *Switch_f);
static void HighClearance_model_active_c(const boolean_T *LogicalOperator, const
  real32_T *Switch_a, const real32_T *Switch_j, const real32_T *Switch_i, const
  real32_T *Switch_f);
static boolean_T HighClearance_model_checkError(const StateBus
  *BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1);
static boolean_T HighClearance_model_checkCalibrating(void);
static boolean_T HighClearance_model_checkDown(const StateBus
  *BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1);
static boolean_T HighClearance_model_checkUp(const StateBus
  *BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1);
static boolean_T HighClearance_model_checkMovingDown(const StateBus
  *BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1);
static boolean_T HighClearance_model_checkMovingUp(const StateBus
  *BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1);
static boolean_T HighClearance_model_parkBrakeOkay(void);
static boolean_T HighClearance_model_requireSpeed(void);
static boolean_T HighClearance_model_speedOkay(void);
static boolean_T HighClearance_model_wasOkay(void);
static boolean_T HighClearance_model_trackWidthError(void);
static boolean_T HighClearance_model_trackRngCheck(real32_T width);
static boolean_T HighClearance_model_trackWidthOkay_j(void);
static boolean_T HighClearance_model_okayToLower(void);
static boolean_T HighClearance_model_disableLower(void);
static boolean_T HighClearance_model_okayToRaise(void);
static boolean_T HighClearance_model_trackCylError(void);
static boolean_T HighClearance_model_disableRiase(void);
static boolean_T HighClearance_model_calOkay(void);
static void HighClearance_model_clearWarnings(void);
static boolean_T HighClearance_model_noMovementErr(void);
static boolean_T HighClearance_model_targetStateDown(void);
static boolean_T HighClearance_model_targetStateUp(void);
static real_T HighClearance_model_restartTransition(void);
static void HighClearance_model_enter_internal_transitioning(void);
static void HighClearance_model_downWarnings(void);
static void HighClearance_model_upWarnings(void);
static real_T HighClearance_model_pauseTransition(void);
static void HighClearance_model_active(const uint8_T *stopBtn_prev, const
  uint8_T *upBtn_prev, const uint8_T *downBtn_prev);
static boolean_T HighClearance_model_targetStateSelected(void);
static void HighClearance_model_enter_internal_active(void);
static void HighClearance_model_states(const uint8_T *stopBtn_prev, const
  uint8_T *upBtn_prev, const uint8_T *downBtn_prev, const boolean_T
  *engRunning_prev);
static void HighClearance_model_enter_internal_positionStates(const real32_T
  *Switch_p, const real32_T *Switch_c, const real32_T *Switch_pf, const real32_T
  *Switch_al);
static boolean_T HighClearance_model_extendOkay(void);

/*
 * Function for Chart: '<S5>/legState_FrontLeft'
 * function state = checkUpOrDown(legPos)
 */
static uint8_T HighClearance_model_checkUpOrDown(real32_T legPos, boolean_T
  rtu_fieldModeActive, boolean_T rtu_driveCalActive)
{
  uint8_T state;
  real32_T tolerance;

  /* MATLAB Function 'checkUpOrDown': '<S14>:17' */
  /* '<S14>:17:3' if( fieldModeActive || driveCalActive ) */
  if (rtu_fieldModeActive || rtu_driveCalActive)
  {
    /* '<S14>:17:4' tolerance = heightTolerance; */
    tolerance = HighClearance_model_P.heightTolerance;
  }
  else
  {
    /* '<S14>:17:5' else */
    /* '<S14>:17:6' tolerance = heightToleranceRoad; */
    tolerance = HighClearance_model_P.heightToleranceRoad;
  }

  /* '<S14>:17:9' if( legPos >= ( positionSensor_tblData(2) + baseClearance - heightTolerance )) */
  if (legPos >= (HighClearance_model_P.positionSensor_tblData[1] +
                 HighClearance_model_P.baseClearance) -
      HighClearance_model_P.heightTolerance)
  {
    /* '<S14>:17:10' state = heightUp_e; */
    state = heightUp_e;
  }
  else if (legPos <= (HighClearance_model_P.positionSensor_tblData[0] +
                      HighClearance_model_P.baseClearance) + tolerance)
  {
    /* '<S14>:17:11' elseif( legPos <= ( positionSensor_tblData(1) + baseClearance + tolerance )) */
    /* '<S14>:17:12' state = heightDown_e; */
    state = heightDown_e;
  }
  else
  {
    /* '<S14>:17:13' else */
    /* '<S14>:17:14' state = heightUnknown_e; */
    state = heightUnknown_e;
  }

  return state;
}

/* Function for Chart: '<S5>/legState_FrontLeft' */
static void HighClearance_model_enter_internal_normalOperaion(real32_T
  rtu_cylPos, boolean_T rtu_fieldModeActive, boolean_T rtu_driveCalActive,
  FuncInternalData0_legState_FrontLeft_HighClearance_model_T
  *HighClearance_model_FuncGroup0)
{
  /* Chart: '<S5>/legState_FrontLeft' */
  /* Entry Internal 'normalOperaion': '<S14>:104' */
  /* Transition: '<S14>:651' */
  if (HighClearance_model_checkUpOrDown(rtu_cylPos, rtu_fieldModeActive,
       rtu_driveCalActive) == heightUp_e)
  {
    /* Transition: '<S14>:59' */
    HighClearance_model_FuncGroup0->is_normalOperaion =
      HighClearance_model_IN_stopped;

    /* Entry 'stopped': '<S14>:77' */
    HighClearance_model_FuncGroup0->prevPos = rtu_cylPos;
    HighClearance_model_FuncGroup0->is_stopped = HighClearance_model_IN_Up;

    /* Entry 'Up': '<S14>:65' */
    HighClearance_model_FuncGroup0->legState = heightUp_e;
  }
  else
  {
    /* Transition: '<S14>:60' */
    if (HighClearance_model_checkUpOrDown(rtu_cylPos, rtu_fieldModeActive,
         rtu_driveCalActive) == heightDown_e)
    {
      /* Transition: '<S14>:62' */
      HighClearance_model_FuncGroup0->is_normalOperaion =
        HighClearance_model_IN_stopped;

      /* Entry 'stopped': '<S14>:77' */
      HighClearance_model_FuncGroup0->prevPos = rtu_cylPos;
      HighClearance_model_FuncGroup0->is_stopped = HighClearance_model_IN_Down;

      /* Entry 'Down': '<S14>:66' */
      HighClearance_model_FuncGroup0->legState = heightDown_e;
    }
    else
    {
      /* Transition: '<S14>:647' */
      HighClearance_model_FuncGroup0->is_normalOperaion =
        HighClearance_model_IN_stopped;

      /* Entry 'stopped': '<S14>:77' */
      HighClearance_model_FuncGroup0->prevPos = rtu_cylPos;
      HighClearance_model_FuncGroup0->is_stopped =
        HighClearance_model_IN_Unknown;

      /* Entry 'Unknown': '<S14>:67' */
      HighClearance_model_FuncGroup0->legState = heightUnknown_e;
    }
  }

  /* End of Chart: '<S5>/legState_FrontLeft' */
}

/*
 * System initialize for atomic system:
 *    '<S5>/legState_FrontLeft'
 *    '<S5>/legState_FrontRight'
 *    '<S5>/legState_RearLeft'
 *    '<S5>/legState_RearRight'
 */
static void HighClearance_model_legState_FrontLeft_Init
  (FuncInternalData0_legState_FrontLeft_HighClearance_model_T
   *HighClearance_model_FuncGroup0)
{
  HighClearance_model_FuncGroup0->is_normalOperaion =
    HighClearance_model_IN_NO_ACTIVE_CHILD;
  HighClearance_model_FuncGroup0->is_moving =
    HighClearance_model_IN_NO_ACTIVE_CHILD;
  HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;
  HighClearance_model_FuncGroup0->is_stopped =
    HighClearance_model_IN_NO_ACTIVE_CHILD;
  HighClearance_model_FuncGroup0->is_active_c2_HighClearance_library = 0U;
  HighClearance_model_FuncGroup0->is_c2_HighClearance_library =
    HighClearance_model_IN_NO_ACTIVE_CHILD;
  HighClearance_model_FuncGroup0->prevPos = 0.0F;
  HighClearance_model_FuncGroup0->legState = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S5>/legState_FrontLeft'
 *    '<S5>/legState_FrontRight'
 *    '<S5>/legState_RearLeft'
 *    '<S5>/legState_RearRight'
 */
static void HighClearance_model_legState_FrontLeft(real32_T rtu_cylPos,
  boolean_T rtu_fieldModeActive, boolean_T rtu_driveCalActive,
  FuncInternalData0_legState_FrontLeft_HighClearance_model_T
  *HighClearance_model_FuncGroup0)
{
  boolean_T guard1 = false;
  if (HighClearance_model_FuncGroup0->temporalCounter_i1 < 8191U)
  {
    HighClearance_model_FuncGroup0->temporalCounter_i1++;
  }

  /* Chart: '<S5>/legState_FrontLeft' */
  /* Gateway: legState */
  /* During: legState */
  if (HighClearance_model_FuncGroup0->is_active_c2_HighClearance_library == 0U)
  {
    /* Entry: legState */
    HighClearance_model_FuncGroup0->is_active_c2_HighClearance_library = 1U;

    /* Entry Internal: legState */
    /* Transition: '<S14>:106' */
    HighClearance_model_FuncGroup0->is_c2_HighClearance_library =
      HighClearance_model_IN_normalOperaion;
    HighClearance_model_enter_internal_normalOperaion(rtu_cylPos,
      rtu_fieldModeActive, rtu_driveCalActive, HighClearance_model_FuncGroup0);
  }
  else if (HighClearance_model_FuncGroup0->is_c2_HighClearance_library ==
           HighClearance_model_IN_error)
  {
    HighClearance_model_FuncGroup0->legState = heightError_e;

    /* During 'error': '<S14>:105' */
    if (rtu_cylPos > 0.0F)
    {
      /* Transition: '<S14>:108' */
      HighClearance_model_FuncGroup0->is_c2_HighClearance_library =
        HighClearance_model_IN_normalOperaion;
      HighClearance_model_enter_internal_normalOperaion(rtu_cylPos,
        rtu_fieldModeActive, rtu_driveCalActive, HighClearance_model_FuncGroup0);
    }
  }
  else
  {
    /* During 'normalOperaion': '<S14>:104' */
    if (rtu_cylPos <= 0.0F)
    {
      /* Transition: '<S14>:107' */
      /* Exit Internal 'normalOperaion': '<S14>:104' */
      /* Exit Internal 'moving': '<S14>:41' */
      HighClearance_model_FuncGroup0->is_moving =
        HighClearance_model_IN_NO_ACTIVE_CHILD;

      /* Exit Internal 'stopped': '<S14>:77' */
      HighClearance_model_FuncGroup0->is_stopped =
        HighClearance_model_IN_NO_ACTIVE_CHILD;
      HighClearance_model_FuncGroup0->is_normalOperaion =
        HighClearance_model_IN_NO_ACTIVE_CHILD;
      HighClearance_model_FuncGroup0->is_c2_HighClearance_library =
        HighClearance_model_IN_error;

      /* Entry 'error': '<S14>:105' */
      HighClearance_model_FuncGroup0->legState = heightError_e;
    }
    else if (HighClearance_model_FuncGroup0->is_normalOperaion ==
             HighClearance_model_IN_moving)
    {
      /* During 'moving': '<S14>:41' */
      /* Transition: '<S14>:83' */
      /* Transition: '<S14>:80' */
      /* Transition: '<S14>:649' */
      /* Transition: '<S14>:639' */
      /* Transition: '<S14>:646' */
      if (HighClearance_model_checkUpOrDown(rtu_cylPos, rtu_fieldModeActive,
           rtu_driveCalActive) == heightUp_e)
      {
        /* Transition: '<S14>:59' */
        /* Exit Internal 'moving': '<S14>:41' */
        HighClearance_model_FuncGroup0->is_moving =
          HighClearance_model_IN_NO_ACTIVE_CHILD;
        HighClearance_model_FuncGroup0->is_normalOperaion =
          HighClearance_model_IN_stopped;

        /* Entry 'stopped': '<S14>:77' */
        HighClearance_model_FuncGroup0->prevPos = rtu_cylPos;
        HighClearance_model_FuncGroup0->is_stopped = HighClearance_model_IN_Up;

        /* Entry 'Up': '<S14>:65' */
        HighClearance_model_FuncGroup0->legState = heightUp_e;
      }
      else
      {
        /* Transition: '<S14>:60' */
        if (HighClearance_model_checkUpOrDown(rtu_cylPos, rtu_fieldModeActive,
             rtu_driveCalActive) == heightDown_e)
        {
          /* Transition: '<S14>:62' */
          /* Exit Internal 'moving': '<S14>:41' */
          HighClearance_model_FuncGroup0->is_moving =
            HighClearance_model_IN_NO_ACTIVE_CHILD;
          HighClearance_model_FuncGroup0->is_normalOperaion =
            HighClearance_model_IN_stopped;

          /* Entry 'stopped': '<S14>:77' */
          HighClearance_model_FuncGroup0->prevPos = rtu_cylPos;
          HighClearance_model_FuncGroup0->is_stopped =
            HighClearance_model_IN_Down;

          /* Entry 'Down': '<S14>:66' */
          HighClearance_model_FuncGroup0->legState = heightDown_e;
        }
        else
        {
          /* Transition: '<S14>:95' */
          /* Transition: '<S14>:96' */
          if (HighClearance_model_FuncGroup0->prevPos - rtu_cylPos >=
              HighClearance_model_P.minDistanceMoving)
          {
            /* Transition: '<S14>:42' */
            /* Exit Internal 'moving': '<S14>:41' */
            HighClearance_model_FuncGroup0->is_normalOperaion =
              HighClearance_model_IN_moving;
            HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;

            /* Entry 'moving': '<S14>:41' */
            HighClearance_model_FuncGroup0->prevPos = rtu_cylPos;
            HighClearance_model_FuncGroup0->is_moving =
              HighClearance_model_IN_movingDown;

            /* Entry 'movingDown': '<S14>:40' */
            HighClearance_model_FuncGroup0->legState = heightMovingDown_e;
          }
          else
          {
            /* Transition: '<S14>:93' */
            if (rtu_cylPos - HighClearance_model_FuncGroup0->prevPos >=
                HighClearance_model_P.minDistanceMoving)
            {
              /* Transition: '<S14>:39' */
              /* Exit Internal 'moving': '<S14>:41' */
              HighClearance_model_FuncGroup0->is_normalOperaion =
                HighClearance_model_IN_moving;
              HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;

              /* Entry 'moving': '<S14>:41' */
              HighClearance_model_FuncGroup0->prevPos = rtu_cylPos;
              HighClearance_model_FuncGroup0->is_moving =
                HighClearance_model_IN_movingUp;

              /* Entry 'movingUp': '<S14>:36' */
              HighClearance_model_FuncGroup0->legState = heightMovingUp_e;
            }
            else if (HighClearance_model_FuncGroup0->temporalCounter_i1 * 10 >=
                     HighClearance_model_P.legMovingTimeout)
            {
              /* Transition: '<S14>:97' */
              /* Exit Internal 'moving': '<S14>:41' */
              HighClearance_model_FuncGroup0->is_moving =
                HighClearance_model_IN_NO_ACTIVE_CHILD;
              HighClearance_model_FuncGroup0->is_normalOperaion =
                HighClearance_model_IN_stopped;

              /* Entry 'stopped': '<S14>:77' */
              HighClearance_model_FuncGroup0->prevPos = rtu_cylPos;
              HighClearance_model_FuncGroup0->is_stopped =
                HighClearance_model_IN_Unknown;

              /* Entry 'Unknown': '<S14>:67' */
              HighClearance_model_FuncGroup0->legState = heightUnknown_e;
            }
            else if (HighClearance_model_FuncGroup0->is_moving ==
                     HighClearance_model_IN_movingDown)
            {
              HighClearance_model_FuncGroup0->legState = heightMovingDown_e;

              /* During 'movingDown': '<S14>:40' */
            }
            else
            {
              HighClearance_model_FuncGroup0->legState = heightMovingUp_e;

              /* During 'movingUp': '<S14>:36' */
            }
          }
        }
      }
    }
    else
    {
      /* During 'stopped': '<S14>:77' */
      guard1 = false;
      if ((HighClearance_model_checkUpOrDown(rtu_cylPos, rtu_fieldModeActive,
            rtu_driveCalActive) != heightUp_e) &&
          (HighClearance_model_checkUpOrDown(rtu_cylPos, rtu_fieldModeActive,
            rtu_driveCalActive) != heightDown_e))
      {
        /* Transition: '<S14>:92' */
        /* Transition: '<S14>:643' */
        if (HighClearance_model_FuncGroup0->prevPos - rtu_cylPos >=
            HighClearance_model_P.minDistanceMoving)
        {
          /* Transition: '<S14>:42' */
          /* Exit Internal 'stopped': '<S14>:77' */
          HighClearance_model_FuncGroup0->is_stopped =
            HighClearance_model_IN_NO_ACTIVE_CHILD;
          HighClearance_model_FuncGroup0->is_normalOperaion =
            HighClearance_model_IN_moving;
          HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;

          /* Entry 'moving': '<S14>:41' */
          HighClearance_model_FuncGroup0->prevPos = rtu_cylPos;
          HighClearance_model_FuncGroup0->is_moving =
            HighClearance_model_IN_movingDown;

          /* Entry 'movingDown': '<S14>:40' */
          HighClearance_model_FuncGroup0->legState = heightMovingDown_e;
        }
        else
        {
          /* Transition: '<S14>:93' */
          if (rtu_cylPos - HighClearance_model_FuncGroup0->prevPos >=
              HighClearance_model_P.minDistanceMoving)
          {
            /* Transition: '<S14>:39' */
            /* Exit Internal 'stopped': '<S14>:77' */
            HighClearance_model_FuncGroup0->is_stopped =
              HighClearance_model_IN_NO_ACTIVE_CHILD;
            HighClearance_model_FuncGroup0->is_normalOperaion =
              HighClearance_model_IN_moving;
            HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;

            /* Entry 'moving': '<S14>:41' */
            HighClearance_model_FuncGroup0->prevPos = rtu_cylPos;
            HighClearance_model_FuncGroup0->is_moving =
              HighClearance_model_IN_movingUp;

            /* Entry 'movingUp': '<S14>:36' */
            HighClearance_model_FuncGroup0->legState = heightMovingUp_e;
          }
          else
          {
            guard1 = true;
          }
        }
      }
      else
      {
        guard1 = true;
      }

      if (guard1)
      {
        switch (HighClearance_model_FuncGroup0->is_stopped)
        {
         case HighClearance_model_IN_Down:
          HighClearance_model_FuncGroup0->legState = heightDown_e;

          /* During 'Down': '<S14>:66' */
          break;

         case HighClearance_model_IN_Unknown:
          HighClearance_model_FuncGroup0->legState = heightUnknown_e;

          /* During 'Unknown': '<S14>:67' */
          /* Transition: '<S14>:650' */
          /* Transition: '<S14>:649' */
          /* Transition: '<S14>:639' */
          /* Transition: '<S14>:646' */
          if (HighClearance_model_checkUpOrDown(rtu_cylPos, rtu_fieldModeActive,
               rtu_driveCalActive) == heightUp_e)
          {
            /* Transition: '<S14>:59' */
            HighClearance_model_FuncGroup0->is_normalOperaion =
              HighClearance_model_IN_stopped;

            /* Entry 'stopped': '<S14>:77' */
            HighClearance_model_FuncGroup0->prevPos = rtu_cylPos;
            HighClearance_model_FuncGroup0->is_stopped =
              HighClearance_model_IN_Up;

            /* Entry 'Up': '<S14>:65' */
            HighClearance_model_FuncGroup0->legState = heightUp_e;
          }
          else
          {
            /* Transition: '<S14>:60' */
            if (HighClearance_model_checkUpOrDown(rtu_cylPos,
                 rtu_fieldModeActive, rtu_driveCalActive) == heightDown_e)
            {
              /* Transition: '<S14>:62' */
              HighClearance_model_FuncGroup0->is_normalOperaion =
                HighClearance_model_IN_stopped;

              /* Entry 'stopped': '<S14>:77' */
              HighClearance_model_FuncGroup0->prevPos = rtu_cylPos;
              HighClearance_model_FuncGroup0->is_stopped =
                HighClearance_model_IN_Down;

              /* Entry 'Down': '<S14>:66' */
              HighClearance_model_FuncGroup0->legState = heightDown_e;
            }
          }
          break;

         default:
          HighClearance_model_FuncGroup0->legState = heightUp_e;

          /* During 'Up': '<S14>:65' */
          break;
        }
      }
    }
  }

  /* End of Chart: '<S5>/legState_FrontLeft' */
}

/* Function for Chart: '<S29>/heightOkayFL' */
static uint8_T HighClearance_model_heightInTolerance(uint8_T rtu_targetState,
  real32_T rtu_legHeightSubject, real32_T rtu_legHeightRef1, real32_T
  rtu_legHeightRef2, real32_T rtu_legHeightRef3, real32_T rtu_tolerance)
{
  uint8_T out;

  /* Graphical Function 'heightInTolerance': '<S48>:49' */
  /* Transition: '<S48>:171' */
  if (rtu_legHeightSubject != 0.0F)
  {
    /* Transition: '<S48>:170' */
    if (((rtu_targetState == heightDown_e) || (rtu_targetState ==
          heightMovingDown_e)) && ((rtu_legHeightRef1 - rtu_legHeightSubject <=
          rtu_tolerance) || (rtu_legHeightRef1 == 0.0F)))
    {
      /* Transition: '<S48>:73' */
      /* Transition: '<S48>:85' */
      /* Transition: '<S48>:139' */
      /* Transition: '<S48>:141' */
      /* Transition: '<S48>:138' */
      /* Transition: '<S48>:137' */
      if ((rtu_legHeightRef2 == 0.0F) || (rtu_legHeightRef2 -
           rtu_legHeightSubject <= rtu_tolerance))
      {
        /* Transition: '<S48>:145' */
        /* Transition: '<S48>:143' */
        /* Transition: '<S48>:144' */
        /* Transition: '<S48>:89' */
        /* Transition: '<S48>:136' */
        if ((rtu_legHeightRef3 == 0.0F) || (rtu_legHeightRef3 -
             rtu_legHeightSubject <= rtu_tolerance))
        {
          /* Transition: '<S48>:152' */
          /* Transition: '<S48>:159' */
          /* Transition: '<S48>:154' */
          /* Transition: '<S48>:90' */
          /* Transition: '<S48>:92' */
          out = 1U;
        }
        else
        {
          /* Transition: '<S48>:135' */
          /* Transition: '<S48>:76' */
          out = 0U;
        }
      }
      else
      {
        /* Transition: '<S48>:134' */
        /* Transition: '<S48>:115' */
        /* Transition: '<S48>:76' */
        out = 0U;
      }
    }
    else if (((rtu_targetState == heightUp_e) || (rtu_targetState ==
               heightMovingUp_e)) && ((rtu_legHeightRef1 == 0.0F) ||
              (rtu_legHeightSubject - rtu_legHeightRef1 <= rtu_tolerance)) &&
             ((rtu_legHeightRef2 == 0.0F) || (rtu_legHeightSubject -
               rtu_legHeightRef2 <= rtu_tolerance)))
    {
      /* Transition: '<S48>:74' */
      /* Transition: '<S48>:107' */
      /* Transition: '<S48>:109' */
      /* Transition: '<S48>:110' */
      /* Transition: '<S48>:78' */
      /* Transition: '<S48>:123' */
      /* Transition: '<S48>:118' */
      /* Transition: '<S48>:120' */
      /* Transition: '<S48>:121' */
      /* Transition: '<S48>:82' */
      /* Transition: '<S48>:126' */
      if ((rtu_legHeightRef3 == 0.0F) || (rtu_legHeightSubject -
           rtu_legHeightRef3 <= rtu_tolerance))
      {
        /* Transition: '<S48>:127' */
        /* Transition: '<S48>:129' */
        /* Transition: '<S48>:130' */
        /* Transition: '<S48>:83' */
        /* Transition: '<S48>:84' */
        out = 1U;
      }
      else
      {
        /* Transition: '<S48>:116' */
        /* Transition: '<S48>:76' */
        out = 0U;
      }
    }
    else
    {
      /* Transition: '<S48>:112' */
      /* Transition: '<S48>:113' */
      /* Transition: '<S48>:115' */
      /* Transition: '<S48>:76' */
      out = 0U;
    }

    /* Transition: '<S48>:180' */
  }
  else
  {
    /* Transition: '<S48>:176' */
    /* Transition: '<S48>:174' */
    /* Transition: '<S48>:178' */
    out = 3U;
  }

  return out;
}

/*
 * System initialize for atomic system:
 *    '<S29>/heightOkayFL'
 *    '<S29>/heightOkayFR'
 *    '<S29>/heightOkayRL'
 *    '<S29>/heightOkayRR'
 */
static void HighClearance_model_heightOkayFL_Init
  (FuncInternalData0_heightOkayFL_HighClearance_model_T
   *HighClearance_model_FuncGroup0)
{
  HighClearance_model_FuncGroup0->is_active_c18_HighClearance_library = 0U;
  HighClearance_model_FuncGroup0->enable_e = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S29>/heightOkayFL'
 *    '<S29>/heightOkayFR'
 *    '<S29>/heightOkayRL'
 *    '<S29>/heightOkayRR'
 */
static void HighClearance_model_heightOkayFL(uint8_T rtu_targetState, real32_T
  rtu_legHeightSubject, real32_T rtu_legHeightRef1, real32_T rtu_legHeightRef2,
  real32_T rtu_legHeightRef3, real32_T rtu_tolerance,
  FuncInternalData0_heightOkayFL_HighClearance_model_T
  *HighClearance_model_FuncGroup0)
{
  /* Chart: '<S29>/heightOkayFL' */
  /* Gateway: heightOkay */
  /* During: heightOkay */
  if (HighClearance_model_FuncGroup0->is_active_c18_HighClearance_library == 0U)
  {
    /* Entry: heightOkay */
    HighClearance_model_FuncGroup0->is_active_c18_HighClearance_library = 1U;

    /* Entry Internal: heightOkay */
    /* Transition: '<S48>:32' */
    /* Entry 'checkTolerance': '<S48>:31' */
    HighClearance_model_FuncGroup0->enable_e =
      HighClearance_model_heightInTolerance(rtu_targetState,
      rtu_legHeightSubject, rtu_legHeightRef1, rtu_legHeightRef2,
      rtu_legHeightRef3, rtu_tolerance);
  }
  else
  {
    /* During 'checkTolerance': '<S48>:31' */
    HighClearance_model_FuncGroup0->enable_e =
      HighClearance_model_heightInTolerance(rtu_targetState,
      rtu_legHeightSubject, rtu_legHeightRef1, rtu_legHeightRef2,
      rtu_legHeightRef3, rtu_tolerance);
  }

  /* End of Chart: '<S29>/heightOkayFL' */
}

/*
 * System initialize for atomic system:
 *    '<S69>/diagLatch1'
 *    '<S70>/diagLatch1'
 *    '<S71>/diagLatch1'
 *    '<S72>/diagLatch1'
 *    '<S260>/diagLatch1'
 *    '<S261>/diagLatch1'
 *    '<S262>/diagLatch1'
 *    '<S263>/diagLatch1'
 */
static void HighClearance_model_diagLatch1_Init
  (FuncInternalData0_diagLatch1_HighClearance_model_T
   *HighClearance_model_FuncGroup0)
{
  HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;
  HighClearance_model_FuncGroup0->is_active_c3_HighClearance_library = 0U;
  HighClearance_model_FuncGroup0->is_c3_HighClearance_library =
    HighClearance_model_IN_NO_ACTIVE_CHILD_m;
  HighClearance_model_FuncGroup0->diagOut = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S69>/diagLatch1'
 *    '<S70>/diagLatch1'
 *    '<S71>/diagLatch1'
 *    '<S72>/diagLatch1'
 *    '<S260>/diagLatch1'
 *    '<S261>/diagLatch1'
 *    '<S262>/diagLatch1'
 *    '<S263>/diagLatch1'
 */
static void HighClearance_model_diagLatch1(uint8_T rtu_diagIn, uint8_T
  rtu_plausi, FuncInternalData0_diagLatch1_HighClearance_model_T
  *HighClearance_model_FuncGroup0)
{
  if (HighClearance_model_FuncGroup0->temporalCounter_i1 < 32767U)
  {
    HighClearance_model_FuncGroup0->temporalCounter_i1++;
  }

  /* Chart: '<S69>/diagLatch1' */
  /* Gateway: positionToClearance/diagLatch1 */
  /* During: positionToClearance/diagLatch1 */
  if (HighClearance_model_FuncGroup0->is_active_c3_HighClearance_library == 0U)
  {
    /* Entry: positionToClearance/diagLatch1 */
    HighClearance_model_FuncGroup0->is_active_c3_HighClearance_library = 1U;

    /* Entry Internal: positionToClearance/diagLatch1 */
    /* Transition: '<S83>:13' */
    HighClearance_model_FuncGroup0->is_c3_HighClearance_library =
      HighClearance_model_IN_noError;
    HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;

    /* Entry 'noError': '<S83>:3' */
    HighClearance_model_FuncGroup0->diagOut = HighClearance_model_P.IOD_OK;
  }
  else
  {
    switch (HighClearance_model_FuncGroup0->is_c3_HighClearance_library)
    {
     case HighClearance_model_IN_IoErr:
      /* During 'IoErr': '<S83>:24' */
      break;

     case HighClearance_model_IN_noError:
      /* During 'noError': '<S83>:3' */
      if (HighClearance_model_FuncGroup0->temporalCounter_i1 >=
          HighClearance_model_P.errDelay * 100)
      {
        /* Transition: '<S83>:15' */
        if (rtu_diagIn != 0)
        {
          /* Transition: '<S83>:11' */
          HighClearance_model_FuncGroup0->is_c3_HighClearance_library =
            HighClearance_model_IN_IoErr;

          /* Entry 'IoErr': '<S83>:24' */
          HighClearance_model_FuncGroup0->diagOut = rtu_diagIn;
        }
        else
        {
          /* Transition: '<S83>:20' */
          if (rtu_plausi != 0)
          {
            /* Transition: '<S83>:21' */
            HighClearance_model_FuncGroup0->is_c3_HighClearance_library =
              HighClearance_model_IN_plausiErr;

            /* Entry 'plausiErr': '<S83>:22' */
            HighClearance_model_FuncGroup0->diagOut = MAX_uint8_T;
          }
        }
      }
      break;

     default:
      /* During 'plausiErr': '<S83>:22' */
      if (rtu_diagIn != 0)
      {
        /* Transition: '<S83>:25' */
        HighClearance_model_FuncGroup0->is_c3_HighClearance_library =
          HighClearance_model_IN_IoErr;

        /* Entry 'IoErr': '<S83>:24' */
        HighClearance_model_FuncGroup0->diagOut = rtu_diagIn;
      }
      break;
    }
  }

  /* End of Chart: '<S69>/diagLatch1' */
}

/*
 * System initialize for enable system:
 *    '<S123>/bangbangPositionControl_FL'
 *    '<S123>/bangbangPositionControl_FR'
 *    '<S123>/bangbangPositionControl_RL'
 *    '<S123>/bangbangPositionControl_RR'
 */
static void HighClearance_model_bangbangPositionControl_FL_Init
  (FuncInternalData0_bangbangPositionControl_FL_HighClearance_model_T
   *HighClearance_model_FuncGroup0)
{
  /* SystemInitialize for Chart: '<S143>/extendRetractLogic' */
  HighClearance_model_FuncGroup0->is_active_c12_HighClearance_library = 0U;
  HighClearance_model_FuncGroup0->is_c12_HighClearance_library =
    HighClearance_model_IN_NO_ACTIVE_CHILD_mw;
  HighClearance_model_FuncGroup0->pwm = 0.0F;
}

/*
 * System reset for enable system:
 *    '<S123>/bangbangPositionControl_FL'
 *    '<S123>/bangbangPositionControl_FR'
 *    '<S123>/bangbangPositionControl_RL'
 *    '<S123>/bangbangPositionControl_RR'
 */
static void HighClearance_model_bangbangPositionControl_FL_Reset
  (FuncInternalData0_bangbangPositionControl_FL_HighClearance_model_T
   *HighClearance_model_FuncGroup0)
{
  /* SystemReset for Chart: '<S143>/extendRetractLogic' */
  HighClearance_model_FuncGroup0->is_active_c12_HighClearance_library = 0U;
  HighClearance_model_FuncGroup0->is_c12_HighClearance_library =
    HighClearance_model_IN_NO_ACTIVE_CHILD_mw;
  HighClearance_model_FuncGroup0->pwm = 0.0F;
}

/*
 * Disable for enable system:
 *    '<S123>/bangbangPositionControl_FL'
 *    '<S123>/bangbangPositionControl_FR'
 *    '<S123>/bangbangPositionControl_RL'
 *    '<S123>/bangbangPositionControl_RR'
 */
static void HighClearance_model_bangbangPositionControl_FL_Disable
  (FuncInternalData0_bangbangPositionControl_FL_HighClearance_model_T
   *HighClearance_model_FuncGroup0)
{
  /* Disable for Outport: '<S143>/dutyCycle' */
  HighClearance_model_FuncGroup0->pwm = 0.0F;
  HighClearance_model_FuncGroup0->bangbangPositionControl_FL_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S123>/bangbangPositionControl_FL'
 *    '<S123>/bangbangPositionControl_FR'
 *    '<S123>/bangbangPositionControl_RL'
 *    '<S123>/bangbangPositionControl_RR'
 */
static void HighClearance_model_bangbangPositionControl_FL(uint8_T rtu_Enable,
  real32_T rtu_setpoint_mm, real32_T rtu_feedback_mm,
  FuncInternalData0_bangbangPositionControl_FL_HighClearance_model_T
  *HighClearance_model_FuncGroup0)
{
  real32_T rtb_Sum;

  /* Outputs for Enabled SubSystem: '<S123>/bangbangPositionControl_FL' incorporates:
   *  EnablePort: '<S143>/Enable'
   */
  if (rtu_Enable > 0)
  {
    if (!HighClearance_model_FuncGroup0->bangbangPositionControl_FL_MODE)
    {
      HighClearance_model_bangbangPositionControl_FL_Reset
        (HighClearance_model_FuncGroup0);
      HighClearance_model_FuncGroup0->bangbangPositionControl_FL_MODE = true;
    }

    /* Sum: '<S143>/Sum' */
    rtb_Sum = rtu_setpoint_mm - rtu_feedback_mm;

    /* Chart: '<S143>/extendRetractLogic' */
    /* Gateway: bangbangPositionControl/extendRetractLogic */
    /* During: bangbangPositionControl/extendRetractLogic */
    if (HighClearance_model_FuncGroup0->is_active_c12_HighClearance_library ==
        0U)
    {
      /* Entry: bangbangPositionControl/extendRetractLogic */
      HighClearance_model_FuncGroup0->is_active_c12_HighClearance_library = 1U;

      /* Entry Internal: bangbangPositionControl/extendRetractLogic */
      /* Transition: '<S160>:9' */
      HighClearance_model_FuncGroup0->is_c12_HighClearance_library =
        HighClearance_model_IN_stop;

      /* Entry 'stop': '<S160>:8' */
      HighClearance_model_FuncGroup0->pwm = 0.0F;
    }
    else
    {
      switch (HighClearance_model_FuncGroup0->is_c12_HighClearance_library)
      {
       case HighClearance_model_IN_extend:
        HighClearance_model_FuncGroup0->pwm =
          HighClearance_model_P.bangBang_maxOut;

        /* During 'extend': '<S160>:3' */
        if (rtb_Sum < HighClearance_model_P.heightControlToleranceStop)
        {
          /* Transition: '<S160>:11' */
          HighClearance_model_FuncGroup0->is_c12_HighClearance_library =
            HighClearance_model_IN_stop;

          /* Entry 'stop': '<S160>:8' */
          HighClearance_model_FuncGroup0->pwm = 0.0F;
        }
        break;

       case HighClearance_model_IN_retract:
        HighClearance_model_FuncGroup0->pwm =
          -HighClearance_model_P.bangBang_maxOut;

        /* During 'retract': '<S160>:7' */
        if (rtb_Sum > -HighClearance_model_P.heightControlToleranceStop)
        {
          /* Transition: '<S160>:13' */
          HighClearance_model_FuncGroup0->is_c12_HighClearance_library =
            HighClearance_model_IN_stop;

          /* Entry 'stop': '<S160>:8' */
          HighClearance_model_FuncGroup0->pwm = 0.0F;
        }
        break;

       default:
        HighClearance_model_FuncGroup0->pwm = 0.0F;

        /* During 'stop': '<S160>:8' */
        if (rtb_Sum > HighClearance_model_P.heightControlToleranceStart)
        {
          /* Transition: '<S160>:10' */
          HighClearance_model_FuncGroup0->is_c12_HighClearance_library =
            HighClearance_model_IN_extend;

          /* Entry 'extend': '<S160>:3' */
          HighClearance_model_FuncGroup0->pwm =
            HighClearance_model_P.bangBang_maxOut;
        }
        else
        {
          if (rtb_Sum < -HighClearance_model_P.heightControlToleranceStart)
          {
            /* Transition: '<S160>:12' */
            HighClearance_model_FuncGroup0->is_c12_HighClearance_library =
              HighClearance_model_IN_retract;

            /* Entry 'retract': '<S160>:7' */
            HighClearance_model_FuncGroup0->pwm =
              -HighClearance_model_P.bangBang_maxOut;
          }
        }
        break;
      }
    }

    /* End of Chart: '<S143>/extendRetractLogic' */
  }
  else
  {
    if (HighClearance_model_FuncGroup0->bangbangPositionControl_FL_MODE)
    {
      HighClearance_model_bangbangPositionControl_FL_Disable
        (HighClearance_model_FuncGroup0);
    }
  }

  /* End of Outputs for SubSystem: '<S123>/bangbangPositionControl_FL' */
}

/* Function for Chart: '<S129>/errorCheckFL' */
static boolean_T HighClearance_model_movingUpOrDown(uint8_T rtu_legState)
{
  boolean_T out;

  /* Graphical Function 'movingUpOrDown': '<S173>:48' */
  /* Transition: '<S173>:50' */
  if ((rtu_legState == heightMovingUp_e) || (rtu_legState == heightMovingDown_e))
  {
    /* Transition: '<S173>:52' */
    /* Transition: '<S173>:57' */
    /* Transition: '<S173>:56' */
    /* Transition: '<S173>:59' */
    out = true;
  }
  else
  {
    /* Transition: '<S173>:54' */
    /* Transition: '<S173>:61' */
    /* Transition: '<S173>:62' */
    out = false;
  }

  return out;
}

/* Function for Chart: '<S129>/errorCheckFL' */
static void HighClearance_model_exit_internal_errorChecking
  (FuncInternalData0_errorCheckFL_HighClearance_model_T
   *HighClearance_model_FuncGroup0)
{
  /* Exit Internal 'errorChecking': '<S173>:36' */
  /* Exit Internal 'positionSensorError': '<S173>:100' */
  /* Exit Internal 'error': '<S173>:104' */
  HighClearance_model_FuncGroup0->is_error =
    HighClearance_model_IN_NO_ACTIVE_CHILD_p;
  HighClearance_model_FuncGroup0->is_positionSensorError =
    HighClearance_model_IN_NO_ACTIVE_CHILD_p;

  /* Exit Internal 'movmentError': '<S173>:99' */
  /* Exit Internal 'states': '<S173>:168' */
  /* Exit Internal 'expectedToMove': '<S173>:22' */
  HighClearance_model_FuncGroup0->is_expectedToMove =
    HighClearance_model_IN_NO_ACTIVE_CHILD_p;

  /* Exit Internal 'notExpectedToMove': '<S173>:24' */
  HighClearance_model_FuncGroup0->is_notExpectedToMove =
    HighClearance_model_IN_NO_ACTIVE_CHILD_p;
  HighClearance_model_FuncGroup0->is_states =
    HighClearance_model_IN_NO_ACTIVE_CHILD_p;
}

/* Function for Chart: '<S129>/errorCheckFL' */
static void HighClearance_model_resetErrors
  (FuncInternalData0_errorCheckFL_HighClearance_model_T
   *HighClearance_model_FuncGroup0)
{
  /* Graphical Function 'resetErrors': '<S173>:160' */
  /* Transition: '<S173>:164' */
  HighClearance_model_FuncGroup0->error.movementErr1 = false;
  HighClearance_model_FuncGroup0->error.movementErr2 = false;
  HighClearance_model_FuncGroup0->error.noMovementErr = false;
}

/* Function for Chart: '<S129>/errorCheckFL' */
static void HighClearance_model_enter_internal_error(uint8_T rtu_targetState,
  FuncInternalData0_errorCheckFL_HighClearance_model_T
  *HighClearance_model_FuncGroup0)
{
  /* Entry Internal 'error': '<S173>:104' */
  /* Transition: '<S173>:113' */
  if (rtu_targetState == heightUp_e)
  {
    /* Transition: '<S173>:129' */
    HighClearance_model_FuncGroup0->is_error = HighClearance_model_IN_up;

    /* Entry 'up': '<S173>:107' */
    HighClearance_model_FuncGroup0->pwmOut_rt = 0.0F;
    HighClearance_model_FuncGroup0->pwmOut_ex =
      HighClearance_model_P.bangBang_maxOut;
  }
  else
  {
    /* Transition: '<S173>:137' */
    if ((rtu_targetState == heightDown_e) || (rtu_targetState ==
         heightMovingDown_e))
    {
      /* Transition: '<S173>:140' */
      /* Transition: '<S173>:221' */
      /* Transition: '<S173>:144' */
      /* Transition: '<S173>:139' */
      HighClearance_model_FuncGroup0->is_error = HighClearance_model_IN_downs;

      /* Entry 'downs': '<S173>:109' */
      HighClearance_model_FuncGroup0->pwmOut_rt =
        HighClearance_model_P.bangBang_maxOut;
      HighClearance_model_FuncGroup0->pwmOut_ex = 0.0F;
    }
    else
    {
      /* Transition: '<S173>:219' */
      /* Transition: '<S173>:145' */
      HighClearance_model_FuncGroup0->is_error = HighClearance_model_IN_other;

      /* Entry 'other': '<S173>:141' */
      HighClearance_model_FuncGroup0->pwmOut_rt = 0.0F;
      HighClearance_model_FuncGroup0->pwmOut_ex = 0.0F;
    }
  }
}

/*
 * System initialize for atomic system:
 *    '<S129>/errorCheckFL'
 *    '<S129>/errorCheckFR'
 *    '<S129>/errorCheckRL'
 *    '<S129>/errorCheckRR'
 */
static void HighClearance_model_errorCheckFL_Init
  (FuncInternalData0_errorCheckFL_HighClearance_model_T
   *HighClearance_model_FuncGroup0)
{
  HighClearance_model_FuncGroup0->is_states =
    HighClearance_model_IN_NO_ACTIVE_CHILD_p;
  HighClearance_model_FuncGroup0->is_expectedToMove =
    HighClearance_model_IN_NO_ACTIVE_CHILD_p;
  HighClearance_model_FuncGroup0->is_notExpectedToMove =
    HighClearance_model_IN_NO_ACTIVE_CHILD_p;
  HighClearance_model_FuncGroup0->is_positionSensorError =
    HighClearance_model_IN_NO_ACTIVE_CHILD_p;
  HighClearance_model_FuncGroup0->is_error =
    HighClearance_model_IN_NO_ACTIVE_CHILD_p;
  HighClearance_model_FuncGroup0->is_errorWithNoCmdStep1 =
    HighClearance_model_IN_NO_ACTIVE_CHILD_p;
  HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;
  HighClearance_model_FuncGroup0->is_active_c13_HighClearance_library = 0U;
  HighClearance_model_FuncGroup0->is_c13_HighClearance_library =
    HighClearance_model_IN_NO_ACTIVE_CHILD_p;
  HighClearance_model_FuncGroup0->pwmOut_ex = 0.0F;
  HighClearance_model_FuncGroup0->pwmOut_rt = 0.0F;
  HighClearance_model_FuncGroup0->ccoReqOff = false;
  HighClearance_model_FuncGroup0->error.movementErr1 = false;
  HighClearance_model_FuncGroup0->error.movementErr2 = false;
  HighClearance_model_FuncGroup0->error.noMovementErr = false;
}

/*
 * Output and update for atomic system:
 *    '<S129>/errorCheckFL'
 *    '<S129>/errorCheckFR'
 *    '<S129>/errorCheckRL'
 *    '<S129>/errorCheckRR'
 */
static void HighClearance_model_errorCheckFL(uint8_T rtu_machineState, uint8_T
  rtu_targetState, uint8_T rtu_legState, real32_T rtu_pwmIn_ex, real32_T
  rtu_pwmIn_rt, boolean_T rtu_override,
  FuncInternalData0_errorCheckFL_HighClearance_model_T
  *HighClearance_model_FuncGroup0)
{
  if (HighClearance_model_FuncGroup0->temporalCounter_i1 < MAX_uint32_T)
  {
    HighClearance_model_FuncGroup0->temporalCounter_i1++;
  }

  /* Gateway: errorCheck */
  HighClearance_model_FuncGroup0->pwmIn_rt_prev =
    HighClearance_model_FuncGroup0->pwmIn_rt_start;
  HighClearance_model_FuncGroup0->pwmIn_rt_start = rtu_pwmIn_rt;
  HighClearance_model_FuncGroup0->pwmIn_ex_prev =
    HighClearance_model_FuncGroup0->pwmIn_ex_start;
  HighClearance_model_FuncGroup0->pwmIn_ex_start = rtu_pwmIn_ex;
  HighClearance_model_FuncGroup0->targetState_prev =
    HighClearance_model_FuncGroup0->targetState_start;
  HighClearance_model_FuncGroup0->targetState_start = rtu_targetState;

  /* Chart: '<S129>/errorCheckFL' */
  /* During: errorCheck */
  if (HighClearance_model_FuncGroup0->is_active_c13_HighClearance_library == 0U)
  {
    HighClearance_model_FuncGroup0->pwmIn_rt_prev = rtu_pwmIn_rt;
    HighClearance_model_FuncGroup0->pwmIn_ex_prev = rtu_pwmIn_ex;
    HighClearance_model_FuncGroup0->targetState_prev = rtu_targetState;

    /* Entry: errorCheck */
    HighClearance_model_FuncGroup0->is_active_c13_HighClearance_library = 1U;

    /* Entry Internal: errorCheck */
    /* Transition: '<S173>:37' */
    HighClearance_model_FuncGroup0->is_c13_HighClearance_library =
      HighClearance_model_IN_errorChecking;

    /* Entry 'errorChecking': '<S173>:36' */
    HighClearance_model_resetErrors(HighClearance_model_FuncGroup0);
    HighClearance_model_FuncGroup0->pwmOut_ex = rtu_pwmIn_ex;
    HighClearance_model_FuncGroup0->pwmOut_rt = rtu_pwmIn_rt;

    /* Entry Internal 'errorChecking': '<S173>:36' */
    /* Entry Internal 'movmentError': '<S173>:99' */
    /* Transition: '<S173>:169' */
    /* Entry Internal 'states': '<S173>:168' */
    /* Transition: '<S173>:86' */
    if ((rtu_pwmIn_ex != 0.0F) || (rtu_pwmIn_rt != 0.0F))
    {
      /* Transition: '<S173>:30' */
      /* Transition: '<S173>:33' */
      HighClearance_model_FuncGroup0->is_states =
        HighClearance_model_IN_expectedToMove;

      /* Entry Internal 'expectedToMove': '<S173>:22' */
      /* Transition: '<S173>:176' */
      HighClearance_model_FuncGroup0->is_expectedToMove =
        HighClearance_model_IN_moving_g;
    }
    else
    {
      /* Transition: '<S173>:87' */
      /* Transition: '<S173>:88' */
      HighClearance_model_FuncGroup0->is_states =
        HighClearance_model_IN_notExpectedToMove;

      /* Entry Internal 'notExpectedToMove': '<S173>:24' */
      /* Transition: '<S173>:35' */
      HighClearance_model_FuncGroup0->is_notExpectedToMove =
        HighClearance_model_IN_stationary;
    }

    /* Entry Internal 'positionSensorError': '<S173>:100' */
    /* Transition: '<S173>:103' */
    HighClearance_model_FuncGroup0->is_positionSensorError =
      HighClearance_model_IN_okay;
  }
  else
  {
    switch (HighClearance_model_FuncGroup0->is_c13_HighClearance_library)
    {
     case HighClearance_model_IN_errorChecking:
      /* During 'errorChecking': '<S173>:36' */
      if ((rtu_machineState == heightCalibrating_e) || rtu_override)
      {
        /* Transition: '<S173>:211' */
        /* Transition: '<S173>:217' */
        HighClearance_model_exit_internal_errorChecking
          (HighClearance_model_FuncGroup0);
        HighClearance_model_FuncGroup0->is_c13_HighClearance_library =
          HighClearance_model_IN_noChecking;

        /* Entry 'noChecking': '<S173>:210' */
        HighClearance_model_FuncGroup0->pwmOut_ex = rtu_pwmIn_ex;
        HighClearance_model_FuncGroup0->pwmOut_rt = rtu_pwmIn_rt;
      }
      else
      {
        HighClearance_model_FuncGroup0->pwmOut_ex = rtu_pwmIn_ex;
        HighClearance_model_FuncGroup0->pwmOut_rt = rtu_pwmIn_rt;

        /* During 'movmentError': '<S173>:99' */
        /* During 'states': '<S173>:168' */
        if ((HighClearance_model_FuncGroup0->pwmIn_ex_prev !=
             HighClearance_model_FuncGroup0->pwmIn_ex_start) ||
            (HighClearance_model_FuncGroup0->pwmIn_rt_prev !=
             HighClearance_model_FuncGroup0->pwmIn_rt_start))
        {
          /* Transition: '<S173>:89' */
          /* Transition: '<S173>:90' */
          /* Exit Internal 'states': '<S173>:168' */
          /* Exit Internal 'expectedToMove': '<S173>:22' */
          HighClearance_model_FuncGroup0->is_expectedToMove =
            HighClearance_model_IN_NO_ACTIVE_CHILD_p;

          /* Exit Internal 'notExpectedToMove': '<S173>:24' */
          HighClearance_model_FuncGroup0->is_notExpectedToMove =
            HighClearance_model_IN_NO_ACTIVE_CHILD_p;

          /* Entry Internal 'states': '<S173>:168' */
          /* Transition: '<S173>:86' */
          if ((rtu_pwmIn_ex != 0.0F) || (rtu_pwmIn_rt != 0.0F))
          {
            /* Transition: '<S173>:30' */
            /* Transition: '<S173>:33' */
            HighClearance_model_FuncGroup0->is_states =
              HighClearance_model_IN_expectedToMove;

            /* Entry Internal 'expectedToMove': '<S173>:22' */
            /* Transition: '<S173>:176' */
            HighClearance_model_FuncGroup0->is_expectedToMove =
              HighClearance_model_IN_moving_g;
          }
          else
          {
            /* Transition: '<S173>:87' */
            /* Transition: '<S173>:88' */
            HighClearance_model_FuncGroup0->is_states =
              HighClearance_model_IN_notExpectedToMove;

            /* Entry Internal 'notExpectedToMove': '<S173>:24' */
            /* Transition: '<S173>:35' */
            HighClearance_model_FuncGroup0->is_notExpectedToMove =
              HighClearance_model_IN_stationary;
          }
        }
        else if (HighClearance_model_FuncGroup0->is_states ==
                 HighClearance_model_IN_expectedToMove)
        {
          /* During 'expectedToMove': '<S173>:22' */
          if (HighClearance_model_FuncGroup0->is_expectedToMove ==
              HighClearance_model_IN_moving_g)
          {
            /* During 'moving': '<S173>:171' */
            if (!HighClearance_model_movingUpOrDown(rtu_legState))
            {
              /* Transition: '<S173>:170' */
              HighClearance_model_FuncGroup0->is_expectedToMove =
                HighClearance_model_IN_stationary;
              HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;
            }
          }
          else
          {
            /* During 'stationary': '<S173>:172' */
            if (HighClearance_model_movingUpOrDown(rtu_legState))
            {
              /* Transition: '<S173>:173' */
              HighClearance_model_FuncGroup0->is_expectedToMove =
                HighClearance_model_IN_moving_g;
            }
            else
            {
              if ((uint32_T)((int32_T)
                             HighClearance_model_FuncGroup0->temporalCounter_i1 *
                             10) >= HighClearance_model_P.noMovementTimeOut)
              {
                /* Transition: '<S173>:177' */
                HighClearance_model_exit_internal_errorChecking
                  (HighClearance_model_FuncGroup0);
                HighClearance_model_FuncGroup0->is_c13_HighClearance_library =
                  HighClearance_model_IN_errorWithCommand;

                /* Entry 'errorWithCommand': '<S173>:179' */
                HighClearance_model_FuncGroup0->error.noMovementErr = true;
              }
            }
          }
        }
        else
        {
          /* During 'notExpectedToMove': '<S173>:24' */
          if (HighClearance_model_FuncGroup0->is_notExpectedToMove ==
              HighClearance_model_IN_moving_g)
          {
            /* During 'moving': '<S173>:38' */
            if (!HighClearance_model_movingUpOrDown(rtu_legState))
            {
              /* Transition: '<S173>:41' */
              HighClearance_model_FuncGroup0->is_notExpectedToMove =
                HighClearance_model_IN_stationary;
            }
            else
            {
              if ((uint32_T)((int32_T)
                             HighClearance_model_FuncGroup0->temporalCounter_i1 *
                             10) >= HighClearance_model_P.movementTimeOut)
              {
                /* Transition: '<S173>:47' */
                HighClearance_model_exit_internal_errorChecking
                  (HighClearance_model_FuncGroup0);
                HighClearance_model_FuncGroup0->is_c13_HighClearance_library =
                  HighClearance_model_IN_errorWithNoCmdStep1;

                /* Entry 'errorWithNoCmdStep1': '<S173>:46' */
                HighClearance_model_FuncGroup0->pwmOut_ex =
                  HighClearance_model_P.bangBang_maxOut;
                HighClearance_model_FuncGroup0->pwmOut_rt =
                  HighClearance_model_P.bangBang_maxOut;
                HighClearance_model_FuncGroup0->error.movementErr1 = true;

                /* Entry Internal 'errorWithNoCmdStep1': '<S173>:46' */
                /* Transition: '<S173>:65' */
                HighClearance_model_FuncGroup0->is_errorWithNoCmdStep1 =
                  HighClearance_model_IN_moving_g;
                HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;
              }
            }
          }
          else
          {
            /* During 'stationary': '<S173>:34' */
            if (HighClearance_model_movingUpOrDown(rtu_legState))
            {
              /* Transition: '<S173>:40' */
              HighClearance_model_FuncGroup0->is_notExpectedToMove =
                HighClearance_model_IN_moving_g;
              HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;
            }
          }
        }

        if (HighClearance_model_FuncGroup0->is_c13_HighClearance_library !=
            HighClearance_model_IN_errorChecking)
        {
        }
        else
        {
          /* During 'positionSensorError': '<S173>:100' */
          if (HighClearance_model_FuncGroup0->is_positionSensorError ==
              HighClearance_model_IN_error_e)
          {
            /* During 'error': '<S173>:104' */
            if (rtu_legState != heightError_e)
            {
              /* Transition: '<S173>:105' */
              /* Exit Internal 'error': '<S173>:104' */
              HighClearance_model_FuncGroup0->is_error =
                HighClearance_model_IN_NO_ACTIVE_CHILD_p;
              HighClearance_model_FuncGroup0->is_positionSensorError =
                HighClearance_model_IN_okay;
            }
            else if (HighClearance_model_FuncGroup0->targetState_prev !=
                     HighClearance_model_FuncGroup0->targetState_start)
            {
              /* Transition: '<S173>:146' */
              /* Exit Internal 'error': '<S173>:104' */
              HighClearance_model_FuncGroup0->is_positionSensorError =
                HighClearance_model_IN_error_e;
              HighClearance_model_enter_internal_error(rtu_targetState,
                HighClearance_model_FuncGroup0);
            }
            else
            {
              switch (HighClearance_model_FuncGroup0->is_error)
              {
               case HighClearance_model_IN_downs:
                /* During 'downs': '<S173>:109' */
                HighClearance_model_FuncGroup0->pwmOut_rt =
                  HighClearance_model_P.bangBang_maxOut;
                HighClearance_model_FuncGroup0->pwmOut_ex = 0.0F;
                break;

               case HighClearance_model_IN_other:
                /* During 'other': '<S173>:141' */
                HighClearance_model_FuncGroup0->pwmOut_rt = 0.0F;
                HighClearance_model_FuncGroup0->pwmOut_ex = 0.0F;
                break;

               default:
                /* During 'up': '<S173>:107' */
                HighClearance_model_FuncGroup0->pwmOut_rt = 0.0F;
                HighClearance_model_FuncGroup0->pwmOut_ex =
                  HighClearance_model_P.bangBang_maxOut;
                break;
              }
            }
          }
          else
          {
            /* During 'okay': '<S173>:102' */
            if (rtu_legState == heightError_e)
            {
              /* Transition: '<S173>:106' */
              HighClearance_model_FuncGroup0->is_positionSensorError =
                HighClearance_model_IN_error_e;
              HighClearance_model_enter_internal_error(rtu_targetState,
                HighClearance_model_FuncGroup0);
            }
          }
        }
      }
      break;

     case HighClearance_model_IN_errorWithCommand:
      /* During 'errorWithCommand': '<S173>:179' */
      if (rtu_targetState == heightUnknown_e)
      {
        /* Transition: '<S173>:190' */
        /* Transition: '<S173>:189' */
        HighClearance_model_FuncGroup0->is_c13_HighClearance_library =
          HighClearance_model_IN_errorChecking;

        /* Entry 'errorChecking': '<S173>:36' */
        HighClearance_model_resetErrors(HighClearance_model_FuncGroup0);
        HighClearance_model_FuncGroup0->pwmOut_ex = rtu_pwmIn_ex;
        HighClearance_model_FuncGroup0->pwmOut_rt = rtu_pwmIn_rt;

        /* Entry Internal 'errorChecking': '<S173>:36' */
        /* Entry Internal 'movmentError': '<S173>:99' */
        /* Transition: '<S173>:169' */
        /* Entry Internal 'states': '<S173>:168' */
        /* Transition: '<S173>:86' */
        if ((rtu_pwmIn_ex != 0.0F) || (rtu_pwmIn_rt != 0.0F))
        {
          /* Transition: '<S173>:30' */
          /* Transition: '<S173>:33' */
          HighClearance_model_FuncGroup0->is_states =
            HighClearance_model_IN_expectedToMove;

          /* Entry Internal 'expectedToMove': '<S173>:22' */
          /* Transition: '<S173>:176' */
          HighClearance_model_FuncGroup0->is_expectedToMove =
            HighClearance_model_IN_moving_g;
        }
        else
        {
          /* Transition: '<S173>:87' */
          /* Transition: '<S173>:88' */
          HighClearance_model_FuncGroup0->is_states =
            HighClearance_model_IN_notExpectedToMove;

          /* Entry Internal 'notExpectedToMove': '<S173>:24' */
          /* Transition: '<S173>:35' */
          HighClearance_model_FuncGroup0->is_notExpectedToMove =
            HighClearance_model_IN_stationary;
        }

        /* Entry Internal 'positionSensorError': '<S173>:100' */
        /* Transition: '<S173>:103' */
        HighClearance_model_FuncGroup0->is_positionSensorError =
          HighClearance_model_IN_okay;
      }
      break;

     case HighClearance_model_IN_errorWithNoCmdStep1:
      /* During 'errorWithNoCmdStep1': '<S173>:46' */
      if (HighClearance_model_FuncGroup0->is_errorWithNoCmdStep1 ==
          HighClearance_model_IN_moving_g)
      {
        /* During 'moving': '<S173>:64' */
        if (!HighClearance_model_movingUpOrDown(rtu_legState))
        {
          /* Transition: '<S173>:67' */
          HighClearance_model_FuncGroup0->is_errorWithNoCmdStep1 =
            HighClearance_model_IN_stationary;
        }
        else
        {
          if ((uint32_T)((int32_T)
                         HighClearance_model_FuncGroup0->temporalCounter_i1 * 10)
              >= HighClearance_model_P.movementTimeOut)
          {
            /* Transition: '<S173>:147' */
            HighClearance_model_FuncGroup0->is_errorWithNoCmdStep1 =
              HighClearance_model_IN_NO_ACTIVE_CHILD_p;
            HighClearance_model_FuncGroup0->is_c13_HighClearance_library =
              HighClearance_model_IN_errorWithNoCmdStep2;

            /* Entry 'errorWithNoCmdStep2': '<S173>:73' */
            HighClearance_model_FuncGroup0->ccoReqOff = true;
            HighClearance_model_FuncGroup0->error.movementErr2 = true;
          }
        }
      }
      else
      {
        /* During 'stationary': '<S173>:66' */
        if (HighClearance_model_movingUpOrDown(rtu_legState))
        {
          /* Transition: '<S173>:68' */
          HighClearance_model_FuncGroup0->is_errorWithNoCmdStep1 =
            HighClearance_model_IN_moving_g;
          HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;
        }
      }
      break;

     case HighClearance_model_IN_errorWithNoCmdStep2:
      HighClearance_model_FuncGroup0->ccoReqOff = true;

      /* During 'errorWithNoCmdStep2': '<S173>:73' */
      break;

     default:
      /* During 'noChecking': '<S173>:210' */
      if ((rtu_machineState != heightCalibrating_e) && (!rtu_override))
      {
        /* Transition: '<S173>:213' */
        /* Transition: '<S173>:216' */
        HighClearance_model_FuncGroup0->is_c13_HighClearance_library =
          HighClearance_model_IN_errorChecking;

        /* Entry 'errorChecking': '<S173>:36' */
        HighClearance_model_resetErrors(HighClearance_model_FuncGroup0);
        HighClearance_model_FuncGroup0->pwmOut_ex = rtu_pwmIn_ex;
        HighClearance_model_FuncGroup0->pwmOut_rt = rtu_pwmIn_rt;

        /* Entry Internal 'errorChecking': '<S173>:36' */
        /* Entry Internal 'movmentError': '<S173>:99' */
        /* Transition: '<S173>:169' */
        /* Entry Internal 'states': '<S173>:168' */
        /* Transition: '<S173>:86' */
        if ((rtu_pwmIn_ex != 0.0F) || (rtu_pwmIn_rt != 0.0F))
        {
          /* Transition: '<S173>:30' */
          /* Transition: '<S173>:33' */
          HighClearance_model_FuncGroup0->is_states =
            HighClearance_model_IN_expectedToMove;

          /* Entry Internal 'expectedToMove': '<S173>:22' */
          /* Transition: '<S173>:176' */
          HighClearance_model_FuncGroup0->is_expectedToMove =
            HighClearance_model_IN_moving_g;
        }
        else
        {
          /* Transition: '<S173>:87' */
          /* Transition: '<S173>:88' */
          HighClearance_model_FuncGroup0->is_states =
            HighClearance_model_IN_notExpectedToMove;

          /* Entry Internal 'notExpectedToMove': '<S173>:24' */
          /* Transition: '<S173>:35' */
          HighClearance_model_FuncGroup0->is_notExpectedToMove =
            HighClearance_model_IN_stationary;
        }

        /* Entry Internal 'positionSensorError': '<S173>:100' */
        /* Transition: '<S173>:103' */
        HighClearance_model_FuncGroup0->is_positionSensorError =
          HighClearance_model_IN_okay;
      }
      else
      {
        HighClearance_model_FuncGroup0->pwmOut_ex = rtu_pwmIn_ex;
        HighClearance_model_FuncGroup0->pwmOut_rt = rtu_pwmIn_rt;
      }
      break;
    }
  }

  /* End of Chart: '<S129>/errorCheckFL' */
}

/* Function for Chart: '<S181>/enableLogic' */
static void HighClearance_model_exit_internal_transitioning
  (FuncInternalData0_enableLogic_HighClearance_model_T
   *HighClearance_model_FuncGroup0)
{
  /* Exit Internal 'transitioning': '<S189>:168' */
  switch (HighClearance_model_FuncGroup0->is_transitioning)
  {
   case HighClearance_model_IN_badHeight:
    /* Exit Internal 'badHeight': '<S189>:197' */
    if (HighClearance_model_FuncGroup0->is_badHeight ==
        HighClearance_model_IN_warning)
    {
      /* Exit 'warning': '<S189>:196' */
      HighClearance_model_FuncGroup0->warningHeight = 0U;
      HighClearance_model_FuncGroup0->is_badHeight =
        HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
    }
    else
    {
      HighClearance_model_FuncGroup0->is_badHeight =
        HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
    }

    HighClearance_model_FuncGroup0->is_transitioning =
      HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
    break;

   case HighClearance_model_IN_badTrack:
    /* Exit Internal 'badTrack': '<S189>:179' */
    if (HighClearance_model_FuncGroup0->is_badTrack ==
        HighClearance_model_IN_warning)
    {
      /* Exit 'warning': '<S189>:192' */
      HighClearance_model_FuncGroup0->warningTrack = 0U;
      HighClearance_model_FuncGroup0->is_badTrack =
        HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
    }
    else
    {
      HighClearance_model_FuncGroup0->is_badTrack =
        HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
    }

    HighClearance_model_FuncGroup0->is_transitioning =
      HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
    break;

   default:
    HighClearance_model_FuncGroup0->is_transitioning =
      HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
    break;
  }
}

/*
 * System initialize for atomic system:
 *    '<S181>/enableLogic'
 *    '<S182>/enableLogic'
 *    '<S183>/enableLogic'
 *    '<S184>/enableLogic'
 */
static void HighClearance_model_enableLogic_Init
  (FuncInternalData0_enableLogic_HighClearance_model_T
   *HighClearance_model_FuncGroup0)
{
  HighClearance_model_FuncGroup0->is_disabled =
    HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
  HighClearance_model_FuncGroup0->is_transitioning =
    HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
  HighClearance_model_FuncGroup0->is_badHeight =
    HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
  HighClearance_model_FuncGroup0->is_badTrack =
    HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
  HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;
  HighClearance_model_FuncGroup0->is_active_c19_HighClearance_library = 0U;
  HighClearance_model_FuncGroup0->is_c19_HighClearance_library =
    HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
  HighClearance_model_FuncGroup0->enable = 0U;
  HighClearance_model_FuncGroup0->warningTrack = 0U;
  HighClearance_model_FuncGroup0->warningHeight = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S181>/enableLogic'
 *    '<S182>/enableLogic'
 *    '<S183>/enableLogic'
 *    '<S184>/enableLogic'
 */
static void HighClearance_model_enableLogic(uint8_T rtu_targetState, uint8_T
  rtu_trackWidthInTolerance, uint8_T rtu_heightInTolerance,
  FuncInternalData0_enableLogic_HighClearance_model_T
  *HighClearance_model_FuncGroup0)
{
  if (HighClearance_model_FuncGroup0->temporalCounter_i1 < MAX_uint32_T)
  {
    HighClearance_model_FuncGroup0->temporalCounter_i1++;
  }

  /* Chart: '<S181>/enableLogic' */
  /* Gateway: enableLogic */
  /* During: enableLogic */
  if (HighClearance_model_FuncGroup0->is_active_c19_HighClearance_library == 0U)
  {
    /* Entry: enableLogic */
    HighClearance_model_FuncGroup0->is_active_c19_HighClearance_library = 1U;

    /* Entry Internal: enableLogic */
    /* Transition: '<S189>:32' */
    HighClearance_model_FuncGroup0->is_c19_HighClearance_library =
      HighClearance_model_IN_disabled;

    /* Entry 'disabled': '<S189>:31' */
    HighClearance_model_FuncGroup0->enable = 0U;

    /* Entry Internal 'disabled': '<S189>:31' */
    /* Transition: '<S189>:169' */
    HighClearance_model_FuncGroup0->is_disabled =
      HighClearance_model_IN_NotTransitioning;

    /* Entry 'NotTransitioning': '<S189>:167' */
    HighClearance_model_FuncGroup0->warningTrack = 0U;
    HighClearance_model_FuncGroup0->warningHeight = 0U;
  }
  else if (HighClearance_model_FuncGroup0->is_c19_HighClearance_library ==
           HighClearance_model_IN_disabled)
  {
    HighClearance_model_FuncGroup0->enable = 0U;

    /* During 'disabled': '<S189>:31' */
    if ((rtu_trackWidthInTolerance != 0) && (rtu_heightInTolerance == 1))
    {
      /* Transition: '<S189>:39' */
      /* Transition: '<S189>:59' */
      /* Exit Internal 'disabled': '<S189>:31' */
      if (HighClearance_model_FuncGroup0->is_disabled ==
          HighClearance_model_IN_transitioning)
      {
        HighClearance_model_exit_internal_transitioning
          (HighClearance_model_FuncGroup0);
        HighClearance_model_FuncGroup0->is_disabled =
          HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
      }
      else
      {
        HighClearance_model_FuncGroup0->is_disabled =
          HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
      }

      HighClearance_model_FuncGroup0->is_c19_HighClearance_library =
        HighClearance_model_IN_enabled;

      /* Entry 'enabled': '<S189>:33' */
      HighClearance_model_FuncGroup0->enable = 1U;
    }
    else if (HighClearance_model_FuncGroup0->is_disabled ==
             HighClearance_model_IN_NotTransitioning)
    {
      /* During 'NotTransitioning': '<S189>:167' */
      if ((rtu_targetState == heightMovingUp_e) || (rtu_targetState ==
           heightMovingDown_e))
      {
        /* Transition: '<S189>:176' */
        /* Transition: '<S189>:175' */
        HighClearance_model_FuncGroup0->is_disabled =
          HighClearance_model_IN_transitioning;

        /* Entry Internal 'transitioning': '<S189>:168' */
        /* Transition: '<S189>:182' */
        HighClearance_model_FuncGroup0->is_transitioning =
          HighClearance_model_IN_okay_o;
      }
    }
    else
    {
      /* During 'transitioning': '<S189>:168' */
      if ((rtu_targetState != heightMovingDown_e) && (rtu_targetState !=
           heightMovingUp_e))
      {
        /* Transition: '<S189>:184' */
        /* Transition: '<S189>:185' */
        HighClearance_model_exit_internal_transitioning
          (HighClearance_model_FuncGroup0);
        HighClearance_model_FuncGroup0->is_disabled =
          HighClearance_model_IN_NotTransitioning;

        /* Entry 'NotTransitioning': '<S189>:167' */
        HighClearance_model_FuncGroup0->warningTrack = 0U;
        HighClearance_model_FuncGroup0->warningHeight = 0U;
      }
      else
      {
        switch (HighClearance_model_FuncGroup0->is_transitioning)
        {
         case HighClearance_model_IN_badHeight:
          /* During 'badHeight': '<S189>:197' */
          if (rtu_heightInTolerance != 0)
          {
            /* Transition: '<S189>:189' */
            /* Exit Internal 'badHeight': '<S189>:197' */
            if (HighClearance_model_FuncGroup0->is_badHeight ==
                HighClearance_model_IN_warning)
            {
              /* Exit 'warning': '<S189>:196' */
              HighClearance_model_FuncGroup0->warningHeight = 0U;
              HighClearance_model_FuncGroup0->is_badHeight =
                HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
            }
            else
            {
              HighClearance_model_FuncGroup0->is_badHeight =
                HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
            }

            HighClearance_model_FuncGroup0->is_transitioning =
              HighClearance_model_IN_okay_o;
          }
          else if ((HighClearance_model_FuncGroup0->is_badHeight ==
                    HighClearance_model_IN_wait) &&
                   (HighClearance_model_FuncGroup0->temporalCounter_i1 >=
                    HighClearance_model_P.ctrlWarningTime * 100.0F))
          {
            /* During 'wait': '<S189>:195' */
            /* Transition: '<S189>:194' */
            HighClearance_model_FuncGroup0->is_badHeight =
              HighClearance_model_IN_warning;

            /* Entry 'warning': '<S189>:196' */
            HighClearance_model_FuncGroup0->warningHeight = 1U;
          }
          else
          {
            /* During 'warning': '<S189>:196' */
          }
          break;

         case HighClearance_model_IN_badTrack:
          /* During 'badTrack': '<S189>:179' */
          if (rtu_trackWidthInTolerance != 0)
          {
            /* Transition: '<S189>:186' */
            /* Exit Internal 'badTrack': '<S189>:179' */
            if (HighClearance_model_FuncGroup0->is_badTrack ==
                HighClearance_model_IN_warning)
            {
              /* Exit 'warning': '<S189>:192' */
              HighClearance_model_FuncGroup0->warningTrack = 0U;
              HighClearance_model_FuncGroup0->is_badTrack =
                HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
            }
            else
            {
              HighClearance_model_FuncGroup0->is_badTrack =
                HighClearance_model_IN_NO_ACTIVE_CHILD_ao;
            }

            HighClearance_model_FuncGroup0->is_transitioning =
              HighClearance_model_IN_okay_o;
          }
          else if ((HighClearance_model_FuncGroup0->is_badTrack ==
                    HighClearance_model_IN_wait) &&
                   (HighClearance_model_FuncGroup0->temporalCounter_i1 >=
                    HighClearance_model_P.ctrlWarningTime * 100.0F))
          {
            /* During 'wait': '<S189>:190' */
            /* Transition: '<S189>:193' */
            HighClearance_model_FuncGroup0->is_badTrack =
              HighClearance_model_IN_warning;

            /* Entry 'warning': '<S189>:192' */
            HighClearance_model_FuncGroup0->warningTrack = 1U;
          }
          else
          {
            /* During 'warning': '<S189>:192' */
          }
          break;

         default:
          /* During 'okay': '<S189>:181' */
          if (rtu_trackWidthInTolerance == 0)
          {
            /* Transition: '<S189>:180' */
            HighClearance_model_FuncGroup0->is_transitioning =
              HighClearance_model_IN_badTrack;

            /* Entry Internal 'badTrack': '<S189>:179' */
            /* Transition: '<S189>:191' */
            HighClearance_model_FuncGroup0->is_badTrack =
              HighClearance_model_IN_wait;
            HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;
          }
          else
          {
            if (rtu_heightInTolerance == 0)
            {
              /* Transition: '<S189>:188' */
              HighClearance_model_FuncGroup0->is_transitioning =
                HighClearance_model_IN_badHeight;

              /* Entry Internal 'badHeight': '<S189>:197' */
              /* Transition: '<S189>:198' */
              HighClearance_model_FuncGroup0->is_badHeight =
                HighClearance_model_IN_wait;
              HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;
            }
          }
          break;
        }
      }
    }
  }
  else
  {
    HighClearance_model_FuncGroup0->enable = 1U;

    /* During 'enabled': '<S189>:33' */
    if ((rtu_heightInTolerance != 1) || (rtu_trackWidthInTolerance == 0))
    {
      /* Transition: '<S189>:60' */
      /* Transition: '<S189>:47' */
      HighClearance_model_FuncGroup0->is_c19_HighClearance_library =
        HighClearance_model_IN_disabled;

      /* Entry 'disabled': '<S189>:31' */
      HighClearance_model_FuncGroup0->enable = 0U;

      /* Entry Internal 'disabled': '<S189>:31' */
      /* Transition: '<S189>:169' */
      HighClearance_model_FuncGroup0->is_disabled =
        HighClearance_model_IN_NotTransitioning;

      /* Entry 'NotTransitioning': '<S189>:167' */
      HighClearance_model_FuncGroup0->warningTrack = 0U;
      HighClearance_model_FuncGroup0->warningHeight = 0U;
    }
  }

  /* End of Chart: '<S181>/enableLogic' */
}

/* Function for Chart: '<S181>/heightOkay' */
static uint8_T HighClearance_model_heightInTolerance_c(uint8_T rtu_targetState,
  real32_T rtu_legHeightSubject, real32_T rtu_legHeightRef1, real32_T
  rtu_legHeightRef2, real32_T rtu_legHeightRef3, real32_T rtu_tolerance)
{
  uint8_T out;

  /* Graphical Function 'heightInTolerance': '<S190>:49' */
  /* Transition: '<S190>:171' */
  if (rtu_legHeightSubject != 0.0F)
  {
    /* Transition: '<S190>:170' */
    if (((rtu_targetState == heightDown_e) || (rtu_targetState ==
          heightMovingDown_e)) && ((rtu_legHeightRef1 - rtu_legHeightSubject <=
          rtu_tolerance) || (rtu_legHeightRef1 == 0.0F)))
    {
      /* Transition: '<S190>:73' */
      /* Transition: '<S190>:85' */
      /* Transition: '<S190>:139' */
      /* Transition: '<S190>:141' */
      /* Transition: '<S190>:138' */
      /* Transition: '<S190>:137' */
      if ((rtu_legHeightRef2 == 0.0F) || (rtu_legHeightRef2 -
           rtu_legHeightSubject <= rtu_tolerance))
      {
        /* Transition: '<S190>:145' */
        /* Transition: '<S190>:143' */
        /* Transition: '<S190>:144' */
        /* Transition: '<S190>:89' */
        /* Transition: '<S190>:136' */
        if ((rtu_legHeightRef3 == 0.0F) || (rtu_legHeightRef3 -
             rtu_legHeightSubject <= rtu_tolerance))
        {
          /* Transition: '<S190>:152' */
          /* Transition: '<S190>:159' */
          /* Transition: '<S190>:154' */
          /* Transition: '<S190>:90' */
          /* Transition: '<S190>:92' */
          out = 1U;
        }
        else
        {
          /* Transition: '<S190>:135' */
          /* Transition: '<S190>:76' */
          out = 0U;
        }
      }
      else
      {
        /* Transition: '<S190>:134' */
        /* Transition: '<S190>:115' */
        /* Transition: '<S190>:76' */
        out = 0U;
      }
    }
    else if (((rtu_targetState == heightUp_e) || (rtu_targetState ==
               heightMovingUp_e)) && ((rtu_legHeightRef1 == 0.0F) ||
              (rtu_legHeightSubject - rtu_legHeightRef1 <= rtu_tolerance)) &&
             ((rtu_legHeightRef2 == 0.0F) || (rtu_legHeightSubject -
               rtu_legHeightRef2 <= rtu_tolerance)))
    {
      /* Transition: '<S190>:74' */
      /* Transition: '<S190>:107' */
      /* Transition: '<S190>:109' */
      /* Transition: '<S190>:110' */
      /* Transition: '<S190>:78' */
      /* Transition: '<S190>:123' */
      /* Transition: '<S190>:118' */
      /* Transition: '<S190>:120' */
      /* Transition: '<S190>:121' */
      /* Transition: '<S190>:82' */
      /* Transition: '<S190>:126' */
      if ((rtu_legHeightRef3 == 0.0F) || (rtu_legHeightSubject -
           rtu_legHeightRef3 <= rtu_tolerance))
      {
        /* Transition: '<S190>:127' */
        /* Transition: '<S190>:129' */
        /* Transition: '<S190>:130' */
        /* Transition: '<S190>:83' */
        /* Transition: '<S190>:84' */
        out = 1U;
      }
      else
      {
        /* Transition: '<S190>:116' */
        /* Transition: '<S190>:76' */
        out = 0U;
      }
    }
    else
    {
      /* Transition: '<S190>:112' */
      /* Transition: '<S190>:113' */
      /* Transition: '<S190>:115' */
      /* Transition: '<S190>:76' */
      out = 0U;
    }

    /* Transition: '<S190>:180' */
  }
  else
  {
    /* Transition: '<S190>:176' */
    /* Transition: '<S190>:174' */
    /* Transition: '<S190>:178' */
    out = 3U;
  }

  return out;
}

/*
 * System initialize for atomic system:
 *    '<S181>/heightOkay'
 *    '<S182>/heightOkay'
 *    '<S183>/heightOkay'
 *    '<S184>/heightOkay'
 */
static void HighClearance_model_heightOkay_Init
  (FuncInternalData0_heightOkay_HighClearance_model_T
   *HighClearance_model_FuncGroup0)
{
  HighClearance_model_FuncGroup0->is_active_c18_HighClearance_library = 0U;
  HighClearance_model_FuncGroup0->enable_e = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S181>/heightOkay'
 *    '<S182>/heightOkay'
 *    '<S183>/heightOkay'
 *    '<S184>/heightOkay'
 */
static void HighClearance_model_heightOkay(uint8_T rtu_targetState, real32_T
  rtu_legHeightSubject, real32_T rtu_legHeightRef1, real32_T rtu_legHeightRef2,
  real32_T rtu_legHeightRef3, real32_T rtu_tolerance,
  FuncInternalData0_heightOkay_HighClearance_model_T
  *HighClearance_model_FuncGroup0)
{
  /* Chart: '<S181>/heightOkay' */
  /* Gateway: heightOkay */
  /* During: heightOkay */
  if (HighClearance_model_FuncGroup0->is_active_c18_HighClearance_library == 0U)
  {
    /* Entry: heightOkay */
    HighClearance_model_FuncGroup0->is_active_c18_HighClearance_library = 1U;

    /* Entry Internal: heightOkay */
    /* Transition: '<S190>:32' */
    /* Entry 'checkTolerance': '<S190>:31' */
    HighClearance_model_FuncGroup0->enable_e =
      HighClearance_model_heightInTolerance_c(rtu_targetState,
      rtu_legHeightSubject, rtu_legHeightRef1, rtu_legHeightRef2,
      rtu_legHeightRef3, rtu_tolerance);
  }
  else
  {
    /* During 'checkTolerance': '<S190>:31' */
    HighClearance_model_FuncGroup0->enable_e =
      HighClearance_model_heightInTolerance_c(rtu_targetState,
      rtu_legHeightSubject, rtu_legHeightRef1, rtu_legHeightRef2,
      rtu_legHeightRef3, rtu_tolerance);
  }

  /* End of Chart: '<S181>/heightOkay' */
}

/* Function for Chart: '<S181>/trackWidthOkay' */
static boolean_T HighClearance_model_trackWidthInTolerance(real32_T
  rtu_targetTrackPos, real32_T rtu_actualTrackPos, boolean_T rtu_trackCoilErr)
{
  boolean_T out;

  /* Graphical Function 'trackWidthInTolerance': '<S191>:34' */
  /* Transition: '<S191>:36' */
  if ((rtu_actualTrackPos <= 0.0F) || rtu_trackCoilErr || ((rtu_targetTrackPos -
        rtu_actualTrackPos <= HighClearance_model_P.trackWidthTolerance) &&
       (rtu_actualTrackPos - rtu_targetTrackPos <=
        HighClearance_model_P.trackWidthTolerance)))
  {
    /* Transition: '<S191>:172' */
    /* Transition: '<S191>:177' */
    /* Transition: '<S191>:178' */
    /* Transition: '<S191>:171' */
    /* Transition: '<S191>:44' */
    /* Transition: '<S191>:45' */
    /* Transition: '<S191>:168' */
    /* Transition: '<S191>:46' */
    out = true;
  }
  else
  {
    /* Transition: '<S191>:175' */
    /* Transition: '<S191>:166' */
    /* Transition: '<S191>:43' */
    out = false;
  }

  return out;
}

/*
 * System initialize for atomic system:
 *    '<S181>/trackWidthOkay'
 *    '<S182>/trackWidthOkay'
 *    '<S183>/trackWidthOkay'
 *    '<S184>/trackWidthOkay'
 */
static void HighClearance_model_trackWidthOkay_Init
  (FuncInternalData0_trackWidthOkay_HighClearance_model_T
   *HighClearance_model_FuncGroup0)
{
  HighClearance_model_FuncGroup0->is_active_c17_HighClearance_library = 0U;
  HighClearance_model_FuncGroup0->enable = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S181>/trackWidthOkay'
 *    '<S182>/trackWidthOkay'
 *    '<S183>/trackWidthOkay'
 *    '<S184>/trackWidthOkay'
 */
static void HighClearance_model_trackWidthOkay(real32_T rtu_targetTrackPos,
  real32_T rtu_actualTrackPos, boolean_T rtu_trackCoilErr,
  FuncInternalData0_trackWidthOkay_HighClearance_model_T
  *HighClearance_model_FuncGroup0)
{
  /* Chart: '<S181>/trackWidthOkay' */
  /* Gateway: trackWidthOkay */
  /* During: trackWidthOkay */
  if (HighClearance_model_FuncGroup0->is_active_c17_HighClearance_library == 0U)
  {
    /* Entry: trackWidthOkay */
    HighClearance_model_FuncGroup0->is_active_c17_HighClearance_library = 1U;

    /* Entry Internal: trackWidthOkay */
    /* Transition: '<S191>:32' */
    /* Entry 'checkTolerance': '<S191>:31' */
    HighClearance_model_FuncGroup0->enable =
      HighClearance_model_trackWidthInTolerance(rtu_targetTrackPos,
      rtu_actualTrackPos, rtu_trackCoilErr);
  }
  else
  {
    /* During 'checkTolerance': '<S191>:31' */
    HighClearance_model_FuncGroup0->enable =
      HighClearance_model_trackWidthInTolerance(rtu_targetTrackPos,
      rtu_actualTrackPos, rtu_trackCoilErr);
  }

  /* End of Chart: '<S181>/trackWidthOkay' */
}

/*
 * System initialize for atomic system:
 *    '<S211>/diagLatch'
 *    '<S211>/diagLatch1'
 *    '<S211>/diagLatch2'
 *    '<S211>/diagLatch3'
 *    '<S211>/diagLatch4'
 *    '<S211>/diagLatch5'
 *    '<S211>/diagLatch6'
 *    '<S211>/diagLatch7'
 *    '<S213>/diagLatch'
 *    '<S213>/diagLatch1'
 *    ...
 */
static void HighClearance_model_diagLatch_Init
  (FuncInternalData0_diagLatch_HighClearance_model_T
   *HighClearance_model_FuncGroup0)
{
  HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;
  HighClearance_model_FuncGroup0->is_active_c4_HighClearance_library = 0U;
  HighClearance_model_FuncGroup0->is_c4_HighClearance_library =
    HighClearance_model_IN_NO_ACTIVE_CHILD_l;
  HighClearance_model_FuncGroup0->diagOut = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S211>/diagLatch'
 *    '<S211>/diagLatch1'
 *    '<S211>/diagLatch2'
 *    '<S211>/diagLatch3'
 *    '<S211>/diagLatch4'
 *    '<S211>/diagLatch5'
 *    '<S211>/diagLatch6'
 *    '<S211>/diagLatch7'
 *    '<S213>/diagLatch'
 *    '<S213>/diagLatch1'
 *    ...
 */
static void HighClearance_model_diagLatch(uint8_T rtu_diagIn,
  FuncInternalData0_diagLatch_HighClearance_model_T
  *HighClearance_model_FuncGroup0)
{
  if (HighClearance_model_FuncGroup0->temporalCounter_i1 < 32767U)
  {
    HighClearance_model_FuncGroup0->temporalCounter_i1++;
  }

  /* Chart: '<S211>/diagLatch' */
  /* Gateway: diagLatch */
  /* During: diagLatch */
  if (HighClearance_model_FuncGroup0->is_active_c4_HighClearance_library == 0U)
  {
    /* Entry: diagLatch */
    HighClearance_model_FuncGroup0->is_active_c4_HighClearance_library = 1U;

    /* Entry Internal: diagLatch */
    /* Transition: '<S216>:13' */
    HighClearance_model_FuncGroup0->is_c4_HighClearance_library =
      HighClearance_model_IN_noError_f;
    HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;

    /* Entry 'noError': '<S216>:3' */
    HighClearance_model_FuncGroup0->diagOut = HighClearance_model_P.IOD_OK;
  }
  else if ((HighClearance_model_FuncGroup0->is_c4_HighClearance_library ==
            HighClearance_model_IN_error_p) ||
           ((HighClearance_model_FuncGroup0->temporalCounter_i1 <
             HighClearance_model_P.errDelay * 100) || (rtu_diagIn == 0)))
  {
    /* During 'error': '<S216>:1' */
  }
  else
  {
    /* During 'noError': '<S216>:3' */
    /* Transition: '<S216>:15' */
    /* Transition: '<S216>:11' */
    HighClearance_model_FuncGroup0->is_c4_HighClearance_library =
      HighClearance_model_IN_error_p;

    /* Entry 'error': '<S216>:1' */
    HighClearance_model_FuncGroup0->diagOut = rtu_diagIn;
  }

  /* End of Chart: '<S211>/diagLatch' */
}

/*
 * System initialize for atomic system:
 *    '<S246>/plausiCheck'
 *    '<S247>/plausiCheck'
 *    '<S248>/plausiCheck'
 *    '<S249>/plausiCheck'
 */
static void HighClearance_model_plausiCheck_Init
  (FuncInternalData0_plausiCheck_HighClearance_model_T
   *HighClearance_model_FuncGroup0)
{
  HighClearance_model_FuncGroup0->is_checking =
    HighClearance_model_IN_NO_ACTIVE_CHILD_d;
  HighClearance_model_FuncGroup0->is_waitToCheck =
    HighClearance_model_IN_NO_ACTIVE_CHILD_d;
  HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;
  HighClearance_model_FuncGroup0->is_active_c5_HighClearance_library = 0U;
  HighClearance_model_FuncGroup0->is_c5_HighClearance_library =
    HighClearance_model_IN_NO_ACTIVE_CHILD_d;
  HighClearance_model_FuncGroup0->positionOut = 0.0F;
  HighClearance_model_FuncGroup0->plausiErr = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S246>/plausiCheck'
 *    '<S247>/plausiCheck'
 *    '<S248>/plausiCheck'
 *    '<S249>/plausiCheck'
 */
static void HighClearance_model_plausiCheck(real32_T rtu_positionIn, real32_T
  rtu_positionDelay, boolean_T rtu_enableCheck,
  FuncInternalData0_plausiCheck_HighClearance_model_T
  *HighClearance_model_FuncGroup0)
{
  if (HighClearance_model_FuncGroup0->temporalCounter_i1 < 32767U)
  {
    HighClearance_model_FuncGroup0->temporalCounter_i1++;
  }

  /* Chart: '<S246>/plausiCheck' */
  /* Gateway: plausiLogic/plausiCheck */
  /* During: plausiLogic/plausiCheck */
  if (HighClearance_model_FuncGroup0->is_active_c5_HighClearance_library == 0U)
  {
    /* Entry: plausiLogic/plausiCheck */
    HighClearance_model_FuncGroup0->is_active_c5_HighClearance_library = 1U;

    /* Entry Internal: plausiLogic/plausiCheck */
    /* Transition: '<S251>:13' */
    HighClearance_model_FuncGroup0->is_c5_HighClearance_library =
      HighClearance_model_IN_waitToCheck;

    /* Entry 'waitToCheck': '<S251>:3' */
    HighClearance_model_FuncGroup0->plausiErr = 0U;
    HighClearance_model_FuncGroup0->positionOut = rtu_positionIn;

    /* Entry Internal 'waitToCheck': '<S251>:3' */
    /* Transition: '<S251>:33' */
    HighClearance_model_FuncGroup0->is_waitToCheck =
      HighClearance_model_IN_disable;
  }
  else if (HighClearance_model_FuncGroup0->is_c5_HighClearance_library ==
           HighClearance_model_IN_checking)
  {
    /* During 'checking': '<S251>:36' */
    if (!rtu_enableCheck)
    {
      /* Transition: '<S251>:37' */
      /* Exit Internal 'checking': '<S251>:36' */
      HighClearance_model_FuncGroup0->is_checking =
        HighClearance_model_IN_NO_ACTIVE_CHILD_d;
      HighClearance_model_FuncGroup0->is_c5_HighClearance_library =
        HighClearance_model_IN_waitToCheck;

      /* Entry 'waitToCheck': '<S251>:3' */
      HighClearance_model_FuncGroup0->plausiErr = 0U;
      HighClearance_model_FuncGroup0->positionOut = rtu_positionIn;

      /* Entry Internal 'waitToCheck': '<S251>:3' */
      /* Transition: '<S251>:33' */
      HighClearance_model_FuncGroup0->is_waitToCheck =
        HighClearance_model_IN_disable;
    }
    else if (HighClearance_model_FuncGroup0->is_checking ==
             HighClearance_model_IN_plausiCheck)
    {
      /* During 'plausiCheck': '<S251>:19' */
      if ((real32_T)fabs(rtu_positionIn - rtu_positionDelay) >
          HighClearance_model_P.plausiDistance)
      {
        /* Transition: '<S251>:22' */
        HighClearance_model_FuncGroup0->is_checking =
          HighClearance_model_IN_plausiError;

        /* Entry 'plausiError': '<S251>:21' */
        HighClearance_model_FuncGroup0->plausiErr = 1U;
        HighClearance_model_FuncGroup0->positionOut = rtu_positionDelay;
      }
      else
      {
        HighClearance_model_FuncGroup0->positionOut = rtu_positionIn;
      }
    }
    else
    {
      HighClearance_model_FuncGroup0->plausiErr = 1U;

      /* During 'plausiError': '<S251>:21' */
    }
  }
  else
  {
    HighClearance_model_FuncGroup0->plausiErr = 0U;

    /* During 'waitToCheck': '<S251>:3' */
    HighClearance_model_FuncGroup0->positionOut = rtu_positionIn;
    if (HighClearance_model_FuncGroup0->is_waitToCheck ==
        HighClearance_model_IN_disable)
    {
      /* During 'disable': '<S251>:31' */
      if (rtu_enableCheck)
      {
        /* Transition: '<S251>:34' */
        HighClearance_model_FuncGroup0->is_waitToCheck =
          HighClearance_model_IN_enable;
        HighClearance_model_FuncGroup0->temporalCounter_i1 = 0U;
      }
    }
    else
    {
      /* During 'enable': '<S251>:32' */
      if (HighClearance_model_FuncGroup0->temporalCounter_i1 >=
          HighClearance_model_P.errDelay * 100)
      {
        /* Transition: '<S251>:15' */
        HighClearance_model_FuncGroup0->is_waitToCheck =
          HighClearance_model_IN_NO_ACTIVE_CHILD_d;
        HighClearance_model_FuncGroup0->is_c5_HighClearance_library =
          HighClearance_model_IN_checking;
        HighClearance_model_FuncGroup0->is_checking =
          HighClearance_model_IN_plausiCheck;

        /* Entry 'plausiCheck': '<S251>:19' */
      }
      else
      {
        if (!rtu_enableCheck)
        {
          /* Transition: '<S251>:35' */
          HighClearance_model_FuncGroup0->is_waitToCheck =
            HighClearance_model_IN_disable;
        }
      }
    }
  }

  /* End of Chart: '<S246>/plausiCheck' */
}

/* Function for Chart: '<S131>/manualOverrides' */
static void HighClearance_model_setIO(void)
{
  /* Inport: '<Root>/manualOverride' */
  /* Graphical Function 'setIO': '<S201>:13' */
  /* Transition: '<S201>:16' */
  switch (HighClearance_model_U.manualOverride)
  {
   case 0xAA01:
    /* Transition: '<S201>:21' */
    /* Transition: '<S201>:26' */
    HighClearance_model_FuncInternalData0.pwm.retract.FrontLeft =
      HighClearance_model_P.bangBang_maxOut;

    /* Transition: '<S201>:66' */
    /* Transition: '<S201>:102' */
    /* Transition: '<S201>:99' */
    /* Transition: '<S201>:191' */
    /* Transition: '<S201>:184' */
    /* Transition: '<S201>:146' */
    /* Transition: '<S201>:147' */
    /* Transition: '<S201>:194' */
    /* Transition: '<S201>:68' */
    break;

   case 0xDD01:
    /* Transition: '<S201>:22' */
    /* Transition: '<S201>:71' */
    HighClearance_model_FuncInternalData0.pwm.retract.FrontLeft = 0.0F;

    /* Transition: '<S201>:77' */
    /* Transition: '<S201>:101' */
    /* Transition: '<S201>:96' */
    /* Transition: '<S201>:190' */
    /* Transition: '<S201>:163' */
    /* Transition: '<S201>:182' */
    /* Transition: '<S201>:153' */
    /* Transition: '<S201>:193' */
    /* Transition: '<S201>:70' */
    break;

   case 0xAA11:
    /* Transition: '<S201>:60' */
    /* Transition: '<S201>:63' */
    /* Transition: '<S201>:65' */
    HighClearance_model_FuncInternalData0.pwm.extend.FrontLeft =
      HighClearance_model_P.bangBang_maxOut;

    /* Transition: '<S201>:102' */
    /* Transition: '<S201>:99' */
    /* Transition: '<S201>:191' */
    /* Transition: '<S201>:184' */
    /* Transition: '<S201>:146' */
    /* Transition: '<S201>:147' */
    /* Transition: '<S201>:194' */
    /* Transition: '<S201>:68' */
    break;

   case 0xDD11:
    /* Transition: '<S201>:78' */
    /* Transition: '<S201>:75' */
    HighClearance_model_FuncInternalData0.pwm.extend.FrontLeft = 0.0F;

    /* Transition: '<S201>:101' */
    /* Transition: '<S201>:96' */
    /* Transition: '<S201>:190' */
    /* Transition: '<S201>:163' */
    /* Transition: '<S201>:182' */
    /* Transition: '<S201>:153' */
    /* Transition: '<S201>:193' */
    /* Transition: '<S201>:70' */
    break;

   case 0xAA02:
    /* Transition: '<S201>:100' */
    /* Transition: '<S201>:86' */
    /* Transition: '<S201>:92' */
    HighClearance_model_FuncInternalData0.pwm.retract.FrontRight =
      HighClearance_model_P.bangBang_maxOut;

    /* Transition: '<S201>:99' */
    /* Transition: '<S201>:191' */
    /* Transition: '<S201>:184' */
    /* Transition: '<S201>:146' */
    /* Transition: '<S201>:147' */
    /* Transition: '<S201>:194' */
    /* Transition: '<S201>:68' */
    break;

   case 0xDD02:
    /* Transition: '<S201>:85' */
    /* Transition: '<S201>:82' */
    HighClearance_model_FuncInternalData0.pwm.retract.FrontRight = 0.0F;

    /* Transition: '<S201>:96' */
    /* Transition: '<S201>:190' */
    /* Transition: '<S201>:163' */
    /* Transition: '<S201>:182' */
    /* Transition: '<S201>:153' */
    /* Transition: '<S201>:193' */
    /* Transition: '<S201>:70' */
    break;

   case 0xAA12:
    /* Transition: '<S201>:88' */
    /* Transition: '<S201>:98' */
    /* Transition: '<S201>:84' */
    HighClearance_model_FuncInternalData0.pwm.extend.FrontRight =
      HighClearance_model_P.bangBang_maxOut;

    /* Transition: '<S201>:191' */
    /* Transition: '<S201>:184' */
    /* Transition: '<S201>:146' */
    /* Transition: '<S201>:147' */
    /* Transition: '<S201>:194' */
    /* Transition: '<S201>:68' */
    break;

   case 0xDD12:
    /* Transition: '<S201>:97' */
    /* Transition: '<S201>:89' */
    HighClearance_model_FuncInternalData0.pwm.extend.FrontRight = 0.0F;

    /* Transition: '<S201>:190' */
    /* Transition: '<S201>:163' */
    /* Transition: '<S201>:182' */
    /* Transition: '<S201>:153' */
    /* Transition: '<S201>:193' */
    /* Transition: '<S201>:70' */
    break;

   case 0xAA03:
    /* Transition: '<S201>:189' */
    /* Transition: '<S201>:167' */
    /* Transition: '<S201>:177' */
    HighClearance_model_FuncInternalData0.pwm.retract.RearLeft =
      HighClearance_model_P.bangBang_maxOut;

    /* Transition: '<S201>:184' */
    /* Transition: '<S201>:146' */
    /* Transition: '<S201>:147' */
    /* Transition: '<S201>:194' */
    /* Transition: '<S201>:68' */
    break;

   case 0xDD03:
    /* Transition: '<S201>:172' */
    /* Transition: '<S201>:188' */
    HighClearance_model_FuncInternalData0.pwm.retract.RearLeft = 0.0F;

    /* Transition: '<S201>:163' */
    /* Transition: '<S201>:182' */
    /* Transition: '<S201>:153' */
    /* Transition: '<S201>:193' */
    /* Transition: '<S201>:70' */
    break;

   case 0xAA13:
    /* Transition: '<S201>:174' */
    /* Transition: '<S201>:185' */
    /* Transition: '<S201>:186' */
    HighClearance_model_FuncInternalData0.pwm.extend.RearLeft =
      HighClearance_model_P.bangBang_maxOut;

    /* Transition: '<S201>:146' */
    /* Transition: '<S201>:147' */
    /* Transition: '<S201>:194' */
    /* Transition: '<S201>:68' */
    break;

   case 0xDD13:
    /* Transition: '<S201>:181' */
    /* Transition: '<S201>:179' */
    HighClearance_model_FuncInternalData0.pwm.extend.RearLeft = 0.0F;

    /* Transition: '<S201>:182' */
    /* Transition: '<S201>:153' */
    /* Transition: '<S201>:193' */
    /* Transition: '<S201>:70' */
    break;

   case 0xAA04:
    /* Transition: '<S201>:170' */
    /* Transition: '<S201>:158' */
    /* Transition: '<S201>:144' */
    HighClearance_model_FuncInternalData0.pwm.retract.RearRight =
      HighClearance_model_P.bangBang_maxOut;

    /* Transition: '<S201>:147' */
    /* Transition: '<S201>:194' */
    /* Transition: '<S201>:68' */
    break;

   case 0xDD04:
    /* Transition: '<S201>:157' */
    /* Transition: '<S201>:162' */
    HighClearance_model_FuncInternalData0.pwm.retract.RearRight = 0.0F;

    /* Transition: '<S201>:153' */
    /* Transition: '<S201>:193' */
    /* Transition: '<S201>:70' */
    break;

   case 0xAA14:
    /* Transition: '<S201>:149' */
    /* Transition: '<S201>:148' */
    /* Transition: '<S201>:145' */
    HighClearance_model_FuncInternalData0.pwm.extend.RearRight =
      HighClearance_model_P.bangBang_maxOut;

    /* Transition: '<S201>:194' */
    /* Transition: '<S201>:68' */
    break;

   case 0xDD14:
    /* Transition: '<S201>:164' */
    /* Transition: '<S201>:154' */
    HighClearance_model_FuncInternalData0.pwm.extend.RearRight = 0.0F;

    /* Transition: '<S201>:193' */
    /* Transition: '<S201>:70' */
    break;

   default:
    /* Transition: '<S201>:192' */
    break;
  }

  /* End of Inport: '<Root>/manualOverride' */
}

/*
 * Function for Chart: '<S23>/calibrationLogic'
 * function state = checkCalValues
 */
static uint16_T HighClearance_model_checkCalValues(void)
{
  uint16_T state;
  real32_T tmp;
  real32_T tmp_0;
  real32_T tmp_1;
  real32_T tmp_2;

  /* MATLAB Function 'checkCalValues': '<S115>:600' */
  /* '<S115>:600:3' state = calBAD_e; */
  state = calBAD_e;

  /* '<S115>:600:5' if 	positionSensorFL_BrkPnts(1) > ( defaultPositionSensor_BrkPnts(1) - calSensorTolerance ) && ... */
  /* '<S115>:600:6' 	positionSensorFL_BrkPnts(1) < ( defaultPositionSensor_BrkPnts(1) + calSensorTolerance ) && ... */
  /* '<S115>:600:7'     positionSensorFL_BrkPnts(2) > ( defaultPositionSensor_BrkPnts(2) - calSensorTolerance ) && ... */
  /* '<S115>:600:8'     positionSensorFL_BrkPnts(2) < ( defaultPositionSensor_BrkPnts(2) + calSensorTolerance ) */
  tmp = HighClearance_model_P.defaultPositionSensor_BrkPnts[0] -
    HighClearance_model_P.calSensorTolerance;
  if (HighClearance_model_P.positionSensorFL_BrkPnts[0] > tmp)
  {
    tmp_0 = HighClearance_model_P.defaultPositionSensor_BrkPnts[0] +
      HighClearance_model_P.calSensorTolerance;
    if (HighClearance_model_P.positionSensorFL_BrkPnts[0] < tmp_0)
    {
      tmp_1 = HighClearance_model_P.defaultPositionSensor_BrkPnts[1] -
        HighClearance_model_P.calSensorTolerance;
      if (HighClearance_model_P.positionSensorFL_BrkPnts[1] > tmp_1)
      {
        tmp_2 = HighClearance_model_P.defaultPositionSensor_BrkPnts[1] +
          HighClearance_model_P.calSensorTolerance;
        if ((HighClearance_model_P.positionSensorFL_BrkPnts[1] < tmp_2) &&
            (HighClearance_model_P.positionSensorFR_BrkPnts[0] > tmp) &&
            (HighClearance_model_P.positionSensorFR_BrkPnts[0] < tmp_0) &&
            (HighClearance_model_P.positionSensorFR_BrkPnts[1] > tmp_1) &&
            (HighClearance_model_P.positionSensorFR_BrkPnts[1] < tmp_2) &&
            (HighClearance_model_P.positionSensorRL_BrkPnts[0] > tmp) &&
            (HighClearance_model_P.positionSensorRL_BrkPnts[0] < tmp_0) &&
            (HighClearance_model_P.positionSensorRL_BrkPnts[1] > tmp_1) &&
            (HighClearance_model_P.positionSensorRL_BrkPnts[1] < tmp_2) &&
            (HighClearance_model_P.positionSensorRR_BrkPnts[0] > tmp) &&
            (HighClearance_model_P.positionSensorRR_BrkPnts[0] < tmp_0) &&
            (HighClearance_model_P.positionSensorRR_BrkPnts[1] > tmp_1) &&
            (HighClearance_model_P.positionSensorRR_BrkPnts[1] < tmp_2))
        {
          /* '<S115>:600:10' if 	positionSensorFR_BrkPnts(1) > ( defaultPositionSensor_BrkPnts(1) - calSensorTolerance ) && ... */
          /* '<S115>:600:11'         positionSensorFR_BrkPnts(1) < ( defaultPositionSensor_BrkPnts(1) + calSensorTolerance ) && ... */
          /* '<S115>:600:12'         positionSensorFR_BrkPnts(2) > ( defaultPositionSensor_BrkPnts(2) - calSensorTolerance ) && ... */
          /* '<S115>:600:13'         positionSensorFR_BrkPnts(2) < ( defaultPositionSensor_BrkPnts(2) + calSensorTolerance ) */
          /* '<S115>:600:15' if 	positionSensorRL_BrkPnts(1) > ( defaultPositionSensor_BrkPnts(1) - calSensorTolerance ) && ... */
          /* '<S115>:600:16'             positionSensorRL_BrkPnts(1) < ( defaultPositionSensor_BrkPnts(1) + calSensorTolerance ) && ... */
          /* '<S115>:600:17'             positionSensorRL_BrkPnts(2) > ( defaultPositionSensor_BrkPnts(2) - calSensorTolerance ) && ... */
          /* '<S115>:600:18'             positionSensorRL_BrkPnts(2) < ( defaultPositionSensor_BrkPnts(2) + calSensorTolerance ) */
          /* '<S115>:600:20' if 	positionSensorRR_BrkPnts(1) > ( defaultPositionSensor_BrkPnts(1) - calSensorTolerance ) && ... */
          /* '<S115>:600:21'                 positionSensorRR_BrkPnts(1) < ( defaultPositionSensor_BrkPnts(1) + calSensorTolerance ) && ... */
          /* '<S115>:600:22'                 positionSensorRR_BrkPnts(2) > ( defaultPositionSensor_BrkPnts(2) - calSensorTolerance ) && ... */
          /* '<S115>:600:23'                 positionSensorRR_BrkPnts(2) < ( defaultPositionSensor_BrkPnts(2) + calSensorTolerance ) */
          /* '<S115>:600:25' state = calOKAY_e; */
          state = calOKAY_e;
        }
      }
    }
  }

  return state;
}

/* Function for Chart: '<S23>/calibrationLogic' */
static boolean_T HighClearance_model_checkCalOkay(void)
{
  boolean_T out;

  /* Graphical Function 'checkCalOkay': '<S115>:588' */
  /* Transition: '<S115>:593' */
  if (HighClearance_model_checkCalValues() == calOKAY_e)
  {
    /* Transition: '<S115>:594' */
    /* Transition: '<S115>:601' */
    /* Transition: '<S115>:597' */
    out = true;
  }
  else
  {
    /* Transition: '<S115>:595' */
    out = false;
  }

  return out;
}

/* Function for Chart: '<S23>/calibrationLogic' */
static boolean_T HighClearance_model_sensorsOkay(void)
{
  boolean_T out;

  /* Inport: '<Root>/heightPosSensors_diag' */
  /* Graphical Function 'sensorsOkay': '<S115>:828' */
  /* Transition: '<S115>:835' */
  if ((HighClearance_model_U.heightPosSensors_diag.FrontLeft ==
       HighClearance_model_P.IOD_OK) &&
      (HighClearance_model_U.heightPosSensors_diag.FrontRight ==
       HighClearance_model_P.IOD_OK) &&
      (HighClearance_model_U.heightPosSensors_diag.RearLeft ==
       HighClearance_model_P.IOD_OK) &&
      (HighClearance_model_U.heightPosSensors_diag.RearRight ==
       HighClearance_model_P.IOD_OK))
  {
    /* Transition: '<S115>:836' */
    /* Transition: '<S115>:838' */
    /* Transition: '<S115>:839' */
    /* Transition: '<S115>:840' */
    /* Transition: '<S115>:841' */
    out = true;
  }
  else
  {
    /* Transition: '<S115>:837' */
    out = false;
  }

  /* End of Inport: '<Root>/heightPosSensors_diag' */
  return out;
}

/* Function for Chart: '<S23>/calibrationLogic' */
static void HighClearance_model_heightDown(void)
{
  /* Graphical Function 'heightDown': '<S115>:237' */
  /* Transition: '<S115>:248' */
  /* Transition: '<S115>:249' */
  /* Transition: '<S115>:250' */
  HighClearance_model_FuncInternalData0.exFL = 0.0F;

  /* Transition: '<S115>:251' */
  HighClearance_model_FuncInternalData0.exFR = 0.0F;

  /* Transition: '<S115>:252' */
  HighClearance_model_FuncInternalData0.exRL = 0.0F;

  /* Transition: '<S115>:253' */
  HighClearance_model_FuncInternalData0.exRR = 0.0F;

  /* Transition: '<S115>:254' */
  HighClearance_model_FuncInternalData0.rtFL =
    HighClearance_model_P.bangBang_maxOut;

  /* Transition: '<S115>:255' */
  HighClearance_model_FuncInternalData0.rtFR =
    HighClearance_model_P.bangBang_maxOut;

  /* Transition: '<S115>:256' */
  HighClearance_model_FuncInternalData0.rtRL =
    HighClearance_model_P.bangBang_maxOut;

  /* Transition: '<S115>:257' */
  HighClearance_model_FuncInternalData0.rtRR =
    HighClearance_model_P.bangBang_maxOut;
}

/* Function for Chart: '<S23>/calibrationLogic' */
static void HighClearance_model_heightStop(void)
{
  /* Graphical Function 'heightStop': '<S115>:153' */
  /* Transition: '<S115>:155' */
  /* Transition: '<S115>:211' */
  /* Transition: '<S115>:163' */
  HighClearance_model_FuncInternalData0.exFL = 0.0F;

  /* Transition: '<S115>:166' */
  HighClearance_model_FuncInternalData0.exFR = 0.0F;

  /* Transition: '<S115>:169' */
  HighClearance_model_FuncInternalData0.exRL = 0.0F;

  /* Transition: '<S115>:171' */
  HighClearance_model_FuncInternalData0.exRR = 0.0F;

  /* Transition: '<S115>:181' */
  HighClearance_model_FuncInternalData0.rtFL = 0.0F;

  /* Transition: '<S115>:183' */
  HighClearance_model_FuncInternalData0.rtFR = 0.0F;

  /* Transition: '<S115>:184' */
  HighClearance_model_FuncInternalData0.rtRL = 0.0F;

  /* Transition: '<S115>:187' */
  HighClearance_model_FuncInternalData0.rtRR = 0.0F;
}

/* Function for Chart: '<S23>/calibrationLogic' */
static void HighClearance_model_clearCalValues(void)
{
  /* Outport: '<Root>/calValues' */
  /* Graphical Function 'clearCalValues': '<S115>:273' */
  /* Transition: '<S115>:284' */
  /* Transition: '<S115>:286' */
  HighClearance_model_Y.calValues.extend.FrontLeft = 0.0F;

  /* Transition: '<S115>:287' */
  HighClearance_model_Y.calValues.extend.FrontRight = 0.0F;

  /* Transition: '<S115>:288' */
  HighClearance_model_Y.calValues.extend.RearLeft = 0.0F;

  /* Transition: '<S115>:289' */
  HighClearance_model_Y.calValues.extend.RearRight = 0.0F;

  /* Transition: '<S115>:290' */
  HighClearance_model_Y.calValues.retract.FrontLeft = 0.0F;

  /* Transition: '<S115>:291' */
  HighClearance_model_Y.calValues.retract.FrontRight = 0.0F;

  /* Transition: '<S115>:292' */
  HighClearance_model_Y.calValues.retract.RearLeft = 0.0F;

  /* Transition: '<S115>:293' */
  HighClearance_model_Y.calValues.retract.RearRight = 0.0F;
}

/* Function for Chart: '<S23>/calibrationLogic' */
static boolean_T HighClearance_model_pauseCal(void)
{
  boolean_T out;

  /* Outport: '<Root>/calState' incorporates:
   *  UnitDelay: '<Root>/Unit Delay'
   *  UnitDelay: '<Root>/Unit Delay1'
   */
  /* Graphical Function 'pauseCal': '<S115>:494' */
  /* Transition: '<S115>:758' */
  if (((((HighClearance_model_Y.calState & calSTEP1_e) == calSTEP1_e) ||
        ((HighClearance_model_Y.calState & calSTEP2_e) == calSTEP2_e)) &&
       (!HighClearance_model_FuncInternalData0.UnitDelay1_DSTATE)) ||
      ((((HighClearance_model_Y.calState & calSTEP3_e) == calSTEP3_e) ||
        ((HighClearance_model_Y.calState & calSTEP4_e) == calSTEP4_e)) &&
       (!HighClearance_model_FuncInternalData0.UnitDelay_DSTATE)))
  {
    /* Transition: '<S115>:773' */
    /* Transition: '<S115>:757' */
    /* Transition: '<S115>:772' */
    /* Transition: '<S115>:786' */
    /* Transition: '<S115>:774' */
    /* Transition: '<S115>:771' */
    out = true;
  }
  else
  {
    /* Transition: '<S115>:761' */
    /* Transition: '<S115>:796' */
    /* Transition: '<S115>:762' */
    out = false;
  }

  /* End of Outport: '<Root>/calState' */
  return out;
}

/* Function for Chart: '<S23>/calibrationLogic' */
static void HighClearance_model_heightUp(void)
{
  /* Graphical Function 'heightUp': '<S115>:214' */
  /* Transition: '<S115>:225' */
  /* Transition: '<S115>:226' */
  /* Transition: '<S115>:227' */
  HighClearance_model_FuncInternalData0.exFL =
    HighClearance_model_P.bangBang_maxOut;

  /* Transition: '<S115>:228' */
  HighClearance_model_FuncInternalData0.exFR =
    HighClearance_model_P.bangBang_maxOut;

  /* Transition: '<S115>:229' */
  HighClearance_model_FuncInternalData0.exRL =
    HighClearance_model_P.bangBang_maxOut;

  /* Transition: '<S115>:230' */
  HighClearance_model_FuncInternalData0.exRR =
    HighClearance_model_P.bangBang_maxOut;

  /* Transition: '<S115>:231' */
  HighClearance_model_FuncInternalData0.rtFL = 0.0F;

  /* Transition: '<S115>:232' */
  HighClearance_model_FuncInternalData0.rtFR = 0.0F;

  /* Transition: '<S115>:233' */
  HighClearance_model_FuncInternalData0.rtRL = 0.0F;

  /* Transition: '<S115>:234' */
  HighClearance_model_FuncInternalData0.rtRR = 0.0F;
}

/* Function for Chart: '<S23>/calibrationLogic' */
static void HighClearance_model_updateCalUpValues(const real32_T *Switch_a,
  const real32_T *Switch_j, const real32_T *Switch_i, const real32_T *Switch_f)
{
  /* Outport: '<Root>/calValues' */
  /* Graphical Function 'updateCalUpValues': '<S115>:325' */
  /* Transition: '<S115>:331' */
  /* Transition: '<S115>:332' */
  HighClearance_model_Y.calValues.extend.FrontLeft = *Switch_a;

  /* Transition: '<S115>:333' */
  HighClearance_model_Y.calValues.extend.FrontRight = *Switch_j;

  /* Transition: '<S115>:334' */
  HighClearance_model_Y.calValues.extend.RearLeft = *Switch_i;

  /* Transition: '<S115>:335' */
  HighClearance_model_Y.calValues.extend.RearRight = *Switch_f;
}

/*
 * Function for Chart: '<S23>/calibrationLogic'
 * function state = checkDownValues(FL, FR, RL, RR)
 */
static uint16_T HighClearance_model_checkDownValues(real32_T FL, real32_T FR,
  real32_T RL, real32_T RR)
{
  uint16_T state;
  real32_T tmp;
  real32_T tmp_0;

  /* MATLAB Function 'checkDownValues': '<S115>:858' */
  /* '<S115>:858:3' state = calBAD_e; */
  state = calBAD_e;

  /* '<S115>:858:5' if 	FL > ( defaultPositionSensor_BrkPnts(1) - calSensorTolerance ) && ... */
  /* '<S115>:858:6'     FL < ( defaultPositionSensor_BrkPnts(1) + calSensorTolerance ) */
  tmp = HighClearance_model_P.defaultPositionSensor_BrkPnts[0] -
    HighClearance_model_P.calSensorTolerance;
  if (FL > tmp)
  {
    tmp_0 = HighClearance_model_P.defaultPositionSensor_BrkPnts[0] +
      HighClearance_model_P.calSensorTolerance;
    if ((FL < tmp_0) && (FR > tmp) && (FR < tmp_0) && (RL > tmp) && (RL < tmp_0)
        && (RR > tmp) && (RR < tmp_0))
    {
      /* '<S115>:858:8' if 	FR > ( defaultPositionSensor_BrkPnts(1) - calSensorTolerance ) && ... */
      /* '<S115>:858:9'         FR < ( defaultPositionSensor_BrkPnts(1) + calSensorTolerance ) */
      /* '<S115>:858:11' if 	RL > ( defaultPositionSensor_BrkPnts(1) - calSensorTolerance ) && ... */
      /* '<S115>:858:12'             RL < ( defaultPositionSensor_BrkPnts(1) + calSensorTolerance ) */
      /* '<S115>:858:14' if 	RR > ( defaultPositionSensor_BrkPnts(1) - calSensorTolerance ) && ... */
      /* '<S115>:858:15'                 RR < ( defaultPositionSensor_BrkPnts(1) + calSensorTolerance ) */
      /* '<S115>:858:17' state = calOKAY_e; */
      state = calOKAY_e;
    }
  }

  return state;
}

/*
 * Function for Chart: '<S23>/calibrationLogic'
 * function state = checkCalDownValues
 */
static uint16_T HighClearance_model_checkCalDownValues(void)
{
  uint16_T state;

  /* Outport: '<Root>/calValues' */
  /* MATLAB Function 'checkCalDownValues': '<S115>:848' */
  /* '<S115>:848:3' state = checkDownValues(calValues.retract.FrontLeft,... */
  /* '<S115>:848:4'         calValues.retract.FrontRight,... */
  /* '<S115>:848:5'         calValues.retract.RearLeft,... */
  /* '<S115>:848:6'         calValues.retract.RearRight); */
  state = HighClearance_model_checkDownValues
    (HighClearance_model_Y.calValues.retract.FrontLeft,
     HighClearance_model_Y.calValues.retract.FrontRight,
     HighClearance_model_Y.calValues.retract.RearLeft,
     HighClearance_model_Y.calValues.retract.RearRight);
  return state;
}

/*
 * Function for Chart: '<S23>/calibrationLogic'
 * function state = checkUpValues(FL, FR, RL ,RR)
 */
static uint16_T HighClearance_model_checkUpValues(real32_T FL, real32_T FR,
  real32_T RL, real32_T RR)
{
  uint16_T state;
  real32_T tmp;
  real32_T tmp_0;

  /* MATLAB Function 'checkUpValues': '<S115>:860' */
  /* '<S115>:860:3' state = calBAD_e; */
  state = calBAD_e;

  /* '<S115>:860:5' if 	FL > ( defaultPositionSensor_BrkPnts(2) - calSensorTolerance ) && ... */
  /* '<S115>:860:6'     FL < ( defaultPositionSensor_BrkPnts(2) + calSensorTolerance ) */
  tmp = HighClearance_model_P.defaultPositionSensor_BrkPnts[1] -
    HighClearance_model_P.calSensorTolerance;
  if (FL > tmp)
  {
    tmp_0 = HighClearance_model_P.defaultPositionSensor_BrkPnts[1] +
      HighClearance_model_P.calSensorTolerance;
    if ((FL < tmp_0) && (FR > tmp) && (FR < tmp_0) && (RL > tmp) && (RL < tmp_0)
        && (RR > tmp) && (RR < tmp_0))
    {
      /* '<S115>:860:8' if 	FR > ( defaultPositionSensor_BrkPnts(2) - calSensorTolerance ) && ... */
      /* '<S115>:860:9'         FR < ( defaultPositionSensor_BrkPnts(2) + calSensorTolerance ) */
      /* '<S115>:860:11' if 	RL > ( defaultPositionSensor_BrkPnts(2) - calSensorTolerance ) && ... */
      /* '<S115>:860:12'             RL < ( defaultPositionSensor_BrkPnts(2) + calSensorTolerance ) */
      /* '<S115>:860:14' if 	RR > ( defaultPositionSensor_BrkPnts(2) - calSensorTolerance ) && ... */
      /* '<S115>:860:15'                 RR < ( defaultPositionSensor_BrkPnts(2) + calSensorTolerance ) */
      /* '<S115>:860:17' state = calOKAY_e; */
      state = calOKAY_e;
    }
  }

  return state;
}

/*
 * Function for Chart: '<S23>/calibrationLogic'
 * function state = checkCalUpValues
 */
static uint16_T HighClearance_model_checkCalUpValues(void)
{
  uint16_T state;

  /* Outport: '<Root>/calValues' */
  /* MATLAB Function 'checkCalUpValues': '<S115>:850' */
  /* '<S115>:850:3' state = checkUpValues(calValues.extend.FrontLeft,... */
  /* '<S115>:850:4'         calValues.extend.FrontRight,... */
  /* '<S115>:850:5'         calValues.extend.RearLeft,... */
  /* '<S115>:850:6'         calValues.extend.RearRight); */
  state = HighClearance_model_checkUpValues
    (HighClearance_model_Y.calValues.extend.FrontLeft,
     HighClearance_model_Y.calValues.extend.FrontRight,
     HighClearance_model_Y.calValues.extend.RearLeft,
     HighClearance_model_Y.calValues.extend.RearRight);
  return state;
}

/* Function for Chart: '<S23>/calibrationLogic' */
static void HighClearance_model_updateCalDownValues(const real32_T *Switch_a,
  const real32_T *Switch_j, const real32_T *Switch_i, const real32_T *Switch_f)
{
  /* Outport: '<Root>/calValues' */
  /* Graphical Function 'updateCalDownValues': '<S115>:295' */
  /* Transition: '<S115>:305' */
  /* Transition: '<S115>:310' */
  HighClearance_model_Y.calValues.retract.FrontLeft = *Switch_a;

  /* Transition: '<S115>:311' */
  HighClearance_model_Y.calValues.retract.FrontRight = *Switch_j;

  /* Transition: '<S115>:312' */
  HighClearance_model_Y.calValues.retract.RearLeft = *Switch_i;

  /* Transition: '<S115>:313' */
  HighClearance_model_Y.calValues.retract.RearRight = *Switch_f;
}

/* Function for Chart: '<S23>/calibrationLogic' */
static void HighClearance_model_active_c(const boolean_T *LogicalOperator, const
  real32_T *Switch_a, const real32_T *Switch_j, const real32_T *Switch_i, const
  real32_T *Switch_f)
{
  int32_T tmp;

  /* During 'active': '<S115>:24' */
  switch (HighClearance_model_FuncInternalData0.is_active)
  {
   case HighClearance_model_IN_checkDownCalValues:
    /* Inport: '<Root>/engRunning' */
    /* During 'checkDownCalValues': '<S115>:259' */
    if ((HighClearance_model_checkCalDownValues() == calBAD_e) ||
        ((!HighClearance_model_sensorsOkay()) || (*LogicalOperator) ||
         (!HighClearance_model_U.engRunning)))
    {
      /* Transition: '<S115>:317' */
      /* Transition: '<S115>:369' */
      HighClearance_model_FuncInternalData0.is_active =
        HighClearance_model_IN_error_i;

      /* Entry 'error': '<S115>:533' */
      HighClearance_model_heightStop();

      /* Outport: '<Root>/calState' */
      /* Entry 'badDownCal': '<S115>:316' */
      HighClearance_model_Y.calState = calERROR2_e;
    }
    else
    {
      if (HighClearance_model_checkCalDownValues() == calOKAY_e)
      {
        /* Transition: '<S115>:456' */
        HighClearance_model_FuncInternalData0.is_active =
          HighClearance_model_IN_step3;
        HighClearance_model_FuncInternalData0.temporalCounter_i2 = 0U;

        /* Outport: '<Root>/calState' */
        /* Entry 'step3': '<S115>:416' */
        HighClearance_model_Y.calState = calSTEP3_e;

        /* Entry Internal 'step3': '<S115>:416' */
        /* Transition: '<S115>:532' */
        HighClearance_model_FuncInternalData0.is_step3 =
          HighClearance_model_IN_active;

        /* Entry 'active': '<S115>:531' */
        HighClearance_model_heightUp();

        /* Entry Internal 'active': '<S115>:531' */
        /* Transition: '<S115>:417' */
        HighClearance_model_FuncInternalData0.is_active_d =
          HighClearance_model_IN_moving_j;
      }
    }
    break;

   case HighClearance_model_IN_checkUpCalValues:
    /* Inport: '<Root>/engRunning' */
    /* During 'checkUpCalValues': '<S115>:258' */
    if ((HighClearance_model_checkCalUpValues() == calBAD_e) ||
        ((!HighClearance_model_sensorsOkay()) || (*LogicalOperator) ||
         (!HighClearance_model_U.engRunning)))
    {
      /* Transition: '<S115>:337' */
      /* Transition: '<S115>:370' */
      HighClearance_model_FuncInternalData0.is_active =
        HighClearance_model_IN_error_i;

      /* Entry 'error': '<S115>:533' */
      HighClearance_model_heightStop();

      /* Outport: '<Root>/calState' */
      /* Entry 'badUpCal': '<S115>:336' */
      HighClearance_model_Y.calState = calERROR4_e;
    }
    else
    {
      if (HighClearance_model_checkCalUpValues() == calOKAY_e)
      {
        /* Transition: '<S115>:460' */
        HighClearance_model_FuncInternalData0.is_active =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
        HighClearance_model_FuncInternalData0.is_calCommanded =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
        HighClearance_model_FuncInternalData0.is_c2_HighClearance_model =
          HighClearance_model_IN_UpdateValues;
        HighClearance_model_FuncInternalData0.temporalCounter_i1_d = 0U;

        /* Outport: '<Root>/calState' */
        /* Entry 'UpdateValues': '<S115>:844' */
        HighClearance_model_Y.calState = calSTEP5_e;
      }
    }
    break;

   case HighClearance_model_IN_error_i:
    /* During 'error': '<S115>:533' */
    break;

   case HighClearance_model_IN_step1:
    /* Inport: '<Root>/engRunning' */
    /* During 'step1': '<S115>:124' */
    if ((HighClearance_model_FuncInternalData0.temporalCounter_i2 >= (uint32_T)
         (HighClearance_model_P.calStepTimeOut * 100)) ||
        ((!HighClearance_model_sensorsOkay()) || (*LogicalOperator) ||
         (!HighClearance_model_U.engRunning)))
    {
      /* Transition: '<S115>:367' */
      /* Transition: '<S115>:368' */
      /* Exit Internal 'step1': '<S115>:124' */
      if (HighClearance_model_FuncInternalData0.is_step1 ==
          HighClearance_model_IN_paused_a)
      {
        /* Exit 'paused': '<S115>:513' */
        HighClearance_model_FuncInternalData0.is_step1 =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      }
      else
      {
        /* Exit Internal 'active': '<S115>:511' */
        HighClearance_model_FuncInternalData0.is_active_c =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
        HighClearance_model_FuncInternalData0.is_step1 =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      }

      HighClearance_model_FuncInternalData0.is_active =
        HighClearance_model_IN_error_i;

      /* Entry 'error': '<S115>:533' */
      HighClearance_model_heightStop();

      /* Outport: '<Root>/calState' */
      /* Entry 'errorStep1': '<S115>:338' */
      HighClearance_model_Y.calState = calERROR1_e;
    }
    else if (HighClearance_model_FuncInternalData0.is_step1 ==
             HighClearance_model_IN_active)
    {
      /* During 'active': '<S115>:511' */
      if (HighClearance_model_pauseCal())
      {
        /* Transition: '<S115>:514' */
        /* Exit Internal 'active': '<S115>:511' */
        HighClearance_model_FuncInternalData0.is_active_c =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
        HighClearance_model_FuncInternalData0.is_step1 =
          HighClearance_model_IN_paused_a;

        /* Entry 'paused': '<S115>:513' */
        HighClearance_model_heightStop();

        /* Outport: '<Root>/calState' */
        tmp = HighClearance_model_Y.calState + calPAUSED_e;
        if (tmp > 65535)
        {
          tmp = 65535;
        }

        /* Outport: '<Root>/calState' */
        HighClearance_model_Y.calState = (uint16_T)tmp;
      }
      else if (HighClearance_model_FuncInternalData0.is_active_c ==
               HighClearance_model_IN_moving_j)
      {
        /* During 'moving': '<S115>:408' */
        if (HighClearance_model_checkDownValues(*Switch_a, *Switch_j, *Switch_i,
             *Switch_f) == calOKAY_e)
        {
          /* Transition: '<S115>:411' */
          HighClearance_model_FuncInternalData0.is_active_c =
            HighClearance_model_IN_stopped_l;
          HighClearance_model_FuncInternalData0.temporalCounter_i1_d = 0U;
        }
      }
      else
      {
        /* During 'stopped': '<S115>:410' */
        if (HighClearance_model_checkDownValues(*Switch_a, *Switch_j, *Switch_i,
             *Switch_f) != calOKAY_e)
        {
          /* Transition: '<S115>:414' */
          HighClearance_model_FuncInternalData0.is_active_c =
            HighClearance_model_IN_moving_j;
        }
        else
        {
          if (HighClearance_model_FuncInternalData0.temporalCounter_i1_d * 10 >=
              HighClearance_model_P.calSettlingTime)
          {
            /* Transition: '<S115>:412' */
            HighClearance_model_FuncInternalData0.is_active_c =
              HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            HighClearance_model_FuncInternalData0.is_step1 =
              HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            HighClearance_model_FuncInternalData0.is_active =
              HighClearance_model_IN_step2;

            /* Outport: '<Root>/calState' */
            /* Entry 'step2': '<S115>:128' */
            HighClearance_model_Y.calState = calSTEP2_e;

            /* Entry Internal 'step2': '<S115>:128' */
            /* Transition: '<S115>:522' */
            HighClearance_model_FuncInternalData0.is_step2 =
              HighClearance_model_IN_active;

            /* Entry 'active': '<S115>:519' */
            HighClearance_model_heightDown();
          }
        }
      }
    }
    else
    {
      /* During 'paused': '<S115>:513' */
      if (!HighClearance_model_pauseCal())
      {
        /* Outport: '<Root>/calState' */
        /* Transition: '<S115>:515' */
        /* Exit 'paused': '<S115>:513' */
        tmp = HighClearance_model_Y.calState - calPAUSED_e;
        if (tmp < 0)
        {
          tmp = 0;
        }

        /* Outport: '<Root>/calState' */
        HighClearance_model_Y.calState = (uint16_T)tmp;
        HighClearance_model_FuncInternalData0.is_step1 =
          HighClearance_model_IN_active;

        /* Entry 'active': '<S115>:511' */
        HighClearance_model_heightDown();

        /* Entry Internal 'active': '<S115>:511' */
        /* Transition: '<S115>:409' */
        HighClearance_model_FuncInternalData0.is_active_c =
          HighClearance_model_IN_moving_j;
      }
    }
    break;

   case HighClearance_model_IN_step2:
    /* Inport: '<Root>/calCmd' incorporates:
     *  Outport: '<Root>/calState'
     */
    /* During 'step2': '<S115>:128' */
    if ((HighClearance_model_U.calCmd == calCONFIRM2_e) &&
        (HighClearance_model_Y.calState == calSTEP2_e))
    {
      /* Transition: '<S115>:132' */
      /* Exit Internal 'step2': '<S115>:128' */
      if (HighClearance_model_FuncInternalData0.is_step2 ==
          HighClearance_model_IN_paused_a)
      {
        /* Exit 'paused': '<S115>:517' */
        tmp = HighClearance_model_Y.calState - calPAUSED_e;
        if (tmp < 0)
        {
          tmp = 0;
        }

        HighClearance_model_Y.calState = (uint16_T)tmp;
        HighClearance_model_FuncInternalData0.is_step2 =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      }
      else
      {
        HighClearance_model_FuncInternalData0.is_step2 =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      }

      HighClearance_model_FuncInternalData0.is_active =
        HighClearance_model_IN_checkDownCalValues;

      /* Entry 'checkDownCalValues': '<S115>:259' */
      HighClearance_model_updateCalDownValues(Switch_a, Switch_j, Switch_i,
        Switch_f);
      HighClearance_model_heightStop();
    }
    else if (HighClearance_model_U.calCmd == calDECLINE_e)
    {
      /* Transition: '<S115>:371' */
      /* Exit Internal 'step2': '<S115>:128' */
      if (HighClearance_model_FuncInternalData0.is_step2 ==
          HighClearance_model_IN_paused_a)
      {
        /* Exit 'paused': '<S115>:517' */
        HighClearance_model_FuncInternalData0.is_step2 =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      }
      else
      {
        HighClearance_model_FuncInternalData0.is_step2 =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      }

      HighClearance_model_FuncInternalData0.is_active =
        HighClearance_model_IN_step1;
      HighClearance_model_FuncInternalData0.temporalCounter_i2 = 0U;

      /* Entry 'step1': '<S115>:124' */
      HighClearance_model_Y.calState = calSTEP1_e;

      /* Entry Internal 'step1': '<S115>:124' */
      /* Transition: '<S115>:512' */
      HighClearance_model_FuncInternalData0.is_step1 =
        HighClearance_model_IN_active;

      /* Entry 'active': '<S115>:511' */
      HighClearance_model_heightDown();

      /* Entry Internal 'active': '<S115>:511' */
      /* Transition: '<S115>:409' */
      HighClearance_model_FuncInternalData0.is_active_c =
        HighClearance_model_IN_moving_j;
    }
    else if (HighClearance_model_FuncInternalData0.is_step2 ==
             HighClearance_model_IN_active)
    {
      /* During 'active': '<S115>:519' */
      if (HighClearance_model_pauseCal())
      {
        /* Transition: '<S115>:518' */
        HighClearance_model_FuncInternalData0.is_step2 =
          HighClearance_model_IN_paused_a;

        /* Entry 'paused': '<S115>:517' */
        HighClearance_model_heightStop();
        tmp = HighClearance_model_Y.calState + calPAUSED_e;
        if (tmp > 65535)
        {
          tmp = 65535;
        }

        HighClearance_model_Y.calState = (uint16_T)tmp;
      }
    }
    else
    {
      /* During 'paused': '<S115>:517' */
      if (!HighClearance_model_pauseCal())
      {
        /* Transition: '<S115>:516' */
        /* Exit 'paused': '<S115>:517' */
        tmp = HighClearance_model_Y.calState - calPAUSED_e;
        if (tmp < 0)
        {
          tmp = 0;
        }

        HighClearance_model_Y.calState = (uint16_T)tmp;
        HighClearance_model_FuncInternalData0.is_step2 =
          HighClearance_model_IN_active;

        /* Entry 'active': '<S115>:519' */
        HighClearance_model_heightDown();
      }
    }
    break;

   case HighClearance_model_IN_step3:
    /* Inport: '<Root>/engRunning' */
    /* During 'step3': '<S115>:416' */
    if ((HighClearance_model_FuncInternalData0.temporalCounter_i2 >= (uint32_T)
         (HighClearance_model_P.calStepTimeOut * 100)) ||
        ((!HighClearance_model_sensorsOkay()) || (*LogicalOperator) ||
         (!HighClearance_model_U.engRunning)))
    {
      /* Transition: '<S115>:457' */
      /* Transition: '<S115>:458' */
      /* Exit Internal 'step3': '<S115>:416' */
      if (HighClearance_model_FuncInternalData0.is_step3 ==
          HighClearance_model_IN_paused_a)
      {
        /* Exit 'paused': '<S115>:529' */
        HighClearance_model_FuncInternalData0.is_step3 =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      }
      else
      {
        /* Exit Internal 'active': '<S115>:531' */
        HighClearance_model_FuncInternalData0.is_active_d =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
        HighClearance_model_FuncInternalData0.is_step3 =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      }

      HighClearance_model_FuncInternalData0.is_active =
        HighClearance_model_IN_error_i;

      /* Entry 'error': '<S115>:533' */
      HighClearance_model_heightStop();

      /* Outport: '<Root>/calState' */
      /* Entry 'errorStep3': '<S115>:339' */
      HighClearance_model_Y.calState = calERROR3_e;
    }
    else if (HighClearance_model_FuncInternalData0.is_step3 ==
             HighClearance_model_IN_active)
    {
      /* During 'active': '<S115>:531' */
      if (HighClearance_model_pauseCal())
      {
        /* Transition: '<S115>:530' */
        /* Exit Internal 'active': '<S115>:531' */
        HighClearance_model_FuncInternalData0.is_active_d =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
        HighClearance_model_FuncInternalData0.is_step3 =
          HighClearance_model_IN_paused_a;

        /* Entry 'paused': '<S115>:529' */
        HighClearance_model_heightStop();

        /* Outport: '<Root>/calState' */
        tmp = HighClearance_model_Y.calState + calPAUSED_e;
        if (tmp > 65535)
        {
          tmp = 65535;
        }

        /* Outport: '<Root>/calState' */
        HighClearance_model_Y.calState = (uint16_T)tmp;
      }
      else if (HighClearance_model_FuncInternalData0.is_active_d ==
               HighClearance_model_IN_moving_j)
      {
        /* During 'moving': '<S115>:437' */
        if (HighClearance_model_checkUpValues(*Switch_a, *Switch_j, *Switch_i,
             *Switch_f) == calOKAY_e)
        {
          /* Transition: '<S115>:418' */
          HighClearance_model_FuncInternalData0.is_active_d =
            HighClearance_model_IN_stopped_l;
          HighClearance_model_FuncInternalData0.temporalCounter_i1_d = 0U;
        }
      }
      else
      {
        /* During 'stopped': '<S115>:438' */
        if (HighClearance_model_checkUpValues(*Switch_a, *Switch_j, *Switch_i,
             *Switch_f) != calOKAY_e)
        {
          /* Transition: '<S115>:421' */
          HighClearance_model_FuncInternalData0.is_active_d =
            HighClearance_model_IN_moving_j;
        }
        else
        {
          if (HighClearance_model_FuncInternalData0.temporalCounter_i1_d * 10 >=
              HighClearance_model_P.calSettlingTime)
          {
            /* Transition: '<S115>:420' */
            HighClearance_model_FuncInternalData0.is_active_d =
              HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            HighClearance_model_FuncInternalData0.is_step3 =
              HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            HighClearance_model_FuncInternalData0.is_active =
              HighClearance_model_IN_step4;

            /* Outport: '<Root>/calState' */
            /* Entry 'step4': '<S115>:133' */
            HighClearance_model_Y.calState = calSTEP4_e;

            /* Entry Internal 'step4': '<S115>:133' */
            /* Transition: '<S115>:523' */
            HighClearance_model_FuncInternalData0.is_step4 =
              HighClearance_model_IN_active;

            /* Entry 'active': '<S115>:527' */
            HighClearance_model_heightUp();
          }
        }
      }
    }
    else
    {
      /* During 'paused': '<S115>:529' */
      if (!HighClearance_model_pauseCal())
      {
        /* Outport: '<Root>/calState' */
        /* Transition: '<S115>:528' */
        /* Exit 'paused': '<S115>:529' */
        tmp = HighClearance_model_Y.calState - calPAUSED_e;
        if (tmp < 0)
        {
          tmp = 0;
        }

        /* Outport: '<Root>/calState' */
        HighClearance_model_Y.calState = (uint16_T)tmp;
        HighClearance_model_FuncInternalData0.is_step3 =
          HighClearance_model_IN_active;

        /* Entry 'active': '<S115>:531' */
        HighClearance_model_heightUp();

        /* Entry Internal 'active': '<S115>:531' */
        /* Transition: '<S115>:417' */
        HighClearance_model_FuncInternalData0.is_active_d =
          HighClearance_model_IN_moving_j;
      }
    }
    break;

   default:
    /* Inport: '<Root>/calCmd' incorporates:
     *  Outport: '<Root>/calState'
     */
    /* During 'step4': '<S115>:133' */
    if ((HighClearance_model_U.calCmd == calCONFIRM4_e) &&
        (HighClearance_model_Y.calState == calSTEP4_e))
    {
      /* Transition: '<S115>:261' */
      /* Exit Internal 'step4': '<S115>:133' */
      if (HighClearance_model_FuncInternalData0.is_step4 ==
          HighClearance_model_IN_paused_a)
      {
        /* Exit 'paused': '<S115>:524' */
        tmp = HighClearance_model_Y.calState - calPAUSED_e;
        if (tmp < 0)
        {
          tmp = 0;
        }

        HighClearance_model_Y.calState = (uint16_T)tmp;
        HighClearance_model_FuncInternalData0.is_step4 =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      }
      else
      {
        HighClearance_model_FuncInternalData0.is_step4 =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      }

      HighClearance_model_FuncInternalData0.is_active =
        HighClearance_model_IN_checkUpCalValues;

      /* Entry 'checkUpCalValues': '<S115>:258' */
      HighClearance_model_updateCalUpValues(Switch_a, Switch_j, Switch_i,
        Switch_f);
      HighClearance_model_heightStop();
    }
    else if (HighClearance_model_U.calCmd == calDECLINE_e)
    {
      /* Transition: '<S115>:459' */
      /* Exit Internal 'step4': '<S115>:133' */
      if (HighClearance_model_FuncInternalData0.is_step4 ==
          HighClearance_model_IN_paused_a)
      {
        /* Exit 'paused': '<S115>:524' */
        HighClearance_model_FuncInternalData0.is_step4 =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      }
      else
      {
        HighClearance_model_FuncInternalData0.is_step4 =
          HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      }

      HighClearance_model_FuncInternalData0.is_active =
        HighClearance_model_IN_step3;
      HighClearance_model_FuncInternalData0.temporalCounter_i2 = 0U;

      /* Entry 'step3': '<S115>:416' */
      HighClearance_model_Y.calState = calSTEP3_e;

      /* Entry Internal 'step3': '<S115>:416' */
      /* Transition: '<S115>:532' */
      HighClearance_model_FuncInternalData0.is_step3 =
        HighClearance_model_IN_active;

      /* Entry 'active': '<S115>:531' */
      HighClearance_model_heightUp();

      /* Entry Internal 'active': '<S115>:531' */
      /* Transition: '<S115>:417' */
      HighClearance_model_FuncInternalData0.is_active_d =
        HighClearance_model_IN_moving_j;
    }
    else if (HighClearance_model_FuncInternalData0.is_step4 ==
             HighClearance_model_IN_active)
    {
      /* During 'active': '<S115>:527' */
      if (HighClearance_model_pauseCal())
      {
        /* Transition: '<S115>:526' */
        HighClearance_model_FuncInternalData0.is_step4 =
          HighClearance_model_IN_paused_a;

        /* Entry 'paused': '<S115>:524' */
        HighClearance_model_heightStop();
        tmp = HighClearance_model_Y.calState + calPAUSED_e;
        if (tmp > 65535)
        {
          tmp = 65535;
        }

        HighClearance_model_Y.calState = (uint16_T)tmp;
      }
    }
    else
    {
      /* During 'paused': '<S115>:524' */
      if (!HighClearance_model_pauseCal())
      {
        /* Transition: '<S115>:525' */
        /* Exit 'paused': '<S115>:524' */
        tmp = HighClearance_model_Y.calState - calPAUSED_e;
        if (tmp < 0)
        {
          tmp = 0;
        }

        HighClearance_model_Y.calState = (uint16_T)tmp;
        HighClearance_model_FuncInternalData0.is_step4 =
          HighClearance_model_IN_active;

        /* Entry 'active': '<S115>:527' */
        HighClearance_model_heightUp();
      }
    }
    break;
  }
}

/* Function for Chart: '<S5>/actualMachineState' */
static boolean_T HighClearance_model_checkError(const StateBus
  *BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1)
{
  boolean_T out;

  /* Graphical Function 'checkError': '<S13>:411' */
  /* Transition: '<S13>:413' */
  if ((BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->FrontLeft
       == heightError_e) ||
      (BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->FrontRight
       == heightError_e) ||
      (BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->RearLeft
       == heightError_e) ||
      (BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->RearRight
       == heightError_e))
  {
    /* Transition: '<S13>:416' */
    /* Transition: '<S13>:442' */
    /* Transition: '<S13>:431' */
    /* Transition: '<S13>:443' */
    /* Transition: '<S13>:430' */
    /* Transition: '<S13>:444' */
    /* Transition: '<S13>:435' */
    /* Transition: '<S13>:445' */
    out = true;

    /* Transition: '<S13>:441' */
  }
  else
  {
    /* Transition: '<S13>:418' */
    /* Transition: '<S13>:436' */
    /* Transition: '<S13>:437' */
    /* Transition: '<S13>:440' */
    out = false;
  }

  return out;
}

/* Function for Chart: '<S5>/actualMachineState' */
static boolean_T HighClearance_model_checkCalibrating(void)
{
  boolean_T out;

  /* Graphical Function 'checkCalibrating': '<S13>:613' */
  /* Transition: '<S13>:615' */
  if (HighClearance_model_FuncInternalData0.calActive)
  {
    /* Transition: '<S13>:635' */
    /* Transition: '<S13>:639' */
    out = true;

    /* Transition: '<S13>:638' */
  }
  else
  {
    /* Transition: '<S13>:636' */
    out = false;
  }

  return out;
}

/* Function for Chart: '<S5>/actualMachineState' */
static boolean_T HighClearance_model_checkDown(const StateBus
  *BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1)
{
  boolean_T out;

  /* Graphical Function 'checkDown': '<S13>:534' */
  /* Transition: '<S13>:542' */
  if ((BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->FrontLeft
       == heightDown_e) &&
      (BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->FrontRight
       == heightDown_e) &&
      (BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->RearLeft
       == heightDown_e) &&
      (BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->RearRight
       == heightDown_e))
  {
    /* Transition: '<S13>:543' */
    /* Transition: '<S13>:545' */
    /* Transition: '<S13>:546' */
    /* Transition: '<S13>:547' */
    /* Transition: '<S13>:548' */
    out = true;

    /* Transition: '<S13>:549' */
  }
  else
  {
    /* Transition: '<S13>:544' */
    out = false;
  }

  return out;
}

/* Function for Chart: '<S5>/actualMachineState' */
static boolean_T HighClearance_model_checkUp(const StateBus
  *BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1)
{
  boolean_T out;

  /* Graphical Function 'checkUp': '<S13>:508' */
  /* Transition: '<S13>:519' */
  if ((BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->FrontLeft
       == heightUp_e) &&
      (BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->FrontRight
       == heightUp_e) &&
      (BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->RearLeft
       == heightUp_e) &&
      (BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->RearRight
       == heightUp_e))
  {
    /* Transition: '<S13>:520' */
    /* Transition: '<S13>:523' */
    /* Transition: '<S13>:526' */
    /* Transition: '<S13>:529' */
    /* Transition: '<S13>:531' */
    out = true;

    /* Transition: '<S13>:532' */
  }
  else
  {
    /* Transition: '<S13>:530' */
    out = false;
  }

  return out;
}

/* Function for Chart: '<S5>/actualMachineState' */
static boolean_T HighClearance_model_checkMovingDown(const StateBus
  *BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1)
{
  boolean_T out;

  /* Graphical Function 'checkMovingDown': '<S13>:482' */
  /* Transition: '<S13>:493' */
  if ((BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->FrontLeft
       == heightMovingDown_e) ||
      (BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->FrontRight
       == heightMovingDown_e) ||
      (BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->RearLeft
       == heightMovingDown_e) ||
      (BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->RearRight
       == heightMovingDown_e))
  {
    /* Transition: '<S13>:494' */
    /* Transition: '<S13>:496' */
    /* Transition: '<S13>:497' */
    /* Transition: '<S13>:499' */
    /* Transition: '<S13>:500' */
    /* Transition: '<S13>:502' */
    /* Transition: '<S13>:503' */
    /* Transition: '<S13>:505' */
    out = true;

    /* Transition: '<S13>:506' */
  }
  else
  {
    /* Transition: '<S13>:495' */
    /* Transition: '<S13>:498' */
    /* Transition: '<S13>:501' */
    /* Transition: '<S13>:504' */
    out = false;
  }

  return out;
}

/* Function for Chart: '<S5>/actualMachineState' */
static boolean_T HighClearance_model_checkMovingUp(const StateBus
  *BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1)
{
  boolean_T out;

  /* Graphical Function 'checkMovingUp': '<S13>:456' */
  /* Transition: '<S13>:467' */
  if ((BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->FrontLeft
       == heightMovingUp_e) ||
      (BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->FrontRight
       == heightMovingUp_e) ||
      (BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->RearLeft
       == heightMovingUp_e) ||
      (BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1->RearRight
       == heightMovingUp_e))
  {
    /* Transition: '<S13>:468' */
    /* Transition: '<S13>:470' */
    /* Transition: '<S13>:471' */
    /* Transition: '<S13>:473' */
    /* Transition: '<S13>:474' */
    /* Transition: '<S13>:476' */
    /* Transition: '<S13>:477' */
    /* Transition: '<S13>:479' */
    out = true;

    /* Transition: '<S13>:480' */
  }
  else
  {
    /* Transition: '<S13>:469' */
    /* Transition: '<S13>:472' */
    /* Transition: '<S13>:475' */
    /* Transition: '<S13>:478' */
    out = false;
  }

  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_parkBrakeOkay(void)
{
  boolean_T out;

  /* Inport: '<Root>/selectedGear' */
  /* Graphical Function 'parkBrakeOkay': '<S7>:1550' */
  /* Transition: '<S7>:1555' */
  if (HighClearance_model_U.selectedGear != 251.0F)
  {
    /* Transition: '<S7>:1556' */
    /* Transition: '<S7>:1558' */
    out = true;

    /* Transition: '<S7>:1559' */
  }
  else
  {
    /* Transition: '<S7>:1557' */
    out = false;
  }

  /* End of Inport: '<Root>/selectedGear' */
  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_requireSpeed(void)
{
  /* Graphical Function 'requireSpeed': '<S7>:717' */
  /* Transition: '<S7>:725' */
  /* Transition: '<S7>:727' */
  /* Transition: '<S7>:1582' */
  /* Transition: '<S7>:1108' */
  /* Transition: '<S7>:1126' */
  /* Transition: '<S7>:1127' */
  /* Transition: '<S7>:1128' */
  /* Transition: '<S7>:1133' */
  /* Transition: '<S7>:1181' */
  /* Transition: '<S7>:733' */
  return false;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_speedOkay(void)
{
  boolean_T out;

  /* Inport: '<Root>/machineSpeedKph' */
  /* Graphical Function 'speedOkay': '<S7>:870' */
  /* Transition: '<S7>:880' */
  if ((HighClearance_model_requireSpeed() &&
       (HighClearance_model_U.machineSpeedKph >
        HighClearance_model_P.errorMinSpd)) ||
      (HighClearance_model_U.machineSpeedKph >=
       HighClearance_model_P.minTransitionMachineSpd))
  {
    /* Transition: '<S7>:881' */
    /* Transition: '<S7>:882' */
    /* Transition: '<S7>:884' */
    /* Transition: '<S7>:885' */
    if (HighClearance_model_U.machineSpeedKph <=
        HighClearance_model_P.maxTransitionMachineSpd)
    {
      /* Transition: '<S7>:886' */
      /* Transition: '<S7>:889' */
      out = true;
    }
    else
    {
      /* Transition: '<S7>:888' */
      /* Transition: '<S7>:890' */
      out = false;
    }
  }
  else
  {
    /* Transition: '<S7>:883' */
    /* Transition: '<S7>:887' */
    /* Transition: '<S7>:891' */
    /* Transition: '<S7>:890' */
    out = false;
  }

  /* End of Inport: '<Root>/machineSpeedKph' */
  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_wasOkay(void)
{
  boolean_T out;

  /* Graphical Function 'wasOkay': '<S7>:794' */
  /* Transition: '<S7>:799' */
  /* Transition: '<S7>:1669' */
  /* Transition: '<S7>:1670' */
  /* Transition: '<S7>:1671' */
  /* Transition: '<S7>:802' */
  out = true;

  /* Transition: '<S7>:1661' */
  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_trackWidthError(void)
{
  boolean_T out;

  /* Graphical Function 'trackWidthError': '<S7>:833' */
  /* Transition: '<S7>:844' */
  if ((HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_8_BusCreator1.FrontLeft
       <= 0.0F) ||
      (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_8_BusCreator1.FrontRight
       <= 0.0F) ||
      (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_8_BusCreator1.RearLeft
       <= 0.0F) ||
      (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_8_BusCreator1.RearRight
       <= 0.0F))
  {
    /* Transition: '<S7>:845' */
    /* Transition: '<S7>:847' */
    /* Transition: '<S7>:848' */
    /* Transition: '<S7>:850' */
    /* Transition: '<S7>:851' */
    /* Transition: '<S7>:853' */
    /* Transition: '<S7>:854' */
    /* Transition: '<S7>:856' */
    out = true;

    /* Transition: '<S7>:857' */
  }
  else
  {
    /* Transition: '<S7>:846' */
    /* Transition: '<S7>:849' */
    /* Transition: '<S7>:852' */
    /* Transition: '<S7>:855' */
    out = false;
  }

  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_trackRngCheck(real32_T width)
{
  boolean_T out;

  /* Graphical Function 'trackRngCheck': '<S7>:781' */
  /* Transition: '<S7>:787' */
  if (!HighClearance_model_trackWidthError())
  {
    /* Transition: '<S7>:788' */
    if ((width >= HighClearance_model_P.trackWidthMin -
         HighClearance_model_P.trackWidthTolerance) && (width <=
         HighClearance_model_P.trackWidthMax +
         HighClearance_model_P.trackWidthTolerance))
    {
      /* Transition: '<S7>:789' */
      /* Transition: '<S7>:791' */
      /* Transition: '<S7>:792' */
      out = true;
    }
    else
    {
      /* Transition: '<S7>:790' */
      out = false;
    }
  }
  else
  {
    /* Transition: '<S7>:790' */
    out = false;
  }

  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_trackWidthOkay_j(void)
{
  boolean_T out;

  /* Graphical Function 'trackWidthOkay': '<S7>:805' */
  /* Transition: '<S7>:817' */
  if (HighClearance_model_trackRngCheck
      (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_8_BusCreator1.FrontLeft))
  {
    /* Transition: '<S7>:820' */
    if (HighClearance_model_trackRngCheck
        (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_8_BusCreator1.FrontRight))
    {
      /* Transition: '<S7>:823' */
      if (HighClearance_model_trackRngCheck
          (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_8_BusCreator1.RearLeft))
      {
        /* Transition: '<S7>:826' */
        if (HighClearance_model_trackRngCheck
            (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_8_BusCreator1.RearRight))
        {
          /* Transition: '<S7>:829' */
          /* Transition: '<S7>:830' */
          out = true;
        }
        else
        {
          /* Transition: '<S7>:827' */
          /* Transition: '<S7>:828' */
          out = false;

          /* Transition: '<S7>:831' */
        }
      }
      else
      {
        /* Transition: '<S7>:824' */
        /* Transition: '<S7>:825' */
        /* Transition: '<S7>:828' */
        out = false;

        /* Transition: '<S7>:831' */
      }
    }
    else
    {
      /* Transition: '<S7>:821' */
      /* Transition: '<S7>:822' */
      /* Transition: '<S7>:825' */
      /* Transition: '<S7>:828' */
      out = false;

      /* Transition: '<S7>:831' */
    }
  }
  else
  {
    /* Transition: '<S7>:818' */
    /* Transition: '<S7>:819' */
    /* Transition: '<S7>:822' */
    /* Transition: '<S7>:825' */
    /* Transition: '<S7>:828' */
    out = false;

    /* Transition: '<S7>:831' */
  }

  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_okayToLower(void)
{
  boolean_T out;

  /* Graphical Function 'okayToLower': '<S7>:736' */
  /* Transition: '<S7>:749' */
  if (HighClearance_model_parkBrakeOkay())
  {
    /* Transition: '<S7>:1546' */
    if (HighClearance_model_speedOkay())
    {
      /* Transition: '<S7>:750' */
      if (HighClearance_model_wasOkay())
      {
        /* Inport: '<Root>/fieldModeActive' */
        /* Transition: '<S7>:751' */
        /* Transition: '<S7>:752' */
        if (HighClearance_model_U.fieldModeActive)
        {
          /* Transition: '<S7>:753' */
          if (HighClearance_model_trackWidthError())
          {
            /* Transition: '<S7>:754' */
            /* Transition: '<S7>:760' */
            out = true;
          }
          else
          {
            /* Transition: '<S7>:1654' */
            if (HighClearance_model_trackWidthOkay_j())
            {
              /* Transition: '<S7>:1655' */
              /* Transition: '<S7>:1656' */
              /* Transition: '<S7>:760' */
              out = true;
            }
            else
            {
              /* Transition: '<S7>:755' */
              /* Transition: '<S7>:765' */
              out = false;
            }
          }
        }
        else
        {
          /* Transition: '<S7>:755' */
          /* Transition: '<S7>:765' */
          out = false;
        }

        /* End of Inport: '<Root>/fieldModeActive' */
      }
      else
      {
        /* Transition: '<S7>:755' */
        /* Transition: '<S7>:765' */
        out = false;
      }
    }
    else
    {
      /* Transition: '<S7>:755' */
      /* Transition: '<S7>:765' */
      out = false;
    }
  }
  else
  {
    /* Transition: '<S7>:755' */
    /* Transition: '<S7>:765' */
    out = false;
  }

  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_disableLower(void)
{
  boolean_T out;

  /* Graphical Function 'disableLower': '<S7>:1250' */
  /* Transition: '<S7>:1267' */
  if ((HighClearance_model_FuncInternalData0.prevTargetState ==
       heightMovingDown_e) && (!HighClearance_model_FuncInternalData0.alive))
  {
    /* Transition: '<S7>:1315' */
    /* Transition: '<S7>:1638' */
    /* Transition: '<S7>:1408' */
    /* Transition: '<S7>:1288' */
    out = true;
  }
  else
  {
    /* Transition: '<S7>:1416' */
    /* Transition: '<S7>:1287' */
    /* Transition: '<S7>:1289' */
    out = false;
  }

  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_okayToRaise(void)
{
  boolean_T out;

  /* Graphical Function 'okayToRaise': '<S7>:893' */
  /* Transition: '<S7>:900' */
  /* Transition: '<S7>:1248' */
  /* Transition: '<S7>:1548' */
  if (HighClearance_model_trackWidthOkay_j())
  {
    /* Transition: '<S7>:901' */
    if (HighClearance_model_speedOkay())
    {
      /* Transition: '<S7>:1302' */
      if (HighClearance_model_wasOkay())
      {
        /* Inport: '<Root>/fieldModeActive' */
        /* Transition: '<S7>:1296' */
        /* Transition: '<S7>:1300' */
        if (HighClearance_model_U.fieldModeActive)
        {
          /* Transition: '<S7>:1291' */
          /* Transition: '<S7>:905' */
          out = true;
        }
        else
        {
          /* Transition: '<S7>:903' */
          /* Transition: '<S7>:907' */
          out = false;
        }

        /* End of Inport: '<Root>/fieldModeActive' */
      }
      else
      {
        /* Transition: '<S7>:903' */
        /* Transition: '<S7>:907' */
        out = false;
      }
    }
    else
    {
      /* Transition: '<S7>:903' */
      /* Transition: '<S7>:907' */
      out = false;
    }
  }
  else
  {
    /* Transition: '<S7>:903' */
    /* Transition: '<S7>:907' */
    out = false;
  }

  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_trackCylError(void)
{
  boolean_T out;

  /* Graphical Function 'trackCylError': '<S7>:1135' */
  /* Transition: '<S7>:1146' */
  if ((HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.extend.FrontLeft
       != HighClearance_model_P.IOD_OK) ||
      (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.extend.FrontRight
       != HighClearance_model_P.IOD_OK) ||
      (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.extend.RearLeft
       != HighClearance_model_P.IOD_OK) ||
      (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.extend.RearRight
       != HighClearance_model_P.IOD_OK) ||
      (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.retract.FrontLeft
       != HighClearance_model_P.IOD_OK) ||
      (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.retract.FrontRight
       != HighClearance_model_P.IOD_OK) ||
      (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.retract.RearLeft
       != HighClearance_model_P.IOD_OK) ||
      (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.retract.RearRight
       != HighClearance_model_P.IOD_OK))
  {
    /* Transition: '<S7>:1147' */
    /* Transition: '<S7>:1149' */
    /* Transition: '<S7>:1150' */
    /* Transition: '<S7>:1152' */
    /* Transition: '<S7>:1153' */
    /* Transition: '<S7>:1155' */
    /* Transition: '<S7>:1156' */
    /* Transition: '<S7>:1179' */
    /* Transition: '<S7>:1172' */
    /* Transition: '<S7>:1177' */
    /* Transition: '<S7>:1169' */
    /* Transition: '<S7>:1175' */
    /* Transition: '<S7>:1165' */
    /* Transition: '<S7>:1166' */
    /* Transition: '<S7>:1168' */
    /* Transition: '<S7>:1158' */
    out = true;

    /* Transition: '<S7>:1159' */
  }
  else
  {
    /* Transition: '<S7>:1148' */
    /* Transition: '<S7>:1151' */
    /* Transition: '<S7>:1154' */
    /* Transition: '<S7>:1178' */
    /* Transition: '<S7>:1164' */
    /* Transition: '<S7>:1171' */
    /* Transition: '<S7>:1176' */
    /* Transition: '<S7>:1157' */
    out = false;
  }

  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_disableRiase(void)
{
  boolean_T out;
  boolean_T guard1 = false;

  /* Graphical Function 'disableRiase': '<S7>:1419' */
  /* Transition: '<S7>:1428' */
  guard1 = false;
  if (HighClearance_model_FuncInternalData0.prevTargetState == heightMovingUp_e)
  {
    /* Transition: '<S7>:1435' */
    if (!HighClearance_model_FuncInternalData0.alive)
    {
      /* Transition: '<S7>:1636' */
      /* Transition: '<S7>:1637' */
      /* Transition: '<S7>:1433' */
      /* Transition: '<S7>:1651' */
      /* Transition: '<S7>:1447' */
      /* Transition: '<S7>:1467' */
      /* Transition: '<S7>:1480' */
      /* Transition: '<S7>:1481' */
      /* Transition: '<S7>:1482' */
      /* Transition: '<S7>:1503' */
      /* Transition: '<S7>:1490' */
      /* Transition: '<S7>:1496' */
      /* Transition: '<S7>:1486' */
      /* Transition: '<S7>:1437' */
      out = true;
    }
    else
    {
      /* Transition: '<S7>:1449' */
      guard1 = true;
    }
  }
  else
  {
    /* Transition: '<S7>:1431' */
    if (HighClearance_model_FuncInternalData0.prevTargetState == heightDown_e)
    {
      /* Transition: '<S7>:1430' */
      guard1 = true;
    }
    else
    {
      /* Transition: '<S7>:1436' */
      /* Transition: '<S7>:1453' */
      /* Transition: '<S7>:1438' */
      out = false;
    }
  }

  if (guard1)
  {
    if (HighClearance_model_trackWidthError())
    {
      /* Transition: '<S7>:1460' */
      /* Transition: '<S7>:1433' */
      /* Transition: '<S7>:1651' */
      /* Transition: '<S7>:1447' */
      /* Transition: '<S7>:1467' */
      /* Transition: '<S7>:1480' */
      /* Transition: '<S7>:1481' */
      /* Transition: '<S7>:1482' */
      /* Transition: '<S7>:1503' */
      /* Transition: '<S7>:1490' */
      /* Transition: '<S7>:1496' */
      /* Transition: '<S7>:1486' */
      /* Transition: '<S7>:1437' */
      out = true;
    }
    else
    {
      /* Transition: '<S7>:1432' */
      if (HighClearance_model_trackCylError())
      {
        /* Transition: '<S7>:1633' */
        /* Transition: '<S7>:1651' */
        /* Transition: '<S7>:1447' */
        /* Transition: '<S7>:1467' */
        /* Transition: '<S7>:1480' */
        /* Transition: '<S7>:1481' */
        /* Transition: '<S7>:1482' */
        /* Transition: '<S7>:1503' */
        /* Transition: '<S7>:1490' */
        /* Transition: '<S7>:1496' */
        /* Transition: '<S7>:1486' */
        /* Transition: '<S7>:1437' */
        out = true;
      }
      else
      {
        /* Transition: '<S7>:1648' */
        if (!HighClearance_model_FuncInternalData0.dwnBtnOk)
        {
          /* Transition: '<S7>:1646' */
          /* Transition: '<S7>:1447' */
          /* Transition: '<S7>:1467' */
          /* Transition: '<S7>:1480' */
          /* Transition: '<S7>:1481' */
          /* Transition: '<S7>:1482' */
          /* Transition: '<S7>:1503' */
          /* Transition: '<S7>:1490' */
          /* Transition: '<S7>:1496' */
          /* Transition: '<S7>:1486' */
          /* Transition: '<S7>:1437' */
          out = true;
        }
        else
        {
          /* Outport: '<Root>/machineState' */
          /* Transition: '<S7>:1458' */
          if (HighClearance_model_Y.machineState == heightError_e)
          {
            /* Transition: '<S7>:1462' */
            /* Transition: '<S7>:1467' */
            /* Transition: '<S7>:1480' */
            /* Transition: '<S7>:1481' */
            /* Transition: '<S7>:1482' */
            /* Transition: '<S7>:1503' */
            /* Transition: '<S7>:1490' */
            /* Transition: '<S7>:1496' */
            /* Transition: '<S7>:1486' */
            /* Transition: '<S7>:1437' */
            out = true;
          }
          else
          {
            /* Transition: '<S7>:1465' */
            if (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.extend.FrontLeft
                != HighClearance_model_P.IOD_OK)
            {
              /* Transition: '<S7>:1463' */
              /* Transition: '<S7>:1480' */
              /* Transition: '<S7>:1481' */
              /* Transition: '<S7>:1482' */
              /* Transition: '<S7>:1503' */
              /* Transition: '<S7>:1490' */
              /* Transition: '<S7>:1496' */
              /* Transition: '<S7>:1486' */
              /* Transition: '<S7>:1437' */
              out = true;
            }
            else
            {
              /* Transition: '<S7>:1477' */
              if (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.extend.FrontRight
                  != HighClearance_model_P.IOD_OK)
              {
                /* Transition: '<S7>:1469' */
                /* Transition: '<S7>:1481' */
                /* Transition: '<S7>:1482' */
                /* Transition: '<S7>:1503' */
                /* Transition: '<S7>:1490' */
                /* Transition: '<S7>:1496' */
                /* Transition: '<S7>:1486' */
                /* Transition: '<S7>:1437' */
                out = true;
              }
              else
              {
                /* Transition: '<S7>:1478' */
                if (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.extend.RearLeft
                    != HighClearance_model_P.IOD_OK)
                {
                  /* Transition: '<S7>:1472' */
                  /* Transition: '<S7>:1482' */
                  /* Transition: '<S7>:1503' */
                  /* Transition: '<S7>:1490' */
                  /* Transition: '<S7>:1496' */
                  /* Transition: '<S7>:1486' */
                  /* Transition: '<S7>:1437' */
                  out = true;
                }
                else
                {
                  /* Transition: '<S7>:1479' */
                  if (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.extend.RearRight
                      != HighClearance_model_P.IOD_OK)
                  {
                    /* Transition: '<S7>:1475' */
                    /* Transition: '<S7>:1503' */
                    /* Transition: '<S7>:1490' */
                    /* Transition: '<S7>:1496' */
                    /* Transition: '<S7>:1486' */
                    /* Transition: '<S7>:1437' */
                    out = true;
                  }
                  else
                  {
                    /* Transition: '<S7>:1502' */
                    if (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.retract.FrontLeft
                        != HighClearance_model_P.IOD_OK)
                    {
                      /* Transition: '<S7>:1497' */
                      /* Transition: '<S7>:1490' */
                      /* Transition: '<S7>:1496' */
                      /* Transition: '<S7>:1486' */
                      /* Transition: '<S7>:1437' */
                      out = true;
                    }
                    else
                    {
                      /* Transition: '<S7>:1483' */
                      if (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.retract.FrontRight
                          != HighClearance_model_P.IOD_OK)
                      {
                        /* Transition: '<S7>:1491' */
                        /* Transition: '<S7>:1496' */
                        /* Transition: '<S7>:1486' */
                        /* Transition: '<S7>:1437' */
                        out = true;
                      }
                      else
                      {
                        /* Transition: '<S7>:1494' */
                        if (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.retract.RearLeft
                            != HighClearance_model_P.IOD_OK)
                        {
                          /* Transition: '<S7>:1492' */
                          /* Transition: '<S7>:1486' */
                          /* Transition: '<S7>:1437' */
                          out = true;
                        }
                        else
                        {
                          /* Transition: '<S7>:1500' */
                          if (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.retract.RearRight
                              != HighClearance_model_P.IOD_OK)
                          {
                            /* Transition: '<S7>:1499' */
                            /* Transition: '<S7>:1437' */
                            out = true;
                          }
                          else
                          {
                            /* Transition: '<S7>:1501' */
                            /* Transition: '<S7>:1438' */
                            out = false;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }

          /* End of Outport: '<Root>/machineState' */
        }
      }
    }
  }

  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_calOkay(void)
{
  boolean_T out;

  /* Outport: '<Root>/machineState' */
  /* Graphical Function 'calOkay': '<S7>:767' */
  /* Transition: '<S7>:773' */
  if ((HighClearance_model_Y.machineState != heightCalibrating_e) &&
      HighClearance_model_FuncInternalData0.calOkay)
  {
    /* Transition: '<S7>:774' */
    /* Transition: '<S7>:776' */
    /* Transition: '<S7>:777' */
    out = true;
  }
  else
  {
    /* Transition: '<S7>:775' */
    out = false;

    /* Transition: '<S7>:778' */
  }

  /* End of Outport: '<Root>/machineState' */
  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static void HighClearance_model_clearWarnings(void)
{
  /* Outport: '<Root>/userWarnings' */
  /* Graphical Function 'clearWarnings': '<S7>:686' */
  /* Transition: '<S7>:688' */
  HighClearance_model_Y.userWarnings.trackWidth = false;
  HighClearance_model_Y.userWarnings.speed = false;
  HighClearance_model_Y.userWarnings.guide = false;
  HighClearance_model_Y.userWarnings.was = false;
  HighClearance_model_Y.userWarnings.fws = false;
  HighClearance_model_Y.userWarnings.fieldRoad = false;
  HighClearance_model_Y.userWarnings.cal = false;
  HighClearance_model_Y.userWarnings.parkBrake = false;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_noMovementErr(void)
{
  boolean_T out;

  /* Graphical Function 'noMovementErr': '<S7>:1514' */
  /* Transition: '<S7>:1526' */
  if (HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_14_BusCreator1.FrontLeft.noMovementErr
      ||
      HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_14_BusCreator1.FrontRight.noMovementErr
      ||
      HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_14_BusCreator1.RearLeft.noMovementErr
      ||
      HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_14_BusCreator1.RearRight.noMovementErr)
  {
    /* Transition: '<S7>:1529' */
    /* Transition: '<S7>:1543' */
    /* Transition: '<S7>:1532' */
    /* Transition: '<S7>:1541' */
    /* Transition: '<S7>:1535' */
    /* Transition: '<S7>:1542' */
    /* Transition: '<S7>:1538' */
    /* Transition: '<S7>:1539' */
    out = true;
  }
  else
  {
    /* Transition: '<S7>:1527' */
    /* Transition: '<S7>:1528' */
    /* Transition: '<S7>:1531' */
    /* Transition: '<S7>:1537' */
    out = false;

    /* Transition: '<S7>:1540' */
  }

  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_targetStateDown(void)
{
  boolean_T out;

  /* Outport: '<Root>/targetState' */
  /* Graphical Function 'targetStateDown': '<S7>:1319' */
  /* Transition: '<S7>:1336' */
  if ((HighClearance_model_Y.targetState == heightDown_e) ||
      (HighClearance_model_Y.targetState == heightMovingDown_e))
  {
    /* Transition: '<S7>:1337' */
    /* Transition: '<S7>:1339' */
    /* Transition: '<S7>:1340' */
    /* Transition: '<S7>:1357' */
    out = true;
  }
  else
  {
    /* Transition: '<S7>:1338' */
    /* Transition: '<S7>:1356' */
    /* Transition: '<S7>:1358' */
    out = false;
  }

  /* End of Outport: '<Root>/targetState' */
  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_targetStateUp(void)
{
  boolean_T out;

  /* Outport: '<Root>/targetState' */
  /* Graphical Function 'targetStateUp': '<S7>:1360' */
  /* Transition: '<S7>:1377' */
  if ((HighClearance_model_Y.targetState == heightUp_e) ||
      (HighClearance_model_Y.targetState == heightMovingUp_e))
  {
    /* Transition: '<S7>:1378' */
    /* Transition: '<S7>:1380' */
    /* Transition: '<S7>:1381' */
    /* Transition: '<S7>:1398' */
    out = true;
  }
  else
  {
    /* Transition: '<S7>:1379' */
    /* Transition: '<S7>:1397' */
    /* Transition: '<S7>:1399' */
    out = false;
  }

  /* End of Outport: '<Root>/targetState' */
  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static real_T HighClearance_model_restartTransition(void)
{
  real_T out;

  /* Graphical Function 'restartTransition': '<S7>:1018' */
  /* Transition: '<S7>:1056' */
  if ((HighClearance_model_FuncInternalData0.prevTargetState == heightMovingUp_e)
      && HighClearance_model_okayToRaise())
  {
    /* Transition: '<S7>:1047' */
    /* Transition: '<S7>:1048' */
    /* Transition: '<S7>:1050' */
    /* Transition: '<S7>:1046' */
    out = 1.0;
  }
  else
  {
    /* Transition: '<S7>:1049' */
    if (HighClearance_model_FuncInternalData0.prevTargetState ==
        heightMovingDown_e)
    {
      /* Transition: '<S7>:1051' */
      if (HighClearance_model_okayToLower())
      {
        /* Transition: '<S7>:1052' */
        /* Transition: '<S7>:1046' */
        out = 1.0;
      }
      else
      {
        /* Transition: '<S7>:1053' */
        /* Transition: '<S7>:1055' */
        out = 0.0;
      }
    }
    else
    {
      /* Transition: '<S7>:1053' */
      /* Transition: '<S7>:1055' */
      out = 0.0;
    }
  }

  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static void HighClearance_model_enter_internal_transitioning(void)
{
  /* Entry Internal 'transitioning': '<S7>:285' */
  switch (HighClearance_model_FuncInternalData0.was_transitioning)
  {
   case HighClearance_model_IN_down_h:
    HighClearance_model_FuncInternalData0.is_transitioning =
      HighClearance_model_IN_down_h;
    HighClearance_model_FuncInternalData0.was_transitioning =
      HighClearance_model_IN_down_h;

    /* Outport: '<Root>/targetState' */
    /* Entry 'down': '<S7>:89' */
    HighClearance_model_Y.targetState = heightMovingDown_e;
    HighClearance_model_FuncInternalData0.prevTargetState = heightMovingDown_e;

    /* Outport: '<Root>/mfaLeds' */
    HighClearance_model_Y.mfaLeds.upBtn = 0U;
    HighClearance_model_Y.mfaLeds.downBtn = 2U;
    break;

   case HighClearance_model_IN_up_mf:
    HighClearance_model_FuncInternalData0.is_transitioning =
      HighClearance_model_IN_up_mf;
    HighClearance_model_FuncInternalData0.was_transitioning =
      HighClearance_model_IN_up_mf;

    /* Outport: '<Root>/targetState' */
    /* Entry 'up': '<S7>:88' */
    HighClearance_model_Y.targetState = heightMovingUp_e;
    HighClearance_model_FuncInternalData0.prevTargetState = heightMovingUp_e;

    /* Outport: '<Root>/mfaLeds' */
    HighClearance_model_Y.mfaLeds.upBtn = 2U;
    HighClearance_model_Y.mfaLeds.downBtn = 0U;
    break;
  }
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static void HighClearance_model_downWarnings(void)
{
  /* Outport: '<Root>/userWarnings' incorporates:
   *  Inport: '<Root>/fieldModeActive'
   */
  /* Graphical Function 'downWarnings': '<S7>:975' */
  /* Transition: '<S7>:977' */
  HighClearance_model_Y.userWarnings.trackWidth =
    !HighClearance_model_trackWidthOkay_j();
  HighClearance_model_Y.userWarnings.speed = !HighClearance_model_speedOkay();
  HighClearance_model_Y.userWarnings.guide = false;
  HighClearance_model_Y.userWarnings.was = !HighClearance_model_wasOkay();
  HighClearance_model_Y.userWarnings.fws = false;
  HighClearance_model_Y.userWarnings.fieldRoad =
    !HighClearance_model_U.fieldModeActive;
  HighClearance_model_Y.userWarnings.cal = !HighClearance_model_calOkay();
  HighClearance_model_Y.userWarnings.parkBrake =
    !HighClearance_model_parkBrakeOkay();
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static void HighClearance_model_upWarnings(void)
{
  /* Outport: '<Root>/userWarnings' incorporates:
   *  Inport: '<Root>/fieldModeActive'
   */
  /* Graphical Function 'upWarnings': '<S7>:972' */
  /* Transition: '<S7>:974' */
  HighClearance_model_Y.userWarnings.trackWidth =
    !HighClearance_model_trackWidthOkay_j();
  HighClearance_model_Y.userWarnings.speed = !HighClearance_model_speedOkay();
  HighClearance_model_Y.userWarnings.guide = false;
  HighClearance_model_Y.userWarnings.was = !HighClearance_model_wasOkay();
  HighClearance_model_Y.userWarnings.fws = false;
  HighClearance_model_Y.userWarnings.fieldRoad =
    !HighClearance_model_U.fieldModeActive;
  HighClearance_model_Y.userWarnings.cal = !HighClearance_model_calOkay();
  HighClearance_model_Y.userWarnings.parkBrake = false;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static real_T HighClearance_model_pauseTransition(void)
{
  real_T out;

  /* Outport: '<Root>/targetState' */
  /* Graphical Function 'pauseTransition': '<S7>:926' */
  /* Transition: '<S7>:939' */
  if ((HighClearance_model_Y.targetState == heightMovingUp_e) &&
      (!HighClearance_model_okayToRaise()))
  {
    /* Transition: '<S7>:980' */
    /* Transition: '<S7>:982' */
    /* Transition: '<S7>:944' */
    HighClearance_model_upWarnings();

    /* Transition: '<S7>:985' */
    /* Transition: '<S7>:955' */
    out = 1.0;
  }
  else
  {
    /* Transition: '<S7>:983' */
    if (HighClearance_model_Y.targetState == heightMovingDown_e)
    {
      /* Transition: '<S7>:987' */
      if (!HighClearance_model_okayToLower())
      {
        /* Transition: '<S7>:989' */
        /* Transition: '<S7>:990' */
        HighClearance_model_downWarnings();

        /* Transition: '<S7>:955' */
        out = 1.0;
      }
      else
      {
        /* Transition: '<S7>:1057' */
        /* Transition: '<S7>:1058' */
        /* Transition: '<S7>:950' */
        out = 0.0;
      }
    }
    else
    {
      /* Transition: '<S7>:1057' */
      /* Transition: '<S7>:1058' */
      /* Transition: '<S7>:950' */
      out = 0.0;
    }
  }

  /* End of Outport: '<Root>/targetState' */
  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static void HighClearance_model_active(const uint8_T *stopBtn_prev, const
  uint8_T *upBtn_prev, const uint8_T *downBtn_prev)
{
  boolean_T guard1 = false;
  boolean_T guard2 = false;

  /* Inport: '<Root>/manualOverride' */
  /* During 'active': '<S7>:969' */
  if (((*stopBtn_prev != HighClearance_model_FuncInternalData0.stopBtn_start) &&
       (HighClearance_model_FuncInternalData0.stopBtn_start == 1)) ||
      (HighClearance_model_U.manualOverride != 0) ||
      (!HighClearance_model_calOkay()) ||
      ((HighClearance_model_FuncInternalData0.prevTargetState ==
        heightMovingDown_e) && HighClearance_model_disableLower()) ||
      ((HighClearance_model_FuncInternalData0.prevTargetState ==
        heightMovingUp_e) && HighClearance_model_disableRiase()) ||
      HighClearance_model_noMovementErr())
  {
    /* Transition: '<S7>:101' */
    /* Transition: '<S7>:1585' */
    /* Transition: '<S7>:1506' */
    /* Transition: '<S7>:1309' */
    /* Transition: '<S7>:1308' */
    /* Transition: '<S7>:1203' */
    /* Transition: '<S7>:1205' */
    /* Transition: '<S7>:1512' */
    /* Exit Internal 'active': '<S7>:969' */
    /* Exit Internal 'transitioning': '<S7>:285' */
    HighClearance_model_FuncInternalData0.is_transitioning =
      HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
    HighClearance_model_FuncInternalData0.is_active_dy =
      HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
    HighClearance_model_FuncInternalData0.is_states_k =
      HighClearance_model_IN_doNothing;

    /* Outport: '<Root>/targetState' */
    /* Entry 'doNothing': '<S7>:72' */
    HighClearance_model_Y.targetState = heightUnknown_e;
    HighClearance_model_clearWarnings();

    /* Outport: '<Root>/mfaLeds' */
    HighClearance_model_Y.mfaLeds.downBtn = 0U;
    HighClearance_model_Y.mfaLeds.upBtn = 0U;
  }
  else
  {
    guard1 = false;
    guard2 = false;
    if ((*upBtn_prev != HighClearance_model_FuncInternalData0.upBtn_start) &&
        (HighClearance_model_FuncInternalData0.upBtn_start == 1) &&
        HighClearance_model_targetStateDown())
    {
      /* Transition: '<S7>:278' */
      /* Transition: '<S7>:1198' */
      /* Transition: '<S7>:701' */
      if (HighClearance_model_calOkay())
      {
        /* Transition: '<S7>:1187' */
        if (HighClearance_model_Y.machineState == heightUp_e)
        {
          /* Transition: '<S7>:1625' */
          /* Exit Internal 'active': '<S7>:969' */
          /* Exit Internal 'transitioning': '<S7>:285' */
          HighClearance_model_FuncInternalData0.is_transitioning =
            HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
          HighClearance_model_FuncInternalData0.is_states_k =
            HighClearance_model_IN_active;

          /* Entry 'active': '<S7>:969' */
          HighClearance_model_clearWarnings();
          HighClearance_model_FuncInternalData0.is_active_dy =
            HighClearance_model_IN_holdUp;
          HighClearance_model_FuncInternalData0.was_active =
            HighClearance_model_IN_holdUp;

          /* Outport: '<Root>/targetState' */
          /* Entry 'holdUp': '<S7>:1062' */
          HighClearance_model_Y.targetState = heightUp_e;
          HighClearance_model_FuncInternalData0.prevTargetState = heightUp_e;

          /* Outport: '<Root>/mfaLeds' */
          HighClearance_model_Y.mfaLeds.upBtn = 1U;
          HighClearance_model_Y.mfaLeds.downBtn = 0U;
        }
        else if (HighClearance_model_okayToRaise() &&
                 (!HighClearance_model_disableRiase()))
        {
          /* Transition: '<S7>:1626' */
          /* Transition: '<S7>:1632' */
          /* Exit Internal 'active': '<S7>:969' */
          /* Exit Internal 'transitioning': '<S7>:285' */
          HighClearance_model_FuncInternalData0.is_states_k =
            HighClearance_model_IN_active;

          /* Entry 'active': '<S7>:969' */
          HighClearance_model_clearWarnings();
          HighClearance_model_FuncInternalData0.is_active_dy =
            HighClearance_model_IN_transitioning_n;
          HighClearance_model_FuncInternalData0.was_active =
            HighClearance_model_IN_transitioning_n;
          HighClearance_model_FuncInternalData0.is_transitioning =
            HighClearance_model_IN_up_mf;
          HighClearance_model_FuncInternalData0.was_transitioning =
            HighClearance_model_IN_up_mf;

          /* Outport: '<Root>/targetState' */
          /* Entry 'up': '<S7>:88' */
          HighClearance_model_Y.targetState = heightMovingUp_e;
          HighClearance_model_FuncInternalData0.prevTargetState =
            heightMovingUp_e;

          /* Outport: '<Root>/mfaLeds' */
          HighClearance_model_Y.mfaLeds.upBtn = 2U;
          HighClearance_model_Y.mfaLeds.downBtn = 0U;
        }
        else
        {
          guard1 = true;
        }
      }
      else
      {
        guard1 = true;
      }
    }
    else if ((*downBtn_prev !=
              HighClearance_model_FuncInternalData0.downBtn_start) &&
             (HighClearance_model_FuncInternalData0.downBtn_start == 1) &&
             HighClearance_model_targetStateUp())
    {
      /* Transition: '<S7>:281' */
      /* Transition: '<S7>:1200' */
      /* Transition: '<S7>:700' */
      if (HighClearance_model_calOkay())
      {
        /* Transition: '<S7>:1190' */
        if (HighClearance_model_Y.machineState == heightDown_e)
        {
          /* Transition: '<S7>:1621' */
          /* Exit Internal 'active': '<S7>:969' */
          /* Exit Internal 'transitioning': '<S7>:285' */
          HighClearance_model_FuncInternalData0.is_transitioning =
            HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
          HighClearance_model_FuncInternalData0.is_states_k =
            HighClearance_model_IN_active;

          /* Entry 'active': '<S7>:969' */
          HighClearance_model_clearWarnings();
          HighClearance_model_FuncInternalData0.is_active_dy =
            HighClearance_model_IN_holdDown;
          HighClearance_model_FuncInternalData0.was_active =
            HighClearance_model_IN_holdDown;

          /* Outport: '<Root>/targetState' */
          /* Entry 'holdDown': '<S7>:1065' */
          HighClearance_model_Y.targetState = heightDown_e;
          HighClearance_model_FuncInternalData0.prevTargetState = heightDown_e;

          /* Outport: '<Root>/mfaLeds' */
          HighClearance_model_Y.mfaLeds.upBtn = 0U;
          HighClearance_model_Y.mfaLeds.downBtn = 1U;
        }
        else if (HighClearance_model_okayToLower() &&
                 (!HighClearance_model_disableLower()))
        {
          /* Transition: '<S7>:1623' */
          /* Transition: '<S7>:1631' */
          /* Exit Internal 'active': '<S7>:969' */
          /* Exit Internal 'transitioning': '<S7>:285' */
          HighClearance_model_FuncInternalData0.is_states_k =
            HighClearance_model_IN_active;

          /* Entry 'active': '<S7>:969' */
          HighClearance_model_clearWarnings();
          HighClearance_model_FuncInternalData0.is_active_dy =
            HighClearance_model_IN_transitioning_n;
          HighClearance_model_FuncInternalData0.was_active =
            HighClearance_model_IN_transitioning_n;
          HighClearance_model_FuncInternalData0.is_transitioning =
            HighClearance_model_IN_down_h;
          HighClearance_model_FuncInternalData0.was_transitioning =
            HighClearance_model_IN_down_h;

          /* Outport: '<Root>/targetState' */
          /* Entry 'down': '<S7>:89' */
          HighClearance_model_Y.targetState = heightMovingDown_e;
          HighClearance_model_FuncInternalData0.prevTargetState =
            heightMovingDown_e;

          /* Outport: '<Root>/mfaLeds' */
          HighClearance_model_Y.mfaLeds.upBtn = 0U;
          HighClearance_model_Y.mfaLeds.downBtn = 2U;
        }
        else
        {
          guard2 = true;
        }
      }
      else
      {
        guard2 = true;
      }
    }
    else
    {
      switch (HighClearance_model_FuncInternalData0.is_active_dy)
      {
       case HighClearance_model_IN_holdDown:
        /* Outport: '<Root>/targetState' */
        HighClearance_model_Y.targetState = heightDown_e;

        /* During 'holdDown': '<S7>:1065' */
        break;

       case HighClearance_model_IN_holdUp:
        /* Outport: '<Root>/targetState' */
        HighClearance_model_Y.targetState = heightUp_e;

        /* During 'holdUp': '<S7>:1062' */
        break;

       case HighClearance_model_IN_paused:
        /* Outport: '<Root>/targetState' */
        HighClearance_model_Y.targetState = heightUnknown_e;

        /* During 'paused': '<S7>:293' */
        if (HighClearance_model_FuncInternalData0.temporalCounter_i1_db >= 2U)
        {
          /* Transition: '<S7>:1561' */
          HighClearance_model_FuncInternalData0.is_active_dy =
            HighClearance_model_IN_wait_e;
          HighClearance_model_FuncInternalData0.was_active =
            HighClearance_model_IN_wait_e;

          /* Entry 'wait': '<S7>:1562' */
          HighClearance_model_clearWarnings();
        }
        break;

       case HighClearance_model_IN_transitioning_n:
        /* During 'transitioning': '<S7>:285' */
        if (HighClearance_model_pauseTransition() != 0.0)
        {
          /* Transition: '<S7>:979' */
          /* Exit Internal 'transitioning': '<S7>:285' */
          HighClearance_model_FuncInternalData0.is_transitioning =
            HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
          HighClearance_model_FuncInternalData0.is_active_dy =
            HighClearance_model_IN_paused;
          HighClearance_model_FuncInternalData0.was_active =
            HighClearance_model_IN_paused;
          HighClearance_model_FuncInternalData0.temporalCounter_i1_db = 0U;

          /* Outport: '<Root>/targetState' */
          /* Entry 'paused': '<S7>:293' */
          HighClearance_model_Y.targetState = heightUnknown_e;
        }
        else if (HighClearance_model_FuncInternalData0.is_transitioning ==
                 HighClearance_model_IN_down_h)
        {
          /* Outport: '<Root>/targetState' */
          HighClearance_model_Y.targetState = heightMovingDown_e;

          /* Outport: '<Root>/machineState' incorporates:
           *  Outport: '<Root>/mfaLeds'
           *  Outport: '<Root>/targetState'
           */
          /* During 'down': '<S7>:89' */
          if (HighClearance_model_Y.machineState == heightDown_e)
          {
            /* Transition: '<S7>:958' */
            HighClearance_model_FuncInternalData0.is_transitioning =
              HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            HighClearance_model_FuncInternalData0.is_active_dy =
              HighClearance_model_IN_holdDown;
            HighClearance_model_FuncInternalData0.was_active =
              HighClearance_model_IN_holdDown;

            /* Entry 'holdDown': '<S7>:1065' */
            HighClearance_model_Y.targetState = heightDown_e;
            HighClearance_model_FuncInternalData0.prevTargetState = heightDown_e;
            HighClearance_model_Y.mfaLeds.upBtn = 0U;
            HighClearance_model_Y.mfaLeds.downBtn = 1U;
          }
        }
        else
        {
          /* Outport: '<Root>/targetState' */
          HighClearance_model_Y.targetState = heightMovingUp_e;

          /* Outport: '<Root>/machineState' incorporates:
           *  Outport: '<Root>/mfaLeds'
           *  Outport: '<Root>/targetState'
           */
          /* During 'up': '<S7>:88' */
          if (HighClearance_model_Y.machineState == heightUp_e)
          {
            /* Transition: '<S7>:957' */
            HighClearance_model_FuncInternalData0.is_transitioning =
              HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            HighClearance_model_FuncInternalData0.is_active_dy =
              HighClearance_model_IN_holdUp;
            HighClearance_model_FuncInternalData0.was_active =
              HighClearance_model_IN_holdUp;

            /* Entry 'holdUp': '<S7>:1062' */
            HighClearance_model_Y.targetState = heightUp_e;
            HighClearance_model_FuncInternalData0.prevTargetState = heightUp_e;
            HighClearance_model_Y.mfaLeds.upBtn = 1U;
            HighClearance_model_Y.mfaLeds.downBtn = 0U;
          }
        }
        break;

       default:
        /* During 'wait': '<S7>:1562' */
        if (HighClearance_model_restartTransition() != 0.0)
        {
          /* Transition: '<S7>:924' */
          /* Transition: '<S7>:1564' */
          HighClearance_model_FuncInternalData0.is_active_dy =
            HighClearance_model_IN_transitioning_n;
          HighClearance_model_FuncInternalData0.was_active =
            HighClearance_model_IN_transitioning_n;
          HighClearance_model_enter_internal_transitioning();
        }
        break;
      }
    }

    if (guard2)
    {
      /* Transition: '<S7>:691' */
      /* Exit Internal 'active': '<S7>:969' */
      /* Exit Internal 'transitioning': '<S7>:285' */
      HighClearance_model_FuncInternalData0.is_transitioning =
        HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      HighClearance_model_FuncInternalData0.is_active_dy =
        HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      HighClearance_model_FuncInternalData0.is_states_k =
        HighClearance_model_IN_updateWarningsDown;
      HighClearance_model_FuncInternalData0.temporalCounter_i1_db = 0U;

      /* Entry 'updateWarningsDown': '<S7>:690' */
      HighClearance_model_downWarnings();
    }

    if (guard1)
    {
      /* Transition: '<S7>:689' */
      /* Exit Internal 'active': '<S7>:969' */
      /* Exit Internal 'transitioning': '<S7>:285' */
      HighClearance_model_FuncInternalData0.is_transitioning =
        HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      HighClearance_model_FuncInternalData0.is_active_dy =
        HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
      HighClearance_model_FuncInternalData0.is_states_k =
        HighClearance_model_IN_updateWarningsUp;
      HighClearance_model_FuncInternalData0.temporalCounter_i1_db = 0U;

      /* Entry 'updateWarningsUp': '<S7>:119' */
      HighClearance_model_upWarnings();
    }
  }

  /* End of Inport: '<Root>/manualOverride' */
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static boolean_T HighClearance_model_targetStateSelected(void)
{
  boolean_T out;

  /* Outport: '<Root>/targetState' */
  /* Graphical Function 'targetStateSelected': '<S7>:1067' */
  /* Transition: '<S7>:1075' */
  if ((HighClearance_model_Y.targetState == heightDown_e) ||
      (HighClearance_model_Y.targetState == heightUp_e) ||
      (HighClearance_model_Y.targetState == heightMovingUp_e) ||
      (HighClearance_model_Y.targetState == heightMovingDown_e))
  {
    /* Transition: '<S7>:1076' */
    /* Transition: '<S7>:1078' */
    /* Transition: '<S7>:1079' */
    /* Transition: '<S7>:1095' */
    /* Transition: '<S7>:1088' */
    /* Transition: '<S7>:1086' */
    /* Transition: '<S7>:1090' */
    /* Transition: '<S7>:1082' */
    out = true;
  }
  else
  {
    /* Transition: '<S7>:1077' */
    /* Transition: '<S7>:1094' */
    /* Transition: '<S7>:1093' */
    /* Transition: '<S7>:1080' */
    /* Transition: '<S7>:1083' */
    out = false;
  }

  /* End of Outport: '<Root>/targetState' */
  return out;
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static void HighClearance_model_enter_internal_active(void)
{
  /* Entry Internal 'active': '<S7>:969' */
  switch (HighClearance_model_FuncInternalData0.was_active)
  {
   case HighClearance_model_IN_holdDown:
    HighClearance_model_FuncInternalData0.is_active_dy =
      HighClearance_model_IN_holdDown;
    HighClearance_model_FuncInternalData0.was_active =
      HighClearance_model_IN_holdDown;

    /* Outport: '<Root>/targetState' */
    /* Entry 'holdDown': '<S7>:1065' */
    HighClearance_model_Y.targetState = heightDown_e;
    HighClearance_model_FuncInternalData0.prevTargetState = heightDown_e;

    /* Outport: '<Root>/mfaLeds' */
    HighClearance_model_Y.mfaLeds.upBtn = 0U;
    HighClearance_model_Y.mfaLeds.downBtn = 1U;
    break;

   case HighClearance_model_IN_holdUp:
    HighClearance_model_FuncInternalData0.is_active_dy =
      HighClearance_model_IN_holdUp;
    HighClearance_model_FuncInternalData0.was_active =
      HighClearance_model_IN_holdUp;

    /* Outport: '<Root>/targetState' */
    /* Entry 'holdUp': '<S7>:1062' */
    HighClearance_model_Y.targetState = heightUp_e;
    HighClearance_model_FuncInternalData0.prevTargetState = heightUp_e;

    /* Outport: '<Root>/mfaLeds' */
    HighClearance_model_Y.mfaLeds.upBtn = 1U;
    HighClearance_model_Y.mfaLeds.downBtn = 0U;
    break;

   case HighClearance_model_IN_paused:
    HighClearance_model_FuncInternalData0.is_active_dy =
      HighClearance_model_IN_paused;
    HighClearance_model_FuncInternalData0.was_active =
      HighClearance_model_IN_paused;
    HighClearance_model_FuncInternalData0.temporalCounter_i1_db = 0U;

    /* Outport: '<Root>/targetState' */
    /* Entry 'paused': '<S7>:293' */
    HighClearance_model_Y.targetState = heightUnknown_e;
    break;

   case HighClearance_model_IN_transitioning_n:
    HighClearance_model_FuncInternalData0.is_active_dy =
      HighClearance_model_IN_transitioning_n;
    HighClearance_model_FuncInternalData0.was_active =
      HighClearance_model_IN_transitioning_n;
    HighClearance_model_enter_internal_transitioning();
    break;

   case HighClearance_model_IN_wait_e:
    HighClearance_model_FuncInternalData0.is_active_dy =
      HighClearance_model_IN_wait_e;
    HighClearance_model_FuncInternalData0.was_active =
      HighClearance_model_IN_wait_e;

    /* Entry 'wait': '<S7>:1562' */
    HighClearance_model_clearWarnings();
    break;
  }
}

/* Function for Chart: '<S1>/TargetStateArbitration' */
static void HighClearance_model_states(const uint8_T *stopBtn_prev, const
  uint8_T *upBtn_prev, const uint8_T *downBtn_prev, const boolean_T
  *engRunning_prev)
{
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T guard3 = false;

  /* During 'states': '<S7>:1191' */
  if ((*engRunning_prev !=
       HighClearance_model_FuncInternalData0.engRunning_start) &&
      (!HighClearance_model_FuncInternalData0.engRunning_start))
  {
    /* Transition: '<S7>:1658' */
    /* Exit Internal 'states': '<S7>:1191' */
    /* Exit Internal 'active': '<S7>:969' */
    /* Exit Internal 'transitioning': '<S7>:285' */
    HighClearance_model_FuncInternalData0.is_transitioning =
      HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
    HighClearance_model_FuncInternalData0.is_active_dy =
      HighClearance_model_IN_NO_ACTIVE_CHILD_jn;

    /* Entry 'states': '<S7>:1191' */
    HighClearance_model_Y.okayToLower = HighClearance_model_okayToLower();
    if (HighClearance_model_Y.okayToLower)
    {
      HighClearance_model_Y.okayToLower = !HighClearance_model_disableLower();
    }

    HighClearance_model_Y.okayToRaise = HighClearance_model_okayToRaise();
    if (HighClearance_model_Y.okayToRaise)
    {
      HighClearance_model_Y.okayToRaise = !HighClearance_model_disableRiase();
    }

    /* Entry Internal 'states': '<S7>:1191' */
    /* Transition: '<S7>:1202' */
    HighClearance_model_FuncInternalData0.is_states_k =
      HighClearance_model_IN_waitForEngineRunning;

    /* Outport: '<Root>/targetState' */
    /* Entry 'waitForEngineRunning': '<S7>:697' */
    HighClearance_model_Y.targetState = heightUnknown_e;

    /* Outport: '<Root>/mfaLeds' */
    HighClearance_model_Y.mfaLeds.downBtn = 0U;
    HighClearance_model_Y.mfaLeds.upBtn = 0U;
  }
  else
  {
    HighClearance_model_Y.okayToLower = HighClearance_model_okayToLower();
    if (HighClearance_model_Y.okayToLower)
    {
      HighClearance_model_Y.okayToLower = !HighClearance_model_disableLower();
    }

    HighClearance_model_Y.okayToRaise = HighClearance_model_okayToRaise();
    if (HighClearance_model_Y.okayToRaise)
    {
      HighClearance_model_Y.okayToRaise = !HighClearance_model_disableRiase();
    }

    guard1 = false;
    guard2 = false;
    guard3 = false;
    switch (HighClearance_model_FuncInternalData0.is_states_k)
    {
     case HighClearance_model_IN_active:
      HighClearance_model_active(stopBtn_prev, upBtn_prev, downBtn_prev);
      break;

     case HighClearance_model_IN_doNothing:
      /* Outport: '<Root>/targetState' */
      HighClearance_model_Y.targetState = heightUnknown_e;

      /* During 'doNothing': '<S7>:72' */
      if ((*upBtn_prev != HighClearance_model_FuncInternalData0.upBtn_start) &&
          (HighClearance_model_FuncInternalData0.upBtn_start == 1))
      {
        /* Transition: '<S7>:93' */
        if (HighClearance_model_calOkay())
        {
          /* Transition: '<S7>:1187' */
          if (HighClearance_model_Y.machineState == heightUp_e)
          {
            /* Transition: '<S7>:1625' */
            HighClearance_model_FuncInternalData0.is_states_k =
              HighClearance_model_IN_active;

            /* Entry 'active': '<S7>:969' */
            HighClearance_model_clearWarnings();
            HighClearance_model_FuncInternalData0.is_active_dy =
              HighClearance_model_IN_holdUp;
            HighClearance_model_FuncInternalData0.was_active =
              HighClearance_model_IN_holdUp;

            /* Outport: '<Root>/targetState' */
            /* Entry 'holdUp': '<S7>:1062' */
            HighClearance_model_Y.targetState = heightUp_e;
            HighClearance_model_FuncInternalData0.prevTargetState = heightUp_e;

            /* Outport: '<Root>/mfaLeds' */
            HighClearance_model_Y.mfaLeds.upBtn = 1U;
            HighClearance_model_Y.mfaLeds.downBtn = 0U;
          }
          else if (HighClearance_model_okayToRaise() &&
                   (!HighClearance_model_disableRiase()))
          {
            /* Transition: '<S7>:1626' */
            /* Transition: '<S7>:1632' */
            HighClearance_model_FuncInternalData0.is_states_k =
              HighClearance_model_IN_active;

            /* Entry 'active': '<S7>:969' */
            HighClearance_model_clearWarnings();
            HighClearance_model_FuncInternalData0.is_active_dy =
              HighClearance_model_IN_transitioning_n;
            HighClearance_model_FuncInternalData0.was_active =
              HighClearance_model_IN_transitioning_n;
            HighClearance_model_FuncInternalData0.is_transitioning =
              HighClearance_model_IN_up_mf;
            HighClearance_model_FuncInternalData0.was_transitioning =
              HighClearance_model_IN_up_mf;

            /* Outport: '<Root>/targetState' */
            /* Entry 'up': '<S7>:88' */
            HighClearance_model_Y.targetState = heightMovingUp_e;
            HighClearance_model_FuncInternalData0.prevTargetState =
              heightMovingUp_e;

            /* Outport: '<Root>/mfaLeds' */
            HighClearance_model_Y.mfaLeds.upBtn = 2U;
            HighClearance_model_Y.mfaLeds.downBtn = 0U;
          }
          else
          {
            guard2 = true;
          }
        }
        else
        {
          guard2 = true;
        }
      }
      else
      {
        if ((*downBtn_prev !=
             HighClearance_model_FuncInternalData0.downBtn_start) &&
            (HighClearance_model_FuncInternalData0.downBtn_start == 1))
        {
          /* Transition: '<S7>:94' */
          if (HighClearance_model_calOkay())
          {
            /* Transition: '<S7>:1190' */
            if (HighClearance_model_Y.machineState == heightDown_e)
            {
              /* Transition: '<S7>:1621' */
              HighClearance_model_FuncInternalData0.is_states_k =
                HighClearance_model_IN_active;

              /* Entry 'active': '<S7>:969' */
              HighClearance_model_clearWarnings();
              HighClearance_model_FuncInternalData0.is_active_dy =
                HighClearance_model_IN_holdDown;
              HighClearance_model_FuncInternalData0.was_active =
                HighClearance_model_IN_holdDown;

              /* Outport: '<Root>/targetState' */
              /* Entry 'holdDown': '<S7>:1065' */
              HighClearance_model_Y.targetState = heightDown_e;
              HighClearance_model_FuncInternalData0.prevTargetState =
                heightDown_e;

              /* Outport: '<Root>/mfaLeds' */
              HighClearance_model_Y.mfaLeds.upBtn = 0U;
              HighClearance_model_Y.mfaLeds.downBtn = 1U;
            }
            else if (HighClearance_model_okayToLower() &&
                     (!HighClearance_model_disableLower()))
            {
              /* Transition: '<S7>:1623' */
              /* Transition: '<S7>:1631' */
              HighClearance_model_FuncInternalData0.is_states_k =
                HighClearance_model_IN_active;

              /* Entry 'active': '<S7>:969' */
              HighClearance_model_clearWarnings();
              HighClearance_model_FuncInternalData0.is_active_dy =
                HighClearance_model_IN_transitioning_n;
              HighClearance_model_FuncInternalData0.was_active =
                HighClearance_model_IN_transitioning_n;
              HighClearance_model_FuncInternalData0.is_transitioning =
                HighClearance_model_IN_down_h;
              HighClearance_model_FuncInternalData0.was_transitioning =
                HighClearance_model_IN_down_h;

              /* Outport: '<Root>/targetState' */
              /* Entry 'down': '<S7>:89' */
              HighClearance_model_Y.targetState = heightMovingDown_e;
              HighClearance_model_FuncInternalData0.prevTargetState =
                heightMovingDown_e;

              /* Outport: '<Root>/mfaLeds' */
              HighClearance_model_Y.mfaLeds.upBtn = 0U;
              HighClearance_model_Y.mfaLeds.downBtn = 2U;
            }
            else
            {
              guard3 = true;
            }
          }
          else
          {
            guard3 = true;
          }
        }
      }
      break;

     case HighClearance_model_IN_updateWarningsDown:
      /* During 'updateWarningsDown': '<S7>:690' */
      if (HighClearance_model_FuncInternalData0.temporalCounter_i1_db >= 2U)
      {
        /* Transition: '<S7>:703' */
        if (HighClearance_model_targetStateSelected())
        {
          /* Transition: '<S7>:704' */
          HighClearance_model_FuncInternalData0.is_states_k =
            HighClearance_model_IN_active;

          /* Entry 'active': '<S7>:969' */
          HighClearance_model_clearWarnings();
          HighClearance_model_enter_internal_active();
        }
        else
        {
          /* Transition: '<S7>:709' */
          HighClearance_model_FuncInternalData0.is_states_k =
            HighClearance_model_IN_doNothing;

          /* Outport: '<Root>/targetState' */
          /* Entry 'doNothing': '<S7>:72' */
          HighClearance_model_Y.targetState = heightUnknown_e;
          HighClearance_model_clearWarnings();

          /* Outport: '<Root>/mfaLeds' */
          HighClearance_model_Y.mfaLeds.downBtn = 0U;
          HighClearance_model_Y.mfaLeds.upBtn = 0U;
        }
      }
      break;

     case HighClearance_model_IN_updateWarningsUp:
      /* During 'updateWarningsUp': '<S7>:119' */
      if (HighClearance_model_FuncInternalData0.temporalCounter_i1_db >= 2U)
      {
        /* Transition: '<S7>:707' */
        if (HighClearance_model_targetStateSelected())
        {
          /* Transition: '<S7>:706' */
          HighClearance_model_FuncInternalData0.is_states_k =
            HighClearance_model_IN_active;

          /* Entry 'active': '<S7>:969' */
          HighClearance_model_clearWarnings();
          HighClearance_model_enter_internal_active();
        }
        else
        {
          /* Transition: '<S7>:708' */
          HighClearance_model_FuncInternalData0.is_states_k =
            HighClearance_model_IN_doNothing;

          /* Outport: '<Root>/targetState' */
          /* Entry 'doNothing': '<S7>:72' */
          HighClearance_model_Y.targetState = heightUnknown_e;
          HighClearance_model_clearWarnings();

          /* Outport: '<Root>/mfaLeds' */
          HighClearance_model_Y.mfaLeds.downBtn = 0U;
          HighClearance_model_Y.mfaLeds.upBtn = 0U;
        }
      }
      break;

     default:
      /* Outport: '<Root>/targetState' */
      HighClearance_model_Y.targetState = heightUnknown_e;

      /* During 'waitForEngineRunning': '<S7>:697' */
      if (HighClearance_model_U.engRunning)
      {
        /* Transition: '<S7>:698' */
        if (HighClearance_model_U.fieldModeActive)
        {
          /* Transition: '<S7>:1612' */
          if (HighClearance_model_calOkay())
          {
            /* Transition: '<S7>:1610' */
            if (HighClearance_model_Y.machineState == heightUp_e)
            {
              /* Transition: '<S7>:1568' */
              /* Transition: '<S7>:1570' */
              /* Transition: '<S7>:1571' */
              HighClearance_model_FuncInternalData0.is_states_k =
                HighClearance_model_IN_active;

              /* Entry 'active': '<S7>:969' */
              HighClearance_model_clearWarnings();
              HighClearance_model_FuncInternalData0.is_active_dy =
                HighClearance_model_IN_holdUp;
              HighClearance_model_FuncInternalData0.was_active =
                HighClearance_model_IN_holdUp;

              /* Outport: '<Root>/targetState' */
              /* Entry 'holdUp': '<S7>:1062' */
              HighClearance_model_Y.targetState = heightUp_e;
              HighClearance_model_FuncInternalData0.prevTargetState = heightUp_e;

              /* Outport: '<Root>/mfaLeds' */
              HighClearance_model_Y.mfaLeds.upBtn = 1U;
              HighClearance_model_Y.mfaLeds.downBtn = 0U;
            }
            else
            {
              /* Transition: '<S7>:1574' */
              if (HighClearance_model_Y.machineState == heightDown_e)
              {
                /* Transition: '<S7>:1573' */
                HighClearance_model_FuncInternalData0.is_states_k =
                  HighClearance_model_IN_active;

                /* Entry 'active': '<S7>:969' */
                HighClearance_model_clearWarnings();
                HighClearance_model_FuncInternalData0.is_active_dy =
                  HighClearance_model_IN_holdDown;
                HighClearance_model_FuncInternalData0.was_active =
                  HighClearance_model_IN_holdDown;

                /* Outport: '<Root>/targetState' */
                /* Entry 'holdDown': '<S7>:1065' */
                HighClearance_model_Y.targetState = heightDown_e;
                HighClearance_model_FuncInternalData0.prevTargetState =
                  heightDown_e;

                /* Outport: '<Root>/mfaLeds' */
                HighClearance_model_Y.mfaLeds.upBtn = 0U;
                HighClearance_model_Y.mfaLeds.downBtn = 1U;
              }
              else
              {
                /* Transition: '<S7>:1576' */
                /* Transition: '<S7>:1617' */
                guard1 = true;
              }
            }
          }
          else
          {
            /* Transition: '<S7>:1618' */
            /* Transition: '<S7>:1617' */
            guard1 = true;
          }
        }
        else
        {
          /* Transition: '<S7>:1615' */
          guard1 = true;
        }
      }
      break;
    }

    if (guard3)
    {
      /* Transition: '<S7>:691' */
      HighClearance_model_FuncInternalData0.is_states_k =
        HighClearance_model_IN_updateWarningsDown;
      HighClearance_model_FuncInternalData0.temporalCounter_i1_db = 0U;

      /* Entry 'updateWarningsDown': '<S7>:690' */
      HighClearance_model_downWarnings();
    }

    if (guard2)
    {
      /* Transition: '<S7>:689' */
      HighClearance_model_FuncInternalData0.is_states_k =
        HighClearance_model_IN_updateWarningsUp;
      HighClearance_model_FuncInternalData0.temporalCounter_i1_db = 0U;

      /* Entry 'updateWarningsUp': '<S7>:119' */
      HighClearance_model_upWarnings();
    }

    if (guard1)
    {
      /* Transition: '<S7>:1614' */
      /* Transition: '<S7>:1577' */
      HighClearance_model_FuncInternalData0.is_states_k =
        HighClearance_model_IN_doNothing;

      /* Entry 'doNothing': '<S7>:72' */
      HighClearance_model_clearWarnings();

      /* Outport: '<Root>/mfaLeds' */
      HighClearance_model_Y.mfaLeds.downBtn = 0U;
      HighClearance_model_Y.mfaLeds.upBtn = 0U;
    }
  }
}

/* Function for Chart: '<S6>/TargetPosition' */
static void HighClearance_model_enter_internal_positionStates(const real32_T
  *Switch_p, const real32_T *Switch_c, const real32_T *Switch_pf, const real32_T
  *Switch_al)
{
  real32_T postionTargets_tmp;

  /* Outport: '<Root>/targetState' incorporates:
   *  Outport: '<Root>/postionTargets'
   */
  /* Entry Internal 'positionStates': '<S19>:26' */
  /* Transition: '<S19>:21' */
  if ((HighClearance_model_Y.targetState == heightUp_e) ||
      (HighClearance_model_Y.targetState == heightMovingUp_e))
  {
    /* Transition: '<S19>:8' */
    HighClearance_model_FuncInternalData0.is_positionStates =
      HighClearance_model_IN_up_f;

    /* Entry 'up': '<S19>:3' */
    postionTargets_tmp = HighClearance_model_P.positionSensor_tblData[1] +
      HighClearance_model_P.baseClearance;
    HighClearance_model_Y.postionTargets.FrontLeft = postionTargets_tmp;
    HighClearance_model_Y.postionTargets.FrontRight = postionTargets_tmp;
    HighClearance_model_Y.postionTargets.RearLeft = postionTargets_tmp;
    HighClearance_model_Y.postionTargets.RearRight = postionTargets_tmp;
  }
  else if ((HighClearance_model_Y.targetState == heightDown_e) ||
           (HighClearance_model_Y.targetState == heightMovingDown_e))
  {
    /* Transition: '<S19>:22' */
    HighClearance_model_FuncInternalData0.is_positionStates =
      HighClearance_model_IN_down_h;

    /* Entry 'down': '<S19>:6' */
    postionTargets_tmp = HighClearance_model_P.positionSensor_tblData[0] +
      HighClearance_model_P.baseClearance;
    HighClearance_model_Y.postionTargets.FrontLeft = postionTargets_tmp;
    HighClearance_model_Y.postionTargets.FrontRight = postionTargets_tmp;
    HighClearance_model_Y.postionTargets.RearLeft = postionTargets_tmp;
    HighClearance_model_Y.postionTargets.RearRight = postionTargets_tmp;
  }
  else
  {
    /* Transition: '<S19>:24' */
    HighClearance_model_FuncInternalData0.is_positionStates =
      HighClearance_model_IN_stop_h;

    /* Entry 'stop': '<S19>:23' */
    HighClearance_model_Y.postionTargets.FrontLeft = *Switch_p;
    HighClearance_model_Y.postionTargets.FrontRight = *Switch_c;
    HighClearance_model_Y.postionTargets.RearLeft = *Switch_pf;
    HighClearance_model_Y.postionTargets.RearRight = *Switch_al;
  }

  /* End of Outport: '<Root>/targetState' */
}

/* Function for Chart: '<S1>/ladderExtendLogic' */
static boolean_T HighClearance_model_extendOkay(void)
{
  boolean_T out;

  /* Inport: '<Root>/selectedGear' incorporates:
   *  Outport: '<Root>/machineState'
   */
  /* Graphical Function 'extendOkay': '<S10>:14' */
  /* Transition: '<S10>:16' */
  if ((HighClearance_model_U.selectedGear == 251.0F) &&
      (HighClearance_model_Y.machineState == heightUp_e))
  {
    /* Transition: '<S10>:18' */
    /* Transition: '<S10>:20' */
    /* Transition: '<S10>:26' */
    out = true;
  }
  else
  {
    /* Transition: '<S10>:25' */
    /* Transition: '<S10>:24' */
    out = false;
  }

  /* End of Inport: '<Root>/selectedGear' */
  return out;
}

/* Model step function */
void HighClearance_model_step(void)
{
  real32_T rtb_uDLookupTable;
  real32_T rtb_uDLookupTable1;
  real32_T rtb_uDLookupTable2;
  real32_T rtb_uDLookupTable3;
  real32_T rtb_RearLeft_l;
  real32_T rtb_RearRight_p;
  boolean_T LogicalOperator;
  StateBus BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1;
  real32_T Switch_pf;
  real32_T Switch_a;
  real32_T Switch_j;
  real32_T Switch_m;
  real32_T Switch_retract_FrontRight;
  real32_T Switch_retract_RearLeft;
  real32_T Switch_retract_RearRight;
  uint16_T override_prev;
  uint8_T stopBtn_prev;
  uint8_T upBtn_prev;
  uint8_T downBtn_prev;
  real32_T Switch_al;
  real32_T Switch_i;
  real32_T Switch_f;

  /* Chart: '<S131>/manualOverrides' incorporates:
   *  Inport: '<Root>/manualOverride'
   */
  /* Gateway: Control/manualOverrides/manualOverrides */
  override_prev = HighClearance_model_FuncInternalData0.override_start;
  HighClearance_model_FuncInternalData0.override_start =
    HighClearance_model_U.manualOverride;

  /* During: Control/manualOverrides/manualOverrides */
  if (HighClearance_model_FuncInternalData0.is_active_c7_HighClearance_model ==
      0U)
  {
    /* Entry: Control/manualOverrides/manualOverrides */
    HighClearance_model_FuncInternalData0.is_active_c7_HighClearance_model = 1U;

    /* Entry Internal: Control/manualOverrides/manualOverrides */
    /* Transition: '<S201>:7' */
    HighClearance_model_FuncInternalData0.is_c7_HighClearance_model =
      HighClearance_model_IN_normal;

    /* Outport: '<Root>/manualOverrideEnable' */
    /* Entry 'normal': '<S201>:6' */
    HighClearance_model_Y.manualOverrideEnable = false;
  }
  else if (HighClearance_model_FuncInternalData0.is_c7_HighClearance_model ==
           HighClearance_model_IN_normal)
  {
    /* Outport: '<Root>/manualOverrideEnable' */
    HighClearance_model_Y.manualOverrideEnable = false;

    /* During 'normal': '<S201>:6' */
    if (HighClearance_model_U.manualOverride != 0)
    {
      /* Transition: '<S201>:9' */
      HighClearance_model_FuncInternalData0.is_c7_HighClearance_model =
        HighClearance_model_IN_overRided;

      /* Outport: '<Root>/manualOverrideEnable' */
      /* Entry 'overRided': '<S201>:8' */
      HighClearance_model_Y.manualOverrideEnable = true;
      HighClearance_model_setIO();
    }
  }
  else
  {
    /* Outport: '<Root>/manualOverrideEnable' */
    HighClearance_model_Y.manualOverrideEnable = true;

    /* During 'overRided': '<S201>:8' */
    if (HighClearance_model_U.manualOverride == 0)
    {
      /* Transition: '<S201>:10' */
      HighClearance_model_FuncInternalData0.is_c7_HighClearance_model =
        HighClearance_model_IN_normal;

      /* Outport: '<Root>/manualOverrideEnable' */
      /* Entry 'normal': '<S201>:6' */
      HighClearance_model_Y.manualOverrideEnable = false;
    }
    else
    {
      if (override_prev != HighClearance_model_FuncInternalData0.override_start)
      {
        /* Transition: '<S201>:195' */
        HighClearance_model_FuncInternalData0.is_c7_HighClearance_model =
          HighClearance_model_IN_overRided;

        /* Outport: '<Root>/manualOverrideEnable' */
        /* Entry 'overRided': '<S201>:8' */
        HighClearance_model_Y.manualOverrideEnable = true;
        HighClearance_model_setIO();
      }
    }
  }

  /* End of Chart: '<S131>/manualOverrides' */

  /* Chart: '<S211>/diagLatch' incorporates:
   *  Inport: '<Root>/cylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.cylCoilDiags.extend.FrontLeft,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch_j);

  /* Chart: '<S211>/diagLatch1' incorporates:
   *  Inport: '<Root>/cylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.cylCoilDiags.retract.FrontLeft,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_l);

  /* Chart: '<S211>/diagLatch2' incorporates:
   *  Inport: '<Root>/cylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.cylCoilDiags.extend.FrontRight,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch2_p);

  /* Chart: '<S211>/diagLatch3' incorporates:
   *  Inport: '<Root>/cylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.cylCoilDiags.retract.FrontRight,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch3_n);

  /* Chart: '<S211>/diagLatch4' incorporates:
   *  Inport: '<Root>/cylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.cylCoilDiags.extend.RearLeft,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch4_m);

  /* Chart: '<S211>/diagLatch5' incorporates:
   *  Inport: '<Root>/cylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.cylCoilDiags.retract.RearLeft,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch5_g);

  /* Chart: '<S211>/diagLatch6' incorporates:
   *  Inport: '<Root>/cylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.cylCoilDiags.extend.RearRight,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch6_g);

  /* Chart: '<S211>/diagLatch7' incorporates:
   *  Inport: '<Root>/cylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.cylCoilDiags.retract.RearRight,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch7_f);

  /* Logic: '<S21>/Logical Operator' incorporates:
   *  Constant: '<S100>/Constant'
   *  Constant: '<S101>/Constant'
   *  Constant: '<S102>/Constant'
   *  Constant: '<S94>/Constant'
   *  Constant: '<S95>/Constant'
   *  Constant: '<S96>/Constant'
   *  Constant: '<S97>/Constant'
   *  Constant: '<S98>/Constant'
   *  Constant: '<S99>/Constant'
   *  Inport: '<Root>/ccoEnableDiag'
   *  RelationalOperator: '<S100>/Compare'
   *  RelationalOperator: '<S101>/Compare'
   *  RelationalOperator: '<S102>/Compare'
   *  RelationalOperator: '<S94>/Compare'
   *  RelationalOperator: '<S95>/Compare'
   *  RelationalOperator: '<S96>/Compare'
   *  RelationalOperator: '<S97>/Compare'
   *  RelationalOperator: '<S98>/Compare'
   *  RelationalOperator: '<S99>/Compare'
   */
  LogicalOperator =
    ((HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch_j.diagOut
      != HighClearance_model_P.IOD_OK) ||
     (HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_l.diagOut
      != HighClearance_model_P.IOD_OK) ||
     (HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch2_p.diagOut
      != HighClearance_model_P.IOD_OK) ||
     (HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch3_n.diagOut
      != HighClearance_model_P.IOD_OK) ||
     (HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch4_m.diagOut
      != HighClearance_model_P.IOD_OK) ||
     (HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch5_g.diagOut
      != HighClearance_model_P.IOD_OK) ||
     (HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch6_g.diagOut
      != HighClearance_model_P.IOD_OK) ||
     (HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch7_f.diagOut
      != HighClearance_model_P.IOD_OK) || (HighClearance_model_U.ccoEnableDiag
      != HighClearance_model_P.IOD_OK));

  /* Fcn: '<S111>/Alpha' incorporates:
   *  Constant: '<S107>/cutoffFreq'
   *  Fcn: '<S112>/Alpha'
   *  Fcn: '<S113>/Alpha'
   *  Fcn: '<S114>/Alpha'
   *  Fcn: '<S240>/Alpha'
   *  Fcn: '<S241>/Alpha'
   *  Fcn: '<S242>/Alpha'
   *  Fcn: '<S243>/Alpha'
   *  Fcn: '<S60>/Alpha'
   *  Fcn: '<S61>/Alpha'
   *  Fcn: '<S62>/Alpha'
   *  Fcn: '<S63>/Alpha'
   */
  Switch_m = 0.0628318563F * HighClearance_model_P.sensorCutOffHz /
    (0.0628318563F * HighClearance_model_P.sensorCutOffHz + 1.0F);

  /* Delay: '<S111>/Delay' incorporates:
   *  Inport: '<Root>/heightPosSensors_mA'
   */
  if (HighClearance_model_FuncInternalData0.icLoad != 0)
  {
    HighClearance_model_FuncInternalData0.Delay_DSTATE =
      HighClearance_model_U.heightPosSensors_mA.FrontLeft;
  }

  /* Sum: '<S111>/Sum' incorporates:
   *  Constant: '<S111>/Constant'
   *  Delay: '<S111>/Delay'
   *  Fcn: '<S111>/Alpha'
   *  Inport: '<Root>/heightPosSensors_mA'
   *  Product: '<S111>/Product1'
   *  Product: '<S111>/product'
   *  Sum: '<S111>/Sum1'
   */
  HighClearance_model_FuncInternalData0.Delay_DSTATE =
    HighClearance_model_U.heightPosSensors_mA.FrontLeft * Switch_m + (1.0F -
    Switch_m) * HighClearance_model_FuncInternalData0.Delay_DSTATE;

  /* Switch: '<S107>/Switch' incorporates:
   *  Constant: '<S107>/useSensorFilter'
   *  Inport: '<Root>/heightPosSensors_mA'
   */
  if (HighClearance_model_P.useSensorFilter)
  {
    Switch_a = HighClearance_model_FuncInternalData0.Delay_DSTATE;
  }
  else
  {
    Switch_a = HighClearance_model_U.heightPosSensors_mA.FrontLeft;
  }

  /* End of Switch: '<S107>/Switch' */

  /* Delay: '<S112>/Delay' incorporates:
   *  Inport: '<Root>/heightPosSensors_mA'
   */
  if (HighClearance_model_FuncInternalData0.icLoad_b != 0)
  {
    HighClearance_model_FuncInternalData0.Delay_DSTATE_j =
      HighClearance_model_U.heightPosSensors_mA.FrontRight;
  }

  /* Sum: '<S112>/Sum' incorporates:
   *  Constant: '<S112>/Constant'
   *  Delay: '<S112>/Delay'
   *  Inport: '<Root>/heightPosSensors_mA'
   *  Product: '<S112>/Product1'
   *  Product: '<S112>/product'
   *  Sum: '<S112>/Sum1'
   */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_j =
    HighClearance_model_U.heightPosSensors_mA.FrontRight * Switch_m + (1.0F -
    Switch_m) * HighClearance_model_FuncInternalData0.Delay_DSTATE_j;

  /* Switch: '<S108>/Switch' incorporates:
   *  Constant: '<S108>/useSensorFilter'
   *  Inport: '<Root>/heightPosSensors_mA'
   */
  if (HighClearance_model_P.useSensorFilter)
  {
    Switch_j = HighClearance_model_FuncInternalData0.Delay_DSTATE_j;
  }
  else
  {
    Switch_j = HighClearance_model_U.heightPosSensors_mA.FrontRight;
  }

  /* End of Switch: '<S108>/Switch' */

  /* Delay: '<S113>/Delay' incorporates:
   *  Inport: '<Root>/heightPosSensors_mA'
   */
  if (HighClearance_model_FuncInternalData0.icLoad_e != 0)
  {
    HighClearance_model_FuncInternalData0.Delay_DSTATE_m =
      HighClearance_model_U.heightPosSensors_mA.RearLeft;
  }

  /* Sum: '<S113>/Sum' incorporates:
   *  Constant: '<S113>/Constant'
   *  Delay: '<S113>/Delay'
   *  Inport: '<Root>/heightPosSensors_mA'
   *  Product: '<S113>/Product1'
   *  Product: '<S113>/product'
   *  Sum: '<S113>/Sum1'
   */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_m =
    HighClearance_model_U.heightPosSensors_mA.RearLeft * Switch_m + (1.0F -
    Switch_m) * HighClearance_model_FuncInternalData0.Delay_DSTATE_m;

  /* Switch: '<S109>/Switch' incorporates:
   *  Constant: '<S109>/useSensorFilter'
   *  Inport: '<Root>/heightPosSensors_mA'
   */
  if (HighClearance_model_P.useSensorFilter)
  {
    Switch_i = HighClearance_model_FuncInternalData0.Delay_DSTATE_m;
  }
  else
  {
    Switch_i = HighClearance_model_U.heightPosSensors_mA.RearLeft;
  }

  /* End of Switch: '<S109>/Switch' */

  /* Delay: '<S114>/Delay' incorporates:
   *  Inport: '<Root>/heightPosSensors_mA'
   */
  if (HighClearance_model_FuncInternalData0.icLoad_k != 0)
  {
    HighClearance_model_FuncInternalData0.Delay_DSTATE_b =
      HighClearance_model_U.heightPosSensors_mA.RearRight;
  }

  /* Sum: '<S114>/Sum' incorporates:
   *  Constant: '<S114>/Constant'
   *  Delay: '<S114>/Delay'
   *  Inport: '<Root>/heightPosSensors_mA'
   *  Product: '<S114>/Product1'
   *  Product: '<S114>/product'
   *  Sum: '<S114>/Sum1'
   */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_b =
    HighClearance_model_U.heightPosSensors_mA.RearRight * Switch_m + (1.0F -
    Switch_m) * HighClearance_model_FuncInternalData0.Delay_DSTATE_b;

  /* Switch: '<S110>/Switch' incorporates:
   *  Constant: '<S110>/useSensorFilter'
   *  Inport: '<Root>/heightPosSensors_mA'
   */
  if (HighClearance_model_P.useSensorFilter)
  {
    Switch_f = HighClearance_model_FuncInternalData0.Delay_DSTATE_b;
  }
  else
  {
    Switch_f = HighClearance_model_U.heightPosSensors_mA.RearRight;
  }

  /* End of Switch: '<S110>/Switch' */

  /* Chart: '<S23>/calibrationLogic' incorporates:
   *  Inport: '<Root>/calCmd'
   *  Inport: '<Root>/engRunning'
   *  UnitDelay: '<Root>/Unit Delay'
   *  UnitDelay: '<Root>/Unit Delay1'
   */
  if (HighClearance_model_FuncInternalData0.temporalCounter_i1_d < 8191U)
  {
    HighClearance_model_FuncInternalData0.temporalCounter_i1_d++;
  }

  if (HighClearance_model_FuncInternalData0.temporalCounter_i2 < 8388607U)
  {
    HighClearance_model_FuncInternalData0.temporalCounter_i2++;
  }

  /* Gateway: Calibration/stateLogic/calibrationLogic */
  override_prev = HighClearance_model_FuncInternalData0.calCmd_start;
  HighClearance_model_FuncInternalData0.calCmd_start =
    HighClearance_model_U.calCmd;

  /* During: Calibration/stateLogic/calibrationLogic */
  if (HighClearance_model_FuncInternalData0.is_active_c2_HighClearance_model ==
      0U)
  {
    /* Entry: Calibration/stateLogic/calibrationLogic */
    HighClearance_model_FuncInternalData0.is_active_c2_HighClearance_model = 1U;

    /* Entry Internal: Calibration/stateLogic/calibrationLogic */
    /* Transition: '<S115>:23' */
    HighClearance_model_FuncInternalData0.is_c2_HighClearance_model =
      HighClearance_model_IN_inactive;

    /* Entry 'inactive': '<S115>:22' */
    HighClearance_model_FuncInternalData0.calActive = false;

    /* Outport: '<Root>/calOverride' */
    HighClearance_model_Y.calOverride = false;
    HighClearance_model_heightStop();
    HighClearance_model_clearCalValues();

    /* Outport: '<Root>/calState' */
    HighClearance_model_Y.calState = HighClearance_model_checkCalValues();
    HighClearance_model_FuncInternalData0.calOkay =
      HighClearance_model_checkCalOkay();
  }
  else
  {
    switch (HighClearance_model_FuncInternalData0.is_c2_HighClearance_model)
    {
     case HighClearance_model_IN_UpdateValues:
      /* During 'UpdateValues': '<S115>:844' */
      if (HighClearance_model_FuncInternalData0.temporalCounter_i1_d >= 2U)
      {
        /* Transition: '<S115>:845' */
        HighClearance_model_FuncInternalData0.is_c2_HighClearance_model =
          HighClearance_model_IN_inactive;

        /* Entry 'inactive': '<S115>:22' */
        HighClearance_model_FuncInternalData0.calActive = false;

        /* Outport: '<Root>/calOverride' */
        HighClearance_model_Y.calOverride = false;
        HighClearance_model_heightStop();
        HighClearance_model_clearCalValues();

        /* Outport: '<Root>/calState' */
        HighClearance_model_Y.calState = HighClearance_model_checkCalValues();
        HighClearance_model_FuncInternalData0.calOkay =
          HighClearance_model_checkCalOkay();
      }
      break;

     case HighClearance_model_IN_calCommanded:
      /* During 'calCommanded': '<S115>:121' */
      if (HighClearance_model_U.calCmd == calABORT_e)
      {
        /* Transition: '<S115>:123' */
        /* Exit Internal 'calCommanded': '<S115>:121' */
        if (HighClearance_model_FuncInternalData0.is_calCommanded ==
            HighClearance_model_IN_active)
        {
          /* Exit Internal 'active': '<S115>:24' */
          switch (HighClearance_model_FuncInternalData0.is_active)
          {
           case HighClearance_model_IN_step1:
            /* Exit Internal 'step1': '<S115>:124' */
            if (HighClearance_model_FuncInternalData0.is_step1 ==
                HighClearance_model_IN_paused_a)
            {
              /* Exit 'paused': '<S115>:513' */
              HighClearance_model_FuncInternalData0.is_step1 =
                HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            }
            else
            {
              /* Exit Internal 'active': '<S115>:511' */
              HighClearance_model_FuncInternalData0.is_active_c =
                HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
              HighClearance_model_FuncInternalData0.is_step1 =
                HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            }

            HighClearance_model_FuncInternalData0.is_active =
              HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            break;

           case HighClearance_model_IN_step2:
            /* Exit Internal 'step2': '<S115>:128' */
            if (HighClearance_model_FuncInternalData0.is_step2 ==
                HighClearance_model_IN_paused_a)
            {
              /* Exit 'paused': '<S115>:517' */
              HighClearance_model_FuncInternalData0.is_step2 =
                HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            }
            else
            {
              HighClearance_model_FuncInternalData0.is_step2 =
                HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            }

            HighClearance_model_FuncInternalData0.is_active =
              HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            break;

           case HighClearance_model_IN_step3:
            /* Exit Internal 'step3': '<S115>:416' */
            if (HighClearance_model_FuncInternalData0.is_step3 ==
                HighClearance_model_IN_paused_a)
            {
              /* Exit 'paused': '<S115>:529' */
              HighClearance_model_FuncInternalData0.is_step3 =
                HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            }
            else
            {
              /* Exit Internal 'active': '<S115>:531' */
              HighClearance_model_FuncInternalData0.is_active_d =
                HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
              HighClearance_model_FuncInternalData0.is_step3 =
                HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            }

            HighClearance_model_FuncInternalData0.is_active =
              HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            break;

           case HighClearance_model_IN_step4:
            /* Exit Internal 'step4': '<S115>:133' */
            if (HighClearance_model_FuncInternalData0.is_step4 ==
                HighClearance_model_IN_paused_a)
            {
              /* Exit 'paused': '<S115>:524' */
              HighClearance_model_FuncInternalData0.is_step4 =
                HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            }
            else
            {
              HighClearance_model_FuncInternalData0.is_step4 =
                HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            }

            HighClearance_model_FuncInternalData0.is_active =
              HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            break;

           default:
            /* Exit Internal 'error': '<S115>:533' */
            HighClearance_model_FuncInternalData0.is_active =
              HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
            break;
          }

          HighClearance_model_FuncInternalData0.is_calCommanded =
            HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
        }
        else
        {
          HighClearance_model_FuncInternalData0.is_calCommanded =
            HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
        }

        HighClearance_model_FuncInternalData0.is_c2_HighClearance_model =
          HighClearance_model_IN_inactive;

        /* Entry 'inactive': '<S115>:22' */
        HighClearance_model_FuncInternalData0.calActive = false;

        /* Outport: '<Root>/calOverride' */
        HighClearance_model_Y.calOverride = false;
        HighClearance_model_heightStop();
        HighClearance_model_clearCalValues();

        /* Outport: '<Root>/calState' */
        HighClearance_model_Y.calState = HighClearance_model_checkCalValues();
        HighClearance_model_FuncInternalData0.calOkay =
          HighClearance_model_checkCalOkay();
      }
      else if (HighClearance_model_FuncInternalData0.is_calCommanded ==
               HighClearance_model_IN_active)
      {
        HighClearance_model_active_c(&LogicalOperator, &Switch_a, &Switch_j,
          &Switch_i, &Switch_f);
      }
      else
      {
        /* During 'startConditionsFailed': '<S115>:91' */
      }
      break;

     default:
      /* During 'inactive': '<S115>:22' */
      if ((override_prev != HighClearance_model_FuncInternalData0.calCmd_start) &&
          (HighClearance_model_FuncInternalData0.calCmd_start == calSTART_e))
      {
        /* Transition: '<S115>:25' */
        if (HighClearance_model_FuncInternalData0.UnitDelay1_DSTATE &&
            HighClearance_model_FuncInternalData0.UnitDelay_DSTATE &&
            HighClearance_model_sensorsOkay() && ((!LogicalOperator) &&
             HighClearance_model_U.engRunning))
        {
          /* Transition: '<S115>:99' */
          /* Transition: '<S115>:352' */
          /* Transition: '<S115>:843' */
          /* Transition: '<S115>:582' */
          /* Transition: '<S115>:854' */
          HighClearance_model_FuncInternalData0.is_c2_HighClearance_model =
            HighClearance_model_IN_calCommanded;
          HighClearance_model_FuncInternalData0.is_calCommanded =
            HighClearance_model_IN_active;

          /* Entry 'active': '<S115>:24' */
          HighClearance_model_FuncInternalData0.calActive = true;

          /* Outport: '<Root>/calOverride' */
          HighClearance_model_Y.calOverride = true;
          HighClearance_model_FuncInternalData0.calOkay = false;

          /* Entry Internal 'active': '<S115>:24' */
          /* Transition: '<S115>:130' */
          HighClearance_model_FuncInternalData0.is_active =
            HighClearance_model_IN_step1;
          HighClearance_model_FuncInternalData0.temporalCounter_i2 = 0U;

          /* Outport: '<Root>/calState' */
          /* Entry 'step1': '<S115>:124' */
          HighClearance_model_Y.calState = calSTEP1_e;

          /* Entry Internal 'step1': '<S115>:124' */
          /* Transition: '<S115>:512' */
          HighClearance_model_FuncInternalData0.is_step1 =
            HighClearance_model_IN_active;

          /* Entry 'active': '<S115>:511' */
          HighClearance_model_heightDown();

          /* Entry Internal 'active': '<S115>:511' */
          /* Transition: '<S115>:409' */
          HighClearance_model_FuncInternalData0.is_active_c =
            HighClearance_model_IN_moving_j;
        }
        else
        {
          /* Transition: '<S115>:112' */
          /* Transition: '<S115>:113' */
          HighClearance_model_FuncInternalData0.is_c2_HighClearance_model =
            HighClearance_model_IN_calCommanded;
          HighClearance_model_FuncInternalData0.is_calCommanded =
            HighClearance_model_IN_startConditionsFailed;

          /* Outport: '<Root>/calState' */
          /* Entry 'startConditionsFailed': '<S115>:91' */
          HighClearance_model_Y.calState = calERROR0_e;
        }
      }
      else
      {
        /* Outport: '<Root>/calState' */
        HighClearance_model_Y.calState = HighClearance_model_checkCalValues();
        HighClearance_model_FuncInternalData0.calOkay =
          HighClearance_model_checkCalOkay();
      }
      break;
    }
  }

  /* End of Chart: '<S23>/calibrationLogic' */

  /* Switch generated from: '<S212>/Switch' incorporates:
   *  Inport: '<Root>/heightPosSensors_mA'
   *  Lookup_n-D: '<S229>/1-D Lookup Table'
   *  Lookup_n-D: '<S232>/1-D Lookup Table'
   */
  if (HighClearance_model_FuncInternalData0.calOkay)
  {
    Switch_a = look1_iflf_binlca
      (HighClearance_model_U.heightPosSensors_mA.FrontLeft,
       HighClearance_model_P.positionSensorFL_BrkPnts,
       HighClearance_model_P.positionSensor_tblData, 1U);
  }
  else
  {
    Switch_a = look1_iflf_binlca
      (HighClearance_model_U.heightPosSensors_mA.FrontLeft,
       HighClearance_model_P.defaultPositionSensor_BrkPnts,
       HighClearance_model_P.positionSensor_tblData, 1U);
  }

  /* Logic: '<S225>/Logical Operator' incorporates:
   *  Inport: '<Root>/engRunning'
   */
  LogicalOperator = (HighClearance_model_U.engRunning &&
                     HighClearance_model_FuncInternalData0.calOkay);

  /* Chart: '<S246>/plausiCheck' incorporates:
   *  Delay: '<S246>/Delay'
   */
  HighClearance_model_plausiCheck(Switch_a,
    HighClearance_model_FuncInternalData0.Delay_DSTATE_f[0], LogicalOperator,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_c);

  /* Chart: '<S260>/diagLatch1' incorporates:
   *  Inport: '<Root>/heightPosSensors_diag'
   */
  HighClearance_model_diagLatch1
    (HighClearance_model_U.heightPosSensors_diag.FrontLeft,
     HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_c.plausiErr,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_cx);

  /* Delay: '<S240>/Delay' */
  if (HighClearance_model_FuncInternalData0.icLoad_m != 0)
  {
    HighClearance_model_FuncInternalData0.Delay_DSTATE_h =
      HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_c.positionOut;
  }

  /* Sum: '<S240>/Sum' incorporates:
   *  Constant: '<S240>/Constant'
   *  Delay: '<S240>/Delay'
   *  Product: '<S240>/Product1'
   *  Product: '<S240>/product'
   *  Sum: '<S240>/Sum1'
   */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_h =
    HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_c.positionOut
    * Switch_m + (1.0F - Switch_m) *
    HighClearance_model_FuncInternalData0.Delay_DSTATE_h;

  /* Switch: '<S260>/Switch' incorporates:
   *  Constant: '<S236>/useSensorFilter'
   *  Constant: '<S260>/Constant'
   *  Constant: '<S260>/Constant1'
   *  Constant: '<S273>/Constant'
   *  RelationalOperator: '<S273>/Compare'
   *  Sum: '<S260>/Add'
   *  Switch: '<S236>/Switch'
   */
  if (HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_cx.diagOut
      != HighClearance_model_P.IOD_OK)
  {
    Switch_j = 0.0F;
  }
  else
  {
    if (HighClearance_model_P.useSensorFilter)
    {
      /* Switch: '<S236>/Switch' */
      rtb_uDLookupTable = HighClearance_model_FuncInternalData0.Delay_DSTATE_h;
    }
    else
    {
      /* Switch: '<S236>/Switch' */
      rtb_uDLookupTable =
        HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_c.positionOut;
    }

    Switch_j = rtb_uDLookupTable + HighClearance_model_P.baseClearance;
  }

  /* End of Switch: '<S260>/Switch' */

  /* Chart: '<S5>/legState_FrontLeft' incorporates:
   *  Inport: '<Root>/driveCalActive'
   *  Inport: '<Root>/fieldModeActive'
   */
  HighClearance_model_legState_FrontLeft(Switch_j,
    HighClearance_model_U.fieldModeActive, HighClearance_model_U.driveCalActive,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_legState_FrontLeft);

  /* Switch generated from: '<S212>/Switch' incorporates:
   *  Inport: '<Root>/heightPosSensors_mA'
   *  Lookup_n-D: '<S229>/1-D Lookup Table1'
   *  Lookup_n-D: '<S232>/1-D Lookup Table1'
   */
  if (HighClearance_model_FuncInternalData0.calOkay)
  {
    Switch_i = look1_iflf_binlca
      (HighClearance_model_U.heightPosSensors_mA.FrontRight,
       HighClearance_model_P.positionSensorFR_BrkPnts,
       HighClearance_model_P.positionSensor_tblData, 1U);
  }
  else
  {
    Switch_i = look1_iflf_binlca
      (HighClearance_model_U.heightPosSensors_mA.FrontRight,
       HighClearance_model_P.defaultPositionSensor_BrkPnts,
       HighClearance_model_P.positionSensor_tblData, 1U);
  }

  /* Chart: '<S247>/plausiCheck' incorporates:
   *  Delay: '<S247>/Delay'
   */
  HighClearance_model_plausiCheck(Switch_i,
    HighClearance_model_FuncInternalData0.Delay_DSTATE_h4[0], LogicalOperator,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_p);

  /* Chart: '<S261>/diagLatch1' incorporates:
   *  Inport: '<Root>/heightPosSensors_diag'
   */
  HighClearance_model_diagLatch1
    (HighClearance_model_U.heightPosSensors_diag.FrontRight,
     HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_p.plausiErr,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_k);

  /* Delay: '<S241>/Delay' */
  if (HighClearance_model_FuncInternalData0.icLoad_j != 0)
  {
    HighClearance_model_FuncInternalData0.Delay_DSTATE_d =
      HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_p.positionOut;
  }

  /* Sum: '<S241>/Sum' incorporates:
   *  Constant: '<S241>/Constant'
   *  Delay: '<S241>/Delay'
   *  Product: '<S241>/Product1'
   *  Product: '<S241>/product'
   *  Sum: '<S241>/Sum1'
   */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_d =
    HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_p.positionOut
    * Switch_m + (1.0F - Switch_m) *
    HighClearance_model_FuncInternalData0.Delay_DSTATE_d;

  /* Switch: '<S261>/Switch' incorporates:
   *  Constant: '<S237>/useSensorFilter'
   *  Constant: '<S261>/Constant'
   *  Constant: '<S261>/Constant1'
   *  Constant: '<S275>/Constant'
   *  RelationalOperator: '<S275>/Compare'
   *  Sum: '<S261>/Add'
   *  Switch: '<S237>/Switch'
   */
  if (HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_k.diagOut
      != HighClearance_model_P.IOD_OK)
  {
    Switch_f = 0.0F;
  }
  else
  {
    if (HighClearance_model_P.useSensorFilter)
    {
      /* Switch: '<S237>/Switch' */
      rtb_uDLookupTable = HighClearance_model_FuncInternalData0.Delay_DSTATE_d;
    }
    else
    {
      /* Switch: '<S237>/Switch' */
      rtb_uDLookupTable =
        HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_p.positionOut;
    }

    Switch_f = rtb_uDLookupTable + HighClearance_model_P.baseClearance;
  }

  /* End of Switch: '<S261>/Switch' */

  /* Chart: '<S5>/legState_FrontRight' incorporates:
   *  Inport: '<Root>/driveCalActive'
   *  Inport: '<Root>/fieldModeActive'
   */
  HighClearance_model_legState_FrontLeft(Switch_f,
    HighClearance_model_U.fieldModeActive, HighClearance_model_U.driveCalActive,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_legState_FrontRight);

  /* Switch generated from: '<S212>/Switch' incorporates:
   *  Inport: '<Root>/heightPosSensors_mA'
   *  Lookup_n-D: '<S229>/1-D Lookup Table2'
   *  Lookup_n-D: '<S232>/1-D Lookup Table2'
   */
  if (HighClearance_model_FuncInternalData0.calOkay)
  {
    rtb_RearLeft_l = look1_iflf_binlca
      (HighClearance_model_U.heightPosSensors_mA.RearLeft,
       HighClearance_model_P.positionSensorRL_BrkPnts,
       HighClearance_model_P.positionSensor_tblData, 1U);
  }
  else
  {
    rtb_RearLeft_l = look1_iflf_binlca
      (HighClearance_model_U.heightPosSensors_mA.RearLeft,
       HighClearance_model_P.defaultPositionSensor_BrkPnts,
       HighClearance_model_P.positionSensor_tblData, 1U);
  }

  /* Chart: '<S248>/plausiCheck' incorporates:
   *  Delay: '<S248>/Delay'
   */
  HighClearance_model_plausiCheck(rtb_RearLeft_l,
    HighClearance_model_FuncInternalData0.Delay_DSTATE_j0[0], LogicalOperator,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_b);

  /* Chart: '<S262>/diagLatch1' incorporates:
   *  Inport: '<Root>/heightPosSensors_diag'
   */
  HighClearance_model_diagLatch1
    (HighClearance_model_U.heightPosSensors_diag.RearLeft,
     HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_b.plausiErr,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_c);

  /* Delay: '<S242>/Delay' */
  if (HighClearance_model_FuncInternalData0.icLoad_mr != 0)
  {
    HighClearance_model_FuncInternalData0.Delay_DSTATE_k =
      HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_b.positionOut;
  }

  /* Sum: '<S242>/Sum' incorporates:
   *  Constant: '<S242>/Constant'
   *  Delay: '<S242>/Delay'
   *  Product: '<S242>/Product1'
   *  Product: '<S242>/product'
   *  Sum: '<S242>/Sum1'
   */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_k =
    HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_b.positionOut
    * Switch_m + (1.0F - Switch_m) *
    HighClearance_model_FuncInternalData0.Delay_DSTATE_k;

  /* Switch: '<S262>/Switch' incorporates:
   *  Constant: '<S238>/useSensorFilter'
   *  Constant: '<S262>/Constant'
   *  Constant: '<S262>/Constant1'
   *  Constant: '<S277>/Constant'
   *  RelationalOperator: '<S277>/Compare'
   *  Sum: '<S262>/Add'
   *  Switch: '<S238>/Switch'
   */
  if (HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_c.diagOut
      != HighClearance_model_P.IOD_OK)
  {
    Switch_pf = 0.0F;
  }
  else
  {
    if (HighClearance_model_P.useSensorFilter)
    {
      /* Switch: '<S238>/Switch' */
      rtb_uDLookupTable = HighClearance_model_FuncInternalData0.Delay_DSTATE_k;
    }
    else
    {
      /* Switch: '<S238>/Switch' */
      rtb_uDLookupTable =
        HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_b.positionOut;
    }

    Switch_pf = rtb_uDLookupTable + HighClearance_model_P.baseClearance;
  }

  /* End of Switch: '<S262>/Switch' */

  /* Chart: '<S5>/legState_RearLeft' incorporates:
   *  Inport: '<Root>/driveCalActive'
   *  Inport: '<Root>/fieldModeActive'
   */
  HighClearance_model_legState_FrontLeft(Switch_pf,
    HighClearance_model_U.fieldModeActive, HighClearance_model_U.driveCalActive,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_legState_RearLeft);

  /* Switch generated from: '<S212>/Switch' incorporates:
   *  Inport: '<Root>/heightPosSensors_mA'
   *  Lookup_n-D: '<S229>/1-D Lookup Table3'
   *  Lookup_n-D: '<S232>/1-D Lookup Table3'
   */
  if (HighClearance_model_FuncInternalData0.calOkay)
  {
    rtb_RearRight_p = look1_iflf_binlca
      (HighClearance_model_U.heightPosSensors_mA.RearRight,
       HighClearance_model_P.positionSensorRR_BrkPnts,
       HighClearance_model_P.positionSensor_tblData, 1U);
  }
  else
  {
    rtb_RearRight_p = look1_iflf_binlca
      (HighClearance_model_U.heightPosSensors_mA.RearRight,
       HighClearance_model_P.defaultPositionSensor_BrkPnts,
       HighClearance_model_P.positionSensor_tblData, 1U);
  }

  /* Chart: '<S249>/plausiCheck' incorporates:
   *  Delay: '<S249>/Delay'
   */
  HighClearance_model_plausiCheck(rtb_RearRight_p,
    HighClearance_model_FuncInternalData0.Delay_DSTATE_e[0], LogicalOperator,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck);

  /* Chart: '<S263>/diagLatch1' incorporates:
   *  Inport: '<Root>/heightPosSensors_diag'
   */
  HighClearance_model_diagLatch1
    (HighClearance_model_U.heightPosSensors_diag.RearRight,
     HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck.plausiErr,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_m);

  /* Delay: '<S243>/Delay' */
  if (HighClearance_model_FuncInternalData0.icLoad_mg != 0)
  {
    HighClearance_model_FuncInternalData0.Delay_DSTATE_mn =
      HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck.positionOut;
  }

  /* Sum: '<S243>/Sum' incorporates:
   *  Constant: '<S243>/Constant'
   *  Delay: '<S243>/Delay'
   *  Product: '<S243>/Product1'
   *  Product: '<S243>/product'
   *  Sum: '<S243>/Sum1'
   */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_mn =
    HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck.positionOut
    * Switch_m + (1.0F - Switch_m) *
    HighClearance_model_FuncInternalData0.Delay_DSTATE_mn;

  /* Switch: '<S263>/Switch' incorporates:
   *  Constant: '<S239>/useSensorFilter'
   *  Constant: '<S263>/Constant'
   *  Constant: '<S263>/Constant1'
   *  Constant: '<S279>/Constant'
   *  RelationalOperator: '<S279>/Compare'
   *  Sum: '<S263>/Add'
   *  Switch: '<S239>/Switch'
   */
  if (HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_m.diagOut
      != HighClearance_model_P.IOD_OK)
  {
    Switch_al = 0.0F;
  }
  else
  {
    if (HighClearance_model_P.useSensorFilter)
    {
      /* Switch: '<S239>/Switch' */
      rtb_uDLookupTable = HighClearance_model_FuncInternalData0.Delay_DSTATE_mn;
    }
    else
    {
      /* Switch: '<S239>/Switch' */
      rtb_uDLookupTable =
        HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck.positionOut;
    }

    Switch_al = rtb_uDLookupTable + HighClearance_model_P.baseClearance;
  }

  /* End of Switch: '<S263>/Switch' */

  /* Chart: '<S5>/legState_RearRight' incorporates:
   *  Inport: '<Root>/driveCalActive'
   *  Inport: '<Root>/fieldModeActive'
   */
  HighClearance_model_legState_FrontLeft(Switch_al,
    HighClearance_model_U.fieldModeActive, HighClearance_model_U.driveCalActive,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_legState_RearRight);

  /* BusCreator generated from: '<S5>/actualMachineState' */
  BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1.FrontLeft
    =
    HighClearance_model_FuncInternalData0.FuncInternalData0_legState_FrontLeft.legState;
  BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1.FrontRight
    =
    HighClearance_model_FuncInternalData0.FuncInternalData0_legState_FrontRight.legState;
  BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1.RearLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_legState_RearLeft.legState;
  BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1.RearRight
    =
    HighClearance_model_FuncInternalData0.FuncInternalData0_legState_RearRight.legState;

  /* Chart: '<S5>/actualMachineState' */
  if (HighClearance_model_FuncInternalData0.temporalCounter_i1 < MAX_uint32_T)
  {
    HighClearance_model_FuncInternalData0.temporalCounter_i1++;
  }

  /* Gateway: Arbitration/ActualStateArbitration/actualMachineState */
  /* During: Arbitration/ActualStateArbitration/actualMachineState */
  if (HighClearance_model_FuncInternalData0.is_active_c5_HighClearance_model ==
      0U)
  {
    /* Entry: Arbitration/ActualStateArbitration/actualMachineState */
    HighClearance_model_FuncInternalData0.is_active_c5_HighClearance_model = 1U;

    /* Entry Internal: Arbitration/ActualStateArbitration/actualMachineState */
    /* Transition: '<S13>:631' */
    /* Transition: '<S13>:590' */
    if (HighClearance_model_checkError
        (&BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1))
    {
      /* Transition: '<S13>:587' */
      HighClearance_model_FuncInternalData0.temporalCounter_i1 = 0U;
      HighClearance_model_FuncInternalData0.is_states_g =
        HighClearance_model_IN_error_i;

      /* Outport: '<Root>/machineState' */
      /* Entry 'error': '<S13>:584' */
      HighClearance_model_Y.machineState = heightError_e;
    }
    else
    {
      /* Transition: '<S13>:628' */
      if (HighClearance_model_checkCalibrating())
      {
        /* Transition: '<S13>:624' */
        HighClearance_model_FuncInternalData0.temporalCounter_i1 = 0U;
        HighClearance_model_FuncInternalData0.is_states_g =
          HighClearance_model_IN_calibrating;

        /* Outport: '<Root>/machineState' */
        /* Entry 'calibrating': '<S13>:619' */
        HighClearance_model_Y.machineState = heightCalibrating_e;
      }
      else
      {
        /* Transition: '<S13>:592' */
        if (HighClearance_model_checkDown
            (&BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1))
        {
          /* Transition: '<S13>:595' */
          HighClearance_model_FuncInternalData0.temporalCounter_i1 = 0U;
          HighClearance_model_FuncInternalData0.is_states_g =
            HighClearance_model_IN_down;

          /* Outport: '<Root>/machineState' */
          /* Entry 'down': '<S13>:406' */
          HighClearance_model_Y.machineState = heightDown_e;
        }
        else
        {
          /* Transition: '<S13>:598' */
          if (HighClearance_model_checkUp
              (&BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1))
          {
            /* Transition: '<S13>:599' */
            HighClearance_model_FuncInternalData0.temporalCounter_i1 = 0U;
            HighClearance_model_FuncInternalData0.is_states_g =
              HighClearance_model_IN_up_m;

            /* Outport: '<Root>/machineState' */
            /* Entry 'up': '<S13>:409' */
            HighClearance_model_Y.machineState = heightUp_e;
          }
          else
          {
            /* Transition: '<S13>:601' */
            if (HighClearance_model_checkMovingDown
                (&BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1))
            {
              /* Transition: '<S13>:602' */
              HighClearance_model_FuncInternalData0.temporalCounter_i1 = 0U;
              HighClearance_model_FuncInternalData0.is_states_g =
                HighClearance_model_IN_movingDown_a;

              /* Outport: '<Root>/machineState' */
              /* Entry 'movingDown': '<S13>:571' */
              HighClearance_model_Y.machineState = heightMovingDown_e;
            }
            else
            {
              /* Transition: '<S13>:605' */
              if (HighClearance_model_checkMovingUp
                  (&BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1))
              {
                /* Transition: '<S13>:606' */
                HighClearance_model_FuncInternalData0.temporalCounter_i1 = 0U;
                HighClearance_model_FuncInternalData0.is_states_g =
                  HighClearance_model_IN_movingUp_d;

                /* Outport: '<Root>/machineState' */
                /* Entry 'movingUp': '<S13>:574' */
                HighClearance_model_Y.machineState = heightMovingUp_e;
              }
              else
              {
                /* Transition: '<S13>:607' */
                /* Transition: '<S13>:608' */
                HighClearance_model_FuncInternalData0.temporalCounter_i1 = 0U;
                HighClearance_model_FuncInternalData0.is_states_g =
                  HighClearance_model_IN_unKnown;

                /* Outport: '<Root>/machineState' */
                /* Entry 'unKnown': '<S13>:583' */
                HighClearance_model_Y.machineState = heightUnknown_e;
              }
            }
          }
        }
      }
    }
  }
  else
  {
    /* During 'states': '<S13>:585' */
    if ((uint32_T)((int32_T)
                   HighClearance_model_FuncInternalData0.temporalCounter_i1 * 10)
        >= 1U)
    {
      /* Transition: '<S13>:589' */
      /* Transition: '<S13>:590' */
      if (HighClearance_model_checkError
          (&BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1))
      {
        /* Transition: '<S13>:587' */
        /* Exit Internal 'states': '<S13>:585' */
        HighClearance_model_FuncInternalData0.temporalCounter_i1 = 0U;
        HighClearance_model_FuncInternalData0.is_states_g =
          HighClearance_model_IN_error_i;

        /* Outport: '<Root>/machineState' */
        /* Entry 'error': '<S13>:584' */
        HighClearance_model_Y.machineState = heightError_e;
      }
      else
      {
        /* Transition: '<S13>:628' */
        if (HighClearance_model_checkCalibrating())
        {
          /* Transition: '<S13>:624' */
          /* Exit Internal 'states': '<S13>:585' */
          HighClearance_model_FuncInternalData0.temporalCounter_i1 = 0U;
          HighClearance_model_FuncInternalData0.is_states_g =
            HighClearance_model_IN_calibrating;

          /* Outport: '<Root>/machineState' */
          /* Entry 'calibrating': '<S13>:619' */
          HighClearance_model_Y.machineState = heightCalibrating_e;
        }
        else
        {
          /* Transition: '<S13>:592' */
          if (HighClearance_model_checkDown
              (&BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1))
          {
            /* Transition: '<S13>:595' */
            /* Exit Internal 'states': '<S13>:585' */
            HighClearance_model_FuncInternalData0.temporalCounter_i1 = 0U;
            HighClearance_model_FuncInternalData0.is_states_g =
              HighClearance_model_IN_down;

            /* Outport: '<Root>/machineState' */
            /* Entry 'down': '<S13>:406' */
            HighClearance_model_Y.machineState = heightDown_e;
          }
          else
          {
            /* Transition: '<S13>:598' */
            if (HighClearance_model_checkUp
                (&BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1))
            {
              /* Transition: '<S13>:599' */
              /* Exit Internal 'states': '<S13>:585' */
              HighClearance_model_FuncInternalData0.temporalCounter_i1 = 0U;
              HighClearance_model_FuncInternalData0.is_states_g =
                HighClearance_model_IN_up_m;

              /* Outport: '<Root>/machineState' */
              /* Entry 'up': '<S13>:409' */
              HighClearance_model_Y.machineState = heightUp_e;
            }
            else
            {
              /* Transition: '<S13>:601' */
              if (HighClearance_model_checkMovingDown
                  (&BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1))
              {
                /* Transition: '<S13>:602' */
                /* Exit Internal 'states': '<S13>:585' */
                HighClearance_model_FuncInternalData0.temporalCounter_i1 = 0U;
                HighClearance_model_FuncInternalData0.is_states_g =
                  HighClearance_model_IN_movingDown_a;

                /* Outport: '<Root>/machineState' */
                /* Entry 'movingDown': '<S13>:571' */
                HighClearance_model_Y.machineState = heightMovingDown_e;
              }
              else
              {
                /* Transition: '<S13>:605' */
                if (HighClearance_model_checkMovingUp
                    (&BusConversion_InsertedFor_actualMachineState_at_inport_0_BusCreator1))
                {
                  /* Transition: '<S13>:606' */
                  /* Exit Internal 'states': '<S13>:585' */
                  HighClearance_model_FuncInternalData0.temporalCounter_i1 = 0U;
                  HighClearance_model_FuncInternalData0.is_states_g =
                    HighClearance_model_IN_movingUp_d;

                  /* Outport: '<Root>/machineState' */
                  /* Entry 'movingUp': '<S13>:574' */
                  HighClearance_model_Y.machineState = heightMovingUp_e;
                }
                else
                {
                  /* Transition: '<S13>:607' */
                  /* Transition: '<S13>:608' */
                  /* Exit Internal 'states': '<S13>:585' */
                  HighClearance_model_FuncInternalData0.temporalCounter_i1 = 0U;
                  HighClearance_model_FuncInternalData0.is_states_g =
                    HighClearance_model_IN_unKnown;

                  /* Outport: '<Root>/machineState' */
                  /* Entry 'unKnown': '<S13>:583' */
                  HighClearance_model_Y.machineState = heightUnknown_e;
                }
              }
            }
          }
        }
      }
    }
    else
    {
      switch (HighClearance_model_FuncInternalData0.is_states_g)
      {
       case HighClearance_model_IN_calibrating:
        /* Outport: '<Root>/machineState' */
        HighClearance_model_Y.machineState = heightCalibrating_e;

        /* During 'calibrating': '<S13>:619' */
        break;

       case HighClearance_model_IN_down:
        /* Outport: '<Root>/machineState' */
        HighClearance_model_Y.machineState = heightDown_e;

        /* During 'down': '<S13>:406' */
        break;

       case HighClearance_model_IN_error_i:
        /* Outport: '<Root>/machineState' */
        HighClearance_model_Y.machineState = heightError_e;

        /* During 'error': '<S13>:584' */
        break;

       case HighClearance_model_IN_movingDown_a:
        /* Outport: '<Root>/machineState' */
        HighClearance_model_Y.machineState = heightMovingDown_e;

        /* During 'movingDown': '<S13>:571' */
        break;

       case HighClearance_model_IN_movingUp_d:
        /* Outport: '<Root>/machineState' */
        HighClearance_model_Y.machineState = heightMovingUp_e;

        /* During 'movingUp': '<S13>:574' */
        break;

       case HighClearance_model_IN_unKnown:
        /* Outport: '<Root>/machineState' */
        HighClearance_model_Y.machineState = heightUnknown_e;

        /* During 'unKnown': '<S13>:583' */
        break;

       default:
        /* Outport: '<Root>/machineState' */
        HighClearance_model_Y.machineState = heightUp_e;

        /* During 'up': '<S13>:409' */
        break;
      }
    }
  }

  /* End of Chart: '<S5>/actualMachineState' */

  /* Chart: '<S1>/latch' incorporates:
   *  Inport: '<Root>/mfa'
   */
  if (HighClearance_model_FuncInternalData0.temporalCounter_i1_h < 4095U)
  {
    HighClearance_model_FuncInternalData0.temporalCounter_i1_h++;
  }

  /* Gateway: Arbitration/latch */
  /* During: Arbitration/latch */
  if (HighClearance_model_FuncInternalData0.is_active_c10_HighClearance_model ==
      0U)
  {
    /* Entry: Arbitration/latch */
    HighClearance_model_FuncInternalData0.is_active_c10_HighClearance_model = 1U;

    /* Entry Internal: Arbitration/latch */
    /* Transition: '<S11>:2' */
    HighClearance_model_FuncInternalData0.is_c10_HighClearance_model =
      HighClearance_model_IN_isAlive;
    HighClearance_model_FuncInternalData0.temporalCounter_i1_h = 0U;

    /* Entry 'isAlive': '<S11>:1' */
    HighClearance_model_FuncInternalData0.alive = true;
  }
  else if (HighClearance_model_FuncInternalData0.is_c10_HighClearance_model ==
           HighClearance_model_IN_isAlive)
  {
    HighClearance_model_FuncInternalData0.alive = true;

    /* During 'isAlive': '<S11>:1' */
    if ((HighClearance_model_FuncInternalData0.temporalCounter_i1_h >= 3000U) &&
        (HighClearance_model_U.mfa.isAlive == 0))
    {
      /* Transition: '<S11>:8' */
      /* Transition: '<S11>:6' */
      HighClearance_model_FuncInternalData0.is_c10_HighClearance_model =
        HighClearance_model_IN_notAlive;

      /* Entry 'notAlive': '<S11>:3' */
      HighClearance_model_FuncInternalData0.alive = false;
    }
  }
  else
  {
    HighClearance_model_FuncInternalData0.alive = false;

    /* During 'notAlive': '<S11>:3' */
  }

  /* End of Chart: '<S1>/latch' */

  /* Chart: '<S1>/latch1' incorporates:
   *  Inport: '<Root>/mfa'
   */
  if (HighClearance_model_FuncInternalData0.temporalCounter_i1_i < 4095U)
  {
    HighClearance_model_FuncInternalData0.temporalCounter_i1_i++;
  }

  /* Gateway: Arbitration/latch1 */
  /* During: Arbitration/latch1 */
  if (HighClearance_model_FuncInternalData0.is_active_c11_HighClearance_model ==
      0U)
  {
    /* Entry: Arbitration/latch1 */
    HighClearance_model_FuncInternalData0.is_active_c11_HighClearance_model = 1U;

    /* Entry Internal: Arbitration/latch1 */
    /* Transition: '<S12>:2' */
    HighClearance_model_FuncInternalData0.is_c11_HighClearance_model =
      HighClearance_model_IN_okay_p;
    HighClearance_model_FuncInternalData0.temporalCounter_i1_i = 0U;

    /* Entry 'okay': '<S12>:1' */
    HighClearance_model_FuncInternalData0.dwnBtnOk = true;
  }
  else if (HighClearance_model_FuncInternalData0.is_c11_HighClearance_model ==
           HighClearance_model_IN_notOkay)
  {
    HighClearance_model_FuncInternalData0.dwnBtnOk = false;

    /* During 'notOkay': '<S12>:3' */
  }
  else
  {
    HighClearance_model_FuncInternalData0.dwnBtnOk = true;

    /* During 'okay': '<S12>:1' */
    if ((HighClearance_model_FuncInternalData0.temporalCounter_i1_i >= 3000U) &&
        (HighClearance_model_U.mfa.downDiag != 0))
    {
      /* Transition: '<S12>:8' */
      /* Transition: '<S12>:6' */
      HighClearance_model_FuncInternalData0.is_c11_HighClearance_model =
        HighClearance_model_IN_notOkay;

      /* Entry 'notOkay': '<S12>:3' */
      HighClearance_model_FuncInternalData0.dwnBtnOk = false;
    }
  }

  /* End of Chart: '<S1>/latch1' */

  /* Chart: '<S213>/diagLatch' incorporates:
   *  Inport: '<Root>/trackCylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.trackCylCoilDiags.extend.FrontLeft,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch);

  /* Chart: '<S213>/diagLatch2' incorporates:
   *  Inport: '<Root>/trackCylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.trackCylCoilDiags.extend.FrontRight,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch2);

  /* Chart: '<S213>/diagLatch4' incorporates:
   *  Inport: '<Root>/trackCylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.trackCylCoilDiags.extend.RearLeft,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch4);

  /* Chart: '<S213>/diagLatch6' incorporates:
   *  Inport: '<Root>/trackCylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.trackCylCoilDiags.extend.RearRight,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch6);

  /* BusCreator generated from: '<S1>/TargetStateArbitration' */
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.extend.FrontLeft
    = HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch.diagOut;
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.extend.FrontRight
    = HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch2.diagOut;
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.extend.RearLeft
    = HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch4.diagOut;
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.extend.RearRight
    = HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch6.diagOut;

  /* Chart: '<S213>/diagLatch1' incorporates:
   *  Inport: '<Root>/trackCylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.trackCylCoilDiags.retract.FrontLeft,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1);

  /* Chart: '<S213>/diagLatch3' incorporates:
   *  Inport: '<Root>/trackCylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.trackCylCoilDiags.retract.FrontRight,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch3);

  /* Chart: '<S213>/diagLatch5' incorporates:
   *  Inport: '<Root>/trackCylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.trackCylCoilDiags.retract.RearLeft,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch5);

  /* Chart: '<S213>/diagLatch7' incorporates:
   *  Inport: '<Root>/trackCylCoilDiags'
   */
  HighClearance_model_diagLatch
    (HighClearance_model_U.trackCylCoilDiags.retract.RearRight,
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch7);

  /* BusCreator generated from: '<S1>/TargetStateArbitration' */
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.retract.FrontLeft
    = HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1.diagOut;
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.retract.FrontRight
    = HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch3.diagOut;
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.retract.RearLeft
    = HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch5.diagOut;
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1.retract.RearRight
    = HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch7.diagOut;

  /* BusCreator generated from: '<S1>/TargetStateArbitration' incorporates:
   *  Inport: '<Root>/actualTrackWidth_mm'
   */
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_8_BusCreator1
    = HighClearance_model_U.actualTrackWidth_mm;

  /* BusCreator generated from: '<S1>/TargetStateArbitration' */
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.extend.FrontLeft
    =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch_j.diagOut;
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.extend.FrontRight
    =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch2_p.diagOut;
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.extend.RearLeft
    =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch4_m.diagOut;
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.extend.RearRight
    =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch6_g.diagOut;

  /* BusCreator generated from: '<S1>/TargetStateArbitration' */
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.retract.FrontLeft
    =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_l.diagOut;
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.retract.FrontRight
    =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch3_n.diagOut;
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.retract.RearLeft
    =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch5_g.diagOut;
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1.retract.RearRight
    =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch7_f.diagOut;

  /* UnitDelay generated from: '<Root>/Unit Delay3' */
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_14_BusCreator1.FrontLeft
    = HighClearance_model_FuncInternalData0.UnitDelay3_1_DSTATE;

  /* UnitDelay generated from: '<Root>/Unit Delay3' */
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_14_BusCreator1.FrontRight
    = HighClearance_model_FuncInternalData0.UnitDelay3_2_DSTATE;

  /* UnitDelay generated from: '<Root>/Unit Delay3' */
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_14_BusCreator1.RearLeft
    = HighClearance_model_FuncInternalData0.UnitDelay3_3_DSTATE;

  /* UnitDelay generated from: '<Root>/Unit Delay3' */
  HighClearance_model_FuncInternalData0.BusConversion_InsertedFor_TargetStateArbitration_at_inport_14_BusCreator1.RearRight
    = HighClearance_model_FuncInternalData0.UnitDelay3_4_DSTATE;

  /* Chart: '<S1>/TargetStateArbitration' incorporates:
   *  Inport: '<Root>/engRunning'
   *  Inport: '<Root>/mfa'
   *  Outport: '<Root>/mfaLeds'
   */
  if (HighClearance_model_FuncInternalData0.temporalCounter_i1_db < 3U)
  {
    HighClearance_model_FuncInternalData0.temporalCounter_i1_db++;
  }

  /* Gateway: Arbitration/TargetStateArbitration */
  stopBtn_prev = HighClearance_model_FuncInternalData0.stopBtn_start;
  HighClearance_model_FuncInternalData0.stopBtn_start =
    HighClearance_model_U.mfa.stopBtn;
  upBtn_prev = HighClearance_model_FuncInternalData0.upBtn_start;
  HighClearance_model_FuncInternalData0.upBtn_start =
    HighClearance_model_U.mfa.upBtn;
  downBtn_prev = HighClearance_model_FuncInternalData0.downBtn_start;
  HighClearance_model_FuncInternalData0.downBtn_start =
    HighClearance_model_U.mfa.downBtn;
  LogicalOperator = HighClearance_model_FuncInternalData0.engRunning_start;
  HighClearance_model_FuncInternalData0.engRunning_start =
    HighClearance_model_U.engRunning;

  /* During: Arbitration/TargetStateArbitration */
  if (HighClearance_model_FuncInternalData0.is_active_c4_HighClearance_model ==
      0U)
  {
    /* Entry: Arbitration/TargetStateArbitration */
    HighClearance_model_FuncInternalData0.is_active_c4_HighClearance_model = 1U;

    /* Entry Internal: Arbitration/TargetStateArbitration */
    /* Transition: '<S7>:1201' */
    /* Entry 'states': '<S7>:1191' */
    HighClearance_model_Y.okayToLower = HighClearance_model_okayToLower();
    if (HighClearance_model_Y.okayToLower)
    {
      HighClearance_model_Y.okayToLower = !HighClearance_model_disableLower();
    }

    HighClearance_model_Y.okayToRaise = HighClearance_model_okayToRaise();
    if (HighClearance_model_Y.okayToRaise)
    {
      HighClearance_model_Y.okayToRaise = !HighClearance_model_disableRiase();
    }

    /* Entry Internal 'states': '<S7>:1191' */
    /* Transition: '<S7>:1202' */
    HighClearance_model_FuncInternalData0.is_states_k =
      HighClearance_model_IN_waitForEngineRunning;

    /* Outport: '<Root>/targetState' */
    /* Entry 'waitForEngineRunning': '<S7>:697' */
    HighClearance_model_Y.targetState = heightUnknown_e;
    HighClearance_model_Y.mfaLeds.downBtn = 0U;
    HighClearance_model_Y.mfaLeds.upBtn = 0U;
  }
  else
  {
    HighClearance_model_states(&stopBtn_prev, &upBtn_prev, &downBtn_prev,
      &LogicalOperator);
  }

  /* End of Chart: '<S1>/TargetStateArbitration' */

  /* Chart: '<S25>/calState2TargetState' incorporates:
   *  Outport: '<Root>/calState'
   */
  /* Gateway: Calibration/controlLogic/calStateConverstion/calState2TargetState */
  override_prev = HighClearance_model_FuncInternalData0.calState_start;
  HighClearance_model_FuncInternalData0.calState_start =
    HighClearance_model_Y.calState;

  /* During: Calibration/controlLogic/calStateConverstion/calState2TargetState */
  if (HighClearance_model_FuncInternalData0.is_active_c6_HighClearance_model ==
      0U)
  {
    /* Entry: Calibration/controlLogic/calStateConverstion/calState2TargetState */
    HighClearance_model_FuncInternalData0.is_active_c6_HighClearance_model = 1U;

    /* Entry Internal: Calibration/controlLogic/calStateConverstion/calState2TargetState */
    /* Transition: '<S36>:17' */
    /* Entry Internal 'states': '<S36>:14' */
    /* Transition: '<S36>:16' */
    if ((HighClearance_model_Y.calState == calSTEP1_e) ||
        (HighClearance_model_Y.calState == calSTEP2_e))
    {
      /* Transition: '<S36>:20' */
      HighClearance_model_FuncInternalData0.is_states =
        HighClearance_model_IN_Down_k;

      /* Entry 'Down': '<S36>:12' */
      stopBtn_prev = heightDown_e;
    }
    else if ((HighClearance_model_Y.calState == calSTEP3_e) ||
             (HighClearance_model_Y.calState == calSTEP4_e))
    {
      /* Transition: '<S36>:21' */
      HighClearance_model_FuncInternalData0.is_states =
        HighClearance_model_IN_Up_d;

      /* Entry 'Up': '<S36>:13' */
      stopBtn_prev = heightUp_e;
    }
    else
    {
      /* Transition: '<S36>:19' */
      HighClearance_model_FuncInternalData0.is_states =
        HighClearance_model_IN_stop_ht;

      /* Entry 'stop': '<S36>:10' */
      stopBtn_prev = heightUnknown_e;
    }
  }
  else
  {
    /* During 'states': '<S36>:14' */
    if (override_prev != HighClearance_model_FuncInternalData0.calState_start)
    {
      /* Transition: '<S36>:18' */
      /* Exit Internal 'states': '<S36>:14' */
      /* Entry Internal 'states': '<S36>:14' */
      /* Transition: '<S36>:16' */
      if ((HighClearance_model_Y.calState == calSTEP1_e) ||
          (HighClearance_model_Y.calState == calSTEP2_e))
      {
        /* Transition: '<S36>:20' */
        HighClearance_model_FuncInternalData0.is_states =
          HighClearance_model_IN_Down_k;

        /* Entry 'Down': '<S36>:12' */
        stopBtn_prev = heightDown_e;
      }
      else if ((HighClearance_model_Y.calState == calSTEP3_e) ||
               (HighClearance_model_Y.calState == calSTEP4_e))
      {
        /* Transition: '<S36>:21' */
        HighClearance_model_FuncInternalData0.is_states =
          HighClearance_model_IN_Up_d;

        /* Entry 'Up': '<S36>:13' */
        stopBtn_prev = heightUp_e;
      }
      else
      {
        /* Transition: '<S36>:19' */
        HighClearance_model_FuncInternalData0.is_states =
          HighClearance_model_IN_stop_ht;

        /* Entry 'stop': '<S36>:10' */
        stopBtn_prev = heightUnknown_e;
      }
    }
    else
    {
      switch (HighClearance_model_FuncInternalData0.is_states)
      {
       case HighClearance_model_IN_Down_k:
        stopBtn_prev = heightDown_e;

        /* During 'Down': '<S36>:12' */
        break;

       case HighClearance_model_IN_Up_d:
        stopBtn_prev = heightUp_e;

        /* During 'Up': '<S36>:13' */
        break;

       default:
        stopBtn_prev = heightUnknown_e;

        /* During 'stop': '<S36>:10' */
        break;
      }
    }
  }

  /* End of Chart: '<S25>/calState2TargetState' */

  /* Chart: '<S69>/diagLatch1' incorporates:
   *  Inport: '<Root>/heightPosSensors_diag'
   */
  HighClearance_model_diagLatch1
    (HighClearance_model_U.heightPosSensors_diag.FrontLeft, ((uint8_T)0U),
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_bn);

  /* Lookup_n-D: '<S35>/1-D Lookup Table' incorporates:
   *  Inport: '<Root>/heightPosSensors_mA'
   */
  rtb_uDLookupTable = look1_iflf_binlca
    (HighClearance_model_U.heightPosSensors_mA.FrontLeft,
     HighClearance_model_P.defaultPositionSensor_BrkPnts,
     HighClearance_model_P.positionSensor_tblData, 1U);

  /* Delay: '<S60>/Delay' */
  if (HighClearance_model_FuncInternalData0.icLoad_jm != 0)
  {
    HighClearance_model_FuncInternalData0.Delay_DSTATE_df = rtb_uDLookupTable;
  }

  /* Sum: '<S60>/Sum' incorporates:
   *  Constant: '<S60>/Constant'
   *  Delay: '<S60>/Delay'
   *  Product: '<S60>/Product1'
   *  Product: '<S60>/product'
   *  Sum: '<S60>/Sum1'
   */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_df = rtb_uDLookupTable *
    Switch_m + (1.0F - Switch_m) *
    HighClearance_model_FuncInternalData0.Delay_DSTATE_df;

  /* Switch: '<S69>/Switch' incorporates:
   *  Constant: '<S56>/useSensorFilter'
   *  Constant: '<S69>/Constant'
   *  Constant: '<S69>/Constant1'
   *  Constant: '<S82>/Constant'
   *  RelationalOperator: '<S82>/Compare'
   *  Sum: '<S69>/Add'
   *  Switch: '<S56>/Switch'
   */
  if (HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_bn.diagOut
      != HighClearance_model_P.IOD_OK)
  {
    rtb_uDLookupTable = 0.0F;
  }
  else
  {
    if (HighClearance_model_P.useSensorFilter)
    {
      /* Switch: '<S56>/Switch' */
      rtb_uDLookupTable = HighClearance_model_FuncInternalData0.Delay_DSTATE_df;
    }

    rtb_uDLookupTable += HighClearance_model_P.baseClearance;
  }

  /* End of Switch: '<S69>/Switch' */

  /* Chart: '<S70>/diagLatch1' incorporates:
   *  Inport: '<Root>/heightPosSensors_diag'
   */
  HighClearance_model_diagLatch1
    (HighClearance_model_U.heightPosSensors_diag.FrontRight, ((uint8_T)0U),
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_h);

  /* Lookup_n-D: '<S35>/1-D Lookup Table1' incorporates:
   *  Inport: '<Root>/heightPosSensors_mA'
   */
  rtb_uDLookupTable1 = look1_iflf_binlca
    (HighClearance_model_U.heightPosSensors_mA.FrontRight,
     HighClearance_model_P.defaultPositionSensor_BrkPnts,
     HighClearance_model_P.positionSensor_tblData, 1U);

  /* Delay: '<S61>/Delay' */
  if (HighClearance_model_FuncInternalData0.icLoad_n != 0)
  {
    HighClearance_model_FuncInternalData0.Delay_DSTATE_hr = rtb_uDLookupTable1;
  }

  /* Sum: '<S61>/Sum' incorporates:
   *  Constant: '<S61>/Constant'
   *  Delay: '<S61>/Delay'
   *  Product: '<S61>/Product1'
   *  Product: '<S61>/product'
   *  Sum: '<S61>/Sum1'
   */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_hr = rtb_uDLookupTable1 *
    Switch_m + (1.0F - Switch_m) *
    HighClearance_model_FuncInternalData0.Delay_DSTATE_hr;

  /* Switch: '<S70>/Switch' incorporates:
   *  Constant: '<S57>/useSensorFilter'
   *  Constant: '<S70>/Constant'
   *  Constant: '<S70>/Constant1'
   *  Constant: '<S84>/Constant'
   *  RelationalOperator: '<S84>/Compare'
   *  Sum: '<S70>/Add'
   *  Switch: '<S57>/Switch'
   */
  if (HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_h.diagOut
      != HighClearance_model_P.IOD_OK)
  {
    rtb_uDLookupTable1 = 0.0F;
  }
  else
  {
    if (HighClearance_model_P.useSensorFilter)
    {
      /* Switch: '<S57>/Switch' */
      rtb_uDLookupTable1 = HighClearance_model_FuncInternalData0.Delay_DSTATE_hr;
    }

    rtb_uDLookupTable1 += HighClearance_model_P.baseClearance;
  }

  /* End of Switch: '<S70>/Switch' */

  /* Chart: '<S71>/diagLatch1' incorporates:
   *  Inport: '<Root>/heightPosSensors_diag'
   */
  HighClearance_model_diagLatch1
    (HighClearance_model_U.heightPosSensors_diag.RearLeft, ((uint8_T)0U),
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_ln);

  /* Lookup_n-D: '<S35>/1-D Lookup Table2' incorporates:
   *  Inport: '<Root>/heightPosSensors_mA'
   */
  rtb_uDLookupTable2 = look1_iflf_binlca
    (HighClearance_model_U.heightPosSensors_mA.RearLeft,
     HighClearance_model_P.defaultPositionSensor_BrkPnts,
     HighClearance_model_P.positionSensor_tblData, 1U);

  /* Delay: '<S62>/Delay' */
  if (HighClearance_model_FuncInternalData0.icLoad_p != 0)
  {
    HighClearance_model_FuncInternalData0.Delay_DSTATE_i = rtb_uDLookupTable2;
  }

  /* Sum: '<S62>/Sum' incorporates:
   *  Constant: '<S62>/Constant'
   *  Delay: '<S62>/Delay'
   *  Product: '<S62>/Product1'
   *  Product: '<S62>/product'
   *  Sum: '<S62>/Sum1'
   */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_i = rtb_uDLookupTable2 *
    Switch_m + (1.0F - Switch_m) *
    HighClearance_model_FuncInternalData0.Delay_DSTATE_i;

  /* Switch: '<S71>/Switch' incorporates:
   *  Constant: '<S58>/useSensorFilter'
   *  Constant: '<S71>/Constant'
   *  Constant: '<S71>/Constant1'
   *  Constant: '<S86>/Constant'
   *  RelationalOperator: '<S86>/Compare'
   *  Sum: '<S71>/Add'
   *  Switch: '<S58>/Switch'
   */
  if (HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_ln.diagOut
      != HighClearance_model_P.IOD_OK)
  {
    rtb_uDLookupTable2 = 0.0F;
  }
  else
  {
    if (HighClearance_model_P.useSensorFilter)
    {
      /* Switch: '<S58>/Switch' */
      rtb_uDLookupTable2 = HighClearance_model_FuncInternalData0.Delay_DSTATE_i;
    }

    rtb_uDLookupTable2 += HighClearance_model_P.baseClearance;
  }

  /* End of Switch: '<S71>/Switch' */

  /* Chart: '<S72>/diagLatch1' incorporates:
   *  Inport: '<Root>/heightPosSensors_diag'
   */
  HighClearance_model_diagLatch1
    (HighClearance_model_U.heightPosSensors_diag.RearRight, ((uint8_T)0U),
     &HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_b);

  /* Lookup_n-D: '<S35>/1-D Lookup Table3' incorporates:
   *  Inport: '<Root>/heightPosSensors_mA'
   */
  rtb_uDLookupTable3 = look1_iflf_binlca
    (HighClearance_model_U.heightPosSensors_mA.RearRight,
     HighClearance_model_P.defaultPositionSensor_BrkPnts,
     HighClearance_model_P.positionSensor_tblData, 1U);

  /* Delay: '<S63>/Delay' */
  if (HighClearance_model_FuncInternalData0.icLoad_j5 != 0)
  {
    HighClearance_model_FuncInternalData0.Delay_DSTATE_g = rtb_uDLookupTable3;
  }

  /* Sum: '<S63>/Sum' incorporates:
   *  Constant: '<S63>/Constant'
   *  Delay: '<S63>/Delay'
   *  Product: '<S63>/Product1'
   *  Product: '<S63>/product'
   *  Sum: '<S63>/Sum1'
   */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_g = rtb_uDLookupTable3 *
    Switch_m + (1.0F - Switch_m) *
    HighClearance_model_FuncInternalData0.Delay_DSTATE_g;

  /* Switch: '<S72>/Switch' incorporates:
   *  Constant: '<S59>/useSensorFilter'
   *  Constant: '<S72>/Constant'
   *  Constant: '<S72>/Constant1'
   *  Constant: '<S88>/Constant'
   *  RelationalOperator: '<S88>/Compare'
   *  Sum: '<S72>/Add'
   *  Switch: '<S59>/Switch'
   */
  if (HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_b.diagOut
      != HighClearance_model_P.IOD_OK)
  {
    Switch_m = 0.0F;
  }
  else
  {
    if (HighClearance_model_P.useSensorFilter)
    {
      /* Switch: '<S59>/Switch' */
      rtb_uDLookupTable3 = HighClearance_model_FuncInternalData0.Delay_DSTATE_g;
    }

    Switch_m = rtb_uDLookupTable3 + HighClearance_model_P.baseClearance;
  }

  /* End of Switch: '<S72>/Switch' */

  /* Gain: '<S34>/Gain' incorporates:
   *  Constant: '<S34>/Constant'
   */
  rtb_uDLookupTable3 = HighClearance_model_P.calTolMultiplier *
    HighClearance_model_P.heightDiffTolerance;

  /* Chart: '<S29>/heightOkayFL' */
  HighClearance_model_heightOkayFL(stopBtn_prev, rtb_uDLookupTable,
    rtb_uDLookupTable1, rtb_uDLookupTable2, Switch_m, rtb_uDLookupTable3,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayFL);

  /* Chart: '<S29>/heightOkayFR' */
  HighClearance_model_heightOkayFL(stopBtn_prev, rtb_uDLookupTable1,
    rtb_uDLookupTable, rtb_uDLookupTable2, Switch_m, rtb_uDLookupTable3,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayFR);

  /* Chart: '<S29>/heightOkayRL' */
  HighClearance_model_heightOkayFL(stopBtn_prev, rtb_uDLookupTable2,
    rtb_uDLookupTable, rtb_uDLookupTable1, Switch_m, rtb_uDLookupTable3,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayRL);

  /* Chart: '<S29>/heightOkayRR' */
  HighClearance_model_heightOkayFL(stopBtn_prev, Switch_m, rtb_uDLookupTable,
    rtb_uDLookupTable1, rtb_uDLookupTable2, rtb_uDLookupTable3,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayRR);

  /* Chart: '<S181>/trackWidthOkay' incorporates:
   *  Constant: '<S202>/Constant'
   *  Constant: '<S203>/Constant'
   *  Inport: '<Root>/actualTrackWidth_mm'
   *  Inport: '<Root>/targetTrackWidth_mm'
   *  Inport: '<Root>/trackCylCoilDiags'
   *  Logic: '<S133>/Logical Operator'
   *  RelationalOperator: '<S202>/Compare'
   *  RelationalOperator: '<S203>/Compare'
   */
  HighClearance_model_trackWidthOkay
    (HighClearance_model_U.targetTrackWidth_mm.FrontLeft,
     HighClearance_model_U.actualTrackWidth_mm.FrontLeft,
     (HighClearance_model_U.trackCylCoilDiags.extend.FrontLeft !=
      HighClearance_model_P.IOD_OK) ||
     (HighClearance_model_U.trackCylCoilDiags.retract.FrontLeft !=
      HighClearance_model_P.IOD_OK),
     &HighClearance_model_FuncInternalData0.FuncInternalData0_trackWidthOkay_o);

  /* Chart: '<S181>/heightOkay' incorporates:
   *  Constant: '<S125>/Constant'
   *  Outport: '<Root>/targetState'
   */
  HighClearance_model_heightOkay(HighClearance_model_Y.targetState, Switch_j,
    Switch_f, Switch_pf, Switch_al, HighClearance_model_P.heightDiffTolerance,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkay_b);

  /* Chart: '<S181>/enableLogic' incorporates:
   *  Outport: '<Root>/targetState'
   */
  HighClearance_model_enableLogic(HighClearance_model_Y.targetState,
    HighClearance_model_FuncInternalData0.FuncInternalData0_trackWidthOkay_o.enable,
    HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkay_b.enable_e,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_n);

  /* Chart: '<S182>/trackWidthOkay' incorporates:
   *  Constant: '<S204>/Constant'
   *  Constant: '<S205>/Constant'
   *  Inport: '<Root>/actualTrackWidth_mm'
   *  Inport: '<Root>/targetTrackWidth_mm'
   *  Inport: '<Root>/trackCylCoilDiags'
   *  Logic: '<S133>/Logical Operator2'
   *  RelationalOperator: '<S204>/Compare'
   *  RelationalOperator: '<S205>/Compare'
   */
  HighClearance_model_trackWidthOkay
    (HighClearance_model_U.targetTrackWidth_mm.FrontRight,
     HighClearance_model_U.actualTrackWidth_mm.FrontRight,
     (HighClearance_model_U.trackCylCoilDiags.extend.FrontRight !=
      HighClearance_model_P.IOD_OK) ||
     (HighClearance_model_U.trackCylCoilDiags.retract.FrontRight !=
      HighClearance_model_P.IOD_OK),
     &HighClearance_model_FuncInternalData0.FuncInternalData0_trackWidthOkay_dh);

  /* Chart: '<S182>/heightOkay' incorporates:
   *  Constant: '<S125>/Constant'
   *  Outport: '<Root>/targetState'
   */
  HighClearance_model_heightOkay(HighClearance_model_Y.targetState, Switch_f,
    Switch_j, Switch_pf, Switch_al, HighClearance_model_P.heightDiffTolerance,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkay_d);

  /* Chart: '<S182>/enableLogic' incorporates:
   *  Outport: '<Root>/targetState'
   */
  HighClearance_model_enableLogic(HighClearance_model_Y.targetState,
    HighClearance_model_FuncInternalData0.FuncInternalData0_trackWidthOkay_dh.enable,
    HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkay_d.enable_e,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_lx);

  /* Chart: '<S183>/trackWidthOkay' incorporates:
   *  Constant: '<S206>/Constant'
   *  Constant: '<S207>/Constant'
   *  Inport: '<Root>/actualTrackWidth_mm'
   *  Inport: '<Root>/targetTrackWidth_mm'
   *  Inport: '<Root>/trackCylCoilDiags'
   *  Logic: '<S133>/Logical Operator3'
   *  RelationalOperator: '<S206>/Compare'
   *  RelationalOperator: '<S207>/Compare'
   */
  HighClearance_model_trackWidthOkay
    (HighClearance_model_U.targetTrackWidth_mm.RearLeft,
     HighClearance_model_U.actualTrackWidth_mm.RearLeft,
     (HighClearance_model_U.trackCylCoilDiags.extend.RearLeft !=
      HighClearance_model_P.IOD_OK) ||
     (HighClearance_model_U.trackCylCoilDiags.retract.RearLeft !=
      HighClearance_model_P.IOD_OK),
     &HighClearance_model_FuncInternalData0.FuncInternalData0_trackWidthOkay_d);

  /* Chart: '<S183>/heightOkay' incorporates:
   *  Constant: '<S125>/Constant'
   *  Outport: '<Root>/targetState'
   */
  HighClearance_model_heightOkay(HighClearance_model_Y.targetState, Switch_pf,
    Switch_j, Switch_f, Switch_al, HighClearance_model_P.heightDiffTolerance,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkay_g);

  /* Chart: '<S183>/enableLogic' incorporates:
   *  Outport: '<Root>/targetState'
   */
  HighClearance_model_enableLogic(HighClearance_model_Y.targetState,
    HighClearance_model_FuncInternalData0.FuncInternalData0_trackWidthOkay_d.enable,
    HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkay_g.enable_e,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_l);

  /* Chart: '<S184>/trackWidthOkay' incorporates:
   *  Constant: '<S208>/Constant'
   *  Constant: '<S209>/Constant'
   *  Inport: '<Root>/actualTrackWidth_mm'
   *  Inport: '<Root>/targetTrackWidth_mm'
   *  Inport: '<Root>/trackCylCoilDiags'
   *  Logic: '<S133>/Logical Operator4'
   *  RelationalOperator: '<S208>/Compare'
   *  RelationalOperator: '<S209>/Compare'
   */
  HighClearance_model_trackWidthOkay
    (HighClearance_model_U.targetTrackWidth_mm.RearRight,
     HighClearance_model_U.actualTrackWidth_mm.RearRight,
     (HighClearance_model_U.trackCylCoilDiags.extend.RearRight !=
      HighClearance_model_P.IOD_OK) ||
     (HighClearance_model_U.trackCylCoilDiags.retract.RearRight !=
      HighClearance_model_P.IOD_OK),
     &HighClearance_model_FuncInternalData0.FuncInternalData0_trackWidthOkay);

  /* Chart: '<S184>/heightOkay' incorporates:
   *  Constant: '<S125>/Constant'
   *  Outport: '<Root>/targetState'
   */
  HighClearance_model_heightOkay(HighClearance_model_Y.targetState, Switch_al,
    Switch_j, Switch_f, Switch_pf, HighClearance_model_P.heightDiffTolerance,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkay);

  /* Chart: '<S184>/enableLogic' incorporates:
   *  Outport: '<Root>/targetState'
   */
  HighClearance_model_enableLogic(HighClearance_model_Y.targetState,
    HighClearance_model_FuncInternalData0.FuncInternalData0_trackWidthOkay.enable,
    HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkay.enable_e,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic);

  /* Chart: '<S6>/TargetPosition' incorporates:
   *  Outport: '<Root>/postionTargets'
   *  Outport: '<Root>/targetState'
   */
  /* Gateway: Arbitration/TargetPositionArbitration/TargetPosition */
  stopBtn_prev = HighClearance_model_FuncInternalData0.targetState_start;
  HighClearance_model_FuncInternalData0.targetState_start =
    HighClearance_model_Y.targetState;

  /* During: Arbitration/TargetPositionArbitration/TargetPosition */
  if (HighClearance_model_FuncInternalData0.is_active_c3_HighClearance_model ==
      0U)
  {
    /* Entry: Arbitration/TargetPositionArbitration/TargetPosition */
    HighClearance_model_FuncInternalData0.is_active_c3_HighClearance_model = 1U;

    /* Entry Internal: Arbitration/TargetPositionArbitration/TargetPosition */
    /* Transition: '<S19>:27' */
    HighClearance_model_enter_internal_positionStates(&Switch_j, &Switch_f,
      &Switch_pf, &Switch_al);
  }
  else
  {
    /* During 'positionStates': '<S19>:26' */
    if (stopBtn_prev != HighClearance_model_FuncInternalData0.targetState_start)
    {
      /* Transition: '<S19>:28' */
      /* Exit Internal 'positionStates': '<S19>:26' */
      HighClearance_model_enter_internal_positionStates(&Switch_j, &Switch_f,
        &Switch_pf, &Switch_al);
    }
    else
    {
      switch (HighClearance_model_FuncInternalData0.is_positionStates)
      {
       case HighClearance_model_IN_down_h:
        /* During 'down': '<S19>:6' */
        break;

       case HighClearance_model_IN_stop_h:
        /* During 'stop': '<S19>:23' */
        HighClearance_model_Y.postionTargets.FrontLeft = Switch_j;
        HighClearance_model_Y.postionTargets.FrontRight = Switch_f;
        HighClearance_model_Y.postionTargets.RearLeft = Switch_pf;
        HighClearance_model_Y.postionTargets.RearRight = Switch_al;
        break;

       default:
        /* During 'up': '<S19>:3' */
        break;
      }
    }
  }

  /* End of Chart: '<S6>/TargetPosition' */

  /* Chart: '<S3>/controlEnableLogic' incorporates:
   *  Inport: '<Root>/fieldModeActive'
   *  Outport: '<Root>/targetState'
   */
  /* Gateway: Control/controlEnableLogic */
  /* During: Control/controlEnableLogic */
  if (HighClearance_model_FuncInternalData0.is_active_c1_HighClearance_model ==
      0U)
  {
    /* Entry: Control/controlEnableLogic */
    HighClearance_model_FuncInternalData0.is_active_c1_HighClearance_model = 1U;

    /* Entry Internal: Control/controlEnableLogic */
    /* Transition: '<S124>:4' */
    HighClearance_model_FuncInternalData0.is_c1_HighClearance_model =
      HighClearance_model_IN_disabled_p;

    /* Entry 'disabled': '<S124>:3' */
    HighClearance_model_Y.controlEnable = false;
  }
  else if (HighClearance_model_FuncInternalData0.is_c1_HighClearance_model ==
           HighClearance_model_IN_disabled_p)
  {
    HighClearance_model_Y.controlEnable = false;

    /* During 'disabled': '<S124>:3' */
    if ((HighClearance_model_Y.targetState == heightDown_e) ||
        ((HighClearance_model_Y.targetState == heightUp_e) ||
         ((HighClearance_model_Y.targetState == heightMovingUp_e) ||
          (HighClearance_model_Y.targetState == heightMovingDown_e))))
    {
      /* Transition: '<S124>:6' */
      /* Transition: '<S124>:14' */
      /* Transition: '<S124>:18' */
      /* Transition: '<S124>:19' */
      /* Transition: '<S124>:39' */
      /* Transition: '<S124>:36' */
      /* Transition: '<S124>:33' */
      if (HighClearance_model_U.fieldModeActive)
      {
        /* Transition: '<S124>:30' */
        HighClearance_model_FuncInternalData0.is_c1_HighClearance_model =
          HighClearance_model_IN_enabled_e;

        /* Entry 'enabled': '<S124>:5' */
        HighClearance_model_Y.controlEnable = true;
      }
      else
      {
        /* Transition: '<S124>:42' */
        /* Transition: '<S124>:41' */
        HighClearance_model_FuncInternalData0.is_c1_HighClearance_model =
          HighClearance_model_IN_disabled_p;

        /* Entry 'disabled': '<S124>:3' */
      }
    }
  }
  else
  {
    HighClearance_model_Y.controlEnable = true;

    /* During 'enabled': '<S124>:5' */
    if (((HighClearance_model_Y.targetState != heightUp_e) &&
         (HighClearance_model_Y.targetState != heightDown_e) &&
         (HighClearance_model_Y.targetState != heightMovingUp_e) &&
         (HighClearance_model_Y.targetState != heightMovingDown_e)) ||
        (!HighClearance_model_U.fieldModeActive))
    {
      /* Transition: '<S124>:16' */
      /* Transition: '<S124>:17' */
      /* Transition: '<S124>:23' */
      /* Transition: '<S124>:21' */
      /* Transition: '<S124>:43' */
      HighClearance_model_FuncInternalData0.is_c1_HighClearance_model =
        HighClearance_model_IN_disabled_p;

      /* Entry 'disabled': '<S124>:3' */
      HighClearance_model_Y.controlEnable = false;
    }
  }

  /* End of Chart: '<S3>/controlEnableLogic' */

  /* Outputs for Enabled SubSystem: '<S3>/bangbangPosition_control' incorporates:
   *  EnablePort: '<S123>/Enable'
   */
  if (HighClearance_model_Y.controlEnable)
  {
    HighClearance_model_FuncInternalData0.bangbangPosition_control_MODE = true;

    /* Outputs for Enabled SubSystem: '<S123>/bangbangPositionControl_FL' */
    /* SystemInitialize for Outport: '<Root>/postionTargets' */
    HighClearance_model_bangbangPositionControl_FL
      (HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_n.enable,
       HighClearance_model_Y.postionTargets.FrontLeft, Switch_j,
       &HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FL);

    /* End of Outputs for SubSystem: '<S123>/bangbangPositionControl_FL' */

    /* Outputs for Enabled SubSystem: '<S123>/bangbangPositionControl_FR' */
    HighClearance_model_bangbangPositionControl_FL
      (HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_lx.enable,
       HighClearance_model_Y.postionTargets.FrontRight, Switch_f,
       &HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FR);

    /* End of Outputs for SubSystem: '<S123>/bangbangPositionControl_FR' */

    /* Outputs for Enabled SubSystem: '<S123>/bangbangPositionControl_RL' */
    HighClearance_model_bangbangPositionControl_FL
      (HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_l.enable,
       HighClearance_model_Y.postionTargets.RearLeft, Switch_pf,
       &HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RL);

    /* End of Outputs for SubSystem: '<S123>/bangbangPositionControl_RL' */

    /* Outputs for Enabled SubSystem: '<S123>/bangbangPositionControl_RR' */
    HighClearance_model_bangbangPositionControl_FL
      (HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic.enable,
       HighClearance_model_Y.postionTargets.RearRight, Switch_al,
       &HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RR);

    /* End of Outputs for SubSystem: '<S123>/bangbangPositionControl_RR' */

    /* Switch: '<S156>/Switch' */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FL.pwm
        > 0.0F)
    {
      /* BusCreator: '<S147>/Bus Creator' */
      HighClearance_model_FuncInternalData0.BusCreator.extend.FrontLeft =
        HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FL.pwm;
    }
    else
    {
      /* BusCreator: '<S147>/Bus Creator' incorporates:
       *  Constant: '<S156>/Constant'
       */
      HighClearance_model_FuncInternalData0.BusCreator.extend.FrontLeft = 0.0F;
    }

    /* End of Switch: '<S156>/Switch' */

    /* Switch: '<S157>/Switch' */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FR.pwm
        > 0.0F)
    {
      /* BusCreator: '<S147>/Bus Creator' */
      HighClearance_model_FuncInternalData0.BusCreator.extend.FrontRight =
        HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FR.pwm;
    }
    else
    {
      /* BusCreator: '<S147>/Bus Creator' incorporates:
       *  Constant: '<S157>/Constant'
       */
      HighClearance_model_FuncInternalData0.BusCreator.extend.FrontRight = 0.0F;
    }

    /* End of Switch: '<S157>/Switch' */

    /* Switch: '<S158>/Switch' */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RL.pwm
        > 0.0F)
    {
      /* BusCreator: '<S147>/Bus Creator' */
      HighClearance_model_FuncInternalData0.BusCreator.extend.RearLeft =
        HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RL.pwm;
    }
    else
    {
      /* BusCreator: '<S147>/Bus Creator' incorporates:
       *  Constant: '<S158>/Constant'
       */
      HighClearance_model_FuncInternalData0.BusCreator.extend.RearLeft = 0.0F;
    }

    /* End of Switch: '<S158>/Switch' */

    /* Switch: '<S159>/Switch' */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RR.pwm
        > 0.0F)
    {
      /* BusCreator: '<S147>/Bus Creator' */
      HighClearance_model_FuncInternalData0.BusCreator.extend.RearRight =
        HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RR.pwm;
    }
    else
    {
      /* BusCreator: '<S147>/Bus Creator' incorporates:
       *  Constant: '<S159>/Constant'
       */
      HighClearance_model_FuncInternalData0.BusCreator.extend.RearRight = 0.0F;
    }

    /* End of Switch: '<S159>/Switch' */

    /* Switch: '<S156>/Switch1' incorporates:
     *  Constant: '<S156>/Constant'
     */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FL.pwm
        >= 0.0F)
    {
      rtb_uDLookupTable = 0.0F;
    }
    else
    {
      rtb_uDLookupTable =
        HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FL.pwm;
    }

    /* End of Switch: '<S156>/Switch1' */

    /* BusCreator: '<S147>/Bus Creator' incorporates:
     *  Abs: '<S156>/Abs'
     */
    HighClearance_model_FuncInternalData0.BusCreator.retract.FrontLeft =
      (real32_T)fabs(rtb_uDLookupTable);

    /* Switch: '<S157>/Switch1' incorporates:
     *  Constant: '<S157>/Constant'
     */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FR.pwm
        >= 0.0F)
    {
      rtb_uDLookupTable = 0.0F;
    }
    else
    {
      rtb_uDLookupTable =
        HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FR.pwm;
    }

    /* End of Switch: '<S157>/Switch1' */

    /* BusCreator: '<S147>/Bus Creator' incorporates:
     *  Abs: '<S157>/Abs'
     */
    HighClearance_model_FuncInternalData0.BusCreator.retract.FrontRight =
      (real32_T)fabs(rtb_uDLookupTable);

    /* Switch: '<S158>/Switch1' incorporates:
     *  Constant: '<S158>/Constant'
     */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RL.pwm
        >= 0.0F)
    {
      rtb_uDLookupTable = 0.0F;
    }
    else
    {
      rtb_uDLookupTable =
        HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RL.pwm;
    }

    /* End of Switch: '<S158>/Switch1' */

    /* BusCreator: '<S147>/Bus Creator' incorporates:
     *  Abs: '<S158>/Abs'
     */
    HighClearance_model_FuncInternalData0.BusCreator.retract.RearLeft =
      (real32_T)fabs(rtb_uDLookupTable);

    /* Switch: '<S159>/Switch1' incorporates:
     *  Constant: '<S159>/Constant'
     */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RR.pwm
        >= 0.0F)
    {
      rtb_uDLookupTable = 0.0F;
    }
    else
    {
      rtb_uDLookupTable =
        HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RR.pwm;
    }

    /* End of Switch: '<S159>/Switch1' */

    /* BusCreator: '<S147>/Bus Creator' incorporates:
     *  Abs: '<S159>/Abs'
     */
    HighClearance_model_FuncInternalData0.BusCreator.retract.RearRight =
      (real32_T)fabs(rtb_uDLookupTable);
  }
  else
  {
    if (HighClearance_model_FuncInternalData0.bangbangPosition_control_MODE)
    {
      /* Disable for Enabled SubSystem: '<S123>/bangbangPositionControl_FL' */
      if (HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FL.bangbangPositionControl_FL_MODE)
      {
        HighClearance_model_bangbangPositionControl_FL_Disable
          (&HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FL);
      }

      /* End of Disable for SubSystem: '<S123>/bangbangPositionControl_FL' */

      /* Disable for Enabled SubSystem: '<S123>/bangbangPositionControl_FR' */
      if (HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FR.bangbangPositionControl_FL_MODE)
      {
        HighClearance_model_bangbangPositionControl_FL_Disable
          (&HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FR);
      }

      /* End of Disable for SubSystem: '<S123>/bangbangPositionControl_FR' */

      /* Disable for Enabled SubSystem: '<S123>/bangbangPositionControl_RL' */
      if (HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RL.bangbangPositionControl_FL_MODE)
      {
        HighClearance_model_bangbangPositionControl_FL_Disable
          (&HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RL);
      }

      /* End of Disable for SubSystem: '<S123>/bangbangPositionControl_RL' */

      /* Disable for Enabled SubSystem: '<S123>/bangbangPositionControl_RR' */
      if (HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RR.bangbangPositionControl_FL_MODE)
      {
        HighClearance_model_bangbangPositionControl_FL_Disable
          (&HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RR);
      }

      /* End of Disable for SubSystem: '<S123>/bangbangPositionControl_RR' */

      /* Disable for Outport: '<S123>/coilDutyCycle_pct' */
      HighClearance_model_FuncInternalData0.BusCreator =
        HighClearance_model_rtZCoilBus;
      HighClearance_model_FuncInternalData0.bangbangPosition_control_MODE =
        false;
    }
  }

  /* End of Outputs for SubSystem: '<S3>/bangbangPosition_control' */

  /* Switch: '<S122>/Switch' incorporates:
   *  Outport: '<Root>/calOverride'
   */
  if (HighClearance_model_Y.calOverride)
  {
    /* Switch: '<S39>/Switch1' incorporates:
     *  BusCreator: '<S116>/Bus Creator1'
     *  DataTypeConversion: '<S39>/Data Type Conversion1'
     */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayFL.enable_e
        > 0)
    {
      Switch_m = HighClearance_model_FuncInternalData0.exFL;
    }
    else
    {
      Switch_m =
        HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayFL.enable_e;
    }

    /* End of Switch: '<S39>/Switch1' */

    /* Switch: '<S41>/Switch1' incorporates:
     *  BusCreator: '<S116>/Bus Creator1'
     *  DataTypeConversion: '<S41>/Data Type Conversion1'
     */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayFR.enable_e
        > 0)
    {
      rtb_uDLookupTable = HighClearance_model_FuncInternalData0.exFR;
    }
    else
    {
      rtb_uDLookupTable =
        HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayFR.enable_e;
    }

    /* End of Switch: '<S41>/Switch1' */

    /* Switch: '<S43>/Switch1' incorporates:
     *  BusCreator: '<S116>/Bus Creator1'
     *  DataTypeConversion: '<S43>/Data Type Conversion1'
     */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayRL.enable_e
        > 0)
    {
      rtb_uDLookupTable1 = HighClearance_model_FuncInternalData0.exRL;
    }
    else
    {
      rtb_uDLookupTable1 =
        HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayRL.enable_e;
    }

    /* End of Switch: '<S43>/Switch1' */

    /* Switch: '<S45>/Switch1' incorporates:
     *  BusCreator: '<S116>/Bus Creator1'
     *  DataTypeConversion: '<S45>/Data Type Conversion1'
     */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayRR.enable_e
        > 0)
    {
      rtb_uDLookupTable2 = HighClearance_model_FuncInternalData0.exRR;
    }
    else
    {
      rtb_uDLookupTable2 =
        HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayRR.enable_e;
    }

    /* End of Switch: '<S45>/Switch1' */

    /* Switch: '<S40>/Switch1' incorporates:
     *  BusCreator: '<S116>/Bus Creator2'
     *  DataTypeConversion: '<S40>/Data Type Conversion1'
     */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayFL.enable_e
        > 0)
    {
      rtb_uDLookupTable3 = HighClearance_model_FuncInternalData0.rtFL;
    }
    else
    {
      rtb_uDLookupTable3 =
        HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayFL.enable_e;
    }

    /* End of Switch: '<S40>/Switch1' */

    /* Switch: '<S42>/Switch1' incorporates:
     *  BusCreator: '<S116>/Bus Creator2'
     *  DataTypeConversion: '<S42>/Data Type Conversion1'
     */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayFR.enable_e
        > 0)
    {
      Switch_retract_FrontRight = HighClearance_model_FuncInternalData0.rtFR;
    }
    else
    {
      Switch_retract_FrontRight =
        HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayFR.enable_e;
    }

    /* End of Switch: '<S42>/Switch1' */

    /* Switch: '<S44>/Switch1' incorporates:
     *  BusCreator: '<S116>/Bus Creator2'
     *  DataTypeConversion: '<S44>/Data Type Conversion1'
     */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayRL.enable_e
        > 0)
    {
      Switch_retract_RearLeft = HighClearance_model_FuncInternalData0.rtRL;
    }
    else
    {
      Switch_retract_RearLeft =
        HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayRL.enable_e;
    }

    /* End of Switch: '<S44>/Switch1' */

    /* Switch: '<S46>/Switch1' incorporates:
     *  BusCreator: '<S116>/Bus Creator2'
     *  DataTypeConversion: '<S46>/Data Type Conversion1'
     */
    if (HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayRR.enable_e
        > 0)
    {
      Switch_retract_RearRight = HighClearance_model_FuncInternalData0.rtRR;
    }
    else
    {
      Switch_retract_RearRight =
        HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayRR.enable_e;
    }

    /* End of Switch: '<S46>/Switch1' */
  }
  else
  {
    Switch_m = HighClearance_model_FuncInternalData0.BusCreator.extend.FrontLeft;
    rtb_uDLookupTable =
      HighClearance_model_FuncInternalData0.BusCreator.extend.FrontRight;
    rtb_uDLookupTable1 =
      HighClearance_model_FuncInternalData0.BusCreator.extend.RearLeft;
    rtb_uDLookupTable2 =
      HighClearance_model_FuncInternalData0.BusCreator.extend.RearRight;
    rtb_uDLookupTable3 =
      HighClearance_model_FuncInternalData0.BusCreator.retract.FrontLeft;
    Switch_retract_FrontRight =
      HighClearance_model_FuncInternalData0.BusCreator.retract.FrontRight;
    Switch_retract_RearLeft =
      HighClearance_model_FuncInternalData0.BusCreator.retract.RearLeft;
    Switch_retract_RearRight =
      HighClearance_model_FuncInternalData0.BusCreator.retract.RearRight;
  }

  /* End of Switch: '<S122>/Switch' */

  /* Chart: '<S129>/errorCheckFL' incorporates:
   *  Outport: '<Root>/machineState'
   *  Outport: '<Root>/targetState'
   *  UnitDelay: '<S3>/Unit Delay'
   */
  HighClearance_model_errorCheckFL(HighClearance_model_Y.machineState,
    HighClearance_model_Y.targetState,
    HighClearance_model_FuncInternalData0.FuncInternalData0_legState_FrontLeft.legState,
    Switch_m, rtb_uDLookupTable3,
    HighClearance_model_FuncInternalData0.UnitDelay_DSTATE_i,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckFL);

  /* Chart: '<S129>/errorCheckFR' incorporates:
   *  Outport: '<Root>/machineState'
   *  Outport: '<Root>/targetState'
   *  UnitDelay: '<S3>/Unit Delay'
   */
  HighClearance_model_errorCheckFL(HighClearance_model_Y.machineState,
    HighClearance_model_Y.targetState,
    HighClearance_model_FuncInternalData0.FuncInternalData0_legState_FrontRight.legState,
    rtb_uDLookupTable, Switch_retract_FrontRight,
    HighClearance_model_FuncInternalData0.UnitDelay_DSTATE_i,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckFR);

  /* Chart: '<S129>/errorCheckRL' incorporates:
   *  Outport: '<Root>/machineState'
   *  Outport: '<Root>/targetState'
   *  UnitDelay: '<S3>/Unit Delay'
   */
  HighClearance_model_errorCheckFL(HighClearance_model_Y.machineState,
    HighClearance_model_Y.targetState,
    HighClearance_model_FuncInternalData0.FuncInternalData0_legState_RearLeft.legState,
    rtb_uDLookupTable1, Switch_retract_RearLeft,
    HighClearance_model_FuncInternalData0.UnitDelay_DSTATE_i,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckRL);

  /* Chart: '<S129>/errorCheckRR' incorporates:
   *  Outport: '<Root>/machineState'
   *  Outport: '<Root>/targetState'
   *  UnitDelay: '<S3>/Unit Delay'
   */
  HighClearance_model_errorCheckFL(HighClearance_model_Y.machineState,
    HighClearance_model_Y.targetState,
    HighClearance_model_FuncInternalData0.FuncInternalData0_legState_RearRight.legState,
    rtb_uDLookupTable2, Switch_retract_RearRight,
    HighClearance_model_FuncInternalData0.UnitDelay_DSTATE_i,
    &HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckRR);

  /* BusCreator: '<S172>/Bus Creator' incorporates:
   *  BusCreator: '<S172>/Bus Creator1'
   *  BusCreator: '<S172>/Bus Creator2'
   *  Outport: '<Root>/coilDutyCycle_pct'
   */
  HighClearance_model_Y.coilDutyCycle_pct.extend.FrontLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckFL.pwmOut_ex;
  HighClearance_model_Y.coilDutyCycle_pct.extend.FrontRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckFR.pwmOut_ex;
  HighClearance_model_Y.coilDutyCycle_pct.extend.RearLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckRL.pwmOut_ex;
  HighClearance_model_Y.coilDutyCycle_pct.extend.RearRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckRR.pwmOut_ex;
  HighClearance_model_Y.coilDutyCycle_pct.retract.FrontLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckFL.pwmOut_rt;
  HighClearance_model_Y.coilDutyCycle_pct.retract.FrontRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckFR.pwmOut_rt;
  HighClearance_model_Y.coilDutyCycle_pct.retract.RearLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckRL.pwmOut_rt;
  HighClearance_model_Y.coilDutyCycle_pct.retract.RearRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckRR.pwmOut_rt;

  /* Switch: '<S131>/Switch1' incorporates:
   *  Outport: '<Root>/manualOverrideEnable'
   */
  if (HighClearance_model_Y.manualOverrideEnable)
  {
    /* Outport: '<Root>/coilDutyCycle_pct' */
    HighClearance_model_Y.coilDutyCycle_pct =
      HighClearance_model_FuncInternalData0.pwm;
  }

  /* End of Switch: '<S131>/Switch1' */

  /* Switch: '<S131>/Switch' incorporates:
   *  Outport: '<Root>/manualOverrideEnable'
   */
  if (HighClearance_model_Y.manualOverrideEnable)
  {
    /* Outport: '<Root>/ccoReqOff' incorporates:
     *  Constant: '<S131>/Constant'
     */
    HighClearance_model_Y.ccoReqOff = false;
  }
  else
  {
    /* Outport: '<Root>/ccoReqOff' incorporates:
     *  Logic: '<S129>/Logical Operator'
     */
    HighClearance_model_Y.ccoReqOff =
      (HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckFR.ccoReqOff
       ||
       HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckRR.ccoReqOff
       ||
       HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckFL.ccoReqOff
       ||
       HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckRL.ccoReqOff);
  }

  /* End of Switch: '<S131>/Switch' */

  /* BusCreator generated from: '<Root>/legErrors' incorporates:
   *  Outport: '<Root>/legErrors'
   */
  HighClearance_model_Y.legErrors.FrontLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckFL.error;
  HighClearance_model_Y.legErrors.FrontRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckFR.error;
  HighClearance_model_Y.legErrors.RearLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckRL.error;
  HighClearance_model_Y.legErrors.RearRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckRR.error;

  /* Chart: '<S1>/ladderExtendLogic' */
  /* Gateway: Arbitration/ladderExtendLogic */
  /* During: Arbitration/ladderExtendLogic */
  if (HighClearance_model_FuncInternalData0.is_active_c8_HighClearance_model ==
      0U)
  {
    /* Entry: Arbitration/ladderExtendLogic */
    HighClearance_model_FuncInternalData0.is_active_c8_HighClearance_model = 1U;

    /* Entry Internal: Arbitration/ladderExtendLogic */
    /* Transition: '<S10>:12' */
    if (HighClearance_model_extendOkay())
    {
      /* Transition: '<S10>:27' */
      HighClearance_model_FuncInternalData0.is_c8_HighClearance_model =
        HighClearance_model_IN_extend_h;

      /* Outport: '<Root>/extenedLadder' */
      /* Entry 'extend': '<S10>:6' */
      HighClearance_model_Y.extenedLadder = true;
    }
    else
    {
      /* Transition: '<S10>:13' */
      HighClearance_model_FuncInternalData0.is_c8_HighClearance_model =
        HighClearance_model_IN_retract_n;

      /* Outport: '<Root>/extenedLadder' */
      /* Entry 'retract': '<S10>:4' */
      HighClearance_model_Y.extenedLadder = false;
    }
  }
  else if (HighClearance_model_FuncInternalData0.is_c8_HighClearance_model ==
           HighClearance_model_IN_extend_h)
  {
    /* Outport: '<Root>/extenedLadder' */
    HighClearance_model_Y.extenedLadder = true;

    /* During 'extend': '<S10>:6' */
    if (!HighClearance_model_extendOkay())
    {
      /* Transition: '<S10>:31' */
      HighClearance_model_FuncInternalData0.is_c8_HighClearance_model =
        HighClearance_model_IN_retract_n;

      /* Outport: '<Root>/extenedLadder' */
      /* Entry 'retract': '<S10>:4' */
      HighClearance_model_Y.extenedLadder = false;
    }
  }
  else
  {
    /* Outport: '<Root>/extenedLadder' */
    HighClearance_model_Y.extenedLadder = false;

    /* During 'retract': '<S10>:4' */
    if (HighClearance_model_extendOkay())
    {
      /* Transition: '<S10>:32' */
      HighClearance_model_FuncInternalData0.is_c8_HighClearance_model =
        HighClearance_model_IN_extend_h;

      /* Outport: '<Root>/extenedLadder' */
      /* Entry 'extend': '<S10>:6' */
      HighClearance_model_Y.extenedLadder = true;
    }
  }

  /* End of Chart: '<S1>/ladderExtendLogic' */

  /* Outport: '<Root>/controlActive' incorporates:
   *  Constant: '<S134>/Constant'
   *  Constant: '<S135>/Constant'
   *  Constant: '<S136>/Constant'
   *  Constant: '<S137>/Constant'
   *  Constant: '<S138>/Constant'
   *  Constant: '<S139>/Constant'
   *  Constant: '<S140>/Constant'
   *  Constant: '<S141>/Constant'
   *  Logic: '<S122>/Logical Operator'
   *  RelationalOperator: '<S134>/Compare'
   *  RelationalOperator: '<S135>/Compare'
   *  RelationalOperator: '<S136>/Compare'
   *  RelationalOperator: '<S137>/Compare'
   *  RelationalOperator: '<S138>/Compare'
   *  RelationalOperator: '<S139>/Compare'
   *  RelationalOperator: '<S140>/Compare'
   *  RelationalOperator: '<S141>/Compare'
   */
  HighClearance_model_Y.controlActive = ((Switch_m != 0.0F) ||
    (rtb_uDLookupTable3 != 0.0F) || (rtb_uDLookupTable != 0.0F) ||
    (Switch_retract_FrontRight != 0.0F) || (rtb_uDLookupTable1 != 0.0F) ||
    (Switch_retract_RearLeft != 0.0F) || (rtb_uDLookupTable2 != 0.0F) ||
    (Switch_retract_RearRight != 0.0F));

  /* BusCreator generated from: '<Root>/legEnable' incorporates:
   *  Outport: '<Root>/legEnable'
   */
  HighClearance_model_Y.legEnable.FrontLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_n.enable;
  HighClearance_model_Y.legEnable.FrontRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_lx.enable;
  HighClearance_model_Y.legEnable.RearLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_l.enable;
  HighClearance_model_Y.legEnable.RearRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic.enable;

  /* BusCreator generated from: '<S130>/Bus Creator' */
  HighClearance_model_Y.controlWarnings.track.FrontLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_n.warningTrack;
  HighClearance_model_Y.controlWarnings.track.FrontRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_lx.warningTrack;
  HighClearance_model_Y.controlWarnings.track.RearLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_l.warningTrack;
  HighClearance_model_Y.controlWarnings.track.RearRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic.warningTrack;

  /* BusCreator generated from: '<S130>/Bus Creator' */
  HighClearance_model_Y.controlWarnings.height.FrontLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_n.warningHeight;
  HighClearance_model_Y.controlWarnings.height.FrontRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_lx.warningHeight;
  HighClearance_model_Y.controlWarnings.height.RearLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_l.warningHeight;
  HighClearance_model_Y.controlWarnings.height.RearRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic.warningHeight;

  /* BusCreator generated from: '<Root>/legState' incorporates:
   *  Outport: '<Root>/legState'
   */
  HighClearance_model_Y.legState.FrontLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_legState_FrontLeft.legState;
  HighClearance_model_Y.legState.FrontRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_legState_FrontRight.legState;
  HighClearance_model_Y.legState.RearLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_legState_RearLeft.legState;
  HighClearance_model_Y.legState.RearRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_legState_RearRight.legState;

  /* BusCreator generated from: '<Root>/legClearnace_mm' incorporates:
   *  Outport: '<Root>/legClearnace_mm'
   */
  HighClearance_model_Y.legClearnace_mm.FrontLeft = Switch_j;
  HighClearance_model_Y.legClearnace_mm.FrontRight = Switch_f;
  HighClearance_model_Y.legClearnace_mm.RearLeft = Switch_pf;
  HighClearance_model_Y.legClearnace_mm.RearRight = Switch_al;

  /* Outport: '<Root>/strokeLegnthFlt_mm' incorporates:
   *  BusCreator generated from: '<Root>/strokeLegnthFlt_mm'
   */
  HighClearance_model_Y.strokeLegnthFlt_mm.FrontLeft =
    HighClearance_model_FuncInternalData0.Delay_DSTATE_h;
  HighClearance_model_Y.strokeLegnthFlt_mm.FrontRight =
    HighClearance_model_FuncInternalData0.Delay_DSTATE_d;
  HighClearance_model_Y.strokeLegnthFlt_mm.RearLeft =
    HighClearance_model_FuncInternalData0.Delay_DSTATE_k;
  HighClearance_model_Y.strokeLegnthFlt_mm.RearRight =
    HighClearance_model_FuncInternalData0.Delay_DSTATE_mn;

  /* BusCreator generated from: '<Root>/heightPosDiagsLatched' incorporates:
   *  Outport: '<Root>/heightPosDiagsLatched'
   */
  HighClearance_model_Y.heightPosDiagsLatched.FrontLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_cx.diagOut;
  HighClearance_model_Y.heightPosDiagsLatched.FrontRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_k.diagOut;
  HighClearance_model_Y.heightPosDiagsLatched.RearLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_c.diagOut;
  HighClearance_model_Y.heightPosDiagsLatched.RearRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_m.diagOut;

  /* BusCreator generated from: '<Root>/strokeLegnthRaw_mm' incorporates:
   *  Outport: '<Root>/strokeLegnthRaw_mm'
   */
  HighClearance_model_Y.strokeLegnthRaw_mm.FrontLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_c.positionOut;
  HighClearance_model_Y.strokeLegnthRaw_mm.FrontRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_p.positionOut;
  HighClearance_model_Y.strokeLegnthRaw_mm.RearLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_b.positionOut;
  HighClearance_model_Y.strokeLegnthRaw_mm.RearRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck.positionOut;

  /* BusCreator generated from: '<Root>/cylCoilDiagsLatched' */
  HighClearance_model_Y.cylCoilDiagsLatched.retract.FrontLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_l.diagOut;
  HighClearance_model_Y.cylCoilDiagsLatched.retract.FrontRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch3_n.diagOut;
  HighClearance_model_Y.cylCoilDiagsLatched.retract.RearLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch5_g.diagOut;
  HighClearance_model_Y.cylCoilDiagsLatched.retract.RearRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch7_f.diagOut;

  /* BusCreator generated from: '<Root>/cylCoilDiagsLatched' */
  HighClearance_model_Y.cylCoilDiagsLatched.extend.FrontLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch_j.diagOut;
  HighClearance_model_Y.cylCoilDiagsLatched.extend.FrontRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch2_p.diagOut;
  HighClearance_model_Y.cylCoilDiagsLatched.extend.RearLeft =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch4_m.diagOut;
  HighClearance_model_Y.cylCoilDiagsLatched.extend.RearRight =
    HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch6_g.diagOut;

  /* Update for Delay: '<S111>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad = 0U;

  /* Update for Delay: '<S112>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_b = 0U;

  /* Update for Delay: '<S113>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_e = 0U;

  /* Update for Delay: '<S114>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_k = 0U;

  /* Update for UnitDelay: '<Root>/Unit Delay' incorporates:
   *  Outport: '<Root>/okayToRaise'
   */
  HighClearance_model_FuncInternalData0.UnitDelay_DSTATE =
    HighClearance_model_Y.okayToRaise;

  /* Update for UnitDelay: '<Root>/Unit Delay1' incorporates:
   *  Outport: '<Root>/okayToLower'
   */
  HighClearance_model_FuncInternalData0.UnitDelay1_DSTATE =
    HighClearance_model_Y.okayToLower;

  /* Update for Delay: '<S246>/Delay' */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_f[0] =
    HighClearance_model_FuncInternalData0.Delay_DSTATE_f[1];

  /* Update for Delay: '<S247>/Delay' */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_h4[0] =
    HighClearance_model_FuncInternalData0.Delay_DSTATE_h4[1];

  /* Update for Delay: '<S248>/Delay' */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_j0[0] =
    HighClearance_model_FuncInternalData0.Delay_DSTATE_j0[1];

  /* Update for Delay: '<S249>/Delay' */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_e[0] =
    HighClearance_model_FuncInternalData0.Delay_DSTATE_e[1];

  /* Update for Delay: '<S246>/Delay' */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_f[1] =
    HighClearance_model_FuncInternalData0.Delay_DSTATE_f[2];

  /* Update for Delay: '<S247>/Delay' */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_h4[1] =
    HighClearance_model_FuncInternalData0.Delay_DSTATE_h4[2];

  /* Update for Delay: '<S248>/Delay' */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_j0[1] =
    HighClearance_model_FuncInternalData0.Delay_DSTATE_j0[2];

  /* Update for Delay: '<S249>/Delay' */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_e[1] =
    HighClearance_model_FuncInternalData0.Delay_DSTATE_e[2];

  /* Update for Delay: '<S246>/Delay' */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_f[2] = Switch_a;

  /* Update for Delay: '<S240>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_m = 0U;

  /* Update for Delay: '<S247>/Delay' */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_h4[2] = Switch_i;

  /* Update for Delay: '<S241>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_j = 0U;

  /* Update for Delay: '<S248>/Delay' */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_j0[2] = rtb_RearLeft_l;

  /* Update for Delay: '<S242>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_mr = 0U;

  /* Update for Delay: '<S249>/Delay' */
  HighClearance_model_FuncInternalData0.Delay_DSTATE_e[2] = rtb_RearRight_p;

  /* Update for Delay: '<S243>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_mg = 0U;

  /* Update for UnitDelay generated from: '<Root>/Unit Delay3' */
  HighClearance_model_FuncInternalData0.UnitDelay3_1_DSTATE =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckFL.error;

  /* Update for UnitDelay generated from: '<Root>/Unit Delay3' */
  HighClearance_model_FuncInternalData0.UnitDelay3_2_DSTATE =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckFR.error;

  /* Update for UnitDelay generated from: '<Root>/Unit Delay3' */
  HighClearance_model_FuncInternalData0.UnitDelay3_3_DSTATE =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckRL.error;

  /* Update for UnitDelay generated from: '<Root>/Unit Delay3' */
  HighClearance_model_FuncInternalData0.UnitDelay3_4_DSTATE =
    HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckRR.error;

  /* Update for Delay: '<S60>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_jm = 0U;

  /* Update for Delay: '<S61>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_n = 0U;

  /* Update for Delay: '<S62>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_p = 0U;

  /* Update for Delay: '<S63>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_j5 = 0U;

  /* Update for UnitDelay: '<S3>/Unit Delay' incorporates:
   *  Outport: '<Root>/manualOverrideEnable'
   */
  HighClearance_model_FuncInternalData0.UnitDelay_DSTATE_i =
    HighClearance_model_Y.manualOverrideEnable;
}

/* Model initialize function */
void HighClearance_model_initialize(void)
{
  /* Registration code */

  /* Initialize Internal Data Grouped For Same Function */
  (void) memset((void *)&HighClearance_model_FuncInternalData0, 0,
                sizeof(FuncInternalData0_HighClearance_model_T));

  /* external inputs */
  (void)memset(&HighClearance_model_U, 0, sizeof(ExtU_HighClearance_model_T));

  /* external outputs */
  (void) memset((void *)&HighClearance_model_Y, 0,
                sizeof(ExtY_HighClearance_model_T));

  /* InitializeConditions for Delay: '<S111>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad = 1U;

  /* InitializeConditions for Delay: '<S112>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_b = 1U;

  /* InitializeConditions for Delay: '<S113>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_e = 1U;

  /* InitializeConditions for Delay: '<S114>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_k = 1U;

  /* InitializeConditions for Delay: '<S240>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_m = 1U;

  /* InitializeConditions for Delay: '<S241>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_j = 1U;

  /* InitializeConditions for Delay: '<S242>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_mr = 1U;

  /* InitializeConditions for Delay: '<S243>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_mg = 1U;

  /* InitializeConditions for Delay: '<S60>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_jm = 1U;

  /* InitializeConditions for Delay: '<S61>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_n = 1U;

  /* InitializeConditions for Delay: '<S62>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_p = 1U;

  /* InitializeConditions for Delay: '<S63>/Delay' */
  HighClearance_model_FuncInternalData0.icLoad_j5 = 1U;

  /* SystemInitialize for Chart: '<S131>/manualOverrides' */
  HighClearance_model_FuncInternalData0.is_active_c7_HighClearance_model = 0U;
  HighClearance_model_FuncInternalData0.is_c7_HighClearance_model =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.pwm.extend.FrontLeft = 0.0F;
  HighClearance_model_FuncInternalData0.pwm.extend.FrontRight = 0.0F;
  HighClearance_model_FuncInternalData0.pwm.extend.RearLeft = 0.0F;
  HighClearance_model_FuncInternalData0.pwm.extend.RearRight = 0.0F;
  HighClearance_model_FuncInternalData0.pwm.retract.FrontLeft = 0.0F;
  HighClearance_model_FuncInternalData0.pwm.retract.FrontRight = 0.0F;
  HighClearance_model_FuncInternalData0.pwm.retract.RearLeft = 0.0F;
  HighClearance_model_FuncInternalData0.pwm.retract.RearRight = 0.0F;

  /* SystemInitialize for Outport: '<Root>/manualOverrideEnable' incorporates:
   *  Chart: '<S131>/manualOverrides'
   */
  HighClearance_model_Y.manualOverrideEnable = false;

  /* SystemInitialize for Chart: '<S211>/diagLatch' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch_j);

  /* SystemInitialize for Chart: '<S211>/diagLatch1' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_l);

  /* SystemInitialize for Chart: '<S211>/diagLatch2' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch2_p);

  /* SystemInitialize for Chart: '<S211>/diagLatch3' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch3_n);

  /* SystemInitialize for Chart: '<S211>/diagLatch4' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch4_m);

  /* SystemInitialize for Chart: '<S211>/diagLatch5' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch5_g);

  /* SystemInitialize for Chart: '<S211>/diagLatch6' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch6_g);

  /* SystemInitialize for Chart: '<S211>/diagLatch7' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch7_f);

  /* SystemInitialize for Chart: '<S23>/calibrationLogic' */
  HighClearance_model_FuncInternalData0.is_calCommanded =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.is_active =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.is_step1 =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.is_active_c =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.is_step2 =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.is_step3 =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.temporalCounter_i2 = 0U;
  HighClearance_model_FuncInternalData0.is_active_d =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.temporalCounter_i1_d = 0U;
  HighClearance_model_FuncInternalData0.is_step4 =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.is_active_c2_HighClearance_model = 0U;
  HighClearance_model_FuncInternalData0.is_c2_HighClearance_model =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.calActive = false;
  HighClearance_model_FuncInternalData0.calOkay = false;

  /* SystemInitialize for Outport: '<Root>/calOverride' incorporates:
   *  Chart: '<S23>/calibrationLogic'
   */
  HighClearance_model_Y.calOverride = false;

  /* SystemInitialize for Chart: '<S23>/calibrationLogic' */
  HighClearance_model_FuncInternalData0.exFL = 0.0F;
  HighClearance_model_FuncInternalData0.rtFL = 0.0F;
  HighClearance_model_FuncInternalData0.exFR = 0.0F;
  HighClearance_model_FuncInternalData0.rtFR = 0.0F;
  HighClearance_model_FuncInternalData0.exRL = 0.0F;
  HighClearance_model_FuncInternalData0.rtRL = 0.0F;
  HighClearance_model_FuncInternalData0.exRR = 0.0F;
  HighClearance_model_FuncInternalData0.rtRR = 0.0F;

  /* SystemInitialize for Outport: '<Root>/calState' incorporates:
   *  Chart: '<S23>/calibrationLogic'
   */
  HighClearance_model_Y.calState = 0U;

  /* SystemInitialize for Chart: '<S23>/calibrationLogic' incorporates:
   *  Outport: '<Root>/calValues'
   */
  HighClearance_model_Y.calValues.extend.FrontLeft = 0.0F;
  HighClearance_model_Y.calValues.extend.FrontRight = 0.0F;
  HighClearance_model_Y.calValues.extend.RearLeft = 0.0F;
  HighClearance_model_Y.calValues.extend.RearRight = 0.0F;
  HighClearance_model_Y.calValues.retract.FrontLeft = 0.0F;
  HighClearance_model_Y.calValues.retract.FrontRight = 0.0F;
  HighClearance_model_Y.calValues.retract.RearLeft = 0.0F;
  HighClearance_model_Y.calValues.retract.RearRight = 0.0F;

  /* SystemInitialize for Chart: '<S246>/plausiCheck' */
  HighClearance_model_plausiCheck_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_c);

  /* SystemInitialize for Chart: '<S260>/diagLatch1' */
  HighClearance_model_diagLatch1_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_cx);

  /* SystemInitialize for Chart: '<S5>/legState_FrontLeft' */
  HighClearance_model_legState_FrontLeft_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_legState_FrontLeft);

  /* SystemInitialize for Chart: '<S247>/plausiCheck' */
  HighClearance_model_plausiCheck_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_p);

  /* SystemInitialize for Chart: '<S261>/diagLatch1' */
  HighClearance_model_diagLatch1_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_k);

  /* SystemInitialize for Chart: '<S5>/legState_FrontRight' */
  HighClearance_model_legState_FrontLeft_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_legState_FrontRight);

  /* SystemInitialize for Chart: '<S248>/plausiCheck' */
  HighClearance_model_plausiCheck_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck_b);

  /* SystemInitialize for Chart: '<S262>/diagLatch1' */
  HighClearance_model_diagLatch1_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_c);

  /* SystemInitialize for Chart: '<S5>/legState_RearLeft' */
  HighClearance_model_legState_FrontLeft_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_legState_RearLeft);

  /* SystemInitialize for Chart: '<S249>/plausiCheck' */
  HighClearance_model_plausiCheck_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_plausiCheck);

  /* SystemInitialize for Chart: '<S263>/diagLatch1' */
  HighClearance_model_diagLatch1_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_m);

  /* SystemInitialize for Chart: '<S5>/legState_RearRight' */
  HighClearance_model_legState_FrontLeft_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_legState_RearRight);

  /* SystemInitialize for Chart: '<S5>/actualMachineState' */
  HighClearance_model_FuncInternalData0.is_states_g =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.temporalCounter_i1 = 0U;
  HighClearance_model_FuncInternalData0.is_active_c5_HighClearance_model = 0U;

  /* SystemInitialize for Outport: '<Root>/machineState' incorporates:
   *  Chart: '<S5>/actualMachineState'
   */
  HighClearance_model_Y.machineState = 0U;

  /* SystemInitialize for Chart: '<S1>/latch' */
  HighClearance_model_FuncInternalData0.temporalCounter_i1_h = 0U;
  HighClearance_model_FuncInternalData0.is_active_c10_HighClearance_model = 0U;
  HighClearance_model_FuncInternalData0.is_c10_HighClearance_model =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.alive = false;

  /* SystemInitialize for Chart: '<S1>/latch1' */
  HighClearance_model_FuncInternalData0.temporalCounter_i1_i = 0U;
  HighClearance_model_FuncInternalData0.is_active_c11_HighClearance_model = 0U;
  HighClearance_model_FuncInternalData0.is_c11_HighClearance_model =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.dwnBtnOk = false;

  /* SystemInitialize for Chart: '<S213>/diagLatch' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch);

  /* SystemInitialize for Chart: '<S213>/diagLatch2' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch2);

  /* SystemInitialize for Chart: '<S213>/diagLatch4' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch4);

  /* SystemInitialize for Chart: '<S213>/diagLatch6' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch6);

  /* SystemInitialize for Chart: '<S213>/diagLatch1' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1);

  /* SystemInitialize for Chart: '<S213>/diagLatch3' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch3);

  /* SystemInitialize for Chart: '<S213>/diagLatch5' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch5);

  /* SystemInitialize for Chart: '<S213>/diagLatch7' */
  HighClearance_model_diagLatch_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch7);

  /* SystemInitialize for Chart: '<S1>/TargetStateArbitration' */
  HighClearance_model_FuncInternalData0.is_states_k =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.is_active_dy =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.was_active =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.is_transitioning =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.was_transitioning =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.temporalCounter_i1_db = 0U;
  HighClearance_model_FuncInternalData0.is_active_c4_HighClearance_model = 0U;
  HighClearance_model_FuncInternalData0.prevTargetState = 0U;

  /* SystemInitialize for Outport: '<Root>/targetState' incorporates:
   *  Chart: '<S1>/TargetStateArbitration'
   */
  HighClearance_model_Y.targetState = 0U;

  /* SystemInitialize for Chart: '<S1>/TargetStateArbitration' incorporates:
   *  Outport: '<Root>/mfaLeds'
   *  Outport: '<Root>/userWarnings'
   */
  HighClearance_model_Y.userWarnings.trackWidth = false;
  HighClearance_model_Y.userWarnings.speed = false;
  HighClearance_model_Y.userWarnings.guide = false;
  HighClearance_model_Y.userWarnings.was = false;
  HighClearance_model_Y.userWarnings.fws = false;
  HighClearance_model_Y.userWarnings.fieldRoad = false;
  HighClearance_model_Y.userWarnings.cal = false;
  HighClearance_model_Y.userWarnings.parkBrake = false;
  HighClearance_model_Y.mfaLeds.upBtn = 0U;
  HighClearance_model_Y.mfaLeds.downBtn = 0U;
  HighClearance_model_Y.mfaLeds.stopBtn = 0U;
  HighClearance_model_Y.mfaLeds.isAlive = 0U;
  HighClearance_model_Y.mfaLeds.downDiag = 0U;

  /* SystemInitialize for Outport: '<Root>/okayToRaise' incorporates:
   *  Chart: '<S1>/TargetStateArbitration'
   */
  HighClearance_model_Y.okayToRaise = false;

  /* SystemInitialize for Outport: '<Root>/okayToLower' incorporates:
   *  Chart: '<S1>/TargetStateArbitration'
   */
  HighClearance_model_Y.okayToLower = false;

  /* SystemInitialize for Chart: '<S25>/calState2TargetState' */
  HighClearance_model_FuncInternalData0.is_states =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.is_active_c6_HighClearance_model = 0U;

  /* SystemInitialize for Chart: '<S69>/diagLatch1' */
  HighClearance_model_diagLatch1_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_bn);

  /* SystemInitialize for Chart: '<S70>/diagLatch1' */
  HighClearance_model_diagLatch1_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_h);

  /* SystemInitialize for Chart: '<S71>/diagLatch1' */
  HighClearance_model_diagLatch1_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_ln);

  /* SystemInitialize for Chart: '<S72>/diagLatch1' */
  HighClearance_model_diagLatch1_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_diagLatch1_b);

  /* SystemInitialize for Chart: '<S29>/heightOkayFL' */
  HighClearance_model_heightOkayFL_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayFL);

  /* SystemInitialize for Chart: '<S29>/heightOkayFR' */
  HighClearance_model_heightOkayFL_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayFR);

  /* SystemInitialize for Chart: '<S29>/heightOkayRL' */
  HighClearance_model_heightOkayFL_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayRL);

  /* SystemInitialize for Chart: '<S29>/heightOkayRR' */
  HighClearance_model_heightOkayFL_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkayRR);

  /* SystemInitialize for Chart: '<S181>/trackWidthOkay' */
  HighClearance_model_trackWidthOkay_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_trackWidthOkay_o);

  /* SystemInitialize for Chart: '<S181>/heightOkay' */
  HighClearance_model_heightOkay_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkay_b);

  /* SystemInitialize for Chart: '<S181>/enableLogic' */
  HighClearance_model_enableLogic_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_n);

  /* SystemInitialize for Chart: '<S182>/trackWidthOkay' */
  HighClearance_model_trackWidthOkay_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_trackWidthOkay_dh);

  /* SystemInitialize for Chart: '<S182>/heightOkay' */
  HighClearance_model_heightOkay_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkay_d);

  /* SystemInitialize for Chart: '<S182>/enableLogic' */
  HighClearance_model_enableLogic_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_lx);

  /* SystemInitialize for Chart: '<S183>/trackWidthOkay' */
  HighClearance_model_trackWidthOkay_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_trackWidthOkay_d);

  /* SystemInitialize for Chart: '<S183>/heightOkay' */
  HighClearance_model_heightOkay_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkay_g);

  /* SystemInitialize for Chart: '<S183>/enableLogic' */
  HighClearance_model_enableLogic_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic_l);

  /* SystemInitialize for Chart: '<S184>/trackWidthOkay' */
  HighClearance_model_trackWidthOkay_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_trackWidthOkay);

  /* SystemInitialize for Chart: '<S184>/heightOkay' */
  HighClearance_model_heightOkay_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_heightOkay);

  /* SystemInitialize for Chart: '<S184>/enableLogic' */
  HighClearance_model_enableLogic_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_enableLogic);

  /* SystemInitialize for Chart: '<S6>/TargetPosition' incorporates:
   *  Outport: '<Root>/postionTargets'
   */
  HighClearance_model_FuncInternalData0.is_positionStates =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;
  HighClearance_model_FuncInternalData0.is_active_c3_HighClearance_model = 0U;
  HighClearance_model_Y.postionTargets.FrontLeft = 0.0F;
  HighClearance_model_Y.postionTargets.FrontRight = 0.0F;
  HighClearance_model_Y.postionTargets.RearLeft = 0.0F;
  HighClearance_model_Y.postionTargets.RearRight = 0.0F;

  /* SystemInitialize for Chart: '<S3>/controlEnableLogic' */
  HighClearance_model_FuncInternalData0.is_active_c1_HighClearance_model = 0U;
  HighClearance_model_FuncInternalData0.is_c1_HighClearance_model =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;

  /* SystemInitialize for Enabled SubSystem: '<S3>/bangbangPosition_control' */
  /* SystemInitialize for Enabled SubSystem: '<S123>/bangbangPositionControl_FL' */
  HighClearance_model_bangbangPositionControl_FL_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FL);

  /* End of SystemInitialize for SubSystem: '<S123>/bangbangPositionControl_FL' */

  /* SystemInitialize for Enabled SubSystem: '<S123>/bangbangPositionControl_FR' */
  HighClearance_model_bangbangPositionControl_FL_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_FR);

  /* End of SystemInitialize for SubSystem: '<S123>/bangbangPositionControl_FR' */

  /* SystemInitialize for Enabled SubSystem: '<S123>/bangbangPositionControl_RL' */
  HighClearance_model_bangbangPositionControl_FL_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RL);

  /* End of SystemInitialize for SubSystem: '<S123>/bangbangPositionControl_RL' */

  /* SystemInitialize for Enabled SubSystem: '<S123>/bangbangPositionControl_RR' */
  HighClearance_model_bangbangPositionControl_FL_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_bangbangPositionControl_RR);

  /* End of SystemInitialize for SubSystem: '<S123>/bangbangPositionControl_RR' */
  /* End of SystemInitialize for SubSystem: '<S3>/bangbangPosition_control' */

  /* SystemInitialize for Chart: '<S129>/errorCheckFL' */
  HighClearance_model_errorCheckFL_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckFL);

  /* SystemInitialize for Chart: '<S129>/errorCheckFR' */
  HighClearance_model_errorCheckFL_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckFR);

  /* SystemInitialize for Chart: '<S129>/errorCheckRL' */
  HighClearance_model_errorCheckFL_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckRL);

  /* SystemInitialize for Chart: '<S129>/errorCheckRR' */
  HighClearance_model_errorCheckFL_Init
    (&HighClearance_model_FuncInternalData0.FuncInternalData0_errorCheckRR);

  /* SystemInitialize for Chart: '<S1>/ladderExtendLogic' */
  HighClearance_model_FuncInternalData0.is_active_c8_HighClearance_model = 0U;
  HighClearance_model_FuncInternalData0.is_c8_HighClearance_model =
    HighClearance_model_IN_NO_ACTIVE_CHILD_jn;

  /* SystemInitialize for Outport: '<Root>/extenedLadder' incorporates:
   *  Chart: '<S1>/ladderExtendLogic'
   */
  HighClearance_model_Y.extenedLadder = false;
}

/* Model terminate function */
void HighClearance_model_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
