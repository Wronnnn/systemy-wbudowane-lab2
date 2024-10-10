#define F_CPU 1000000L
#include <util/delay.h>
#include <avr/io.h>
#include "getkey.h"

int main(void)
{
	DDRA = 0x0F;
	PORTA = 0xF0;
	DDRC = 0xFF;
	while (1) {
		PORTC = get_key();
		_delay_ms(500);
	}
}
