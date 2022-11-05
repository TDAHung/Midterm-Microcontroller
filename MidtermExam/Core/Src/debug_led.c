/*
 * debug_led.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Mr.HUNG
 */

#include "debug_led.h"

void led_debug(void) {
	if(timer2_flag == 1) {
		setTimer2(1000);
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	}
}
