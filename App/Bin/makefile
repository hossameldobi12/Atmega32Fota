#File name: makefile
#Purpose:   Contains the compiler commands to have the final executable image (.hex)
#Author:    Ahmed Ashraf
#Date:      02-12-2022
#Version:   v2.4

# Include directories
INC_DIR := -I../LIB
INC_DIR += -I../MCAL/MDIO
INC_DIR += -I../MCAL/MUART
INC_DIR += -I../MCAL/GIE
INC_DIR += -I../MCAL/EEPROM



# C source files
C_FILES := ../main.c
C_FILES += ../MCAL/MDIO/DIO.c
C_FILES += ../MCAL/MUART/MUART_program.c
C_FILES += ../MCAL/GIE/GIE_prog.c
C_FILES += ../MCAL/EEPROM/EEPROM_prog.c



# Object files
OBJ_FILES := main.o
OBJ_FILES += DIO.o
OBJ_FILES += MUART_program.o
OBJ_FILES += GIE_prog.o
OBJ_FILES += EEPROM_prog.o



# AVR Controller configuration
CONTROLLER := atmega32
CONTROLLER_CLK := 16000000

# Compiler configuration variables
CC := avr-gcc
COMPILER_OPTIONS := -mmcu=$(CONTROLLER) -DF_CPU=$(CONTROLLER_CLK) -Wall -Os $(INC_DIR)

# Elf and Hex files
ELF_FILE := main.elf
HEX_FILE := main.hex

############################################ Rules ############################################

all: $(C_FILES) clean main.hex

main.elf:
	@echo "Compiling C files......."
	@$(CC) $(COMPILER_OPTIONS) -c $(C_FILES)
	@echo "Linking C files......."
	@$(CC) -Wl,-Map=main.map -mmcu=$(CONTROLLER) $(OBJ_FILES) -o main.elf

main.hex: main.elf
	@echo "Generating Hex file......."
	@avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature main.elf -O ihex main.hex

flash: $(HEX_FILE)
	@echo "Flashing software......."
	@avrdude -c usbasp -p atmega32 -U flash:w:$(HEX_FILE)

clean:
	@rm -rf *.hex *.elf *.map *.o