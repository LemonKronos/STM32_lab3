/*
 * global.c
 *
 *  Created on: 28 thg 10, 2024
 *      Author: TRONG DAT
 */
#include "main.h"
#include "global.h"

#ifdef P_CLOCK
  int p_flag = 0;
  int p_dur  = 0;
  void p_clockSet(int dur){
	  p_flag = 0;
	  p_dur = dur / 10;

  }
  void p_clockRun(){
	  p_dur--;
	  if(p_dur == 0) p_flag = 1;
  }
#endif

// software timer
uint8_t timer_flag[NUM_FLAG]= {0, 0, 0, 0};

// 7 segment
uint8_t led_index = 0;

// traffic light
traffic_way main_traffic = {
		.way = main_way,
		.count_down = 1,
		.red = 4,
		.yellow = 2,
		.green = 4
};
traffic_way side_traffic = {
		.way = side_way,
		.count_down = 1,
		.red = 6,
		.yellow = 1,
		.green = 3
};

// finite state machine
machine_state m_mode = mode1;
