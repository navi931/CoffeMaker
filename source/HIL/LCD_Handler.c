#include "LCD_Handler.h"

void InitScreen(void){
	LCD_init();
}

void printInLCD(uint_8 * array,uint_8 size){
	sendString(&array[0],size);
}

void clearLCD(void){
	LCD_command(CLRSCR);
	LCD_command(BLINK_CURSOR);
}
