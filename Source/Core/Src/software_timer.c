/*
 * software_timer.c
 *
 *  Created on: Oct 9, 2024
 *      Author: TRONG DAT
 */
#include "software_timer.h"
#include "main.h"



void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim ){
	if( htim->Instance == TIM2 ){
		button_reading () ;
	}
}

