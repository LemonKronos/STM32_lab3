/*
 * fsm_run.c
 *
 *  Created on: 28 thg 10, 2024
 *      Author: TRONG DAT
 */
#include "main.h"
#include "fsm_run.h"
#include "global.h"
#include "traffic_light.h"
#include "display7seg.h"
#include "software_timer.h"

extern traffic_way main_traffic, side_traffic;

void fsm_run(machine_state mode){
	switch(mode){
	case mode1:// run normally
		fsm_traffic(&t_mode_main, &main_traffic, &timer_flag[6], 0);
		fsm_traffic(&t_mode_side, &side_traffic, &timer_flag[7], 1);
		if(timer_flag[4] == 1){
			HAL_GPIO_TogglePin(TEST_GPIO_Port, TEST_Pin);
			countDown7SEG(0);
			countDown7SEG(1);
			set_timer(1000, &timer_flag[4]);
		}
		if(timer_flag[5] == 1){
			if(led_index >= MAX_LED) led_index = 0;
			display7SEG(led_index++);
			set_timer(100, &timer_flag[5]);
		}
		break;
	case mode2:

		break;
	case mode3:

		break;
	case mode4:

		break;
	default:

		break;
	}
}
