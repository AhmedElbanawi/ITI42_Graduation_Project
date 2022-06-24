#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "URT.h"
#include "RECORD.h"



static UINT8_t Record[MAX_RECORD_SIZE];

UINT8_t*
RECORD_Get(void){
	UINT8_t Character;
	UINT16_t i=0;

	do {
		Character = URT_Rx_Char();
		if (Character != ':') {
			Record[i] = Character;
			++i;
		}

	} while (Character != STOP_CHAR);

	return &Record[0];
}
