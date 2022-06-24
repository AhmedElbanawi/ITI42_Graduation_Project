#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "URT.h"
#include "UDS.h"
#include "WDT.h"
#include "REQ.h"

static void
REQ_Update(UINT8_t Request);

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

		REQ_Update(UDS_REQ_DATA_TRANSFER);

		break;

	case UDS_CFG_FEES:

		REQ_Update(UDS_CFG_FEES);

		break;

	case UDS_CFG_BALANCE:

		REQ_Update(UDS_CFG_BALANCE);

		break;

	default:

		break;

	}
}

static void
REQ_Update(UDS_t Request){

	GIC;

	UDS_Write_Request(Request);

	WDT_Priode(WDT_16_MS);

	WDT_Enable();

	while (1);

}
