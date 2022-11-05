/*
 * button.c
 *
 *  Created on: Nov 1, 2022
 *      Author: Mr.HUNG
 */
#include "button.h"

#define NO_OF_BUTTONS 				       3

#define BUTTON_HOLD		   				   3000
#define PRESSED                  		   GPIO_PIN_RESET
#define NORMAL                 			   GPIO_PIN_SET

GPIO_TypeDef * buttonPort[NO_OF_BUTTONS] = {
	RESET_GPIO_Port,
	INC_GPIO_Port,
	DEC_GPIO_Port
};

uint16_t buttonPin[NO_OF_BUTTONS] = {
	RESET_Pin,
	INC_Pin,
	DEC_Pin
};

uint8_t buttonBuffer[NO_OF_BUTTONS] = {NORMAL, NORMAL, NORMAL};
uint8_t ButtonBuffer0[NO_OF_BUTTONS] = {NORMAL, NORMAL, NORMAL};
uint8_t ButtonBuffer1[NO_OF_BUTTONS] = {NORMAL, NORMAL, NORMAL};
uint8_t ButtonBuffer2[NO_OF_BUTTONS] = {NORMAL, NORMAL, NORMAL};

int flagButtonPressed[NO_OF_BUTTONS];
int flagButtonHold[NO_OF_BUTTONS];

int counterButtonHold[NO_OF_BUTTONS] = {0, 0, 0};

void button_reading(){
	for(int i = 0; i < NO_OF_BUTTONS; i++) {
		ButtonBuffer2[i] = ButtonBuffer1[i];
		ButtonBuffer1[i] = ButtonBuffer0[i];
		ButtonBuffer0[i] = HAL_GPIO_ReadPin(buttonPort[i], buttonPin[i]);
		if((ButtonBuffer2[i] == ButtonBuffer1[i]) && (ButtonBuffer1[i] == ButtonBuffer0[i])) {
			if(buttonBuffer[i] != ButtonBuffer0[i]) {
				buttonBuffer[i] = ButtonBuffer0[i];
				if(buttonBuffer[i] == PRESSED) {
					counterButtonHold[i] = BUTTON_HOLD;
					if(CYCLE > 0) counterButtonHold[i] /= CYCLE;
					flagButtonPressed[i] = 1;
				}
				else flagButtonHold[i] = 0;
			}
			else {
				if(buttonBuffer[i] == PRESSED) {
					counterButtonHold[i]--;
					if(counterButtonHold[i] == 0) flagButtonHold[i] = 1;
				}
			}
		}
	}
}

int isButtonPressed(int index) {
	if(index < 0 || index > NO_OF_BUTTONS) return 0;
	if(flagButtonPressed[index] == 1) {
		flagButtonPressed[index] = 0;
		return 1;
	}
	return 0;
}

int isButtonHold(int index) {
	if(index < 0 || index > NO_OF_BUTTONS) return 0;
	if(flagButtonHold[index] == 1) {
		return 1;
	}
	return 0;
}
