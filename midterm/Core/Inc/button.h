/*
 * button.h
 *
 *  Created on: Nov 3, 2022
 *      Author: Mr.HUNG
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
//#include "fsm_control_7Seg.h"

#define NORMAL GPIO_PIN_SET
#define PRESSED GPIO_PIN_RESET

void subKeyProcess();
void getKeyInput();

#endif /* INC_BUTTON_H_ */
