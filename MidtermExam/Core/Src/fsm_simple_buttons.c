/*
 * fsm_simple_buttons.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Mr.HUNG
 */

#include "fsm_simple_buttons.h"

#define RESET_BUTTON	0
#define INC_BUTTON		1
#define DEC_BUTTON		2

#define WAIT_TIME		10000
#define AUTO_DEC		1000

void fsm_simple_buttons_run(void) {
	switch(status) {
	case INIT:
		setTimer1(CYCLE);
		setTimer2(CYCLE);
		setTimer3(WAIT_TIME);
		resetCounter();
		status = WAIT;
		break;
	case RST:
		setTimer3(WAIT_TIME);
		resetCounter();
		status = WAIT;
		break;
	case INC:
		setTimer3(WAIT_TIME);
		increaseCounter();
		status = WAIT;
		break;

	case DEC:
		setTimer3(WAIT_TIME);
		decreaseCounter();
		status = WAIT;
		break;

	case HOLD_INC:
		if(timer1_flag == 1 && isButtonHold(INC_BUTTON)) {
			setTimer1(AUTO_DEC);
			increaseCounter();
			display7SEG();
		}

		if(!isButtonHold(INC_BUTTON)) {
			setTimer3(WAIT_TIME);
			status = WAIT;
		}
		break;

	case HOLD_DEC:
		if(timer1_flag == 1 && isButtonHold(DEC_BUTTON)) {
			setTimer1(AUTO_DEC);
			decreaseCounter();
			display7SEG();
		}

		if(!isButtonHold(DEC_BUTTON)) {
			setTimer3(WAIT_TIME);
			status = WAIT;
		}
		break;
	case WAIT:
		display7SEG();

		if(isButtonPressed(RESET_BUTTON)) {
			status = RST;
		}
		if(isButtonPressed(INC_BUTTON)) {
			status = INC;
		}
		if(isButtonPressed(DEC_BUTTON)) {
			status = DEC;
		}

		if(isButtonHold(INC_BUTTON)) {
			setTimer3(0);
			status = HOLD_INC;
		}
		if(isButtonHold(DEC_BUTTON)) {
			setTimer3(0);
			status = HOLD_DEC;
		}

		if(timer3_flag == 1) {
			setTimer1(AUTO_DEC);
			status = AUTO;
			countdown();
			display7SEG();
		}
		break;

	case AUTO:
		if(timer1_flag == 1) {
			setTimer1(AUTO_DEC);
			countdown();
			display7SEG();
		}

		if(isButtonPressed(RESET_BUTTON)) {
			status = RST;
		}

		if(isButtonPressed(INC_BUTTON)) {
			status = INC;
		}

		if(isButtonPressed(DEC_BUTTON)) {
			status = DEC;
		}
		break;

	default: break;
	}
}
