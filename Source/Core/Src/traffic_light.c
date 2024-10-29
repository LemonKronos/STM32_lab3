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

//#define UNIT_TEST

traffic_mode	t_mode_main = RED,
				t_mode_side = GREEN;

void fsm_traffic_main(traffic_mode mode){
	switch(mode){
	case RED:
		if(timer_flag[2] == 1){
			t_mode_main = GREEN;
			lit_green_main();
			timer_flag[2] = 0;
			set_timer(green_main, &timer_flag[2]);
		}
		break;
	case YELLOW:
		if(timer_flag[2] == 1){
			t_mode_main = RED;
			lit_red_main();
			timer_flag[2] = 0;
			set_timer(red_main, &timer_flag[2]);
		}
		break;
	case GREEN:
		if(timer_flag[2] == 1){
			t_mode_main = YELLOW;
			lit_yellow_main();
			timer_flag[2] = 0;
			set_timer(yellow_main, &timer_flag[2]);
		}
		break;
	default:

		break;
	}
}

void fsm_traffic_side(traffic_mode mode){
	switch(mode){
		case RED:
			if(timer_flag[3] == 1){
				t_mode_side = GREEN;
				lit_green_side();
				timer_flag[2] = 0;
				set_timer(green_main, &timer_flag[2]);
			}
			break;
		case YELLOW:
			if(timer_flag[2] == 1){
				t_mode_main = RED;
				lit_red_main();
				timer_flag[2] = 0;
				set_timer(red_main, &timer_flag[2]);
			}
			break;
		case GREEN:
			if(timer_flag[2] == 1){
				t_mode_main = YELLOW;
				lit_yellow_main();
				timer_flag[2] = 0;
				set_timer(yellow_main, &timer_flag[2]);
			}
			break;
		default:

			break;
		}
}

void lit_red_main(){
	HAL_GPIO_WritePin(LED0_R_GPIO_Port, LED0_R_Pin, RESET);
	HAL_GPIO_WritePin(LED0_Y_GPIO_Port, LED0_Y_Pin, SET);
}
void lit_yellow_main(){
	HAL_GPIO_WritePin(LED0_Y_GPIO_Port, LED0_Y_Pin, RESET);
	HAL_GPIO_WritePin(LED0_G_GPIO_Port, LED0_G_Pin, SET);
}
void lit_green_main(){
	HAL_GPIO_WritePin(LED0_G_GPIO_Port, LED0_G_Pin, RESET);
	HAL_GPIO_WritePin(LED0_R_GPIO_Port, LED0_R_Pin, SET);
}
void lit_red_side(){
	HAL_GPIO_WritePin(LED1_R_GPIO_Port, LED1_R_Pin, RESET);
	HAL_GPIO_WritePin(LED1_Y_GPIO_Port, LED1_Y_Pin, SET);
}
void lit_yellow_side(){
	HAL_GPIO_WritePin(LED1_Y_GPIO_Port, LED1_Y_Pin, RESET);
	HAL_GPIO_WritePin(LED1_G_GPIO_Port, LED1_G_Pin, SET);
}
void lit_green_side(){
	HAL_GPIO_WritePin(LED1_G_GPIO_Port, LED1_G_Pin, RESET);
	HAL_GPIO_WritePin(LED1_R_GPIO_Port, LED1_R_Pin, SET);
}

#ifdef UNIT_TEST
void unit_test_traffic(){

}
#endif
