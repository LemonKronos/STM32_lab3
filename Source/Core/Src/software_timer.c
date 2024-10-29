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
#include "global.h"

uint8_t  currentTimerSlotWheel1 = 0, currentTimerSlotWheel2 = 0;

void set_timer(uint16_t duration, uint8_t* timer_flag){
	Timer* newTimer = (Timer*)malloc(sizeof(Timer));
	if (newTimer == NULL) return;
	newTimer->duration = duration;
	newTimer->timer_flag = timer_flag;
	if(duration / TIMER_CYCLE >= WHEEL1){// assign to wheel 2
		uint8_t newTimerSlot = (currentTimerSlotWheel2 + (duration / TIMER_CYCLE) / WHEEL1) % WHEEL2;
		newTimer->next = timerWheel2[newTimerSlot];
		timerWheel2[newTimerSlot] = newTimer;
	}
	else{// assign to wheel 1
		uint8_t newTimerSlot = (currentTimerSlotWheel1 + duration / TIMER_CYCLE) % WHEEL1;
		newTimer->next = timerWheel1[newTimerSlot];
		timerWheel1[newTimerSlot] = newTimer;
	}
}

void timer_tick(){
    if (currentTimerSlotWheel1 == 0){
        Timer* processTimer = timerWheel2[currentTimerSlotWheel2];
        while (processTimer != NULL){
            uint8_t newTimerSlot = (processTimer->duration / TIMER_CYCLE) % WHEEL1;
            Timer* newTimer = (Timer*)malloc(sizeof(Timer));
            if (newTimer == NULL) return;
            newTimer->duration = processTimer->duration % (WHEEL1 * TIMER_CYCLE);
            newTimer->timer_flag = processTimer->timer_flag;
            newTimer->next = timerWheel1[newTimerSlot];
            timerWheel1[newTimerSlot] = newTimer;

            Timer* temp = processTimer;
            processTimer = processTimer->next;
            free(temp);
        }
        timerWheel2[currentTimerSlotWheel2] = NULL;
        currentTimerSlotWheel2 = (currentTimerSlotWheel2 + 1) % WHEEL2;
    }

    Timer* processTimer = timerWheel1[currentTimerSlotWheel1];
    while (processTimer != NULL) {
        *(processTimer->timer_flag) = 1;
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
		button_reading();
	}
}

void unit_test_software_timer(){
	if(timer_flag[0] >= 1){
		HAL_GPIO_TogglePin(TEST_Timer_GPIO_Port, TEST_Timer_Pin);
		timer_flag[0] = 0;
		set_timer(1000, &timer_flag[0]);
	}
//	if(timer_flag[1] >= 1){
//		HAL_GPIO_TogglePin(TEST_Button_GPIO_Port, TEST_Button_Pin);
//		timer_flag[1] = 0;
//		set_timer(20, &timer_flag[1]);
//	}
}

