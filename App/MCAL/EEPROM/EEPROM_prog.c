/**
 * @file EEPROM_prog.h
 * @author Hossam Eldobi (hossameldobi12@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-17
 *
 */

/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/

#include "STD_MACROS.h"
#include "EEPROM_int.h"
#include <avr/io.h>

/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/

u8_t EEPROM_ui8ReadByteFromAddress(const u16_t u16_tAddress)
{
	/* Wait for completion of previous write */
	while (((EECR & (1 << EEWE)) >> EEWE) == 1)
		;
	/* Set up address register */
	EEAR = u16_tAddress;
	/* Start EEPROM read by writing EERE */
	EECR |= (1 << EERE);
	/* Return data from data register */
	return EEDR;
}

void EEPROM_vWriteByteToAddress(const u16_t uiAddress, const u8_t uiData)
{

	/* Wait for completion of previous write process*/
	while (((EECR & (1 << EEWE)) >> EEWE) == 1)
		;
	/* Set up address register */
	EEAR = uiAddress;

	/* Read the byte in the address of EEAR */
	EECR |= (1 << EERE);
	if (EEDR != uiData) // compare the value read to the value to be written
	{					// if they are not equal then write the data
		EEDR = uiData;	// move the data to EEDR

		/* Write logical one to EEMWE */
		EECR |= (1 << EEMWE);
		/* Start EEPROM write by setting EEWE */
		EECR |= (1 << EEWE);
	}
	else
	{
	}
}
