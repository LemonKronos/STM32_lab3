/*
 * input_processing.h
 *
 *  Created on: Oct 9, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

#include "main.h"
#include "global.h"
#include "input_reading.h"
#include "input_processing.h"
#include "display7seg.h"
#include "software_timer.h"
#include "traffic_light.h"
#include "fsm_run.h"

extern traffic_way main_traffic, side_traffic;

typedef enum{
	NORMAL,
	FREEZE,
	FAST,
	FORWARD
}normal_mode;

normal_mode Nmode;

typedef enum{
	WAIT,
	UP,
	UP_FAST,
	DOWN,
	DOWN_FAST
}config_mode;

config_mode Cmode;

typedef enum{
	lRED,
	lYELLOW,
	lGREEN
} ledColor;

void fsm_input_driven_normal();
void fsm_input_driven_config(ledColor color, uint8_t* time1, uint8_t* time2);
void flushLed();
void toggleLed(ledColor color);

#endif /* INC_INPUT_PROCESSING_H_ */
