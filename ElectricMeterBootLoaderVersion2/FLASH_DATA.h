#ifndef  FLASH_DATA_H
#define FLASH_DATA_H

/**
 * @brief this function used to store data in specific address inside the internal e2prom
 * 
 * @param Address this is the current address of e2prom
 * @param Data this is the current data to be stored
 */

void
FLASH_Data_Write(UINT16_t Address, UINT8_t Data);

/**
 * @brief this function used to get data from specific address inside the internal e2prom
 * 
 * @param Address the address to be read from
 * @return UINT8_t the returend value
 */

UINT8_t
FLASH_Data_Read(UINT16_t Address);

#endif
