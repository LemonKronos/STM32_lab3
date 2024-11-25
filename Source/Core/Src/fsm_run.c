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
#include "input_processing.h"

void fsm_run(machine_state mode){
	switch(mode){
	case mode1:// run normally
		if(flagForButtonHold[0] == 1){
			m_mode = modeReset;
			resetButtonFlag();
		}
		else if(flagForButtonPress[0] == 1){
			m_mode = mode2;
			cancel_timer(&timer_flag[1]);
			cancel_timer(&timer_flag[2]);
			flushLed();
			led_counter[0] = main_traffic.red;
			led_counter[1] = 2;
			update7SEG(counter);
			resetButtonFlag();
		}
		else fsm_input_driven_normal();
		break;

	case mode2:
		if(flagForButtonHold[0] == 1){
			m_mode = modeReset;
			resetButtonFlag();
		}
		else if(flagForButtonPress[0] == 1){
			m_mode = mode3;
			flushLed();
			led_counter[0] = main_traffic.yellow;
			led_counter[1] = 3;
			update7SEG(counter);
			resetButtonFlag();
		}
		else fsm_input_driven_config(lRED, &main_traffic.red, &side_traffic.green);
		break;

	case mode3:
		if(flagForButtonHold[0] == 1){
			m_mode = modeReset;
			resetButtonFlag();
		}
		else if(flagForButtonPress[0] == 1){
			m_mode = mode4;
			flushLed();
			led_counter[0] = main_traffic.green;
			led_counter[1] = 4;
			update7SEG(counter);
			resetButtonFlag();
		}
		else fsm_input_driven_config(lYELLOW, &main_traffic.yellow, &side_traffic.red);
		break;

	case mode4:
		if(flagForButtonHold[0] == 1){
			m_mode = modeReset;
			resetButtonFlag();
		}
		else if(flagForButtonPress[0] == 1){
			m_mode = mode1;
			t_mode_main = RED;
			t_mode_side = YELLOW;
			cancel_timer(&timer_flag[3]);
			timer_flag[1] = 1;
			timer_flag[2] = 1;
			timer_flag[3] = 1;
			update7SEG(traffic);
			resetButtonFlag();
		}
		else fsm_input_driven_config(lGREEN, &main_traffic.green, &side_traffic.red);
		break;

	case modeReset:
		resetButtonFlag();
		cancel_timer(&timer_flag[1]);
		cancel_timer(&timer_flag[2]);
		cancel_timer(&timer_flag[3]);
		cancel_timer(&timer_flag[4]);
		cancel_timer(&timer_flag[5]);
		set_timer(1000, &timer_flag[1]);
		set_timer(1000, &timer_flag[2]);
		set_timer(1000, &timer_flag[3]);
		set_timer(1000, &timer_flag[4]);
		set_timer(1000, &timer_flag[5]);

		main_traffic.count_down = 1;
		main_traffic.red = 4;
		main_traffic.yellow = 2;
		main_traffic.green = 4;

		side_traffic.count_down = 1;
		side_traffic.red = 6;
		side_traffic.yellow = 1;
		side_traffic.green = 3;

		m_mode = mode1;
		t_mode_main = RED,
		t_mode_side = YELLOW;
		break;

	default:
		mode = mode1;
		break;
	}
}
