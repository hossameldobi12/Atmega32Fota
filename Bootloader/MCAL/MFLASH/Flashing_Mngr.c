/**
 * @file    Flashing_mangr.c
 * @author  Hossam Eldobi (hossameldobi12@gmail.com)
 * @brief   This file contains interfacing information related to flash module
 * @version 1.0
 * @date    2023-02-10
 *
 *
 */

/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/

#include "LSTD_TYPES.h"
#include "Flashing_Mngr.h"
#include "MUART_interface.h"
#include "HLED_interface.h"
#include "EEPROM_int.h"
#include <avr/boot.h>
#include <util/delay.h>

/***************************************************************************************************/
/*                                        Important variables                                      */
/***************************************************************************************************/

u8_t page_number = 0;
u8_t CheckFlag = 1;
static u8_t packet[128] = {0};
static u8_t RecivedData = 0;

/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/

void boot_program_page(u16_t page, u8_t *buf)
{
	u16_t i;
	u8_t sreg;
	u32_t address;
	u16_t word;

	// Disable interrupts.
	sreg = SREG;
	asm("cli");
	address = page * SPM_PAGESIZE;

	boot_page_erase_safe(address);
	boot_spm_busy_wait();

	for (i = 0; i < SPM_PAGESIZE; i += 2)
	{
		// Set up little Endian word.
		word = *buf++;
		word += (*buf++) << 8;

		boot_page_fill_safe(address + i, word);
	}

	boot_page_write_safe(address); // Store buffer in flash page.

	// Reenable RWW-section again. We need this if we want to jump back
	// to the application after bootloading.

	boot_rww_enable_safe();

	// Re-enable interrupts (if they were ever enabled).

	SREG = sreg;
}

void flash_app()
{
	static u8_t counter = 0;

	muart_recvByte(&RecivedData);
	if (Start == RecivedData && CheckFlag == 1)
	{
		muart_sendByte(OK);
		CheckFlag = 0;
	}
	else if (Exit == RecivedData && CheckFlag == 1)
	{
		hled_ledValueOFF(LED0);
		EEPROM_vWriteByteToAddress(VALID_APP_ADDRESS, 1);
		asm("jmp 0");
	}
	else
	{
		packet[counter] = RecivedData;
		counter++;
		while (counter < 128)
		{
			muart_recvByte(&packet[counter]);
			counter++;
		}
		boot_program_page(page_number, &packet[0]);
		page_number++;
		counter = 0;
		CheckFlag = 1;
		muart_sendByte(OK);
	}
}
