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

void fsm_run(machine_state mode){
	switch(mode){
	case mode1:// run normaly
		fsm_traffic_main(t_mode_main);
		fsm_traffic_side(t_mode_side);
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
