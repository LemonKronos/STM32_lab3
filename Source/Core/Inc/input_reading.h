/*
 * input_processing.h
 *
 *  Created on: Oct 9, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "main.h"

#define UNIT_TEST

GPIO_PinState button_pin_read(uint8_t index);
void button_reading();
unsigned char is_button_press(unsigned char index);
unsigned char is_button_hold(unsigned char index);
unsigned char is_button_double_tap(unsigned char index);
unsigned char is_button_tap_hold(unsigned char index);

#ifdef UNIT_TEST
void unit_test_button_read();
void unit_test_button_read_adv(unsigned char index);
#endif

#endif /* INC_INPUT_READING_H_ */
