/**
 * @file    HLED_cfg.h
 * @author Hossam Eldobi (hossameldobi12@gmail.com)
 * @brief   This file contains configuration information related to LED module
 * @version 1.0
 * @date    2022-09-10
 * 
 * 
 */

/*Header file guard*/
#ifndef __HLED_CFG_H__
#define __HLED_CFG_H__

/***************************************************************************************************/
/*                                         Configuration macros                                    */
/***************************************************************************************************/

/*LED0 port and pin configuration*/
#define LED0_PORT      (PORTC)
#define LED0_PIN       (PIN2) 

/*LED1 port and pin configuration*/
#define LED1_PORT      (PORTC)
#define LED1_PIN       (PIN7) 

/*LED2 port and pin configuration*/
#define LED2_PORT      (PORTD)
#define LED2_PIN       (PIN3) 

#endif /*__HLED_CFG_H__*/