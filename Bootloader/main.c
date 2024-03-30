
#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MDIO_interface.h"
#include "HLED_interface.h"
#include "MUART_interface.h"
#include "EEPROM_int.h"
#include "Flashing_Mngr.h"
#include <util/delay.h>

u8_t validAPP_Val = 0;
u8_t reqFromApp_Val = 0;
int main()
{
    validAPP_Val = EEPROM_ui8ReadByteFromAddress(VALID_APP_ADDRESS);
    reqFromApp_Val = EEPROM_ui8ReadByteFromAddress(REQ_FROM_APP_ADDRESS);
    hled_init(LED0);
    if ((validAPP_Val != 1) | (reqFromApp_Val == 1))
    {

        mdio_setPinStatus(PORTD, PIN0, INPUT_FLOAT);
        mdio_setPinStatus(PORTD, PIN1, OUTPUT);
        muart_init(UART_9600_BPS);
        hled_ledValueON(LED0);

        while (1)
        {
            if (reqFromApp_Val == 1)
            {

                reqFromApp_Val = 0;
                EEPROM_vWriteByteToAddress(REQ_FROM_APP_ADDRESS, 0);
                muart_sendByte(OK);
            }
            flash_app();
        }
    }
    else
    {
        asm("jmp 0");
    }
    return 0;
}