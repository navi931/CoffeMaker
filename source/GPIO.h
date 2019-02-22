/*
 * GPIO.h
 *
 *  Created on: 22/02/2019
 *      Author: IVAN
 */
#include "MKL27Z644.h"
#ifndef GPIO_H_
#define GPIO_H_
#define SUCCESS 1
#define ERROR 0
#define LUGARES 19	//Puerto B 19
typedef unsigned char uint_8;

uint_8 SetGpio(uint_8 prender);
void InitGPIO(void);


#endif /* GPIO_H_ */
