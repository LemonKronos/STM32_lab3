/*
 * software_timer.c
 *
 *  Created on: Oct 9, 2024
 *      Author: TRONG DAT
 */
#include "input_reading.h"
#include "software_timer.h"
#include "main.h"
#include "stdlib.h"

uint8_t  currentTimerSlotWheel1 = 0, currentTimerSlotWheel2 = 0;

void set_timer(int duration, void (*timerdo)(void)){
	Timer* newTimer = (Timer*)malloc(sizeof(Timer));
	newTimer->duration = duration;
	newTimer->timerdo = timerdo;
	if(duration / TIMER_CYCLE > WHEEL1){
		uint8_t newTimerSlot = (duration / TIMER_CYCLE) / WHEEL1;
		newTimer->next = timerWheel2[newTimerSlot];
		timerWheel2[newTimerSlot] = newTimer;
	}
	else{
		uint8_t newTimerSlot = (duration / TIMER_CYCLE) % WHEEL1;
		newTimer->next = timerWheel1[newTimerSlot];
		timerWheel1[newTimerSlot] = newTimer;
	}
}

void timer_tick(){
	Timer* processTimer = timerWheel2[currentTimerSlotWheel2];
	while(processTimer != NULL){
		uint8_t newTimerSlot = (processTimer->duration/TIMER_CYCLE) % WHEEL1;
		Timer* newTimer = (Timer*)malloc(sizeof(Timer));
		newTimer->next = timerWheel1[newTimerSlot];
		timerWheel1[newTimerSlot] = newTimer;
	}
	timerWheel2[currentTimerSlotWheel2] = NULL;
	currentTimerSlotWheel2 = (currentTimerSlotWheel2 + 1) % WHEEL2;
	processTimer = timerWheel1[currentTimerSlotWheel1];
	while(processTimer != NULL){
		processTimer->timerdo();
		Timer* temp = processTimer;
		processTimer = processTimer->next;
		free(temp);
	}
	timerWheel1[currentTimerSlotWheel1] = NULL;
	currentTimerSlotWheel1 = (currentTimerSlotWheel1 + 1) % WHEEL1;
}

void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim ){
	if( htim->Instance == TIM2 ){
		timer_tick();
		button_reading() ;
	}
}

