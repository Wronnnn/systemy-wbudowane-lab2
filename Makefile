# Nazwa docelowa (nazwa pliku wynikowego bez rozszerzenia)
TARGET = main

# Mikrokontroler (np. ATmega32)
MCU = atmega32

# Narzędzia AVR
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size

# Opcje kompilatora
CFLAGS = -mmcu=$(MCU) -Wall -Os -DF_CPU=16000000UL
LDFLAGS = -mmcu=$(MCU)

# Pliki źródłowe
SRC = main.c getkey.c

# Pliki obiektowe (zamiana rozszerzenia .c na .o)
OBJ = $(SRC:.c=.o)

# Reguły budowania
all: $(TARGET).hex

$(TARGET).elf: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	$(SIZE) $<

clean:
	rm -f *.o *.elf *.hex
