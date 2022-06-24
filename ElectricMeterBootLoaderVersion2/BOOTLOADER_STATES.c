#include "BOOTLOADER_STATES.h"

/**
 * @brief this variable used to express the bootloader current state
 *
 */
static BOOTLOADER_STATE_t Bootloader_State;

void
BOOTLOADER_STATE_Init(void){

	Bootloader_State=CHECKING_APPLICATION_EXIST;
}

BOOTLOADER_STATE_t
BOOTLOADER_STATE_Get(void){

	return Bootloader_State;
}

void
BOOTLOADER_STATE_Set(BOOTLOADER_STATE_t State){

	Bootloader_State = State;

}
