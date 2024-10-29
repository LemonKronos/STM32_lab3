/*
 * input_processing.h
 *
 *  Created on: Oct 9, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "main.h"

GPIO_PinState button_pin_read(uint8_t index);
void button_reading();
unsigned char is_button_press(unsigned char index);
unsigned char is_button_hold(unsigned char index);
unsigned char is_button_double_tap(unsigned char index);
unsigned char is_button_tap_hold(unsigned char index);
void unit_test_button_read();

#endif /* INC_INPUT_READING_H_ */
