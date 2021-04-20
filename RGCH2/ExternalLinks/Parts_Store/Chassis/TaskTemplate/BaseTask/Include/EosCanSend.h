#pragma once

#include "CanMessage.h"
#include "J1939TP.h"

sint32 sendCanMsg(CanMessage* canMsg, BusNode canPort);

EosCan_te convertBusNode(BusNode canPort);
