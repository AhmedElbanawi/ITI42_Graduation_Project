#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "URT.h"
#include "UDS.h"
#include "WDT.h"
#include "REQ.h"



void
REQ_Init(void){
	UART_ISR_PTR=REQ_Handler;
}

void
REQ_Handler(void){
	UINT8_t Curr_Req;
	Curr_Req=URT_Rx_Byte();

	switch(Curr_Req){

	case UDS_REQ_DATA_TRANSFER:
		GIC;
		UDS_Write_Request(UDS_REQ_DATA_TRANSFER);
		WDT_Priode(WDT_16_MS);
		WDT_Enable();
		while(1);
		break;


	default:
		break;

	}
}
