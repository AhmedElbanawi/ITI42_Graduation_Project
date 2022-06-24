#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "CRC.h"

BOOL_t
CRC_Check(UINT8_t*Record)
{
	BOOL_t State = FALSE;
	UINT32_t Sum = 0;
	UINT16_t Idx = 0;
	UINT8_t Curr_Crc;

	while (Record[Idx + 2] != STOP_CHAR) {
		Sum += Asci2Hex(Record[Idx], Record[1 + Idx]);
		Idx += 2;
	}
	Sum &= 0xff;
	Curr_Crc = 0x100UL - Sum;
	if (Curr_Crc == Asci2Hex(Record[Idx], Record[1 + Idx])) {
		State = TRUE;
	}

	return State;

}


UINT8_t
Asci2Hex(UINT8_t MSB4, UINT8_t LSB4)
{
	UINT8_t Hex=0;
	if( (MSB4 >='0' && MSB4 <='9') && (LSB4 >='0' && LSB4 <='9') ){
		Hex= ( (MSB4-'0')<<4 ) | (LSB4-'0');
	}else if( (MSB4 >='0' && MSB4 <='9') ){
		if(LSB4 >='A' && LSB4 <='Z'){
			Hex= ( (MSB4-'0')<<4 ) | (LSB4-'A'+10);
		}
	}else if( (LSB4 >='0' && LSB4 <='9') ){
		if(MSB4 >='A' && MSB4 <='Z'){
			Hex= ( (MSB4-'A'+10)<<4 ) | (LSB4-'0');
		}
	}else if( (MSB4 >='A' && MSB4 <='Z') && (LSB4 >='A' && LSB4 <='Z') ){
		Hex= ( (MSB4-'A'+10)<<4 ) | (LSB4-'A'+10);
	}else {

	}
	return Hex;
}
