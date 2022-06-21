#ifndef RECORD_H
#define RECORD_H
#define MAX_RECORD_SIZE 262

/**
 * @brief this function used to get the current record from hex file
 * 
 * @return UINT8_t* this is pointer to the current record
 */
UINT8_t*
RECORD_Get(void);

#endif
