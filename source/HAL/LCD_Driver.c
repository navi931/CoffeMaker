#include "MKL27Z644.h"
#include "LCD_Driver.h"
void  delayUs(uint_16  n)
{
	uint_8 i=0;
	uint_8 j=0;
	for(i = 0 ; i<n; i++)
	{
		for(j = 0; j<USINSTRUCTIONS; j++){

		}
	}
}

void LCD_init(void)
{
	SIM->SCGC5 |= 0x1000;			/*PORT D clock Initialization*/
	PORTD->PCR[0]  =  0x100;		/*PORTS 0-7 are initialized*/
	PORTD->PCR[1]  =  0x100;
	PORTD->PCR[2]  =  0x100;
	PORTD->PCR[3]  =  0x100;
	PORTD->PCR[4]  =  0x100;
	PORTD->PCR[5]  =  0x100;
	PORTD->PCR[6]  =  0x100;
	PORTD->PCR[7]  =  0x100;
	GPIOD->PDDR  =  0xFF;			/*ALL PORTD PORTS ARE ENABLED AS OUTPUT*/
	SIM->SCGC5 |= 0x0200; 			/* PORT A clock Initialization */
	PORTA->PCR[2] = 0x100; 			/* Pin activation for PTA2,PTA4 and PTA5 */
	PORTA->PCR[4] = 0x100;
	PORTA->PCR[5]  =  0x100;
	GPIOA->PDDR  |=  0x34; 			/*  PTA2,4 AND 5 are set as output */
	delayMs(PAUSA1); 					/* LCD init sequence */
	LCD_command(INITCOMMAND);
	delayMs(PAUSA2);
	LCD_command(INITCOMMAND);
	delayMs(PAUSA3);
	LCD_command(INITCOMMAND);
	LCD_command(TWOLINES); 			/* two line mode */
	LCD_command(ENTRYMODESET); 		/* Cursor will move to the right*/
	LCD_command(CLRSCR);  			/*  Clear screen */
	LCD_command(BLINK_CURSOR); 		/* Cursor blinks */
}
void LCD_command(uint_8 command)
{
	GPIOA->PCOR = RS | RW;
	GPIOD->PDOR = command; /*El comando es enviado a través de los puertos D*/
	GPIOA->PSOR = EN;	/*We activate the "enable" line*/
	delayMs(LCDDATATIME);
	GPIOA->PCOR = EN;	/*We deactivate the "enable" line*/
	if (command < LCOMMANDSIZE){
		delayMs(LCOMMANDSIZE);
	}
	else{
		delayMs(SCOMMANDSIZE);
	}
}

void LCD_data(uint_8 data)
{
	GPIOA->PSOR = RS;	/*Read mode disabled */
	GPIOA->PCOR = RW;	/*Write mode*/
	GPIOD->PDOR = data; /*The command is sent through the connected PORTD ports*/
	GPIOA->PSOR = EN; /*We activate the "enable" line*/
	delayMs(LCDDATATIME);
	GPIOA->PCOR = EN; /*We disable the "enable" line*/
	delayMs(LCDDATATIME);
}

void delayMs(uint_16 n)
{
	uint_8 i=0;
	uint_8 j=0;
	for(i = 0 ; i < n; i++){
		for(j = 0 ; j < MSINSTRUCTIONS; j++){

		}
	}
}
void sendString(uint_8 * array,uint_8 size)
{
	uint_8 i=0;
	LCD_command(CLRSCR); /*Clearing screen*/
	delayMs(WAITCLEARTIME);
	LCD_command(DISPLAYBUFFER); /*Print on the first line.*/
	if(size<=(LCDLINES*2))
	{
		for(i=0;i<size;i++)
		{
			if(i!=LCDLINES)
			{
				LCD_data(*(array+i)); /*Inserting ASCII values to display.*/
			}
			else
			{
				LCD_command(JUMPLINE); /*Jumping to the next line*/
			}
		}
	}
	else{
		/*SIZE OF THE STRING IS LARGER THAN 32 BYTES*/
	}
}
