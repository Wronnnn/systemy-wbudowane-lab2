#include "getkey.h"
#include <util/delay.h>
#include <avr/io.h>

uint8_t get_key() {
	uint8_t ilWc = 0;
	ilWc = 0;
	uint8_t res = 0, temp, j=0;
	int i;
	for (i=3;i>=0;i--){
		PORTA = ~_BV(i); // negowanie dla kazdej kolumny
		_delay_ms(50);
		temp = PINA & 0xF0;
		switch(temp){ // po jednej kolumnie odczytanie kadego wiersza
			case 0b11100000:
			res = j + 1; // zmienna pomocnicza j okresla numer kolumny
			ilWc++; // zlicza ilosc wcisnietych przyciskow aby zwrocic blad przy wartosci wiekszej niz 1
			break;
			case 0b11010000:
			res = j + 5;
			ilWc++;
			break;
			case 0b10110000:
			res = j + 9;
			ilWc++;
			break;
			case 0b01110000:
			res = j + 13;
			ilWc++;
			break;
			case 0b11110000:
			break;
			default:
			return 0xFF;
		}
		j++;
	}
	if((PINA & 0b00000001) && ilWc == 0){
		return 0xFF;
	}
	if(ilWc>1){
		return 0xFF; // przy wiekszej ilosc wcisnietych przyciskow zwraca blad
	}
	return res;
}