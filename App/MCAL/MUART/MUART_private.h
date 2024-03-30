
/**
 * @file    MUART_PRIVATE.h
 * @author  Hossam Eldobi (hossameldobi12@gmail.com)
 * @brief   This file contains private information related to UART module
 * @version 1.0
 * @date    2022-10-28
 *
 *
 */

/*Header file guard*/
#ifndef __MUART_PRIVATE_H__
#define __MUART_PRIVATE_H__

/***************************************************************************************************/
/*                                         UART Registers                                          */
/***************************************************************************************************/

#define MUART_UDR   (*(volatile u8_t *)(0x2C))
#define MUART_UCSRA (*(volatile u8_t *)(0x2B))
#define MUART_UCSRB (*(volatile u8_t *)(0x2A))
#define MUART_UCSRC (*(volatile u8_t *)(0x40))
#define MUART_UBRRL (*(volatile u8_t *)(0x29))
#define MUART_UBRRH (*(volatile u8_t *)(0x40))

/***************************************************************************************************/
/*                                       UART Registers' bits                                      */
/***************************************************************************************************/

/*UCSRA register bits*/
#define MUART_UCSRA_RXC_BIT (7)
#define MUART_UCSRA_TXC_BIT (6)
#define MUART_UCSRA_UDRE_BIT (5)

#endif /*__MUART_PRIVATE_H__*/