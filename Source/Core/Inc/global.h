/*
 * global.h
 *
 *  Created on: 28 thg 10, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

// software timer
#define NUM_FLAG 4
uint8_t timer_flag[NUM_FLAG];

// 7 segment led
#define MAX_LED 4
uint8_t led_buffer[MAX_LED];
int led_index;

// traffic light
uint8_t counter[2];
uint8_t red_main, yellow_main, green_main,
		red_side, yellow_side, green_side;
uint8_t current_red_main, current_yellow_main, current_green_main,
		current_red_side, current_yellow_side, current_green_side;

// button
#define NUMBER_OF_BUTTONS 3
unsigned char
	flagForButtonPress[NUMBER_OF_BUTTONS],
	flagForButtonHold[NUMBER_OF_BUTTONS],
	flagForButtonDoubleTap[NUMBER_OF_BUTTONS],
	flagForButtonTapHold[NUMBER_OF_BUTTONS];

// finite state machine
typedef enum machine_state{
	mode1,
	mode2,
	mode3,
	mode4
}machine_state;
machine_state m_mode;
#endif /* INC_GLOBAL_H_ */
