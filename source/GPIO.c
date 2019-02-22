#include "GPIO.h"
void InitGPIO()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;			//INICIALIZAR EL PUERTO
	PORTB->PCR[LUGARES] |= PORT_PCR_MUX(1);		//INICIALIZAR EL GPIO
	GPIOB->PDDR |= (1<<LUGARES);				//INICIALIZAR EL GPIO
}

uint_8 SetGpio(uint_8 prender)
{
	if(prender)
	{
		GPIOB->PDDR |= (1<<LUGARES);				//PRENDER EL GPIO
		return SUCCESS;
	}
	else
	{
		GPIOB->PDDR = GPIOB->PDDR &~ (1<<LUGARES);	//APAGAR EL GPIO
		return SUCCESS;
	}
	return ERROR;
}
