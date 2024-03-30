/**
 * @file EEPROM_int.h
 * @author Hossam Eldobi (hossameldobi12@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-17
 *
 */

#ifndef _EEPROM_INT_H
#define _EEPROM_INT_H


/**
 * @brief This function is responsible reading byte from Internal EEPROM
 *
 * @param u16_tAddress
 */
u8_t EEPROM_ui8ReadByteFromAddress(const u16_t u16_tAddress);



/**
 * @brief This function is responsible for writing byte to Internal EEPROM
 *
 * @param u16_tAddress
 * @param u8_tData
 * 
 */
void EEPROM_vWriteByteToAddress(const u16_t u16_tAddress, const u8_t u8_tData);

#endif
