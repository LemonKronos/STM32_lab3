/*
 * input_processing.c
 *
 *  Created on: Oct 9, 2024
 *      Author: TRONG DAT
 */
#include "input_processing.h"
#include "main.h"
#include "global.h"
#include "display7seg.h"

extern volatile uint8_t timer_flag[];

normal_mode Nmode = NORMAL;
config_mode Cmode = WAIT;

void fsm_input_driven_normal(){
	switch(Nmode){
	case NORMAL:
		if(flagForButtonPress[1] == 1){
			cancel_timer(&timer_flag[1]);
			cancel_timer(&timer_flag[2]);
			cancel_timer(&timer_flag[3]);
			Nmode = FREEZE;
			resetButtonFlag();
		}
//		else if(flagForButtonPress[2] == 1){
//			cancel_timer(&timer_flag[1]);
//			if(t_mode_main != GREEN){
//				cancel_timer(&timer_flag[2]);
//			}
//			Nmode = FORWARD;
//			resetButtonFlag();
//		}
//		else if(flagForButtonHold[2] == 1){
//			cancel_timer(&timer_flag[1]);
//			cancel_timer(&timer_flag[2]);
//			cancel_timer(&timer_flag[3]);
//			timer_flag[1] = 1;
//			timer_flag[2] = 1;
//			timer_flag[3] = 1;
//			Nmode = FAST;
//			resetButtonFlag();
//		}
		else{// RUN NORMAL
			fsm_traffic(&t_mode_main, &main_traffic, &timer_flag[1]);
			fsm_traffic(&t_mode_side, &side_traffic, &timer_flag[2]);
			if(timer_flag[3] == 1){
				countDown7SEG();
				set_timer(1000, &timer_flag[3]);
			}
			if(timer_flag[4] == 1){
				if(led_index >= MAX_LED) led_index = 0;
				display7SEG(led_index++);
				set_timer(200, &timer_flag[4]);
			}
		}
		break;
	case FREEZE:
		if(flagForButtonPress[1] == 1){// CHECK BUTTON
			set_timer(main_traffic.count_down *SEC, &timer_flag[1]);
			set_timer(side_traffic.count_down *SEC, &timer_flag[2]);
			set_timer(1000, &timer_flag[3]);
			Nmode = NORMAL;
			resetButtonFlag();
		}
		else{// RUN FREEZE
			fsm_traffic(&t_mode_main, &main_traffic, &timer_flag[1]);
			fsm_traffic(&t_mode_side, &side_traffic, &timer_flag[2]);

			if(timer_flag[4] == 1){
				if(led_index >= MAX_LED) led_index = 0;
				display7SEG(led_index++);
				set_timer(200, &timer_flag[4]);
			}
		}
		break;
	case FAST:
//		if(flagForButtonHold[2] == 1){
//			fsm_traffic(&t_mode_main, &main_traffic, &timer_flag[1]);
//			fsm_traffic(&t_mode_side, &side_traffic, &timer_flag[2]);
//			if(timer_flag[3] == 1){
//				countDown7SEG();
//				set_timer(500, &timer_flag[3]);
//			}
//			if(timer_flag[4] == 1){
//				if(led_index >= MAX_LED) led_index = 0;
//				display7SEG(led_index++);
//				set_timer(200, &timer_flag[4]);
//			}
//		}
//		else{
//			cancel_timer(&timer_flag[1]);
//			cancel_timer(&timer_flag[2]);
//			cancel_timer(&timer_flag[3]);
//			timer_flag[1] = 1;
//			timer_flag[2] = 1;
//			timer_flag[3] = 1;
//			Nmode = NORMAL;
//			resetButtonFlag();
//		}
		break;
	case FORWARD:
//		timer_flag[1] = 1;
//		timer_flag[2] = 1;
//		if(t_mode_main == GREEN){
//			t_mode_side = YELLOW;
//			fsm_traffic(&t_mode_side, &side_traffic, &timer_flag[2]);
//			cancel_timer(&timer_flag[2]);
//			set_timer(main_traffic.yellow *SEC, &timer_flag[2]);
//			side_traffic.count_down = main_traffic.yellow + 1;
//		}
//		else if(t_mode_main == RED){
//			t_mode_side = YELLOW;
//		}
//		Nmode = NORMAL;
//		resetButtonFlag();
		break;
	default:
		Nmode = NORMAL;
		break;
	}
}

void fsm_input_driven_config(ledColor color, uint8_t* time1, uint8_t* time2){
	switch(Cmode){
	case WAIT:
		if(flagForButtonPress[1] == 1){
			Cmode = UP;
			resetButtonFlag();
		}
		else if(flagForButtonHold[1] == 1){
			set_timer(500, &timer_flag[5]);
			Cmode = UP_FAST;
			resetButtonFlag();
		}
		else if(flagForButtonDoubleTap[1] == 1){
			Cmode = DOWN;
			resetButtonFlag();
		}
		else if(flagForButtonTapHold[1] == 1){
			set_timer(500, &timer_flag[5]);
			Cmode = DOWN_FAST;
			resetButtonFlag();
		}
		else if(flagForButtonPress[2] == 1){
			if(led_counter[0] != 0){
				if(led_counter[0] >= *time1){
					*time2 = *time2 + (led_counter[0] - *time1);
				}
				else{
					*time2 = *time2 - (*time1 - led_counter[0]);
				}
				*time1 = led_counter[0];
				HAL_GPIO_TogglePin(TEST_GPIO_Port, TEST_Pin);
			}

			Cmode = WAIT;
			resetButtonFlag();
		}
		else{// RUN WAIT
			if(timer_flag[3] == 1){
				set_timer(500, &timer_flag[3]);
				toggleLed(color);
			}
			if(timer_flag[4] == 1){
				if(led_index >= MAX_LED) led_index = 0;
				display7SEG(led_index++);
				set_timer(200, &timer_flag[4]);
			}
		}
		break;
	case UP:
		if(led_counter[0] < MAX_COUNT_DOWN) led_counter[0]++;
		else led_counter[0] = 0;
		update7SEG(counter);
		Cmode = WAIT;
		break;
	case UP_FAST:
		if(BUTTON[1] == HOLD){
			if(timer_flag[5] == 1){
				set_timer(500, &timer_flag[5]);
				if(led_counter[0] < MAX_COUNT_DOWN) led_counter[0]++;
				else led_counter[0] = 0;
				update7SEG(counter);
			}
			else{
				if(timer_flag[3] == 1){
					set_timer(500, &timer_flag[3]);
					toggleLed(color);
				}
				if(timer_flag[4] == 1){
					if(led_index >= MAX_LED) led_index = 0;
					display7SEG(led_index++);
					set_timer(200, &timer_flag[4]);
				}
			}
		}
		else{
			cancel_timer(&timer_flag[5]);
			resetButtonFlag();
			Cmode = WAIT;
		}
		break;
	case DOWN:
		if(led_counter[0] > 0) led_counter[0]--;
		else led_counter[0] = MAX_COUNT_DOWN;
		update7SEG(counter);
		Cmode = WAIT;
		break;
	case DOWN_FAST:
		if(BUTTON[1] == TAP_HOLD){
			if(timer_flag[5] == 1){
				set_timer(500, &timer_flag[5]);
				if(led_counter[0] > 0) led_counter[0]--;
				else led_counter[0] = MAX_COUNT_DOWN;
				update7SEG(counter);
			}
			else{
				if(timer_flag[3] == 1){
					set_timer(500, &timer_flag[3]);
					toggleLed(color);
				}
				if(timer_flag[4] == 1){
					if(led_index >= MAX_LED) led_index = 0;
					display7SEG(led_index++);
					set_timer(200, &timer_flag[4]);
				}
			}
		}
		else{
			cancel_timer(&timer_flag[5]);
			resetButtonFlag();
			Cmode = WAIT;
		}
		break;
	default:
		Cmode = WAIT;
		break;
	}
}

void toggleLed(ledColor color){
	switch(color){
	case lRED:
		HAL_GPIO_TogglePin(LED0_R_GPIO_Port, LED0_R_Pin);
		HAL_GPIO_TogglePin(LED1_R_GPIO_Port, LED1_R_Pin);
		break;
	case lYELLOW:
		HAL_GPIO_TogglePin(LED0_Y_GPIO_Port, LED0_Y_Pin);
		HAL_GPIO_TogglePin(LED1_Y_GPIO_Port, LED1_Y_Pin);
		break;
	case lGREEN:
		HAL_GPIO_TogglePin(LED0_G_GPIO_Port, LED0_G_Pin);
		HAL_GPIO_TogglePin(LED1_G_GPIO_Port, LED1_G_Pin);
		break;
	}
}

void flushLed(){
	HAL_GPIO_WritePin(LED0_R_GPIO_Port, LED0_R_Pin, SET);
	HAL_GPIO_WritePin(LED1_R_GPIO_Port, LED1_R_Pin, SET);
	HAL_GPIO_WritePin(LED0_Y_GPIO_Port, LED0_Y_Pin, SET);
	HAL_GPIO_WritePin(LED1_Y_GPIO_Port, LED1_Y_Pin, SET);
	HAL_GPIO_WritePin(LED0_G_GPIO_Port, LED0_G_Pin, SET);
	HAL_GPIO_WritePin(LED1_G_GPIO_Port, LED1_G_Pin, SET);
}
