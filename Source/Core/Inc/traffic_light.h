/*
 * traffic_light.h
 *
 *  Created on: Oct 28, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#include "main.h"
#include "global.h"

//#define UNIT_TEST

typedef enum traffic_mode{
	RED,
	YELLOW,
	GREEN
}traffic_mode;
traffic_mode t_mode_main, t_mode_side;

void fsm_traffic(traffic_mode* mode, traffic_way* Tway, uint8_t* timer_flag, uint8_t index);
void lit_red(whichWay way);
void lit_yellow(whichWay way);
void lit_green(whichWay way);

#ifdef UNIT_TEST
void unit_test_traffic();
#endif

#endif /* INC_TRAFFIC_LIGHT_H_ */
