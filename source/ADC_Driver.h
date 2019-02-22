#include "MKL27Z644.h"
#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_
#define SUCCESS 1
#define ERROR 0
typedef unsigned char uint_8;
typedef unsigned long uint_16;
uint_8 ADC_bfnReadADC(uint_8 bChannel,uint_16 * bpADCValue);
void ADC_vfnDriverInit(void);
#endif /* ADC_DRIVER_H_ */
