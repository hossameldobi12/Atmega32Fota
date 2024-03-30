/**
 * @file    Flashing_mangr.h
 * @author  Hossam Eldobi (hossameldobi12@gmail.com)
 * @brief   This file contains interfacing information related to flash module
 * @version 1.0
 * @date    2023-02-10
 *
 *
 */

/*Header file guard*/
#ifndef FLASHING_MNGR_H_
#define FLASHING_MNGR_H_

/***************************************************************************************************/
/*                                         Interfacing macros                                      */
/***************************************************************************************************/

#define VALID_APP_ADDRESS (0x00)
#define REQ_FROM_APP_ADDRESS (0x01)

#define Page_Size (128)
#define Start (0x01)
#define Exit (0x00)
#define OK (0x01)
#define NOT_OK (0x00)

/***************************************************************************************************/
/*                                        Functions' prototypes                                    */
/***************************************************************************************************/

/**
 * @brief This function is used in booting progarm page by page
 *
 * @param  u16_t page , u8_t * buf
 */
void boot_program_page(u16_t page, u8_t *buf);

/**
 * @brief This function is used in flashing APP 
 *
 * @param 
 */

void flash_app();

#endif /* FLASHING_MNGR_H_ */
