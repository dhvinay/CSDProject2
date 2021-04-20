extern "C"
{
#include "CanMessage.h"
#include "eosCan.h"
}

EosCan_te convertBusNode(BusNode canPort)
{
	EosCan_te port;
	switch (canPort)
	{
		case CANBUS_1: 
		{
			port = CAN_1;
			break;
		}
		case CANBUS_2:
		{
			port = CAN_2;
			break;
		}
		case CANBUS_3: 
		{
			port = CAN_3;
			break;
		}
		case CANBUS_4: 
		{
			port = CAN_4;
			break;
		}
		case CANBUS_Last: 
		{
			port = CAN_Last;
			break;
		}
		default: port = CAN_1; // If BusNode not outlined, change port to CAN_1
	}
	return port;
}

sint32 sendCanMsg(CanMessage* canMsg, BusNode canPort)
{
	EosCan_te port = convertBusNode(canPort);

	return EosCanSendExt_s32(port, canMsg->id_u32, canMsg->data_u8, canMsg->dlc_u16);
}