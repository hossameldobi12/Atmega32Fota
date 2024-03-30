/**
 * @file    MUART_interface.h
 * @author  Hossam Eldobi (hossameldobi12@gmail.com)
 * @brief   This file contains private information related to UART module
 * @version 1.0
 * @date    2022-10-28
 *
 *
 */


/*Header file guard*/
#ifndef __MUART_INTERFACE_H__
#define __MUART_INTERFACE_H__

/***************************************************************************************************/
/*                                         Interfacing macros                                      */
/***************************************************************************************************/

/*UART Baud rates*/
#define UART_9600_BPS (123)

/***************************************************************************************************/
/*                                        Functions' prototypes                                    */
/***************************************************************************************************/

/**
 * @brief This function is used in UART initialization with specific baud rate
 *
 * @param au16_baudRate
 */
void muart_init(u16_t au16_baudRate);

/**
 * @brief This function is responsible for sending data byte over UART
 *
 * @param au8_dataByte
 */
void muart_sendByte(u8_t au8_dataByte);

/**
 * @brief This function is responsible for receiving data byte over UART
 *
 * @param pu8_dataByte
 */
void muart_recvByte(u8_t *pu8_dataByte);

#endif /*__MUART_INTERFACE_H__*/