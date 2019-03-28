#include "GPIO_Driver.h"
void InitGPIO(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;			//INICIALIZAR EL PUERTO
	PORTB->PCR[LUGARES] |= PORT_PCR_MUX(1);		//INICIALIZAR EL GPIO
	GPIOB->PDDR |= (1<<LUGARES);				//INICIALIZAR EL GPIO
	SetGpio(0);
}

uint_8 SetGpio(uint_8 prender)
{
	uint_8 state = ERROR;
	if(prender)
	{
		GPIOB->PDDR |= (1<<LUGARES);				//PRENDER EL GPIO
		state = SUCCESS;
	}
	else
	{
		GPIOB->PDDR = GPIOB->PDDR &~ (1<<LUGARES);	//APAGAR EL GPIO
		state = SUCCESS;
	}
	return state;
}

void ToggleGPIO(void)
{
		GPIOB->PDDR^= (1<<LUGARES);					//PRENDER EL GPIO
}
