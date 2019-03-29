#ifndef PIT_H_
#define PIT_H_
#define PIT_INTERRUPT_EN
#define PIT_IRQ PIT_DriverIRQHandler
#include "MKL27Z644.h"
#include "tools.h"
void vfnPITCallbackRegister1(void vfnCallback(void));
void vfnInitPit(uint_32 numero_periodos);
#endif
