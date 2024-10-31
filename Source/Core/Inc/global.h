/*
 * global.h
 *
 *  Created on: 28 thg 10, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define P_CLOCK
#ifdef P_CLOCK
  int p_flag;
  int p_dur;
  void p_clockSet(int dur);
void p_clockRun();
#endif

// software timer
#define SEC 1000
#define NUM_FLAG 8
	/* FLAG NOTE
	 * 0: PA5 TEST_Timer
	 * 1: display 7seg led
	 * 2: traffic light main road
	 * 3: traffic light side road
	 * 4: update 7seg led
	 *
	 *
	 * */
uint8_t timer_flag[NUM_FLAG];
uint8_t flagInterrupt;

// 7 segment led
#define MAX_LED 4
uint8_t led_buffer[MAX_LED];
uint8_t led_index;

// traffic light
typedef enum whichWay{
	main_way,
	side_way
}whichWay;

typedef struct traffic_way{
	whichWay  way;
	uint8_t count_down;
	uint8_t red, yellow, green;
}traffic_way;

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
