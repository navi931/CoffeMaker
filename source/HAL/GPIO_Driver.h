
#ifndef GPIO_H_
#define GPIO_H_
#define SUCCESS 1
#define ERROR 0
#define LUGARES 19	//Puerto B 19
#include "MKL27Z644.h"
#include "types.h"
uint_8 SetGpio(uint_8 prender);
void InitGPIO(void);
void ToggleGPIO(void);
#endif
