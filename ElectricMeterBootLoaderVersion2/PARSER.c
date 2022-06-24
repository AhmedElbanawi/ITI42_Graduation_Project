#include "STD_TYPES.h"
#include "STD_BITS.h"
#include "STD_MEMORY_MAP.h"
#include "CRC.h"
#include "FLASHER.h"
#include "util/delay.h"
#include "URT.h"

/**
 * @brief this function used to debug the current page using the terminal
 * 
 * @param Data this is the current page
 */

void
Display_Page(UINT8_t*Data);

BOOL_t
PARSER_Record(UINT8_t*Data, UINT8_t*Record)
{
	static UINT8_t Idx_Data = 0;
	static UINT16_t NO_Pages = 0;
	UINT8_t Record_Size = 0;
	UINT8_t Idx_Record = 0;
	UINT8_t j = 0;
	BOOL_t AppIsFlashed = FALSE;
	/*check if there is received record*/

	/*check if record hex file ended*/
	if (0x01 == Asci2Hex(Record[6], Record[7])) {
		/*check if there is reminder record bytes */
		if (Idx_Data > 0) {
			/*fill reminder bytes with oxff value*/
			while (Idx_Data < PAGE_SIZE) {
				Data[Idx_Data] = 0xff;
				++Idx_Data;
			}
			/*update no of pages*/
#if 0
			Display_Page(Data);
#endif


			/*Flash code*/
			boot_program_page(NO_Pages, Data);

			++NO_Pages;
		}
		AppIsFlashed = TRUE;
	} else if (0x00 == Asci2Hex(Record[6], Record[7])) {
		/*store current record size*/
		Record_Size = Asci2Hex(Record[0], Record[1]);
		/*extract data from the recorder*/
		for (Idx_Record = 0; Idx_Record < Record_Size; ++Idx_Record) {
			Data[Idx_Data] = Asci2Hex(Record[j + 8], Record[j + 9]);
			//	UDR=Data[Idx_Data];
			//	_delay_ms(1000);
			++Idx_Data;
			if (PAGE_SIZE == Idx_Data) {

#if 0
				Display_Page(Data);
#endif

				/*Flash code*/
				boot_program_page(NO_Pages, Data);
				Idx_Data = 0;
				++NO_Pages;
			}
			j += 2;
		}
	}

	return AppIsFlashed;
}

void
Display_Page(UINT8_t*Data){
	UINT8_t i;
	for (i = 0; i < PAGE_SIZE; ++i) {
		URT_Tx_Char(Data[i]);
	}
}
