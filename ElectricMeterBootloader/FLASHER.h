#ifndef FLASHER_H
#define FLASHER_H

/**
 * @brief this function used to write the current page in the application section
 * 
 * @param page this is the current page number
 * @param buf this is the current 128 bytes
 */
void
boot_program_page (UINT32_t page, UINT8_t *buf);

#endif
