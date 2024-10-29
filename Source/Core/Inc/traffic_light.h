/*
 * traffic_light.h
 *
 *  Created on: Oct 28, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#include "main.h"
#include "display7seg.h"

//#define UNIT_TEST

typedef enum traffic_mode{
	RED,
	YELLOW,
	GREEN
}traffic_mode;

typedef enum traffic_way{
	main_way,
	side_way
}traffic_way;

traffic_mode t_mode_main, t_mode_side;

extern uint8_t	red_main, yellow_main, green_main,
				red_side, yellow_side, green_side;
extern uint8_t 	current_red_main, current_yellow_main, current_green_main,
				current_red_side, current_yellow_side, current_green_side;

void fsm_traffic_main(traffic_mode mode);
void fsm_traffic_side(traffic_mode mode);
void lit_red_main();
void lit_yellow_main();
void lit_green_main();
void lit_red_side();
void lit_yellow_side();
void lit_green_side();

#ifdef UNIT_TEST
void unit_test_traffic();
#endif

#endif /* INC_TRAFFIC_LIGHT_H_ */
