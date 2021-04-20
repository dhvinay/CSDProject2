/* File: HighClearance_model.h */

#ifndef RTW_HEADER_HighClearance_model_h_
#define RTW_HEADER_HighClearance_model_h_
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#ifndef HighClearance_model_COMMON_INCLUDES_
# define HighClearance_model_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                /* HighClearance_model_COMMON_INCLUDES_ */

/* Includes for objects with custom storage classes. */
#include "HighClearance_enum.h"

/* Macros for accessing real-time model data structure */
#ifndef DEFINED_TYPEDEF_FOR_MfaBus_
#define DEFINED_TYPEDEF_FOR_MfaBus_

typedef struct
{
  uint8_T upBtn;
  uint8_T downBtn;
  uint8_T stopBtn;
  uint8_T isAlive;
  uint8_T downDiag;
}
MfaBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CylinderBus_
#define DEFINED_TYPEDEF_FOR_CylinderBus_

typedef struct
{
  real32_T FrontLeft;
  real32_T FrontRight;
  real32_T RearLeft;
  real32_T RearRight;
}
CylinderBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_StateBus_
#define DEFINED_TYPEDEF_FOR_StateBus_

typedef struct
{
  uint8_T FrontLeft;
  uint8_T FrontRight;
  uint8_T RearLeft;
  uint8_T RearRight;
}
StateBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CoilStateBus_
#define DEFINED_TYPEDEF_FOR_CoilStateBus_

typedef struct
{
  StateBus extend;
  StateBus retract;
}
CoilStateBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ErrorBus_
#define DEFINED_TYPEDEF_FOR_ErrorBus_

typedef struct
{
  boolean_T movementErr1;
  boolean_T movementErr2;
  boolean_T noMovementErr;
}
ErrorBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ErrorsBus_
#define DEFINED_TYPEDEF_FOR_ErrorsBus_

typedef struct
{
  ErrorBus FrontLeft;
  ErrorBus FrontRight;
  ErrorBus RearLeft;
  ErrorBus RearRight;
}
ErrorsBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_UserWarningBus_
#define DEFINED_TYPEDEF_FOR_UserWarningBus_

typedef struct
{
  boolean_T trackWidth;
  boolean_T speed;
  boolean_T guide;
  boolean_T was;
  boolean_T fws;
  boolean_T fieldRoad;
  boolean_T cal;
  boolean_T parkBrake;
}
UserWarningBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CoilBus_
#define DEFINED_TYPEDEF_FOR_CoilBus_

typedef struct
{
  CylinderBus extend;
  CylinderBus retract;
}
CoilBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ControlWarningsBus_
#define DEFINED_TYPEDEF_FOR_ControlWarningsBus_

typedef struct
{
  StateBus track;
  StateBus height;
}
ControlWarningsBus;

#endif

/* Internal Data Grouped For Same Function, for system '<S5>/legState_FrontLeft' */
typedef struct
{
  real32_T prevPos;                    /* '<S5>/legState_FrontLeft' */
  uint16_T temporalCounter_i1;         /* '<S5>/legState_FrontLeft' */
  uint8_T legState;                    /* '<S5>/legState_FrontLeft' */
  uint8_T is_active_c2_HighClearance_library;/* '<S5>/legState_FrontLeft' */
  uint8_T is_c2_HighClearance_library; /* '<S5>/legState_FrontLeft' */
  uint8_T is_normalOperaion;           /* '<S5>/legState_FrontLeft' */
  uint8_T is_stopped;                  /* '<S5>/legState_FrontLeft' */
  uint8_T is_moving;                   /* '<S5>/legState_FrontLeft' */
}
FuncInternalData0_legState_FrontLeft_HighClearance_model_T;

/* Internal Data Grouped For Same Function, for system '<S29>/heightOkayFL' */
typedef struct
{
  uint8_T enable_e;                    /* '<S29>/heightOkayFL' */
  uint8_T is_active_c18_HighClearance_library;/* '<S29>/heightOkayFL' */
}
FuncInternalData0_heightOkayFL_HighClearance_model_T;

/* Internal Data Grouped For Same Function, for system '<S69>/diagLatch1' */
typedef struct
{
  uint16_T temporalCounter_i1;         /* '<S69>/diagLatch1' */
  uint8_T diagOut;                     /* '<S69>/diagLatch1' */
  uint8_T is_active_c3_HighClearance_library;/* '<S69>/diagLatch1' */
  uint8_T is_c3_HighClearance_library; /* '<S69>/diagLatch1' */
}
FuncInternalData0_diagLatch1_HighClearance_model_T;

/* Internal Data Grouped For Same Function, for system '<S123>/bangbangPositionControl_FL' */
typedef struct
{
  real32_T pwm;                        /* '<S143>/extendRetractLogic' */
  uint8_T is_active_c12_HighClearance_library;/* '<S143>/extendRetractLogic' */
  uint8_T is_c12_HighClearance_library;/* '<S143>/extendRetractLogic' */
  boolean_T bangbangPositionControl_FL_MODE;/* '<S123>/bangbangPositionControl_FL' */
}
FuncInternalData0_bangbangPositionControl_FL_HighClearance_model_T;

/* Internal Data Grouped For Same Function, for system '<S129>/errorCheckFL' */
typedef struct
{
  ErrorBus error;                      /* '<S129>/errorCheckFL' */
  real32_T pwmOut_ex;                  /* '<S129>/errorCheckFL' */
  real32_T pwmOut_rt;                  /* '<S129>/errorCheckFL' */
  real32_T pwmIn_rt_prev;              /* '<S129>/errorCheckFL' */
  real32_T pwmIn_rt_start;             /* '<S129>/errorCheckFL' */
  real32_T pwmIn_ex_prev;              /* '<S129>/errorCheckFL' */
  real32_T pwmIn_ex_start;             /* '<S129>/errorCheckFL' */
  uint32_T temporalCounter_i1;         /* '<S129>/errorCheckFL' */
  uint8_T is_active_c13_HighClearance_library;/* '<S129>/errorCheckFL' */
  uint8_T is_c13_HighClearance_library;/* '<S129>/errorCheckFL' */
  uint8_T is_states;                   /* '<S129>/errorCheckFL' */
  uint8_T is_expectedToMove;           /* '<S129>/errorCheckFL' */
  uint8_T is_notExpectedToMove;        /* '<S129>/errorCheckFL' */
  uint8_T is_positionSensorError;      /* '<S129>/errorCheckFL' */
  uint8_T is_error;                    /* '<S129>/errorCheckFL' */
  uint8_T is_errorWithNoCmdStep1;      /* '<S129>/errorCheckFL' */
  uint8_T targetState_prev;            /* '<S129>/errorCheckFL' */
  uint8_T targetState_start;           /* '<S129>/errorCheckFL' */
  boolean_T ccoReqOff;                 /* '<S129>/errorCheckFL' */
}
FuncInternalData0_errorCheckFL_HighClearance_model_T;

/* Internal Data Grouped For Same Function, for system '<S181>/enableLogic' */
typedef struct
{
  uint32_T temporalCounter_i1;         /* '<S181>/enableLogic' */
  uint8_T enable;                      /* '<S181>/enableLogic' */
  uint8_T warningTrack;                /* '<S181>/enableLogic' */
  uint8_T warningHeight;               /* '<S181>/enableLogic' */
  uint8_T is_active_c19_HighClearance_library;/* '<S181>/enableLogic' */
  uint8_T is_c19_HighClearance_library;/* '<S181>/enableLogic' */
  uint8_T is_disabled;                 /* '<S181>/enableLogic' */
  uint8_T is_transitioning;            /* '<S181>/enableLogic' */
  uint8_T is_badTrack;                 /* '<S181>/enableLogic' */
  uint8_T is_badHeight;                /* '<S181>/enableLogic' */
}
FuncInternalData0_enableLogic_HighClearance_model_T;

/* Internal Data Grouped For Same Function, for system '<S181>/heightOkay' */
typedef struct
{
  uint8_T enable_e;                    /* '<S181>/heightOkay' */
  uint8_T is_active_c18_HighClearance_library;/* '<S181>/heightOkay' */
}
FuncInternalData0_heightOkay_HighClearance_model_T;

/* Internal Data Grouped For Same Function, for system '<S181>/trackWidthOkay' */
typedef struct
{
  uint8_T enable;                      /* '<S181>/trackWidthOkay' */
  uint8_T is_active_c17_HighClearance_library;/* '<S181>/trackWidthOkay' */
}
FuncInternalData0_trackWidthOkay_HighClearance_model_T;

/* Internal Data Grouped For Same Function, for system '<S211>/diagLatch' */
typedef struct
{
  uint16_T temporalCounter_i1;         /* '<S211>/diagLatch' */
  uint8_T diagOut;                     /* '<S211>/diagLatch' */
  uint8_T is_active_c4_HighClearance_library;/* '<S211>/diagLatch' */
  uint8_T is_c4_HighClearance_library; /* '<S211>/diagLatch' */
}
FuncInternalData0_diagLatch_HighClearance_model_T;

/* Internal Data Grouped For Same Function, for system '<S246>/plausiCheck' */
typedef struct
{
  real32_T positionOut;                /* '<S246>/plausiCheck' */
  uint16_T temporalCounter_i1;         /* '<S246>/plausiCheck' */
  uint8_T plausiErr;                   /* '<S246>/plausiCheck' */
  uint8_T is_active_c5_HighClearance_library;/* '<S246>/plausiCheck' */
  uint8_T is_c5_HighClearance_library; /* '<S246>/plausiCheck' */
  uint8_T is_waitToCheck;              /* '<S246>/plausiCheck' */
  uint8_T is_checking;                 /* '<S246>/plausiCheck' */
}
FuncInternalData0_plausiCheck_HighClearance_model_T;

/* Internal Data Grouped For Same Function, for system '<Root>' */
typedef struct
{
  FuncInternalData0_diagLatch_HighClearance_model_T FuncInternalData0_diagLatch7;/* '<S213>/diagLatch7' */
  FuncInternalData0_diagLatch_HighClearance_model_T FuncInternalData0_diagLatch6;/* '<S213>/diagLatch6' */
  FuncInternalData0_diagLatch_HighClearance_model_T FuncInternalData0_diagLatch5;/* '<S213>/diagLatch5' */
  FuncInternalData0_diagLatch_HighClearance_model_T FuncInternalData0_diagLatch4;/* '<S213>/diagLatch4' */
  FuncInternalData0_diagLatch_HighClearance_model_T FuncInternalData0_diagLatch3;/* '<S213>/diagLatch3' */
  FuncInternalData0_diagLatch_HighClearance_model_T FuncInternalData0_diagLatch2;/* '<S213>/diagLatch2' */
  FuncInternalData0_diagLatch_HighClearance_model_T FuncInternalData0_diagLatch1;/* '<S213>/diagLatch1' */
  FuncInternalData0_diagLatch_HighClearance_model_T FuncInternalData0_diagLatch;/* '<S213>/diagLatch' */
  FuncInternalData0_diagLatch1_HighClearance_model_T
    FuncInternalData0_diagLatch1_m;    /* '<S263>/diagLatch1' */
  FuncInternalData0_diagLatch1_HighClearance_model_T
    FuncInternalData0_diagLatch1_c;    /* '<S262>/diagLatch1' */
  FuncInternalData0_diagLatch1_HighClearance_model_T
    FuncInternalData0_diagLatch1_k;    /* '<S261>/diagLatch1' */
  FuncInternalData0_diagLatch1_HighClearance_model_T
    FuncInternalData0_diagLatch1_cx;   /* '<S260>/diagLatch1' */
  FuncInternalData0_plausiCheck_HighClearance_model_T
    FuncInternalData0_plausiCheck;     /* '<S249>/plausiCheck' */
  FuncInternalData0_plausiCheck_HighClearance_model_T
    FuncInternalData0_plausiCheck_b;   /* '<S248>/plausiCheck' */
  FuncInternalData0_plausiCheck_HighClearance_model_T
    FuncInternalData0_plausiCheck_p;   /* '<S247>/plausiCheck' */
  FuncInternalData0_plausiCheck_HighClearance_model_T
    FuncInternalData0_plausiCheck_c;   /* '<S246>/plausiCheck' */
  FuncInternalData0_diagLatch_HighClearance_model_T
    FuncInternalData0_diagLatch7_f;    /* '<S211>/diagLatch7' */
  FuncInternalData0_diagLatch_HighClearance_model_T
    FuncInternalData0_diagLatch6_g;    /* '<S211>/diagLatch6' */
  FuncInternalData0_diagLatch_HighClearance_model_T
    FuncInternalData0_diagLatch5_g;    /* '<S211>/diagLatch5' */
  FuncInternalData0_diagLatch_HighClearance_model_T
    FuncInternalData0_diagLatch4_m;    /* '<S211>/diagLatch4' */
  FuncInternalData0_diagLatch_HighClearance_model_T
    FuncInternalData0_diagLatch3_n;    /* '<S211>/diagLatch3' */
  FuncInternalData0_diagLatch_HighClearance_model_T
    FuncInternalData0_diagLatch2_p;    /* '<S211>/diagLatch2' */
  FuncInternalData0_diagLatch_HighClearance_model_T
    FuncInternalData0_diagLatch1_l;    /* '<S211>/diagLatch1' */
  FuncInternalData0_diagLatch_HighClearance_model_T
    FuncInternalData0_diagLatch_j;     /* '<S211>/diagLatch' */
  FuncInternalData0_trackWidthOkay_HighClearance_model_T
    FuncInternalData0_trackWidthOkay;  /* '<S184>/trackWidthOkay' */
  FuncInternalData0_heightOkay_HighClearance_model_T
    FuncInternalData0_heightOkay;      /* '<S184>/heightOkay' */
  FuncInternalData0_enableLogic_HighClearance_model_T
    FuncInternalData0_enableLogic;     /* '<S184>/enableLogic' */
  FuncInternalData0_trackWidthOkay_HighClearance_model_T
    FuncInternalData0_trackWidthOkay_d;/* '<S183>/trackWidthOkay' */
  FuncInternalData0_heightOkay_HighClearance_model_T
    FuncInternalData0_heightOkay_g;    /* '<S183>/heightOkay' */
  FuncInternalData0_enableLogic_HighClearance_model_T
    FuncInternalData0_enableLogic_l;   /* '<S183>/enableLogic' */
  FuncInternalData0_trackWidthOkay_HighClearance_model_T
    FuncInternalData0_trackWidthOkay_dh;/* '<S182>/trackWidthOkay' */
  FuncInternalData0_heightOkay_HighClearance_model_T
    FuncInternalData0_heightOkay_d;    /* '<S182>/heightOkay' */
  FuncInternalData0_enableLogic_HighClearance_model_T
    FuncInternalData0_enableLogic_lx;  /* '<S182>/enableLogic' */
  FuncInternalData0_trackWidthOkay_HighClearance_model_T
    FuncInternalData0_trackWidthOkay_o;/* '<S181>/trackWidthOkay' */
  FuncInternalData0_heightOkay_HighClearance_model_T
    FuncInternalData0_heightOkay_b;    /* '<S181>/heightOkay' */
  FuncInternalData0_enableLogic_HighClearance_model_T
    FuncInternalData0_enableLogic_n;   /* '<S181>/enableLogic' */
  FuncInternalData0_errorCheckFL_HighClearance_model_T
    FuncInternalData0_errorCheckRR;    /* '<S129>/errorCheckRR' */
  FuncInternalData0_errorCheckFL_HighClearance_model_T
    FuncInternalData0_errorCheckRL;    /* '<S129>/errorCheckRL' */
  FuncInternalData0_errorCheckFL_HighClearance_model_T
    FuncInternalData0_errorCheckFR;    /* '<S129>/errorCheckFR' */
  FuncInternalData0_errorCheckFL_HighClearance_model_T
    FuncInternalData0_errorCheckFL;    /* '<S129>/errorCheckFL' */
  FuncInternalData0_bangbangPositionControl_FL_HighClearance_model_T
    FuncInternalData0_bangbangPositionControl_RR;/* '<S123>/bangbangPositionControl_RR' */
  FuncInternalData0_bangbangPositionControl_FL_HighClearance_model_T
    FuncInternalData0_bangbangPositionControl_RL;/* '<S123>/bangbangPositionControl_RL' */
  FuncInternalData0_bangbangPositionControl_FL_HighClearance_model_T
    FuncInternalData0_bangbangPositionControl_FR;/* '<S123>/bangbangPositionControl_FR' */
  FuncInternalData0_bangbangPositionControl_FL_HighClearance_model_T
    FuncInternalData0_bangbangPositionControl_FL;/* '<S123>/bangbangPositionControl_FL' */
  FuncInternalData0_diagLatch1_HighClearance_model_T
    FuncInternalData0_diagLatch1_b;    /* '<S72>/diagLatch1' */
  FuncInternalData0_diagLatch1_HighClearance_model_T
    FuncInternalData0_diagLatch1_ln;   /* '<S71>/diagLatch1' */
  FuncInternalData0_diagLatch1_HighClearance_model_T
    FuncInternalData0_diagLatch1_h;    /* '<S70>/diagLatch1' */
  FuncInternalData0_diagLatch1_HighClearance_model_T
    FuncInternalData0_diagLatch1_bn;   /* '<S69>/diagLatch1' */
  FuncInternalData0_heightOkayFL_HighClearance_model_T
    FuncInternalData0_heightOkayRR;    /* '<S29>/heightOkayRR' */
  FuncInternalData0_heightOkayFL_HighClearance_model_T
    FuncInternalData0_heightOkayRL;    /* '<S29>/heightOkayRL' */
  FuncInternalData0_heightOkayFL_HighClearance_model_T
    FuncInternalData0_heightOkayFR;    /* '<S29>/heightOkayFR' */
  FuncInternalData0_heightOkayFL_HighClearance_model_T
    FuncInternalData0_heightOkayFL;    /* '<S29>/heightOkayFL' */
  FuncInternalData0_legState_FrontLeft_HighClearance_model_T
    FuncInternalData0_legState_RearRight;/* '<S5>/legState_RearRight' */
  FuncInternalData0_legState_FrontLeft_HighClearance_model_T
    FuncInternalData0_legState_RearLeft;/* '<S5>/legState_RearLeft' */
  FuncInternalData0_legState_FrontLeft_HighClearance_model_T
    FuncInternalData0_legState_FrontRight;/* '<S5>/legState_FrontRight' */
  FuncInternalData0_legState_FrontLeft_HighClearance_model_T
    FuncInternalData0_legState_FrontLeft;/* '<S5>/legState_FrontLeft' */
  CoilBus pwm;                         /* '<S131>/manualOverrides' */
  CoilBus BusCreator;                  /* '<S147>/Bus Creator' */
  ErrorsBus
    BusConversion_InsertedFor_TargetStateArbitration_at_inport_14_BusCreator1;
  CoilStateBus
    BusConversion_InsertedFor_TargetStateArbitration_at_inport_13_BusCreator1;
  CoilStateBus
    BusConversion_InsertedFor_TargetStateArbitration_at_inport_11_BusCreator1;
  CylinderBus
    BusConversion_InsertedFor_TargetStateArbitration_at_inport_8_BusCreator1;
  ErrorBus UnitDelay3_1_DSTATE;        /* '<Root>/Unit Delay3' */
  ErrorBus UnitDelay3_2_DSTATE;        /* '<Root>/Unit Delay3' */
  ErrorBus UnitDelay3_3_DSTATE;        /* '<Root>/Unit Delay3' */
  ErrorBus UnitDelay3_4_DSTATE;        /* '<Root>/Unit Delay3' */
  real32_T Delay_DSTATE_f[3];          /* '<S246>/Delay' */
  real32_T Delay_DSTATE_h4[3];         /* '<S247>/Delay' */
  real32_T Delay_DSTATE_j0[3];         /* '<S248>/Delay' */
  real32_T Delay_DSTATE_e[3];          /* '<S249>/Delay' */
  real32_T exFL;                       /* '<S23>/calibrationLogic' */
  real32_T rtFL;                       /* '<S23>/calibrationLogic' */
  real32_T exFR;                       /* '<S23>/calibrationLogic' */
  real32_T rtFR;                       /* '<S23>/calibrationLogic' */
  real32_T exRL;                       /* '<S23>/calibrationLogic' */
  real32_T rtRL;                       /* '<S23>/calibrationLogic' */
  real32_T exRR;                       /* '<S23>/calibrationLogic' */
  real32_T rtRR;                       /* '<S23>/calibrationLogic' */
  real32_T Delay_DSTATE;               /* '<S111>/Delay' */
  real32_T Delay_DSTATE_j;             /* '<S112>/Delay' */
  real32_T Delay_DSTATE_m;             /* '<S113>/Delay' */
  real32_T Delay_DSTATE_b;             /* '<S114>/Delay' */
  real32_T Delay_DSTATE_h;             /* '<S240>/Delay' */
  real32_T Delay_DSTATE_d;             /* '<S241>/Delay' */
  real32_T Delay_DSTATE_k;             /* '<S242>/Delay' */
  real32_T Delay_DSTATE_mn;            /* '<S243>/Delay' */
  real32_T Delay_DSTATE_df;            /* '<S60>/Delay' */
  real32_T Delay_DSTATE_hr;            /* '<S61>/Delay' */
  real32_T Delay_DSTATE_i;             /* '<S62>/Delay' */
  real32_T Delay_DSTATE_g;             /* '<S63>/Delay' */
  uint32_T temporalCounter_i2;         /* '<S23>/calibrationLogic' */
  uint32_T temporalCounter_i1;         /* '<S5>/actualMachineState' */
  uint16_T override_start;             /* '<S131>/manualOverrides' */
  uint16_T temporalCounter_i1_d;       /* '<S23>/calibrationLogic' */
  uint16_T calCmd_start;               /* '<S23>/calibrationLogic' */
  uint16_T calState_start;             /* '<S25>/calState2TargetState' */
  uint16_T temporalCounter_i1_i;       /* '<S1>/latch1' */
  uint16_T temporalCounter_i1_h;       /* '<S1>/latch' */
  uint8_T icLoad;                      /* '<S111>/Delay' */
  uint8_T icLoad_b;                    /* '<S112>/Delay' */
  uint8_T icLoad_e;                    /* '<S113>/Delay' */
  uint8_T icLoad_k;                    /* '<S114>/Delay' */
  uint8_T icLoad_m;                    /* '<S240>/Delay' */
  uint8_T icLoad_j;                    /* '<S241>/Delay' */
  uint8_T icLoad_mr;                   /* '<S242>/Delay' */
  uint8_T icLoad_mg;                   /* '<S243>/Delay' */
  uint8_T icLoad_jm;                   /* '<S60>/Delay' */
  uint8_T icLoad_n;                    /* '<S61>/Delay' */
  uint8_T icLoad_p;                    /* '<S62>/Delay' */
  uint8_T icLoad_j5;                   /* '<S63>/Delay' */
  uint8_T is_active_c7_HighClearance_model;/* '<S131>/manualOverrides' */
  uint8_T is_c7_HighClearance_model;   /* '<S131>/manualOverrides' */
  uint8_T is_active_c1_HighClearance_model;/* '<S3>/controlEnableLogic' */
  uint8_T is_c1_HighClearance_model;   /* '<S3>/controlEnableLogic' */
  uint8_T is_active_c2_HighClearance_model;/* '<S23>/calibrationLogic' */
  uint8_T is_c2_HighClearance_model;   /* '<S23>/calibrationLogic' */
  uint8_T is_calCommanded;             /* '<S23>/calibrationLogic' */
  uint8_T is_active;                   /* '<S23>/calibrationLogic' */
  uint8_T is_step3;                    /* '<S23>/calibrationLogic' */
  uint8_T is_active_d;                 /* '<S23>/calibrationLogic' */
  uint8_T is_step4;                    /* '<S23>/calibrationLogic' */
  uint8_T is_step2;                    /* '<S23>/calibrationLogic' */
  uint8_T is_step1;                    /* '<S23>/calibrationLogic' */
  uint8_T is_active_c;                 /* '<S23>/calibrationLogic' */
  uint8_T is_active_c6_HighClearance_model;/* '<S25>/calState2TargetState' */
  uint8_T is_states;                   /* '<S25>/calState2TargetState' */
  uint8_T is_active_c11_HighClearance_model;/* '<S1>/latch1' */
  uint8_T is_c11_HighClearance_model;  /* '<S1>/latch1' */
  uint8_T is_active_c10_HighClearance_model;/* '<S1>/latch' */
  uint8_T is_c10_HighClearance_model;  /* '<S1>/latch' */
  uint8_T is_active_c8_HighClearance_model;/* '<S1>/ladderExtendLogic' */
  uint8_T is_c8_HighClearance_model;   /* '<S1>/ladderExtendLogic' */
  uint8_T is_active_c4_HighClearance_model;/* '<S1>/TargetStateArbitration' */
  uint8_T is_states_k;                 /* '<S1>/TargetStateArbitration' */
  uint8_T is_active_dy;                /* '<S1>/TargetStateArbitration' */
  uint8_T was_active;                  /* '<S1>/TargetStateArbitration' */
  uint8_T is_transitioning;            /* '<S1>/TargetStateArbitration' */
  uint8_T was_transitioning;           /* '<S1>/TargetStateArbitration' */
  uint8_T prevTargetState;             /* '<S1>/TargetStateArbitration' */
  uint8_T temporalCounter_i1_db;       /* '<S1>/TargetStateArbitration' */
  uint8_T stopBtn_start;               /* '<S1>/TargetStateArbitration' */
  uint8_T upBtn_start;                 /* '<S1>/TargetStateArbitration' */
  uint8_T downBtn_start;               /* '<S1>/TargetStateArbitration' */
  uint8_T is_active_c3_HighClearance_model;/* '<S6>/TargetPosition' */
  uint8_T is_positionStates;           /* '<S6>/TargetPosition' */
  uint8_T targetState_start;           /* '<S6>/TargetPosition' */
  uint8_T is_active_c5_HighClearance_model;/* '<S5>/actualMachineState' */
  uint8_T is_states_g;                 /* '<S5>/actualMachineState' */
  boolean_T calActive;                 /* '<S23>/calibrationLogic' */
  boolean_T calOkay;                   /* '<S23>/calibrationLogic' */
  boolean_T dwnBtnOk;                  /* '<S1>/latch1' */
  boolean_T alive;                     /* '<S1>/latch' */
  boolean_T UnitDelay_DSTATE;          /* '<Root>/Unit Delay' */
  boolean_T UnitDelay1_DSTATE;         /* '<Root>/Unit Delay1' */
  boolean_T UnitDelay_DSTATE_i;        /* '<S3>/Unit Delay' */
  boolean_T engRunning_start;          /* '<S1>/TargetStateArbitration' */
  boolean_T bangbangPosition_control_MODE;/* '<S3>/bangbangPosition_control' */
}
FuncInternalData0_HighClearance_model_T;

/* External inputs (root inport signals with default storage) */
typedef struct
{
  MfaBus mfa;                          /* '<Root>/mfa' */
  CylinderBus heightPosSensors_mA;     /* '<Root>/heightPosSensors_mA' */
  StateBus heightPosSensors_diag;      /* '<Root>/heightPosSensors_diag' */
  CylinderBus targetTrackWidth_mm;     /* '<Root>/targetTrackWidth_mm' */
  CylinderBus actualTrackWidth_mm;     /* '<Root>/actualTrackWidth_mm' */
  boolean_T fieldModeActive;           /* '<Root>/fieldModeActive' */
  real32_T machineSpeedKph;            /* '<Root>/machineSpeedKph' */
  real32_T medianWheelAngle;           /* '<Root>/medianWheelAngle' */
  uint16_T calCmd;                     /* '<Root>/calCmd' */
  CoilStateBus cylCoilDiags;           /* '<Root>/cylCoilDiags' */
  uint8_T ccoEnableDiag;               /* '<Root>/ccoEnableDiag' */
  boolean_T engRunning;                /* '<Root>/engRunning' */
  CoilStateBus trackCylCoilDiags;      /* '<Root>/trackCylCoilDiags' */
  uint16_T manualOverride;             /* '<Root>/manualOverride' */
  real32_T selectedGear;               /* '<Root>/selectedGear' */
  boolean_T driveCalActive;            /* '<Root>/driveCalActive' */
}
ExtU_HighClearance_model_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct
{
  CoilBus coilDutyCycle_pct;           /* '<Root>/coilDutyCycle_pct' */
  uint8_T targetState;                 /* '<Root>/targetState' */
  uint8_T machineState;                /* '<Root>/machineState' */
  StateBus legState;                   /* '<Root>/legState' */
  UserWarningBus userWarnings;         /* '<Root>/userWarnings' */
  uint16_T calState;                   /* '<Root>/calState' */
  CoilBus calValues;                   /* '<Root>/calValues' */
  CylinderBus strokeLegnthRaw_mm;      /* '<Root>/strokeLegnthRaw_mm' */
  boolean_T okayToRaise;               /* '<Root>/okayToRaise' */
  boolean_T okayToLower;               /* '<Root>/okayToLower' */
  CylinderBus postionTargets;          /* '<Root>/postionTargets' */
  boolean_T calOverride;               /* '<Root>/calOverride' */
  CylinderBus legClearnace_mm;         /* '<Root>/legClearnace_mm' */
  boolean_T controlActive;             /* '<Root>/controlActive' */
  boolean_T controlEnable;             /* '<Root>/controlEnable' */
  StateBus legEnable;                  /* '<Root>/legEnable' */
  boolean_T ccoReqOff;                 /* '<Root>/ccoReqOff' */
  ErrorsBus legErrors;                 /* '<Root>/legErrors' */
  boolean_T extenedLadder;             /* '<Root>/extenedLadder' */
  boolean_T manualOverrideEnable;      /* '<Root>/manualOverrideEnable' */
  MfaBus mfaLeds;                      /* '<Root>/mfaLeds' */
  CylinderBus strokeLegnthFlt_mm;      /* '<Root>/strokeLegnthFlt_mm' */
  ControlWarningsBus controlWarnings;  /* '<Root>/controlWarnings' */
  CoilStateBus cylCoilDiagsLatched;    /* '<Root>/cylCoilDiagsLatched' */
  StateBus heightPosDiagsLatched;      /* '<Root>/heightPosDiagsLatched' */
}
ExtY_HighClearance_model_T;

/* Parameters (default storage) */
struct P_HighClearance_model_T_
{
  real32_T bangBang_maxOut;            /* Variable: bangBang_maxOut
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
  real32_T baseClearance;              /* Variable: baseClearance
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
  real32_T calSensorTolerance;         /* Variable: calSensorTolerance
                                        * Referenced by: '<S23>/calibrationLogic'
                                        */
  real32_T calTolMultiplier;           /* Variable: calTolMultiplier
                                        * Referenced by: '<S34>/Gain'
                                        */
  real32_T ctrlWarningTime;            /* Variable: ctrlWarningTime
                                        * Referenced by:
                                        *   '<S181>/enableLogic'
                                        *   '<S182>/enableLogic'
                                        *   '<S183>/enableLogic'
                                        *   '<S184>/enableLogic'
                                        */
  real32_T defaultPositionSensor_BrkPnts[2];
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
  real32_T errorMinSpd;                /* Variable: errorMinSpd
                                        * Referenced by: '<S1>/TargetStateArbitration'
                                        */
  real32_T heightControlToleranceStart;/* Variable: heightControlToleranceStart
                                        * Referenced by:
                                        *   '<S143>/extendRetractLogic'
                                        *   '<S144>/extendRetractLogic'
                                        *   '<S145>/extendRetractLogic'
                                        *   '<S146>/extendRetractLogic'
                                        */
  real32_T heightControlToleranceStop; /* Variable: heightControlToleranceStop
                                        * Referenced by:
                                        *   '<S143>/extendRetractLogic'
                                        *   '<S144>/extendRetractLogic'
                                        *   '<S145>/extendRetractLogic'
                                        *   '<S146>/extendRetractLogic'
                                        */
  real32_T heightDiffTolerance;        /* Variable: heightDiffTolerance
                                        * Referenced by:
                                        *   '<S125>/Constant'
                                        *   '<S34>/Constant'
                                        *   '<S181>/enableLogic'
                                        *   '<S182>/enableLogic'
                                        *   '<S183>/enableLogic'
                                        *   '<S184>/enableLogic'
                                        */
  real32_T heightTolerance;            /* Variable: heightTolerance
                                        * Referenced by:
                                        *   '<S5>/legState_FrontLeft'
                                        *   '<S5>/legState_FrontRight'
                                        *   '<S5>/legState_RearLeft'
                                        *   '<S5>/legState_RearRight'
                                        */
  real32_T heightToleranceRoad;        /* Variable: heightToleranceRoad
                                        * Referenced by:
                                        *   '<S5>/legState_FrontLeft'
                                        *   '<S5>/legState_FrontRight'
                                        *   '<S5>/legState_RearLeft'
                                        *   '<S5>/legState_RearRight'
                                        */
  real32_T maxTransitionMachineSpd;    /* Variable: maxTransitionMachineSpd
                                        * Referenced by: '<S1>/TargetStateArbitration'
                                        */
  real32_T minDistanceMoving;          /* Variable: minDistanceMoving
                                        * Referenced by:
                                        *   '<S5>/legState_FrontLeft'
                                        *   '<S5>/legState_FrontRight'
                                        *   '<S5>/legState_RearLeft'
                                        *   '<S5>/legState_RearRight'
                                        */
  real32_T minTransitionMachineSpd;    /* Variable: minTransitionMachineSpd
                                        * Referenced by: '<S1>/TargetStateArbitration'
                                        */
  real32_T movementTimeOut;            /* Variable: movementTimeOut
                                        * Referenced by:
                                        *   '<S129>/errorCheckFL'
                                        *   '<S129>/errorCheckFR'
                                        *   '<S129>/errorCheckRL'
                                        *   '<S129>/errorCheckRR'
                                        */
  real32_T noMovementTimeOut;          /* Variable: noMovementTimeOut
                                        * Referenced by:
                                        *   '<S129>/errorCheckFL'
                                        *   '<S129>/errorCheckFR'
                                        *   '<S129>/errorCheckRL'
                                        *   '<S129>/errorCheckRR'
                                        */
  real32_T plausiDistance;             /* Variable: plausiDistance
                                        * Referenced by:
                                        *   '<S246>/plausiCheck'
                                        *   '<S247>/plausiCheck'
                                        *   '<S248>/plausiCheck'
                                        *   '<S249>/plausiCheck'
                                        */
  real32_T positionSensorFL_BrkPnts[2];/* Variable: positionSensorFL_BrkPnts
                                        * Referenced by:
                                        *   '<S23>/calibrationLogic'
                                        *   '<S232>/1-D Lookup Table'
                                        */
  real32_T positionSensorFR_BrkPnts[2];/* Variable: positionSensorFR_BrkPnts
                                        * Referenced by:
                                        *   '<S23>/calibrationLogic'
                                        *   '<S232>/1-D Lookup Table1'
                                        */
  real32_T positionSensorRL_BrkPnts[2];/* Variable: positionSensorRL_BrkPnts
                                        * Referenced by:
                                        *   '<S23>/calibrationLogic'
                                        *   '<S232>/1-D Lookup Table2'
                                        */
  real32_T positionSensorRR_BrkPnts[2];/* Variable: positionSensorRR_BrkPnts
                                        * Referenced by:
                                        *   '<S23>/calibrationLogic'
                                        *   '<S232>/1-D Lookup Table3'
                                        */
  real32_T positionSensor_tblData[2];  /* Variable: positionSensor_tblData
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
  real32_T sensorCutOffHz;             /* Variable: sensorCutOffHz
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
  real32_T trackWidthMax;              /* Variable: trackWidthMax
                                        * Referenced by: '<S1>/TargetStateArbitration'
                                        */
  real32_T trackWidthMin;              /* Variable: trackWidthMin
                                        * Referenced by: '<S1>/TargetStateArbitration'
                                        */
  real32_T trackWidthTolerance;        /* Variable: trackWidthTolerance
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
  uint16_T calSettlingTime;            /* Variable: calSettlingTime
                                        * Referenced by: '<S23>/calibrationLogic'
                                        */
  uint16_T calStepTimeOut;             /* Variable: calStepTimeOut
                                        * Referenced by: '<S23>/calibrationLogic'
                                        */
  uint16_T legMovingTimeout;           /* Variable: legMovingTimeout
                                        * Referenced by:
                                        *   '<S5>/legState_FrontLeft'
                                        *   '<S5>/legState_FrontRight'
                                        *   '<S5>/legState_RearLeft'
                                        *   '<S5>/legState_RearRight'
                                        */
  boolean_T useSensorFilter;           /* Variable: useSensorFilter
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
  uint8_T IOD_OK;                      /* Variable: IOD_OK
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
  uint8_T errDelay;                    /* Variable: errDelay
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
};

/* Parameters (default storage) */
typedef struct P_HighClearance_model_T_ P_HighClearance_model_T;

/* Internal Data Grouped For Same Function */
extern FuncInternalData0_HighClearance_model_T
  HighClearance_model_FuncInternalData0;

/* Block parameters (default storage) */
extern P_HighClearance_model_T HighClearance_model_P;

/* External inputs (root inport signals with default storage) */
extern ExtU_HighClearance_model_T HighClearance_model_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_HighClearance_model_T HighClearance_model_Y;

/* External data declarations for dependent source files */
extern const CoilBus HighClearance_model_rtZCoilBus;/* CoilBus ground */

/* Model entry point functions */
extern void HighClearance_model_initialize(void);
extern void HighClearance_model_step(void);
extern void HighClearance_model_terminate(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<Root>/Scope1' : Unused code path elimination
 * Block '<Root>/Scope2' : Unused code path elimination
 * Block '<S28>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S28>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S28>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S28>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S118>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S118>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S118>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S118>/Data Type Conversion3' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'HighClearance_model'
 * '<S1>'   : 'HighClearance_model/Arbitration'
 * '<S2>'   : 'HighClearance_model/Calibration'
 * '<S3>'   : 'HighClearance_model/Control'
 * '<S4>'   : 'HighClearance_model/Inputs'
 * '<S5>'   : 'HighClearance_model/Arbitration/ActualStateArbitration'
 * '<S6>'   : 'HighClearance_model/Arbitration/TargetPositionArbitration'
 * '<S7>'   : 'HighClearance_model/Arbitration/TargetStateArbitration'
 * '<S8>'   : 'HighClearance_model/Arbitration/cylinderBreakOut1'
 * '<S9>'   : 'HighClearance_model/Arbitration/cylinderBreakOut2'
 * '<S10>'  : 'HighClearance_model/Arbitration/ladderExtendLogic'
 * '<S11>'  : 'HighClearance_model/Arbitration/latch'
 * '<S12>'  : 'HighClearance_model/Arbitration/latch1'
 * '<S13>'  : 'HighClearance_model/Arbitration/ActualStateArbitration/actualMachineState'
 * '<S14>'  : 'HighClearance_model/Arbitration/ActualStateArbitration/legState_FrontLeft'
 * '<S15>'  : 'HighClearance_model/Arbitration/ActualStateArbitration/legState_FrontRight'
 * '<S16>'  : 'HighClearance_model/Arbitration/ActualStateArbitration/legState_RearLeft'
 * '<S17>'  : 'HighClearance_model/Arbitration/ActualStateArbitration/legState_RearRight'
 * '<S18>'  : 'HighClearance_model/Arbitration/ActualStateArbitration/stateBus'
 * '<S19>'  : 'HighClearance_model/Arbitration/TargetPositionArbitration/TargetPosition'
 * '<S20>'  : 'HighClearance_model/Calibration/controlLogic'
 * '<S21>'  : 'HighClearance_model/Calibration/externalErrorLogic'
 * '<S22>'  : 'HighClearance_model/Calibration/filterSignals'
 * '<S23>'  : 'HighClearance_model/Calibration/stateLogic'
 * '<S24>'  : 'HighClearance_model/Calibration/terminate'
 * '<S25>'  : 'HighClearance_model/Calibration/controlLogic/calStateConverstion'
 * '<S26>'  : 'HighClearance_model/Calibration/controlLogic/cylinderBreakOut'
 * '<S27>'  : 'HighClearance_model/Calibration/controlLogic/enableCoils'
 * '<S28>'  : 'HighClearance_model/Calibration/controlLogic/grounds'
 * '<S29>'  : 'HighClearance_model/Calibration/controlLogic/legEnables'
 * '<S30>'  : 'HighClearance_model/Calibration/controlLogic/positionFilterLogic'
 * '<S31>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance'
 * '<S32>'  : 'HighClearance_model/Calibration/controlLogic/terminate'
 * '<S33>'  : 'HighClearance_model/Calibration/controlLogic/terminate1'
 * '<S34>'  : 'HighClearance_model/Calibration/controlLogic/toleranceDuringCal'
 * '<S35>'  : 'HighClearance_model/Calibration/controlLogic/uncalibratedPositions'
 * '<S36>'  : 'HighClearance_model/Calibration/controlLogic/calStateConverstion/calState2TargetState'
 * '<S37>'  : 'HighClearance_model/Calibration/controlLogic/enableCoils/coilBreakOut'
 * '<S38>'  : 'HighClearance_model/Calibration/controlLogic/enableCoils/coilBus'
 * '<S39>'  : 'HighClearance_model/Calibration/controlLogic/enableCoils/passThroughLogic'
 * '<S40>'  : 'HighClearance_model/Calibration/controlLogic/enableCoils/passThroughLogic1'
 * '<S41>'  : 'HighClearance_model/Calibration/controlLogic/enableCoils/passThroughLogic2'
 * '<S42>'  : 'HighClearance_model/Calibration/controlLogic/enableCoils/passThroughLogic3'
 * '<S43>'  : 'HighClearance_model/Calibration/controlLogic/enableCoils/passThroughLogic4'
 * '<S44>'  : 'HighClearance_model/Calibration/controlLogic/enableCoils/passThroughLogic5'
 * '<S45>'  : 'HighClearance_model/Calibration/controlLogic/enableCoils/passThroughLogic6'
 * '<S46>'  : 'HighClearance_model/Calibration/controlLogic/enableCoils/passThroughLogic7'
 * '<S47>'  : 'HighClearance_model/Calibration/controlLogic/grounds/stateBus'
 * '<S48>'  : 'HighClearance_model/Calibration/controlLogic/legEnables/heightOkayFL'
 * '<S49>'  : 'HighClearance_model/Calibration/controlLogic/legEnables/heightOkayFR'
 * '<S50>'  : 'HighClearance_model/Calibration/controlLogic/legEnables/heightOkayRL'
 * '<S51>'  : 'HighClearance_model/Calibration/controlLogic/legEnables/heightOkayRR'
 * '<S52>'  : 'HighClearance_model/Calibration/controlLogic/legEnables/stateBus'
 * '<S53>'  : 'HighClearance_model/Calibration/controlLogic/positionFilterLogic/cylinderBreakOut'
 * '<S54>'  : 'HighClearance_model/Calibration/controlLogic/positionFilterLogic/cylinderBus'
 * '<S55>'  : 'HighClearance_model/Calibration/controlLogic/positionFilterLogic/cylinderBus2'
 * '<S56>'  : 'HighClearance_model/Calibration/controlLogic/positionFilterLogic/filterLogicFL'
 * '<S57>'  : 'HighClearance_model/Calibration/controlLogic/positionFilterLogic/filterLogicFR'
 * '<S58>'  : 'HighClearance_model/Calibration/controlLogic/positionFilterLogic/filterLogicRL'
 * '<S59>'  : 'HighClearance_model/Calibration/controlLogic/positionFilterLogic/filterLogicRR'
 * '<S60>'  : 'HighClearance_model/Calibration/controlLogic/positionFilterLogic/filterLogicFL/filter'
 * '<S61>'  : 'HighClearance_model/Calibration/controlLogic/positionFilterLogic/filterLogicFR/filter'
 * '<S62>'  : 'HighClearance_model/Calibration/controlLogic/positionFilterLogic/filterLogicRL/filter'
 * '<S63>'  : 'HighClearance_model/Calibration/controlLogic/positionFilterLogic/filterLogicRR/filter'
 * '<S64>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/cylinderBreakOut_FL'
 * '<S65>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/cylinderBreakOut_FR'
 * '<S66>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/cylinderBreakOut_RL'
 * '<S67>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/cylinderBreakOut_RR'
 * '<S68>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/cylinderBus'
 * '<S69>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/positionToClearanceFL'
 * '<S70>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/positionToClearanceFR'
 * '<S71>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/positionToClearanceRL'
 * '<S72>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/positionToClearanceRR'
 * '<S73>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/stateBreakOut_FL'
 * '<S74>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/stateBreakOut_FL1'
 * '<S75>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/stateBreakOut_FR'
 * '<S76>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/stateBreakOut_FR1'
 * '<S77>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/stateBreakOut_RL'
 * '<S78>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/stateBreakOut_RL1'
 * '<S79>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/stateBreakOut_RR'
 * '<S80>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/stateBreakOut_RR1'
 * '<S81>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/stateBus'
 * '<S82>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/positionToClearanceFL/Compare To Constant'
 * '<S83>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/positionToClearanceFL/diagLatch1'
 * '<S84>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/positionToClearanceFR/Compare To Constant'
 * '<S85>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/positionToClearanceFR/diagLatch1'
 * '<S86>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/positionToClearanceRL/Compare To Constant'
 * '<S87>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/positionToClearanceRL/diagLatch1'
 * '<S88>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/positionToClearanceRR/Compare To Constant'
 * '<S89>'  : 'HighClearance_model/Calibration/controlLogic/postionToClearance/positionToClearanceRR/diagLatch1'
 * '<S90>'  : 'HighClearance_model/Calibration/controlLogic/terminate/cylinderBreakOut1'
 * '<S91>'  : 'HighClearance_model/Calibration/controlLogic/terminate1/stateBreakOut'
 * '<S92>'  : 'HighClearance_model/Calibration/controlLogic/uncalibratedPositions/cylinderBreakOut'
 * '<S93>'  : 'HighClearance_model/Calibration/controlLogic/uncalibratedPositions/cylinderBus'
 * '<S94>'  : 'HighClearance_model/Calibration/externalErrorLogic/Compare To Constant'
 * '<S95>'  : 'HighClearance_model/Calibration/externalErrorLogic/Compare To Constant1'
 * '<S96>'  : 'HighClearance_model/Calibration/externalErrorLogic/Compare To Constant2'
 * '<S97>'  : 'HighClearance_model/Calibration/externalErrorLogic/Compare To Constant3'
 * '<S98>'  : 'HighClearance_model/Calibration/externalErrorLogic/Compare To Constant4'
 * '<S99>'  : 'HighClearance_model/Calibration/externalErrorLogic/Compare To Constant5'
 * '<S100>' : 'HighClearance_model/Calibration/externalErrorLogic/Compare To Constant6'
 * '<S101>' : 'HighClearance_model/Calibration/externalErrorLogic/Compare To Constant7'
 * '<S102>' : 'HighClearance_model/Calibration/externalErrorLogic/Compare To Constant8'
 * '<S103>' : 'HighClearance_model/Calibration/externalErrorLogic/coilStateBreakOut'
 * '<S104>' : 'HighClearance_model/Calibration/filterSignals/cylinderBreakOut'
 * '<S105>' : 'HighClearance_model/Calibration/filterSignals/cylinderBus'
 * '<S106>' : 'HighClearance_model/Calibration/filterSignals/cylinderBus2'
 * '<S107>' : 'HighClearance_model/Calibration/filterSignals/filterLogicFL'
 * '<S108>' : 'HighClearance_model/Calibration/filterSignals/filterLogicFR'
 * '<S109>' : 'HighClearance_model/Calibration/filterSignals/filterLogicRL'
 * '<S110>' : 'HighClearance_model/Calibration/filterSignals/filterLogicRR'
 * '<S111>' : 'HighClearance_model/Calibration/filterSignals/filterLogicFL/filter'
 * '<S112>' : 'HighClearance_model/Calibration/filterSignals/filterLogicFR/filter'
 * '<S113>' : 'HighClearance_model/Calibration/filterSignals/filterLogicRL/filter'
 * '<S114>' : 'HighClearance_model/Calibration/filterSignals/filterLogicRR/filter'
 * '<S115>' : 'HighClearance_model/Calibration/stateLogic/calibrationLogic'
 * '<S116>' : 'HighClearance_model/Calibration/stateLogic/coilBus'
 * '<S117>' : 'HighClearance_model/Calibration/stateLogic/cylinderBreakOut'
 * '<S118>' : 'HighClearance_model/Calibration/stateLogic/grounds'
 * '<S119>' : 'HighClearance_model/Calibration/stateLogic/stateBreakOut'
 * '<S120>' : 'HighClearance_model/Calibration/stateLogic/grounds/stateBus'
 * '<S121>' : 'HighClearance_model/Calibration/terminate/cylinderBreakOut1'
 * '<S122>' : 'HighClearance_model/Control/Outputs'
 * '<S123>' : 'HighClearance_model/Control/bangbangPosition_control'
 * '<S124>' : 'HighClearance_model/Control/controlEnableLogic'
 * '<S125>' : 'HighClearance_model/Control/controlTolerance'
 * '<S126>' : 'HighClearance_model/Control/cylinderBreakOut'
 * '<S127>' : 'HighClearance_model/Control/cylinderBreakOut1'
 * '<S128>' : 'HighClearance_model/Control/cylinderBreakOut2'
 * '<S129>' : 'HighClearance_model/Control/errorOverrides'
 * '<S130>' : 'HighClearance_model/Control/legEnablesLogic'
 * '<S131>' : 'HighClearance_model/Control/manualOverrides'
 * '<S132>' : 'HighClearance_model/Control/stateBreakOut'
 * '<S133>' : 'HighClearance_model/Control/trackCoilErrLogic'
 * '<S134>' : 'HighClearance_model/Control/Outputs/Compare To Zero'
 * '<S135>' : 'HighClearance_model/Control/Outputs/Compare To Zero1'
 * '<S136>' : 'HighClearance_model/Control/Outputs/Compare To Zero2'
 * '<S137>' : 'HighClearance_model/Control/Outputs/Compare To Zero3'
 * '<S138>' : 'HighClearance_model/Control/Outputs/Compare To Zero4'
 * '<S139>' : 'HighClearance_model/Control/Outputs/Compare To Zero5'
 * '<S140>' : 'HighClearance_model/Control/Outputs/Compare To Zero6'
 * '<S141>' : 'HighClearance_model/Control/Outputs/Compare To Zero7'
 * '<S142>' : 'HighClearance_model/Control/Outputs/coilBreakOut'
 * '<S143>' : 'HighClearance_model/Control/bangbangPosition_control/bangbangPositionControl_FL'
 * '<S144>' : 'HighClearance_model/Control/bangbangPosition_control/bangbangPositionControl_FR'
 * '<S145>' : 'HighClearance_model/Control/bangbangPosition_control/bangbangPositionControl_RL'
 * '<S146>' : 'HighClearance_model/Control/bangbangPosition_control/bangbangPositionControl_RR'
 * '<S147>' : 'HighClearance_model/Control/bangbangPosition_control/coilBus'
 * '<S148>' : 'HighClearance_model/Control/bangbangPosition_control/cylinderBreakOut_FL'
 * '<S149>' : 'HighClearance_model/Control/bangbangPosition_control/cylinderBreakOut_FL1'
 * '<S150>' : 'HighClearance_model/Control/bangbangPosition_control/cylinderBreakOut_FR'
 * '<S151>' : 'HighClearance_model/Control/bangbangPosition_control/cylinderBreakOut_FR1'
 * '<S152>' : 'HighClearance_model/Control/bangbangPosition_control/cylinderBreakOut_RL'
 * '<S153>' : 'HighClearance_model/Control/bangbangPosition_control/cylinderBreakOut_RL1'
 * '<S154>' : 'HighClearance_model/Control/bangbangPosition_control/cylinderBreakOut_RR1'
 * '<S155>' : 'HighClearance_model/Control/bangbangPosition_control/cylinderBreakOut_RR2'
 * '<S156>' : 'HighClearance_model/Control/bangbangPosition_control/extendRetractCoil'
 * '<S157>' : 'HighClearance_model/Control/bangbangPosition_control/extendRetractCoil1'
 * '<S158>' : 'HighClearance_model/Control/bangbangPosition_control/extendRetractCoil2'
 * '<S159>' : 'HighClearance_model/Control/bangbangPosition_control/extendRetractCoil3'
 * '<S160>' : 'HighClearance_model/Control/bangbangPosition_control/bangbangPositionControl_FL/extendRetractLogic'
 * '<S161>' : 'HighClearance_model/Control/bangbangPosition_control/bangbangPositionControl_FR/extendRetractLogic'
 * '<S162>' : 'HighClearance_model/Control/bangbangPosition_control/bangbangPositionControl_RL/extendRetractLogic'
 * '<S163>' : 'HighClearance_model/Control/bangbangPosition_control/bangbangPositionControl_RR/extendRetractLogic'
 * '<S164>' : 'HighClearance_model/Control/errorOverrides/coilBreakOut_FL_ex'
 * '<S165>' : 'HighClearance_model/Control/errorOverrides/coilBreakOut_FL_rt'
 * '<S166>' : 'HighClearance_model/Control/errorOverrides/coilBreakOut_FR_ex'
 * '<S167>' : 'HighClearance_model/Control/errorOverrides/coilBreakOut_FR_rt'
 * '<S168>' : 'HighClearance_model/Control/errorOverrides/coilBreakOut_RL_ex'
 * '<S169>' : 'HighClearance_model/Control/errorOverrides/coilBreakOut_RL_rt'
 * '<S170>' : 'HighClearance_model/Control/errorOverrides/coilBreakOut_RR_ex'
 * '<S171>' : 'HighClearance_model/Control/errorOverrides/coilBreakOut_RR_rt'
 * '<S172>' : 'HighClearance_model/Control/errorOverrides/coilBus'
 * '<S173>' : 'HighClearance_model/Control/errorOverrides/errorCheckFL'
 * '<S174>' : 'HighClearance_model/Control/errorOverrides/errorCheckFR'
 * '<S175>' : 'HighClearance_model/Control/errorOverrides/errorCheckRL'
 * '<S176>' : 'HighClearance_model/Control/errorOverrides/errorCheckRR'
 * '<S177>' : 'HighClearance_model/Control/errorOverrides/stateBreakOut_FL'
 * '<S178>' : 'HighClearance_model/Control/errorOverrides/stateBreakOut_FR'
 * '<S179>' : 'HighClearance_model/Control/errorOverrides/stateBreakOut_RL'
 * '<S180>' : 'HighClearance_model/Control/errorOverrides/stateBreakOut_RR'
 * '<S181>' : 'HighClearance_model/Control/legEnablesLogic/legEnableFL'
 * '<S182>' : 'HighClearance_model/Control/legEnablesLogic/legEnableFR'
 * '<S183>' : 'HighClearance_model/Control/legEnablesLogic/legEnableRL'
 * '<S184>' : 'HighClearance_model/Control/legEnablesLogic/legEnableRR'
 * '<S185>' : 'HighClearance_model/Control/legEnablesLogic/routing'
 * '<S186>' : 'HighClearance_model/Control/legEnablesLogic/stateBus'
 * '<S187>' : 'HighClearance_model/Control/legEnablesLogic/stateBus1'
 * '<S188>' : 'HighClearance_model/Control/legEnablesLogic/stateBus2'
 * '<S189>' : 'HighClearance_model/Control/legEnablesLogic/legEnableFL/enableLogic'
 * '<S190>' : 'HighClearance_model/Control/legEnablesLogic/legEnableFL/heightOkay'
 * '<S191>' : 'HighClearance_model/Control/legEnablesLogic/legEnableFL/trackWidthOkay'
 * '<S192>' : 'HighClearance_model/Control/legEnablesLogic/legEnableFR/enableLogic'
 * '<S193>' : 'HighClearance_model/Control/legEnablesLogic/legEnableFR/heightOkay'
 * '<S194>' : 'HighClearance_model/Control/legEnablesLogic/legEnableFR/trackWidthOkay'
 * '<S195>' : 'HighClearance_model/Control/legEnablesLogic/legEnableRL/enableLogic'
 * '<S196>' : 'HighClearance_model/Control/legEnablesLogic/legEnableRL/heightOkay'
 * '<S197>' : 'HighClearance_model/Control/legEnablesLogic/legEnableRL/trackWidthOkay'
 * '<S198>' : 'HighClearance_model/Control/legEnablesLogic/legEnableRR/enableLogic'
 * '<S199>' : 'HighClearance_model/Control/legEnablesLogic/legEnableRR/heightOkay'
 * '<S200>' : 'HighClearance_model/Control/legEnablesLogic/legEnableRR/trackWidthOkay'
 * '<S201>' : 'HighClearance_model/Control/manualOverrides/manualOverrides'
 * '<S202>' : 'HighClearance_model/Control/trackCoilErrLogic/Compare To Constant'
 * '<S203>' : 'HighClearance_model/Control/trackCoilErrLogic/Compare To Constant1'
 * '<S204>' : 'HighClearance_model/Control/trackCoilErrLogic/Compare To Constant2'
 * '<S205>' : 'HighClearance_model/Control/trackCoilErrLogic/Compare To Constant3'
 * '<S206>' : 'HighClearance_model/Control/trackCoilErrLogic/Compare To Constant4'
 * '<S207>' : 'HighClearance_model/Control/trackCoilErrLogic/Compare To Constant5'
 * '<S208>' : 'HighClearance_model/Control/trackCoilErrLogic/Compare To Constant6'
 * '<S209>' : 'HighClearance_model/Control/trackCoilErrLogic/Compare To Constant7'
 * '<S210>' : 'HighClearance_model/Control/trackCoilErrLogic/coilStateBreakOut'
 * '<S211>' : 'HighClearance_model/Inputs/clyCoilDiagsLatchLogic'
 * '<S212>' : 'HighClearance_model/Inputs/legPositions'
 * '<S213>' : 'HighClearance_model/Inputs/trackCylCoilDiagsLatchLogic'
 * '<S214>' : 'HighClearance_model/Inputs/clyCoilDiagsLatchLogic/coilStateBreakOut'
 * '<S215>' : 'HighClearance_model/Inputs/clyCoilDiagsLatchLogic/coilStateBus'
 * '<S216>' : 'HighClearance_model/Inputs/clyCoilDiagsLatchLogic/diagLatch'
 * '<S217>' : 'HighClearance_model/Inputs/clyCoilDiagsLatchLogic/diagLatch1'
 * '<S218>' : 'HighClearance_model/Inputs/clyCoilDiagsLatchLogic/diagLatch2'
 * '<S219>' : 'HighClearance_model/Inputs/clyCoilDiagsLatchLogic/diagLatch3'
 * '<S220>' : 'HighClearance_model/Inputs/clyCoilDiagsLatchLogic/diagLatch4'
 * '<S221>' : 'HighClearance_model/Inputs/clyCoilDiagsLatchLogic/diagLatch5'
 * '<S222>' : 'HighClearance_model/Inputs/clyCoilDiagsLatchLogic/diagLatch6'
 * '<S223>' : 'HighClearance_model/Inputs/clyCoilDiagsLatchLogic/diagLatch7'
 * '<S224>' : 'HighClearance_model/Inputs/legPositions/calibratedPositions'
 * '<S225>' : 'HighClearance_model/Inputs/legPositions/checkPlausiLogic'
 * '<S226>' : 'HighClearance_model/Inputs/legPositions/positionFilterLogic'
 * '<S227>' : 'HighClearance_model/Inputs/legPositions/positionPlausibilityCheck'
 * '<S228>' : 'HighClearance_model/Inputs/legPositions/postionToClearance'
 * '<S229>' : 'HighClearance_model/Inputs/legPositions/uncalibratedPositions'
 * '<S230>' : 'HighClearance_model/Inputs/legPositions/calibratedPositions/cylinderBreakOut'
 * '<S231>' : 'HighClearance_model/Inputs/legPositions/calibratedPositions/cylinderBus'
 * '<S232>' : 'HighClearance_model/Inputs/legPositions/calibratedPositions/lookupTables'
 * '<S233>' : 'HighClearance_model/Inputs/legPositions/positionFilterLogic/cylinderBreakOut'
 * '<S234>' : 'HighClearance_model/Inputs/legPositions/positionFilterLogic/cylinderBus'
 * '<S235>' : 'HighClearance_model/Inputs/legPositions/positionFilterLogic/cylinderBus2'
 * '<S236>' : 'HighClearance_model/Inputs/legPositions/positionFilterLogic/filterLogicFL'
 * '<S237>' : 'HighClearance_model/Inputs/legPositions/positionFilterLogic/filterLogicFR'
 * '<S238>' : 'HighClearance_model/Inputs/legPositions/positionFilterLogic/filterLogicRL'
 * '<S239>' : 'HighClearance_model/Inputs/legPositions/positionFilterLogic/filterLogicRR'
 * '<S240>' : 'HighClearance_model/Inputs/legPositions/positionFilterLogic/filterLogicFL/filter'
 * '<S241>' : 'HighClearance_model/Inputs/legPositions/positionFilterLogic/filterLogicFR/filter'
 * '<S242>' : 'HighClearance_model/Inputs/legPositions/positionFilterLogic/filterLogicRL/filter'
 * '<S243>' : 'HighClearance_model/Inputs/legPositions/positionFilterLogic/filterLogicRR/filter'
 * '<S244>' : 'HighClearance_model/Inputs/legPositions/positionPlausibilityCheck/cylinderBreakOut'
 * '<S245>' : 'HighClearance_model/Inputs/legPositions/positionPlausibilityCheck/cylinderBus'
 * '<S246>' : 'HighClearance_model/Inputs/legPositions/positionPlausibilityCheck/plausiLogic'
 * '<S247>' : 'HighClearance_model/Inputs/legPositions/positionPlausibilityCheck/plausiLogic1'
 * '<S248>' : 'HighClearance_model/Inputs/legPositions/positionPlausibilityCheck/plausiLogic2'
 * '<S249>' : 'HighClearance_model/Inputs/legPositions/positionPlausibilityCheck/plausiLogic3'
 * '<S250>' : 'HighClearance_model/Inputs/legPositions/positionPlausibilityCheck/stateBus'
 * '<S251>' : 'HighClearance_model/Inputs/legPositions/positionPlausibilityCheck/plausiLogic/plausiCheck'
 * '<S252>' : 'HighClearance_model/Inputs/legPositions/positionPlausibilityCheck/plausiLogic1/plausiCheck'
 * '<S253>' : 'HighClearance_model/Inputs/legPositions/positionPlausibilityCheck/plausiLogic2/plausiCheck'
 * '<S254>' : 'HighClearance_model/Inputs/legPositions/positionPlausibilityCheck/plausiLogic3/plausiCheck'
 * '<S255>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/cylinderBreakOut_FL'
 * '<S256>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/cylinderBreakOut_FR'
 * '<S257>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/cylinderBreakOut_RL'
 * '<S258>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/cylinderBreakOut_RR'
 * '<S259>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/cylinderBus'
 * '<S260>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/positionToClearanceFL'
 * '<S261>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/positionToClearanceFR'
 * '<S262>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/positionToClearanceRL'
 * '<S263>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/positionToClearanceRR'
 * '<S264>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/stateBreakOut_FL'
 * '<S265>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/stateBreakOut_FL1'
 * '<S266>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/stateBreakOut_FR'
 * '<S267>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/stateBreakOut_FR1'
 * '<S268>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/stateBreakOut_RL'
 * '<S269>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/stateBreakOut_RL1'
 * '<S270>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/stateBreakOut_RR'
 * '<S271>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/stateBreakOut_RR1'
 * '<S272>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/stateBus'
 * '<S273>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/positionToClearanceFL/Compare To Constant'
 * '<S274>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/positionToClearanceFL/diagLatch1'
 * '<S275>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/positionToClearanceFR/Compare To Constant'
 * '<S276>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/positionToClearanceFR/diagLatch1'
 * '<S277>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/positionToClearanceRL/Compare To Constant'
 * '<S278>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/positionToClearanceRL/diagLatch1'
 * '<S279>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/positionToClearanceRR/Compare To Constant'
 * '<S280>' : 'HighClearance_model/Inputs/legPositions/postionToClearance/positionToClearanceRR/diagLatch1'
 * '<S281>' : 'HighClearance_model/Inputs/legPositions/uncalibratedPositions/cylinderBreakOut'
 * '<S282>' : 'HighClearance_model/Inputs/legPositions/uncalibratedPositions/cylinderBus'
 * '<S283>' : 'HighClearance_model/Inputs/trackCylCoilDiagsLatchLogic/coilStateBreakOut'
 * '<S284>' : 'HighClearance_model/Inputs/trackCylCoilDiagsLatchLogic/coilStateBus'
 * '<S285>' : 'HighClearance_model/Inputs/trackCylCoilDiagsLatchLogic/diagLatch'
 * '<S286>' : 'HighClearance_model/Inputs/trackCylCoilDiagsLatchLogic/diagLatch1'
 * '<S287>' : 'HighClearance_model/Inputs/trackCylCoilDiagsLatchLogic/diagLatch2'
 * '<S288>' : 'HighClearance_model/Inputs/trackCylCoilDiagsLatchLogic/diagLatch3'
 * '<S289>' : 'HighClearance_model/Inputs/trackCylCoilDiagsLatchLogic/diagLatch4'
 * '<S290>' : 'HighClearance_model/Inputs/trackCylCoilDiagsLatchLogic/diagLatch5'
 * '<S291>' : 'HighClearance_model/Inputs/trackCylCoilDiagsLatchLogic/diagLatch6'
 * '<S292>' : 'HighClearance_model/Inputs/trackCylCoilDiagsLatchLogic/diagLatch7'
 */
#endif                                 /* RTW_HEADER_HighClearance_model_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
