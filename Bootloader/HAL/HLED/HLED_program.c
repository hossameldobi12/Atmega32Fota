/**
 * @file    HLED_program.c
 * @author  Hossam Eldobi (hossameldobi12@gmail.com)
 * @brief   This file contains logical implementation related to LED module
 * @version 1.0
 * @date    2022-09-16
 * 
 * 
 */

/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MDIO_interface.h"
#include "HLED_cfg.h"
#include "HLED_interface.h"

/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/

void hled_init(u8_t au8_ledNumber)
{
    /*Switching over LED number*/
    switch(au8_ledNumber)
    {
        /*In case of LED0*/
        case LED0:

            /*Setting LED0 pin as output*/
            mdio_setPinStatus(LED0_PORT, LED0_PIN, OUTPUT);

            /*Breaking from this case*/
            break; 

        /*In case of LED1*/
        case LED1:

            /*Setting LED1 pin as output*/
            mdio_setPinStatus(LED1_PORT, LED1_PIN, OUTPUT);

            /*Breaking from this case*/
            break; 

        /*In case of LED2*/
        case LED2:

            /*Setting LED2 pin as output*/
            mdio_setPinStatus(LED2_PORT, LED2_PIN, OUTPUT);

            /*Breaking from this case*/
            break; 

        /*In case*/
        default:

            /*Breaking from this case*/
            break; 
    }  

    /*Return from this function*/
    return;
}

void hled_ledValueON(u8_t au8_ledNumber)
{
    /*Switching over LED number*/
    switch(au8_ledNumber)
    {
        /*In case of LED0*/
        case LED0:

            /*Setting LED0 pin as HIGH*/
            mdio_setPinValue(LED0_PORT, LED0_PIN, HIGH);

            /*Breaking from this case*/
            break; 

        /*In case of LED1*/
        case LED1:

            /*Setting LED1 pin as HIGH*/
            mdio_setPinValue(LED1_PORT, LED1_PIN, HIGH);

            /*Breaking from this case*/
            break; 

        /*In case of LED2*/
        case LED2:

            /*Setting LED2 pin as HIGH*/
            mdio_setPinValue(LED2_PORT, LED2_PIN, HIGH);

            /*Breaking from this case*/
            break; 

        /*In case*/
        default:

            /*Breaking from this case*/
            break; 
    }

    /*Return from this function*/
    return;
}

void hled_ledValueOFF(u8_t au8_ledNumber)
{
    /*Switching over LED number*/
    switch(au8_ledNumber)
    {
        /*In case of LED0*/
        case LED0:

            /*Setting LED0 pin as LOW*/
            mdio_setPinValue(LED0_PORT, LED0_PIN, LOW);

            /*Breaking from this case*/
            break; 

        /*In case of LED1*/
        case LED1:

            /*Setting LED1 pin as LOW*/
            mdio_setPinValue(LED1_PORT, LED1_PIN, LOW);

            /*Breaking from this case*/
            break; 

        /*In case of LED2*/
        case LED2:

            /*Setting LED2 pin as LOW*/
            mdio_setPinValue(LED2_PORT, LED2_PIN, LOW);

            /*Breaking from this case*/
            break; 

        /*In case*/
        default:

            /*Breaking from this case*/
            break; 
    }

    /*Return from this function*/
    return;
}

void hled_toggleLedValue(u8_t au8_ledNumber)
{
    /*Switching over LED number*/
    switch(au8_ledNumber)
    {
        /*In case of LED0*/
        case LED0:

            /*Toogling LED0 pin value*/
            mdio_togglePinValue(LED0_PORT, LED0_PIN);

            /*Breaking from this case*/
            break; 

        /*In case of LED1*/
        case LED1:

            /*Toogling LED1 pin value*/
            mdio_togglePinValue(LED1_PORT, LED1_PIN);

            /*Breaking from this case*/
            break; 

        /*In case of LED2*/
        case LED2:

            /*Toogling LED0 pin value*/
            mdio_togglePinValue(LED2_PORT, LED2_PIN);

            /*Breaking from this case*/
            break; 

        /*In case*/
        default:

            /*Breaking from this case*/
            break; 
    }

    /*Return from this function*/
    return;
}
