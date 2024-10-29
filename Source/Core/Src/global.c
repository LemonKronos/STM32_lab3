/*
 * global.c
 *
 *  Created on: 28 thg 10, 2024
 *      Author: TRONG DAT
 */
#include "main.h"
#include "global.h"

uint8_t counter[2] = {100, 100};
int led_index = 0;
uint8_t timer_flag[NUM_FLAG]= {0, 0, 0, 0};
uint8_t red_main = 10,
		yellow_main = 3,
		green_main = 20,
		red_side = 23,
		yellow_side = 2,
		green_side = 8;
machine_state m_mode = mode1;
