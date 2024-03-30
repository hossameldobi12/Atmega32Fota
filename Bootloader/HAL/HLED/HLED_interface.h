/**
 * @file    HLED_interface.h
 * @author  Hossam Eldobi (hossameldobi12@gmail.com)
 * @brief   This file contains interfacing information related to LED module
 * @version 1.0
 * @date    2022-09-10
 * 
 * 
 */

/*Header file guard*/
#ifndef __HLED_INTERFACE_H__
#define __HLED_INTERFACE_H__

/***************************************************************************************************/
/*                                         Interfacing macros                                      */
/***************************************************************************************************/

/*System LEDs*/
#define LED0        (0)
#define LED1        (1)
#define LED2        (2)

/***************************************************************************************************/
/*                                        Functions' prototypes                                    */
/***************************************************************************************************/

/**
 * @brief This function is responsible for setting a specific LED pin to output
 * 
 * @param au8_ledNumber 
 */
void hled_init(u8_t au8_ledNumber);

/**
 * @brief This function is responsible for setting a specific LED status to ON
 * 
 * @param au8_ledNumber 
 */
void hled_ledValueON(u8_t au8_ledNumber);

/**
 * @brief This function is responsible for setting a specific LED status to OFF
 * 
 * @param au8_ledNumber 
 */
void hled_ledValueOFF(u8_t au8_ledNumber);

/**
 * @brief This function is responsible for toggling a specific LED status (ON -> OFF / OFF -> ON)
 * 
 * @param au8_ledNumber 
 */
void hled_toggleLedValue(u8_t au8_ledNumber);

#endif /*__HLED_INTERFACE_H__*/