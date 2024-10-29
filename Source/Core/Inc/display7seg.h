/*
 * display7seg.h
 *
 *  Created on: 1 thg 10, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_DISPLAY7SEG_H_
#define INC_DISPLAY7SEG_H_

#include "main.h"
#include "global.h"

extern uint8_t led_buffer[MAX_LED];
extern int led_index;
GPIO_TypeDef* port[7];
uint16_t pin[7];

void display7SEG(int index);

void update7SEG();

void countDown7SEG();

void number7SEG(int number);

void unit_test_7seg();

#endif /* INC_DISPLAY7SEG_H_ */
