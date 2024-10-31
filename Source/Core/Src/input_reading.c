/*
 * input_processing.c
 *
 *  Created on: Oct 9, 2024
 *      Author: TRONG DAT
 */
#include <input_reading.h>
#include "main.h"
#include "global.h"

#define UNIT_TEST

// We aim to work with more than one button
// Timer interrupt duration is 10ms, so to pass 1 second,
// we need to jump to the interrupt service routine 100 times
#define HOLD_TIME 100
#define RELEASE_TIME 8

#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

//for unit test
#ifdef UNIT_TEST
#include "display7seg.h"
uint8_t test_button = 0;
#endif
//buffer after debouncing
static GPIO_PinState buttonBuffer[NUMBER_OF_BUTTONS];
//buffer for debouncing
static GPIO_PinState debounceButtonBuffer1[NUMBER_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NUMBER_OF_BUTTONS];
//counter
static uint16_t counterForButtonHold[NUMBER_OF_BUTTONS];
static uint16_t counterForButtonRelease[NUMBER_OF_BUTTONS];

GPIO_PinState button_pin_read(uint8_t index){//this is no good
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
        debounceButtonBuffer1[i] = button_pin_read(i);

        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
            buttonBuffer[i] = debounceButtonBuffer1[i];
        //UPDATE COUNTER

        //REGCONIZE



#ifdef UNIT_TEST
        if(i == 0) test_button = 0;
        test_button = test_button | !buttonBuffer[i];
#endif
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

unsigned char is_button_tap_hold(unsigned char index) {
    if (index >= NUMBER_OF_BUTTONS)
        return 0;
    return (flagForButtonTapHold[index] == 1);
}

#ifdef UNIT_TEST
void unit_test_button_read(){
	if(test_button == 1) HAL_GPIO_WritePin(TEST_Button_GPIO_Port, TEST_Button_Pin, RESET);
	if(test_button == 0) HAL_GPIO_WritePin(TEST_Button_GPIO_Port, TEST_Button_Pin, SET);
}

void unit_test_button_read_adv(unsigned char index){
	if(is_button_press(index)) display7SEG(0); else HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
	if(is_button_hold(index)) display7SEG(1); else HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
	if(is_button_double_tap(index)) display7SEG(2); else HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
	if(is_button_tap_hold(index)) display7SEG(3); else HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);

}
#endif
