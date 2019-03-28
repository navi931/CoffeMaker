#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_
#define SUCCESS 1
#define ERROR 0
#include "MKL27Z644.h"
#include "types.h"
uint_8 ADC_bfnReadADC(uint_8 bChannel,uint_8 * bpADCValue);
void ADC_vfnADCPortInitWater(void);
void ADC_vfnADCPortInitCoffee(void);
void ADC_vfnDriverInit(void);
#endif /* ADC_DRIVER_H_ */
