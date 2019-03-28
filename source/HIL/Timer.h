/*
 * Timer.h
 *
 *  Created on: 15/03/2019
 *      Author: IVAN
 */
#ifndef TIMER_H_
#define TIMER_H_
#define ONE_SECOND 23976000
#include "PIT.h"
typedef unsigned char uint_8;
typedef unsigned long uint_32;

void vfnInitTimer(void);
void vfnCounter(void);
void getTime(uint_8 * get_hour,uint_8 * get_minutes,uint_8 * get_seconds,uint_8 * tiempo);
void setTime(uint_8 set_hours,uint_8 set_minutes,uint_8 set_seconds);

#endif /* TIMER_H_ */
