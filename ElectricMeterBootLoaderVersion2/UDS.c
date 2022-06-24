#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "util/delay.h"
#include "FLASH_DATA.h"
#include "URT.h"
#include "UDS.h"
#define UDS_REQ_ADDRESS 0x01

void
UDS_Write_Request(UDS_t Request){

	switch(Request){

	case UDS_NO_REQ:
		FLASH_Data_Write(UDS_REQ_ADDRESS, UDS_NO_REQ);
		break;

	case UDS_REQ_DATA_TRANSFER:
		FLASH_Data_Write(UDS_REQ_ADDRESS, UDS_REQ_DATA_TRANSFER);
		break;

	default:
		break;

	}

	_delay_ms(1000);

}

UDS_t
UDS_Read_Request(void){

	UDS_t Request = UDS_NO_REQ;

	UINT8_t Reading;

	Reading = FLASH_Data_Read(UDS_REQ_ADDRESS);

	_delay_ms(1000);

	switch (Reading) {

	case UDS_NO_REQ:

		Request = UDS_NO_REQ;

		break;

	case UDS_REQ_DATA_TRANSFER:

		Request = UDS_REQ_DATA_TRANSFER;

		break;

	case UDS_CFG_BALANCE:

		Request = UDS_CFG_BALANCE;

		break;

	case UDS_CFG_FEES:

			Request = UDS_CFG_FEES;

			break;

	default:

		break;
	}
	return Request;
}

void
UDS_Send_Positive_Response(void){
	URT_Tx_Char(UDS_POSITIVE_RESPONSE);
}

void
UDS_Send_Negative_Response(void){
	URT_Tx_Char(UDS_NEGATIVE_RESPONSE);
}
