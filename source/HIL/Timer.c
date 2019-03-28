/*
 * Timer.c
 *
 *  Created on: 15/03/2019
 *      Author: IVAN
 */
#include "Timer.h"

uint_8 seconds = 0;
uint_8 minutes = 0;
uint_8 hours = 0;


void vfnInitTimer(void)
{
	vfnPITCallbackRegister1(vfnCounter);
	vfnInitPit(ONE_SECOND);
	return;
}

void vfnCounter(void)
{
		if(seconds < 59)
		{
			seconds++;
		}
		else if(minutes < 59)
		{
			seconds = 0;
			minutes++;
		}
		else if(hours < 23)
		{
			hours++;
			minutes = 0;
		}
		else
		{
			seconds = 0;
			minutes = 0;
			hours = 0;
		}
	return;
}

void getTime(uint_8 * get_hour,uint_8 * get_minutes,uint_8 * get_seconds,uint_8 * time)
{
	if(seconds != *get_seconds)
	{
		*time = *time + 1;
	}
	*get_hour = hours;
	*get_minutes = minutes;
	*get_seconds = seconds;
	return;
}

void setTime(uint_8 set_hours,uint_8 set_minutes,uint_8 set_seconds)
{
	hours = set_hours;
	minutes = set_minutes;
	seconds = set_seconds;
	return;
}
