/*
 * traffic_light.c
 *
 *  Created on: Oct 28, 2024
 *      Author: TRONG DAT
 */
#include "main.h"
#include "traffic_light.h"
#include "global.h"
#include "software_timer.h"
#include "display7seg.h"

//#define UNIT_TEST

traffic_mode	t_mode_main = RED,
				t_mode_side = GREEN;

void fsm_traffic(traffic_mode* mode, traffic_way* Tway, uint8_t* timer_flag, uint8_t index){
	switch(*mode){
	case RED:
		if(*timer_flag == 1){
			lit_green(Tway->way);
			set_timer(Tway->green *SEC, timer_flag);
			Tway->count_down = Tway->green + 1;
			*mode = GREEN;
			update7SEG(index);
		}
		break;
	case YELLOW:
		if(*timer_flag == 1){
			lit_red(Tway->way);
			set_timer(Tway->red *SEC, timer_flag);
			Tway->count_down = Tway->red + 1;
			*mode = RED;
			update7SEG(index);
		}
		break;
	case GREEN:
		if(*timer_flag == 1){
			lit_yellow(Tway->way);
			set_timer(Tway->yellow *SEC, timer_flag);
			Tway->count_down = Tway->yellow + 1;
			*mode = YELLOW;
			update7SEG(index);
		}
		break;
	default:

		break;
	}
}

void lit_red(whichWay way){
	if(way == main_way){
		HAL_GPIO_WritePin(LED0_R_GPIO_Port, LED0_R_Pin, RESET);
		HAL_GPIO_WritePin(LED0_Y_GPIO_Port, LED0_Y_Pin, SET);
		HAL_GPIO_WritePin(LED0_G_GPIO_Port, LED0_G_Pin, SET);
	}
	if(way == side_way){
		HAL_GPIO_WritePin(LED1_R_GPIO_Port, LED1_R_Pin, RESET);
		HAL_GPIO_WritePin(LED1_Y_GPIO_Port, LED1_Y_Pin, SET);
		HAL_GPIO_WritePin(LED1_G_GPIO_Port, LED1_G_Pin, SET);
	}
}

void lit_yellow(whichWay way){
	if(way == main_way){
		HAL_GPIO_WritePin(LED0_Y_GPIO_Port, LED0_Y_Pin, RESET);
		HAL_GPIO_WritePin(LED0_G_GPIO_Port, LED0_G_Pin, SET);
		HAL_GPIO_WritePin(LED0_R_GPIO_Port, LED0_R_Pin, SET);
	}
	if(way == side_way){
		HAL_GPIO_WritePin(LED1_Y_GPIO_Port, LED1_Y_Pin, RESET);
		HAL_GPIO_WritePin(LED1_G_GPIO_Port, LED1_G_Pin, SET);
		HAL_GPIO_WritePin(LED1_R_GPIO_Port, LED1_R_Pin, SET);
	}
}

void lit_green(whichWay way){
	if(way == main_way){
		HAL_GPIO_WritePin(LED0_G_GPIO_Port, LED0_G_Pin, RESET);
		HAL_GPIO_WritePin(LED0_R_GPIO_Port, LED0_R_Pin, SET);
		HAL_GPIO_WritePin(LED0_Y_GPIO_Port, LED0_Y_Pin, SET);
	}
	if(way == side_way){
		HAL_GPIO_WritePin(LED1_G_GPIO_Port, LED1_G_Pin, RESET);
		HAL_GPIO_WritePin(LED1_R_GPIO_Port, LED1_R_Pin, SET);
		HAL_GPIO_WritePin(LED1_Y_GPIO_Port, LED1_Y_Pin, SET);
	}
}

#ifdef UNIT_TEST
void unit_test_traffic(){

}
#endif
