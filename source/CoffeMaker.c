#include "GPIO.h"
int main(void) {

	volatile uint_8 i = 0;
	InitGPIO();
    while(1) {
    	i = SetGpio(1);
    	i = SetGpio(0);
    }
    return 0 ;
}
