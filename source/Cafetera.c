
#include "MKL27Z644.h"
#include "ADC_Driver.h"
#include "GPIO_Driver.h"
#include "Communication.h"
#include "Timer.h"
#include "LCD_Handler.h"
#define LCD


#define MAKE_COFFEE 		'A'
#define CANCEL_COFFEE 		'B'
#define SET_TIME 			0x0F
#define SET_ALARM 			0x0E
#define CANCEL_ALARM		'C'

#define HOURS 				0b10000000
#define MINUTES 			0b01000000
#define SECONDS 			0b00100000
#define DISABLE				100
#define MINUTES_TOP			60
#define REFRESH				3

#define TIME_COFFEE			2
#define MAX_VALUE_COFFEE 	120
#define MIN_VALUE_WATER 	120
#define WATER_MASK			0b00000010
#define COFFEE_MASK			0b00000001

#define DOS_PUNTOS_ASCII 	58

void vfnMakeCoffee(void);
void vfnCancelCoffee(void);
void vfnSetTime(void);
void vfnSetAlarm(void);
void vfnCancelAlarm(void);
void vfndefaultState(void);

void sumarTiempo(uint_8 * hours,uint_8 * minutes,uint_8 valor);

enum function
{
	eMakeCoffee,
	eCancelCoffee,
	eSetTime,
	eSetAlarm,
	eCancelAlarm,
	edefaultState
};

void (*coffeeState[])(void) =
{
	vfnMakeCoffee,							//0
	vfnCancelCoffee,						//1
	vfnSetTime,								//2
	vfnSetAlarm,							//3
	vfnCancelAlarm,							//4
	vfndefaultState							//5
};

enum lugar_arreglo
{
	eHour_decenas,							//0
	eHour_unidades,							//1
	eDos_puntos1,							//2
	eMinute_decenas,						//3
	eMinute_unidades,						//4
};

uint_8 tiempo = 5;
uint_8 seconds_main = 0;
uint_8 minutes_main = 0;
uint_8 hours_main = 0;

uint_8 seconds_alarm = DISABLE;
uint_8 minutes_alarm = DISABLE;
uint_8 hours_alarm = DISABLE;

uint_8 minutes_set = DISABLE;
uint_8 hours_set = DISABLE;

uint_8 * pointerUART;
uint_8 datauart=0;

uint_8 making_coffee = 0;
uint_8 cancel = 0;
uint_8 cafe_canceled = 0;
uint_8 coffee_water_level = 0;

int main(void)
{

	uint_8 * pointerWater;
	uint_8 * pointerCoffee;
	uint_8 dataWater=0;
	uint_8 dataCoffee=0;

    vfnInitTimer();
    ADC_vfnDriverInit();
    ADC_vfnADCPortInitWater();
    ADC_vfnADCPortInitCoffee();
    COMM_vfnDriverInit();
    InitGPIO();
#ifdef LCD
    InitScreen();
#endif
    pointerWater=&dataWater;
    pointerCoffee=&dataCoffee;
    pointerUART=&datauart;

    while(1)
    {
    	getTime(&hours_main,&minutes_main,&seconds_main,&tiempo);
    	COMM_bfnReceiveMsg(pointerUART);

    	if(pointerUART != NULL)
    	{
    	switch(*pointerUART)
    		{
    			case CANCEL_ALARM:
					{
						coffeeState[eCancelAlarm]();
					}
					break;
    	    	case MAKE_COFFEE:
    	    		{
    	    			coffeeState[eMakeCoffee]();
    	    		}
    	    		break;
    	    	case CANCEL_COFFEE:
    	    		{
    	    			coffeeState[eCancelCoffee]();
    	    		}
    	    		break;
    	    	case SET_TIME:
    				{
    					coffeeState[eSetTime]();
    				}
    	    		break;
    	    	case SET_ALARM:
    				{
    					coffeeState[eSetAlarm]();
    				}
    	    		break;
    	    	default:
    				{
    					coffeeState[edefaultState]();
    				}
    	    		break;
    	    }

			*pointerUART = 0;

			if((minutes_main == minutes_alarm) && (hours_main == hours_alarm) && (cancel == 0))
			{
				coffeeState[eMakeCoffee]();
			}

			if((minutes_main != minutes_alarm) || (hours_main != hours_alarm))
			{
				cancel = 0;
			}

			if ((minutes_main == minutes_set) && (hours_main == hours_set))
			{
				coffeeState[eCancelCoffee]();
				cancel = 0;
				cafe_canceled = 0;
			}

			if(tiempo >= REFRESH)
			{
				coffee_water_level = 0;
				tiempo=0;
				if(pointerWater != NULL)
				{
					ADC_bfnReadADC(0b01100,pointerWater);
					if(*pointerWater > MIN_VALUE_WATER)
						coffee_water_level |= 0b00000010;
				}
				if(pointerCoffee != NULL)
				{
					ADC_bfnReadADC(0b01011,pointerCoffee);
					if(*pointerCoffee < MAX_VALUE_COFFEE)
						coffee_water_level |= 0b00000001;
				}
				COMM_bfnSendMsg(&coffee_water_level,sizeof(coffee_water_level));
			}
    	}
    }
    return 0;
}

void vfnMakeCoffee(void)
{
#if 0
	if(coffee_water_level == (COFFEE_MASK|WATER_MASK))
#endif
	if(1)
	{
		cancel = 0;
		if(making_coffee == 0)
		{
			SetGpio(1);
			hours_set = hours_main;
			minutes_set = minutes_main;
			sumarTiempo(&hours_set,&minutes_set,TIME_COFFEE);
			making_coffee = 1;
		}
	}
	return;
}

void sumarTiempo(uint_8 * hours,uint_8 * minutes,uint_8 valor)
{
	if((*minutes + valor) >= MINUTES_TOP)
	{
		*minutes = (*minutes + valor) - MINUTES_TOP;
		*hours = *hours + 1;
	}
	else
	{
		*minutes = *minutes + valor;
	}
}

void vfnCancelCoffee(void)
{
	SetGpio(0);
	if(making_coffee == 1)
	{
		cancel = 1;
	}
	cafe_canceled = 1;
	making_coffee = 0;
	hours_set = DISABLE;
	minutes_set = DISABLE;
	return;
}

void vfnSetTime(void)
{

	uint_8 puedo_salir = 1;
	while(puedo_salir)
	{
		COMM_bfnReceiveMsg(pointerUART);
		if((*pointerUART | HOURS)  == (*pointerUART))
		{
			hours_main = (*pointerUART & (~HOURS));
			while(puedo_salir)
			{
				COMM_bfnReceiveMsg(pointerUART);
				if((*pointerUART | MINUTES)  == (*pointerUART))
				{
					minutes_main = (*pointerUART & (~MINUTES));
					while(puedo_salir)
					{
						COMM_bfnReceiveMsg(pointerUART);
						if((*pointerUART | SECONDS)  == (*pointerUART))
						{
							seconds_main = (*pointerUART & (~SECONDS));
							puedo_salir = 0;
						}
					}
				}
			}
		}
	}
	setTime(hours_main,minutes_main,seconds_main);
	return;
}

void vfnSetAlarm(void)
{
	uint_8 puedo_salir = 1;
	while(puedo_salir)
	{
		COMM_bfnReceiveMsg(pointerUART);
		if((*pointerUART | HOURS)  == (*pointerUART))
		{
			hours_alarm = (*pointerUART & (~HOURS));
			while(puedo_salir)
			{
				COMM_bfnReceiveMsg(pointerUART);
				if((*pointerUART | MINUTES)  == (*pointerUART))
				{
					minutes_alarm = (*pointerUART & (~MINUTES));
					while(puedo_salir)
					{
						COMM_bfnReceiveMsg(pointerUART);
						if((*pointerUART | SECONDS)  == (*pointerUART))
						{
							seconds_alarm = (*pointerUART & (~SECONDS));
							puedo_salir = 0;
						}
					}
				}
			}
		}
	}
	return;
}

void vfnCancelAlarm(void)
{
	hours_alarm = DISABLE;
	minutes_alarm = DISABLE;
}

void vfndefaultState(void)
{
#ifdef LCD
	static uint_8  lcd_making_coffee [] = "Haciendo Cafe";
	static uint_8 length_making = ((sizeof(lcd_making_coffee) - 1)/sizeof(uint_8));
	static uint_8 lcd_cancel_coffee [] = "Cafe cancelado";
	static uint_8 length_cancel = ((sizeof(lcd_cancel_coffee) - 1)/sizeof(uint_8));
	static uint_8  lcd_default [5] = {0,0,DOS_PUNTOS_ASCII,0,0};
	static uint_8 length_default = (sizeof(lcd_default)/sizeof(uint_8));
	if(tiempo >= REFRESH)
	{
		if(making_coffee == 1)
		{
			printInLCD(&lcd_making_coffee[0],length_making);
		}
		else if(cafe_canceled == 1)
		{
			printInLCD(&lcd_cancel_coffee[0],length_cancel);
			cafe_canceled = 0;
		}
		else
		{
			lcd_default[eHour_decenas] = (hours_main/10) + '0';
			lcd_default[eHour_unidades] = (hours_main%10) + '0';
			lcd_default[eMinute_decenas] = (minutes_main/10) + '0';
			lcd_default[eMinute_unidades] = (minutes_main%10) + '0';
			printInLCD(&lcd_default[0],length_default);
		}
	}
#endif
	return;
}
