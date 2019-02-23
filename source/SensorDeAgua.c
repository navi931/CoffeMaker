
#include "MKL27Z644.h"
#include <stdio.h>
#include "ADC_Driver.h"


int main(void) {
    volatile static int i = 0 ;
    ADC_vfnDriverInit();
    ADC_vfnADCPortInit();
    uint_16 * pointer;
    uint_16 data=0;
    pointer=&data;

    while(1) {
    	i=ADC_bfnReadADC(0b01100,pointer);
    	printf("%i\n",*pointer);
    	i++;
    }
    return 0 ;
}
