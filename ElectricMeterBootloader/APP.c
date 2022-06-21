#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "util/delay.h"
#include "FLASH_DATA.h"
#include "RECORD.h"
#include "CRC.h"
#include "PARSER.h"
#include "UDS.h"
#include "URT.h"
#include "APP.h"
#define APP_UPDATE_ADDRESS 0x00


/**
 * @brief this enum used to express application downloading states
 * 
 */

typedef enum{

	RECEVING_RECORD=0,
	CHECKING_RECORD_CRC,
	STORING_RECORD_WITH_PAGING,
	APP_DOWNLOADING_ENDED

}APP_STATE_DOWNLOAD_t;

/**
 * @brief this function used to debug the current record using terminal
 * 
 */

void
Display_Record(void);

static APP_STATE_DOWNLOAD_t App_State_Download=RECEVING_RECORD;

static UINT8_t*Current_Record=NULL_PTR;

static UINT8_t App[PAGE_SIZE];

void
APP_Write_State(APP_STATE_t State){

	switch(State){

	case APP_NOT_EXIST:
		FLASH_Data_Write(APP_UPDATE_ADDRESS, APP_NOT_EXIST);
		break;

	case APP_EXIST:
		FLASH_Data_Write(APP_UPDATE_ADDRESS, APP_EXIST);
		break;

	default:
		break;

	}

	_delay_ms(1000);

}

APP_STATE_t
APP_Read_State(void){

	APP_STATE_t State = APP_NOT_EXIST;

	UINT8_t Reading;

	Reading = FLASH_Data_Read(APP_UPDATE_ADDRESS);

	_delay_ms(1000);

	switch (Reading) {

	case APP_NOT_EXIST:

		State = APP_NOT_EXIST;

		break;

	case APP_EXIST:

		State = APP_EXIST;

		break;

	default:

		break;
	}
	return State;
}

BOOL_t
APP_Rx(void){

	BOOL_t Finished=FALSE;

	switch(App_State_Download){

	case RECEVING_RECORD:
		Current_Record=RECORD_Get();
		App_State_Download=CHECKING_RECORD_CRC;
		//Display_Record();
		break;

	case CHECKING_RECORD_CRC:
		if(TRUE==CRC_Check(Current_Record)){
			App_State_Download=STORING_RECORD_WITH_PAGING;
		}else {
			App_State_Download=RECEVING_RECORD;
			UDS_Send_Negative_Response();
		}
			break;

	case STORING_RECORD_WITH_PAGING:
		if(TRUE==PARSER_Record(App, Current_Record)){
			App_State_Download=APP_DOWNLOADING_ENDED;
		}else {
			App_State_Download=RECEVING_RECORD;
			UDS_Send_Positive_Response();
		}
			break;

	case APP_DOWNLOADING_ENDED:
		Finished=TRUE;
		UDS_Send_Positive_Response();
			break;

	}
	return Finished;
}


void
Display_Record(void){
	UINT8_t i=0;

	if(Current_Record!=NULL_PTR){

		do {
			URT_Tx_Char(Current_Record[i]);
			++i;
		} while (Current_Record[i] != STOP_CHAR);
		URT_Tx_Char(Current_Record[i]);
	}
}
