#include "STD_MACROS.h"
#include "DIO.h"
#include "GIE_int.h"
#include "MUART_interface.h"
#include "EEPROM_int.h"
#include "util/delay.h"

#define REQ_FROM_APP_ADDRESS (0x01)

int main()
{
    DIO_vsetPINDir('D', 0, 0);
    DIO_vsetPINDir('D', 1, 1);
    muart_init(UART_9600_BPS);
    DIO_vsetPINDir('D', 3, 1);
    DIO_write('D', 3, 1);
#if use_interrupt == 1
    GIE_enable();
#endif
    while (1)
    {
#if use_interrupt == 0
        muart_RecivedStart();
#endif
        if (Start == func())
        {
            DIO_write('D', 3, 0);
            EEPROM_vWriteByteToAddress(REQ_FROM_APP_ADDRESS, 1);
            asm("jmp 0x7000");
        }
    }

    return 0;
}