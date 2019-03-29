#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#define RS 0x04 /* PTA2  */
#define RW 0x10 /* PTA4  */
#define EN 0x20 /* PTA5  */
#define BLINK_CURSOR 0x0F
#define JUMPLINE 0xC0
#define CLRSCR 0x01
#define ENTRYMODESET 0x06
#define TWOLINES 0x38
#define INITCOMMAND 0x30
#define DISPLAYBUFFER 0x80
#define USINSTRUCTIONS 8
#define MSINSTRUCTIONS 7000
#define LCDLINES 16

#define LCOMMANDSIZE 4
#define SCOMMANDSIZE 1

#define WAITCLEARTIME 500
#define LCDDATATIME 1

enum Init{
	PAUSA1=30,
	PAUSA2=10,
	PAUSA3=1
};

typedef unsigned char uint_8;
typedef unsigned long uint_16;
void delayMs(uint_16 n);
void LCD_command(uint_8 command);
void LCD_data(uint_8 data);
void LCD_init(void);
void delayUs(uint_16 n);
void sendString(uint_8 * array,uint_8 size);


#endif
