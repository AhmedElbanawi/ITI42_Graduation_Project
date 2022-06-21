#include "STD_TYPES.h"
#include "STD_BITS.h"
#include "STD_MEMORY_MAP.h"
#include "FLASH_DATA.h"
void
FLASH_Data_Write(UINT16_t Address, UINT8_t Data)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEMWE))
	;
	/* Set up address and data registers */
	EEAR = Address;
	EEDR = Data;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}
UINT8_t
FLASH_Data_Read(UINT16_t Address)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEMWE))
	;
	/* Set up address register */
	EEAR = Address;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}
