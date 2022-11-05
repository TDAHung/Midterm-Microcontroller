/*
 * button.h
 *
 *  Created on: Nov 1, 2022
 *      Author: Mr.HUNG
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "main.h"
#include "timer.h"

void button_reading(void);
int isButtonPressed(int index);
int isButtonHold(int index);

#endif /* INC_INPUT_READING_H_ */
