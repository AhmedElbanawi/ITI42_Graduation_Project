#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "util/delay.h"
#include "FLASH_DATA.h"
#include "URT.h"
#include "UDS.h"

#include "CFG_PAR.h"

UINT64_t
Balance_Read(void){

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

UINT64_t
Fees_Read(void){

	UINT64_t Data=0;
	UINT8_t Idx;

	UINT16_t Curr_Address = FEES_BASE_ADDRESS;

	UINT64_t Fees = 0;

	for (Idx = 0; Idx < FEES_NO_OF_BYTES; ++Idx) {

		Data = (UINT64_t)FLASH_Data_Read(Curr_Address);

		_delay_ms(1000);

		Fees |= (Data << (Idx*8));

		++Curr_Address;

	}

	return Fees;

}

void
Balance_Write(UINT64_t Balance){

	UINT8_t Idx;

	UINT16_t Curr_Address = BALANCE_BASE_ADDRESS;

	for (Idx = 0; Idx < BALANCE_NO_OF_BYTES; ++Idx) {

		FLASH_Data_Write(Curr_Address, Balance);

		_delay_ms(1000);

		Balance >>=8;

		++Curr_Address;

	}

}

void
Fees_Write(UINT64_t Fees){

	UINT8_t Idx;

	UINT16_t Curr_Address = FEES_BASE_ADDRESS;

	for (Idx = 0; Idx < FEES_NO_OF_BYTES; ++Idx) {

		FLASH_Data_Write(Curr_Address, Fees);

		_delay_ms(1000);

		Fees >>=8;

		++Curr_Address;

	}

}
