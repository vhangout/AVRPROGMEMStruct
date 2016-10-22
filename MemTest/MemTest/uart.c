/*
 * uart.c
 *
 * Created: 04.10.2016 22:12:31
 *  Author: Vasia
 */
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

#define loop_until_bit_is_set(sfr,bit) do { } while (bit_is_clear(sfr, bit))
	

void uart_putchar(char c, FILE *stream) {
	cli();
	if (c == '\n') {
		uart_putchar('\r', stream);
	}
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
	sei();
}

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void uart_init(void) {
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0A &= ~(1<<U2X0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00); /* 8-bit data */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);   /* Enable RX and TX */
	stdout = &uart_output;
}