#ifndef UDS_H
#define UDS_H

/**
 * @brief this enum used to express UDS requests
 * 
 */

typedef enum{

	UDS_NO_REQ=0xf8,

	UDS_REQ_DATA_TRANSFER=0x30,

	UDS_POSITIVE_RESPONSE='+',

	UDS_NEGATIVE_RESPONSE='-',

	UDS_CFG_FEES =0x09,

	UDS_CFG_BALANCE =0xB0

}UDS_t;

/**
 * @brief this function used to read the current UDS request from internal e2prom
 * 
 * @return UDS_t 
 */

UDS_t
UDS_Read_Request(void);

/**
 * @brief this function used to store the current UDS request inside internal e2prom
 * 
 * @param Request 
 */

void
UDS_Write_Request(UDS_t Request);

#endif
