#include "LCD_Driver.h"
void  delayUs(uint_16  n){
	uint_8 i; uint_8 j;
	for(i = 0 ; i < n; i++) {
		for(j = 0; j < 8; j++) ;
	}
}

void LCD_init(void){
SIM->SCGC5 |= 0x1000;
PORTD->PCR[0]  =  0x100;
PORTD->PCR[1]  =  0x100;
PORTD->PCR[2]  =  0x100;
PORTD->PCR[3]  =  0x100;
PORTD->PCR[4]  =  0x100;
PORTD->PCR[5]  =  0x100;
PORTD->PCR[6]  =  0x100;
PORTD->PCR[7]  =  0x100;
GPIOD->PDDR  =  0xFF;
SIM->SCGC5 |= 0x0200; /* habilita el reloj del puerto A */
PORTA->PCR[2] = 0x100; /* usaremos el pin 2 del Puerto A */
PORTA->PCR[4] = 0x100; /* usaremos el pin 4 del Puerto A */
PORTA->PCR[5]  =  0x100;  /*  usaremos  el  pin  5  del Puerto A */
GPIOA->PDDR  |=  0x34;  /*  hacemos  a  los  pines  2,  4  y  5 salidad */
delayMs(30); /* secuencia de inicializacion del LCD */
LCD_command(INITCOMMAND);
delayMs(10);
LCD_command(INITCOMMAND);
delayMs(1);
LCD_command(INITCOMMAND);
LCD_command(TWOLINES); /* establece 8 lineas de datos al LCD */
LCD_command(ENTRYMODESET); /* mueve el cursor a la derecha*/
LCD_command(CLRSCR);  /*  limpia  la  pantalla  y  el  cursor regresa a la posicion de inicio */
LCD_command(BLINK_CURSOR); /* el cursor parpadea */
}
void LCD_command(uint_8 command) {
GPIOA->PCOR = RS | RW;
GPIOD->PDOR = command;
GPIOA->PSOR = EN;
delayMs(0);
GPIOA->PCOR = EN;
if (command < 4) delayMs(4);
else delayMs(1);
}

void LCD_data(uint_8 data) {
	GPIOA->PSOR = RS;
	GPIOA->PCOR = RW;
	GPIOD->PDOR = data;
	GPIOA->PSOR = EN;
	delayMs(1);
	GPIOA->PCOR = EN;
	delayMs(1);
}

void delayMs(uint_16 n) {
	int i; int j;
	for(i = 0 ; i < n; i++)
		for(j = 0 ; j < 7000; j++) { }


}
void sendString(uint_8 * array,uint_8 size){
	uint_8 i;
	LCD_command(CLRSCR);
	delayMs(500);
	LCD_command(DISPLAYBUFFER);
	if(size<=32){
		for(i=0;i<size;i++){
			if(i==16){
				LCD_command(JUMPLINE);
			}
			else{
				LCD_data(*(array+i));
			}
		}
	}
}
