/*
 * MemTest.c
 *
 * Created: 08.10.2016 20:44:15
 * Author : Vasia
 */ 

#include <avr/io.h>
#include "uart.h"

#include <avr/pgmspace.h>

typedef struct {
	const char *text;
	const void (*action)(void);
} menu_item_t;
typedef void (*fn_ptr) (PGM_P);

const char menu_1_1_s[] PROGMEM = "Vasia";
const char menu_1_2_s[] PROGMEM = "Petia";
const char menu_1_3_s[] PROGMEM = "Masha";
const char menu_1_4_s[] PROGMEM = "Kostia";
const char menu_1_5_s[] PROGMEM = "Vano";
const char menu_1_6_s[] PROGMEM = "Dasha";

const char * const menu_1_a[] PROGMEM = { menu_1_1_s, menu_1_2_s, menu_1_3_s, menu_1_4_s, menu_1_5_s, menu_1_6_s };

char buffer[10];

#define STRCPI(BUFFER, PGM) strcpy_P(BUFFER, (PGM_P)pgm_read_word(&(PGM)))
#define CALLPTR(PGM, PARAM) ((fn_ptr)pgm_read_word(&PGM))((PGM_P)pgm_read_word(&(PARAM)));

extern void dummy(PGM_P item);

const PROGMEM menu_item_t const struct_menu[] PROGMEM = {
	{ menu_1_1_s, dummy },
	{ menu_1_2_s, dummy },
	{ menu_1_3_s, dummy },
	{ menu_1_4_s, dummy },
	{ menu_1_5_s, dummy },
	{ menu_1_6_s, dummy }
};

/*const PROGMEM menu_t const struct_menu2[] PROGMEM = {
	
};*/

void testArray(void)
{
	puts("test array");
	for (uint8_t i = 0; i < 6; i++) {		
		STRCPI(buffer, menu_1_a[i]);
		puts(buffer);
	}
}

void dummy(PGM_P item)
{
	STRCPI(buffer, ((menu_item_t)item).text);
	puts(buffer);
}

void testStructArray()
{
	puts("test struct array");
	for (uint8_t i = 0; i < 6; i++) {
		STRCPI(buffer, struct_menu[i].text);
		puts(buffer);
		CALLPTR(struct_menu[i].action, struct_menu[i]);
	}
}

void testStructForStruct()
{
	puts("test struct for struct");
	for (uint8_t i = 0; i < 6; i++) {
		STRCPI(buffer, struct_menu[i].text);
		puts(buffer);
		CALLPTR(struct_menu[i].action, struct_menu[i]);
	}
}

int main(void)
{
	uart_init();
    testArray();
	testStructArray();
	//testStructForStruct();
    while (1) 
    {
    }
}

