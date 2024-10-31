/*
 * input_processing.c
 *
 *  Created on: Oct 9, 2024
 *      Author: TRONG DAT
 */
#include "main.h"
#include "input_reading.h"

typedef enum ButtonState {
    BUTTON_IDLE,
    BUTTON_PRESS,
    BUTTON_HOLD,
	BUTTON_DTAP,
	BUTTON_THOLD
}ButtonState;

ButtonState buttonState = BUTTON_IDLE;

void fsm_for_input_processing(void) {
    switch (buttonState) {
        case BUTTON_IDLE:
            if (is_button_press(0)) {
                // TODO: Increase the value of PORT A by one unit
            }
            break;
        case BUTTON_PRESS:

            break;
        case BUTTON_HOLD:

            // TODO: Add further functionality here
            break;
        case BUTTON_DTAP:

        	break;
        case BUTTON_THOLD:

        	break;
        default:

        	break;
    }
}

