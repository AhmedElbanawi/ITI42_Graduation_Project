#ifndef BOOTLOADER_STATES_H
#define BOOTLOADER_STATES_H

/**
 * @brief this enum used to define bootloader states
 *
 */
typedef enum{

	CHECKING_APPLICATION_EXIST=0,
	CHECKING_REQUEST_EXIST,
	CHECKING_TYPE_OF_REQUEST,

	REQUEST_DATA_TRANSFER,

	JMP_TO_APPLICATION_SECTION

}BOOTLOADER_STATE_t;


extern void
BOOTLOADER_STATE_Init(void);

extern BOOTLOADER_STATE_t
BOOTLOADER_STATE_Get(void);

extern void
BOOTLOADER_STATE_Set(BOOTLOADER_STATE_t State);

#endif
