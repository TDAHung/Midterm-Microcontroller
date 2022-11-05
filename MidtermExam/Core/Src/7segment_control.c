/*
 * 7segment_control.c
 *
 *  Created on: Oct 29, 2022
 *      Author: Mr.HUNG
 */

#include "7segment_control.h"

#define NO_OF_SEGMENTS	7
#define NO_OF_VALUES 	10

#define SECOND 			1000

//seven segment ports and pins
GPIO_TypeDef * sevenSegPort[NO_OF_SEGMENTS] = {
	SEG0_GPIO_Port,
	SEG1_GPIO_Port,
	SEG2_GPIO_Port,
	SEG3_GPIO_Port,
	SEG4_GPIO_Port,
	SEG5_GPIO_Port,
	SEG6_GPIO_Port
};

uint16_t sevenSegPin[NO_OF_SEGMENTS] = {
	SEG0_Pin,
	SEG1_Pin,
	SEG2_Pin,
	SEG3_Pin,
	SEG4_Pin,
	SEG5_Pin,
	SEG6_Pin
};

//seven segment display
const uint8_t sevenSegValue[NO_OF_VALUES] = {
	0x40, // 0
	0x79, // 1
	0x24, // 2
	0x30, // 3
	0x19, // 4
	0x12, // 5
	0x02, // 6
	0x78, // 7
	0x00, // 8
	0x10, // 9
};

//seven segment buffer
int counter;

//seven segment functions
void update7SEG(int num) {
	for(int i = 0; i < NO_OF_SEGMENTS; i++) {
		HAL_GPIO_WritePin(sevenSegPort[i], sevenSegPin[i], (sevenSegValue[num] >> i) & 0x01);
	}
}

void resetCounter(void) {
	counter = 0;
}

void increaseCounter(void) {
	if(++counter > 9) counter = 0;
}

void decreaseCounter(void) {
	if(--counter < 0) counter = 9;
}

void countdown(void) {
	if(counter > 0) counter--;
}

void display7SEG(void) {
	update7SEG(counter);
}
