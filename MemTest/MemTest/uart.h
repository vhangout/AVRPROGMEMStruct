/*
 * uart.h
 *
 * Created: 04.10.2016 22:12:18
 *  Author: Vasia
 */ 


#ifndef UART_H_
#define UART_H_
#include <stdio.h>
void uart_init(void); 

void uart_putchar(char c, FILE *stream);

#endif /* UART_H_ */