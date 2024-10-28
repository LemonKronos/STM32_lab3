/*
 * input_processing.c
 *
 *  Created on: Oct 9, 2024
 *      Author: TRONG DAT
 */
#include "main.h"
#include "input_reading.h"

enum ButtonState {
    BUTTON_RELEASED,
    BUTTON_PRESSED,
    BUTTON_PRESSED_MORE_THAN_1_SECOND
};

enum ButtonState buttonState = BUTTON_RELEASED;

void fsm_for_input_processing(void) {
    switch (buttonState) {
        case BUTTON_RELEASED:
            if (is_button_press(0)) {
                buttonState = BUTTON_PRESSED;
                // TODO: Increase the value of PORT A by one unit
            }
            break;
        case BUTTON_PRESSED:
            if (!is_button_press(0)) {
                buttonState = BUTTON_RELEASED;
            } else {
                if (is_button_hold(0)) {
                    buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND;
                }
            }
            break;
        case BUTTON_PRESSED_MORE_THAN_1_SECOND:
            if (!is_button_press(0)) {
                buttonState = BUTTON_RELEASED;
            }
            // TODO: Add further functionality here
            break;
    }
}

