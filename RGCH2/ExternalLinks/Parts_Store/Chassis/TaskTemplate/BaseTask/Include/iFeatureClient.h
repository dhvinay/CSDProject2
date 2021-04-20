#pragma once
#include "FeatureList.h"

extern "C"
{
#include "Eos.h"
}

typedef struct
{
	FCState_te fmcState; //Current state in stateflow diagram here: https://alm.agcocorp.com/polarion/redirect/project/T1_17CH_ST4/wiki/T2-21/EXT%20Feature%20Management?selection=TT-2873
	FCErrorState_te errorState; //Indicates current error state if any have occurred
	uint32 cacheTimestamp; //Timestamp read from caceh on startup
	uint8 numFeaturesRequested; //The hardcoded number of features requested by the task
	uint8 warningBitfield; //Different warnings such as checksum error, invalid timestamp or number of features, etc
} FeatureManagerClientInfo1_ts;

typedef struct
{
	uint32 acmTimestampReceived; //Timestamp received from the ACM
	uint8 numberOfFeaturesUpdated; //Number of features updated with a new value or status from the ACM
} FeatureManagerClientInfo2_ts;

class iFeatureClient
{
public:

	virtual FeatureStatus_te getFeatureStatus( FeatureId_te featureId ) = 0;
	virtual uint32 getFeatureValue( FeatureId_te featureId ) = 0;
	virtual char* getVin(void) = 0;
	virtual FeatureStatus_te getVinStatus(void) = 0; 
	virtual void setEepromCacheChangeStatus(void) = 0;
	virtual FeatureManagerClientInfo1_ts getFMCInfo_1(void) = 0;
	virtual FeatureManagerClientInfo2_ts getFMCInfo_2(void) = 0;
	virtual uint32 getTimestamp(void) = 0;
};
