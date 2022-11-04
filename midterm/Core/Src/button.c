/*
 * button.c
 *
 *  Created on: Nov 3, 2022
 *      Author: Mr.HUNG
 */

#include "button.h"
#include "fsm_control_7Seg.h"

int KeyReg0 = NORMAL;
int KeyReg1 = NORMAL;
int KeyReg2 = NORMAL;

int KeyReg3 = NORMAL;
int TimerForKeyPress = 100;

void subKeyProcess(){
	update7Seg();
}

void getKeyInput(){
	KeyReg0 = KeyReg1;
	KeyReg1 = KeyReg2;
	KeyReg2 = HAL_GPIO_ReadPin(BTNPort,button);
	if((KeyReg0 == KeyReg1) && (KeyReg1 == KeyReg2)){
		if(KeyReg3 != KeyReg2) {
			KeyReg3 = KeyReg2;

			if(KeyReg2 == PRESSED){
				TimerForKeyPress = 200;
				subKeyProcess();
			}
		}
		else {
			TimerForKeyPress--;
			if(TimerForKeyPress == 0){
				if(KeyReg2 == PRESSED) subKeyProcess();
				TimerForKeyPress = 200;
			}
		}
	}
}
