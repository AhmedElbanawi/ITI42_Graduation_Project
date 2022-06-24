#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "util/delay.h"
#include "FLASH_DATA.h"
#include "URT.h"
#include "UDS.h"

#include "CFG_PAR.h"

static UINT64_t
Get_Last_Balance(void);

static UINT64_t
Get_Current_Balance(void);

void
CFG_PAR_Fees_Update(void){

	UINT8_t Data;
	UINT8_t Idx;

	UINT16_t Curr_Address=FEES_BASE_ADDRESS;

	UDS_Send_Positive_Response();

	for(Idx=0; Idx< FEES_NO_OF_BYTES; ++Idx){

		Data=URT_Rx_Char();

		FLASH_Data_Write(Curr_Address, Data);

		_delay_ms(1000);

		++Curr_Address;

		UDS_Send_Positive_Response();
	}

}

void
CFG_PAR_Balance_Update(void){

	UINT8_t Data=0;
	UINT8_t Idx;

	UINT16_t Curr_Address = BALANCE_BASE_ADDRESS;

	UINT64_t Balance=0;

	Balance = Get_Last_Balance();

	Balance += Get_Current_Balance();

	for (Idx = 0; Idx < BALANCE_NO_OF_BYTES; ++Idx) {

			Data = Balance>>(Idx*8);

			FLASH_Data_Write(Curr_Address, Data);

			_delay_ms(1000);

			++Curr_Address;

		}

}

static UINT64_t Get_Last_Balance(void){

	UINT64_t Data=0;
	UINT8_t Idx;

	UINT16_t Curr_Address = BALANCE_BASE_ADDRESS;

	UINT64_t Balance = 0;

	for (Idx = 0; Idx < BALANCE_NO_OF_BYTES; ++Idx) {

		Data = (UINT64_t)FLASH_Data_Read(Curr_Address);

		_delay_ms(1000);

		Balance |= (Data << (Idx*8));

		++Curr_Address;

	}

	return Balance;

}

static UINT64_t
Get_Current_Balance(void){

	UINT64_t Data=0;
	UINT8_t Idx;

	UINT64_t Balance = 0;

	UDS_Send_Positive_Response();

	for (Idx = 0; Idx < BALANCE_NO_OF_BYTES; ++Idx) {

		Data = (UINT64_t)URT_Rx_Char();

		Balance |= (Data << (Idx*8));

		UDS_Send_Positive_Response();

	}

	return Balance;
}
