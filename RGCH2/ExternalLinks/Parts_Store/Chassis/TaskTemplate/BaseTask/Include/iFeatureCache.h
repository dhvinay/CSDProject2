#pragma once
extern "C"
{
#include "Eos.h"
}
#include "FeatureList.h"

typedef struct
{
	FeatureId_te FeatureID;
	FeatureStatus_te FeatureStatus;
	uint32 FeatureValue;
} Feature_ts;

class iFeatureCache
{
public:

	virtual uint8 InitOk(void) = 0;
	virtual uint32 GetTimestamp(void) = 0;
	virtual uint8 GetNumFeaturesInEeprom(void) = 0;
	virtual FeatureStatus_te GetFeatureStatus(FeatureId_te FeatureID) = 0;
	virtual uint32 GetFeatureValue(FeatureId_te FeatureID) = 0;
	virtual char* GetVin(void) = 0;
	virtual FeatureStatus_te GetVinStatus(void) = 0;
	virtual bool UpdateCache(Feature_ts* Feature, uint8 Count, uint32 Timestamp, bool vinReceived, char* vin) = 0;
};
