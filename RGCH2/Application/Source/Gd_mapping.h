/**
 *  @file   Gd_mapping.h
 */

#ifndef __GD_MAPPING_H
    #define __GD_MAPPING_H

/* Set Module GD-Nodes */

//Map here the GD-node name of the separate modules to the GD-node ID coming from the central node list, which is located in XXX_gd_ln.h
//High Clearance
#define GD_LN_HC_DRIVE						GD_LN_DRIVE
#define GD_LN_HC_MFA						GD_LN_MFA




/********** GD-Mapping ***********/

//Map here the GD-indices used in the module vs. the GD-indices coming from other GD-nodes, which are listed in XXXX_gd_id.h
//Only external GD's (coming from other nodes and not delivered by the module itself) have to be mapped
//HighClearance
#define HC_GD_ID_MFA_UP_BUTTON				GD_ID_MFA_C3
#define HC_GD_ID_MFA_UP_BUTTON_LED			GD_ID_MFA_C3_LED
#define HC_GD_ID_MFA_DOWN_BUTTON			GD_ID_MFA_C4
#define HC_GD_ID_MFA_DOWN_BUTTON_LED		GD_ID_MFA_C4_LED
#define HC_GD_ID_MFA_STOP_BUTTON			GD_ID_MFA_A11
#define HC_GD_ID_EOI						GD_ID_Engine_Operating_State
#define HC_GD_ID_ROAD_FIELD_MODE			GD_ID_DRIVE_FIELD_STREET_STATE
#define HC_GD_ID_TRACKWIDTH_FL				GD_ID_TA_FL_POSITION
#define HC_GD_ID_TRACKWIDTH_FR				GD_ID_TA_FR_POSITION
#define HC_GD_ID_TRACKWIDTH_RL				GD_ID_TA_RL_POSITION
#define HC_GD_ID_TRACKWIDTH_RR				GD_ID_TA_RR_POSITION
#define HC_GD_ID_TRACKWIDTH_TARGET_FL		GD_ID_TA_TARGET_TRACKWIDTH_FL
#define HC_GD_ID_TRACKWIDTH_TARGET_FR		GD_ID_TA_TARGET_TRACKWIDTH_FR
#define HC_GD_ID_TRACKWIDTH_TARGET_RL		GD_ID_TA_TARGET_TRACKWIDTH_RL
#define HC_GD_ID_TRACKWIDTH_TARGET_RR		GD_ID_TA_TARGET_TRACKWIDTH_RR
#define HC_GD_ID_TRACK_EXTEND_FL			GD_ID_TA_Actual_Front_Out
#define HC_GD_ID_TRACK_EXTEND_FR			GD_ID_TA_Actual_Front_Out_R
#define HC_GD_ID_TRACK_EXTEND_RL			GD_ID_TA_Actual_Rear_Out 
#define HC_GD_ID_TRACK_EXTEND_RR			GD_ID_TA_Actual_Rear_Out_R 
#define HC_GD_ID_TRACK_RETRACT_FL			GD_ID_TA_Actual_Front_In 
#define HC_GD_ID_TRACK_RETRACT_FR			GD_ID_TA_Actual_Front_In_R 
#define HC_GD_ID_TRACK_RETRACT_RL			GD_ID_TA_Actual_Rear_In	 
#define HC_GD_ID_TRACK_RETRACT_RR			GD_ID_TA_Actual_Rear_In_R	 
#define HC_GD_ID_MACHINE_SPEED				GD_ID_DRIVE_WHEEL_BASED_MACHINE_SPEED
#define HC_GD_ID_WHEEL_ANGLE				GD_ID_SCT_WAS_MEDIAN_ANGLE
#define HC_GD_ID_SELECTED_GEAR				GD_ID_DRIVE_SELECTED_GEAR
#define HC_GD_ID_HYD_CCO_ENABLE				GD_ID_DRIVE_HYDRAULICS_ENABLE
#define HC_GD_ID_HYD_CCO_REQ_OFF			GD_ID_DRIVE_REQUEST_HYD_ENABLE_OFF
#define HC_GD_ID_EMM_SIGNAL_HC_ERROR_W		GD_ID_EMM_SIGNAL_LN54_ERROR_W
#define HC_GD_ID_DRIVE_HYDRO_CAL_STATE		GD_ID_DRIVE_HYDRO_CAL_STATE
/*********************************/

#endif	//__GD_MAPPING_H
