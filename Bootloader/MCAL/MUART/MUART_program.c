/**
 * @file    MUART_program.c
 * @author  Hossam Eldobi (hossameldobi12@gmail.com)
 * @brief   This file contains logical implementation related to UART module
 * @version 1.0
 * @date    2022-10-28
 *
 *
 */

/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MUART_private.h"
#include "MUART_interface.h"

/***************************************************************************************************/
/*                                        Important macros                                         */
/***************************************************************************************************/

/*UART operation macros*/
#define ENABLE_TX_RX_RXINT (0x98)
#define SET_CHARACTER_SIZE_8_BITS (0x86)
#define SHIFT_BY_8 (8)
#define UBRRH_SELECT (0x7F)
#define REGISTER_IS_EMPTY (1)
#define NEW_DATA_RECEIVED (1)

/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/

void muart_init(u16_t au16_baudRate)
{
    /*Enable Rx and Tx pins*/
    MUART_UCSRB = ENABLE_TX_RX_RXINT;

    /*Set the character size to 1 byte*/
    MUART_UCSRC = SET_CHARACTER_SIZE_8_BITS;

    /*Setting the baud rate value into the low register*/
    MUART_UBRRL = (u8_t)au16_baudRate;

    /*Setting the baud rate value into the high register*/
    MUART_UBRRH = (u8_t)((au16_baudRate >> SHIFT_BY_8) & (UBRRH_SELECT));

    /*Return from this function*/
    return;
}

void muart_sendByte(u8_t au8_dataByte)
{
    /*Checking if the UDR register is empty to send a new data*/
    if (GET_BIT(MUART_UCSRA, MUART_UCSRA_UDRE_BIT) == REGISTER_IS_EMPTY)
    {
        /*Setting the data byte to be transmitted*/
        MUART_UDR = au8_dataByte;

        /*Waiting until the communication is done*/
        while (!GET_BIT(MUART_UCSRA, MUART_UCSRA_TXC_BIT))
            ;

        /*Clearing the Tx flag*/
        SET_BIT(MUART_UCSRA, MUART_UCSRA_TXC_BIT);
    }
    else
    {
        /*Do nothing*/
    }

    /*Return from this function*/
    return;
}

void muart_recvByte(u8_t *pu8_dataByte)
{
    /*Checking if there's a new data received or not*/
    while (GET_BIT(MUART_UCSRA, MUART_UCSRA_RXC_BIT) == 0x00)
    {
    }
    *pu8_dataByte = MUART_UDR;

    /*Return from this function*/
    return;
}
