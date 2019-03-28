#ifndef UARTDRIVER_H_
#define UARTDRIVER_H_
#define ERROR 0
#define SUCCESS 1
#define UART_BAUD_RATE 9600
#define UART_BAUD_OSR 15
#define SEL_CLK 8000000
#include "MKL27Z644.h"
#include "types.h"
void UART_vfnDriverInit(void);
void UART_vfnDriverInitPorts(void);
uint_8 UART_bfnSend(uint_8 valor);
uint_8 UART_bfnRead(uint_8* valor);
#endif
