/*
 * input_processing.c
 *
 *  Created on: Oct 9, 2024
 *      Author: TRONG DAT
 */
#include <input_reading.h>
#include "main.h"

// We aim to work with more than one button
#define NUMBER_OF_BUTTONS 3

// Timer interrupt duration is 10ms, so to pass 1 second,
// we need to jump to the interrupt service routine 100 times
#define HOLD_TIME 100
#define RELEASE_TIME 8

#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

//buffer after debouncing
static GPIO_PinState buttonBuffer[NUMBER_OF_BUTTONS];
//buffer for debouncing
static GPIO_PinState debounceButtonBuffer1[NUMBER_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NUMBER_OF_BUTTONS];
//flag
static uint8_t flagForButtonPress[NUMBER_OF_BUTTONS];
static uint8_t flagForButtonHold[NUMBER_OF_BUTTONS];
static uint8_t flagForButtonDoubleTap[NUMBER_OF_BUTTONS];
static uint8_t flagForButtonTapHold[NUMBER_OF_BUTTONS];
//counter
static uint16_t counterForButtonHold[NUMBER_OF_BUTTONS];
static uint16_t counterForButtonRelease[NUMBER_OF_BUTTONS];

GPIO_PinState button_pin_buffer(uint8_t index){//this is no good
	switch(index){
	case 0:
		return HAL_GPIO_ReadPin(BUTTON_0_GPIO_Port, BUTTON_0_Pin);
		break;
	case 1:
		return HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
		break;
	case 2:
		return HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);
		break;
	default:
		break;
	}
	return SET;
}

void button_reading() {
    for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; i++) {
    	//DEBOUNCE
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
        debounceButtonBuffer1[i] = button_pin_buffer(i);

        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
            buttonBuffer[i] = debounceButtonBuffer1[i];

        //UPDATE COUNTER
        if(buttonBuffer[i] == BUTTON_IS_PRESSED){
        	counterForButtonRelease[i] = 0;
        	if(counterForButtonHold[i] < HOLD_TIME) counterForButtonHold[i]++;
        }
        if(buttonBuffer[i] == BUTTON_IS_RELEASED){
        	counterForButtonHold[i] = 0;
        	if(counterForButtonRelease[i] < RELEASE_TIME) counterForButtonRelease[i]++;
        }
        //RECOGNIZE
        if(buttonBuffer[i] == BUTTON_IS_PRESSED){
        	if(counterForButtonRelease[i] >= RELEASE_TIME){//Press or Hold
        		if(counterForButtonHold[i] < HOLD_TIME){//Press
        			flagForButtonPress[i] = 1;
        		}
        		else{//Hold
        			flagForButtonHold[i] = 1;
        		}
        	}
        	else{//Double Tap or Tap Hold
        		if(counterForButtonHold[i] < HOLD_TIME){//Double Tap
        			flagForButtonDoubleTap[i] = 1;
        		}
        		else{//Tap Hold
        			flagForButtonTapHold[i] = 1;
        		}
        	}
        }
        else{//button release idle
        	flagForButtonPress[i] = 0;
        	flagForButtonHold[i] = 0;
        	flagForButtonDoubleTap[i] = 0;
        	flagForButtonTapHold[i] = 0;
        }
    }
}

unsigned char is_button_press(unsigned char index) {
    if (index >= NUMBER_OF_BUTTONS)
        return 0;
    return (flagForButtonPress[index] == 1);
}

unsigned char is_button_hold(unsigned char index) {
    if (index >= NUMBER_OF_BUTTONS)
        return 0;
    return (flagForButtonHold[index] == 1);
}

unsigned char is_button_double_tap(unsigned char index) {
    if (index >= NUMBER_OF_BUTTONS)
        return 0;
    return (flagForButtonDoubleTap[index] == 1);
}

unsigned char is_button_tap_holc(unsigned char index) {
    if (index >= NUMBER_OF_BUTTONS)
        return 0;
    return (flagForButtonTapHold[index] == 1);
}
