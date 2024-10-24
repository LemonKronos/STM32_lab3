/*
 * software_timer.h
 *
 *  Created on: Oct 9, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"

#define TIMER_CYCLE 10
#define WHEEL1 100
#define WHEEL2 99

uint8_t currentTimerSlotWheel1, currentTimerSlotWheel2;

typedef struct Timer{
	int duration;
	void (*timerdo)(void);
	struct Timer* next;
} Timer;

Timer* timerWheel1[WHEEL1];
Timer* timerWheel2[WHEEL2];

void set_timer(int duration, void (*timerdo)(void));

void timer_tick();

void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim );

#endif /* INC_SOFTWARE_TIMER_H_ */
