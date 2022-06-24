#ifndef PARSER_H
#define PARSER_H

/**
 * @brief this function used to extract data from current record and paging it 
 * 
 * @param Data this is the current page
 * @param Record this is the current record to be paged
 * @return BOOL_t return true if the application downloaded successfully
 */

BOOL_t
PARSER_Record(UINT8_t*Data, UINT8_t*Record);

#endif
