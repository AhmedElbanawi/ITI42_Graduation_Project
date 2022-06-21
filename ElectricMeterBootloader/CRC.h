#ifndef CRC_H
#define CRC_H

/**
 * @brief this function used to check if record is correct or not
 * 
 * @param Record this is the current record
 * @return BOOL_t 
 */

BOOL_t
CRC_Check(UINT8_t*Record);

/**
 * @brief this function used to convert asci code to hex
 * 
 * @param MSB4 this is most significant 4 bits
 * @param LSB4 this is least significant 4 bits
 * @return UINT8_t return the hex number
 */

UINT8_t
Asci2Hex(UINT8_t MSB4, UINT8_t LSB4);

#endif
