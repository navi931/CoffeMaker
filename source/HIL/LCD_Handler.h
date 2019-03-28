#ifndef HIL_LCD_HANDLER_H_
#define HIL_LCD_HANDLER_H_
#include "LCD_Driver.h"
void InitScreen(void);
void printInLCD(uint_8 * array,uint_8 size);
void clearLCD(void);

#endif
