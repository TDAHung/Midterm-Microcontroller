///*
// * fsm_control_7Seg.c
// *
// *  Created on: Nov 3, 2022
// *      Author: Mr.HUNG
// */

#include "fsm_control_7Seg.h"

#define ENABLE_LED  	GPIO_PIN_RESET
#define DISABLE_LED  	GPIO_PIN_SET

int led_buffer[3]={0,0,0};

void display7Seg(int num){
	HAL_GPIO_WritePin(led7Port, seg1 | seg2 | seg3 | seg4 | seg5 | seg6 | seg7, DISABLE_LED);
	switch(num)
			{
			case 0:
				HAL_GPIO_WritePin(led7Port, seg1 | seg2 | seg3 | seg4 | seg5 | seg6 , ENABLE_LED);
				HAL_GPIO_WritePin(led7Port, seg7, DISABLE_LED);
				break;
			case 1:
				HAL_GPIO_WritePin(led7Port, seg2 | seg3, ENABLE_LED);
				HAL_GPIO_WritePin(led7Port, seg1 | seg4 | seg5 | seg6 | seg7, DISABLE_LED);
				break;
			case 2:
				HAL_GPIO_WritePin(led7Port, seg1 | seg2 | seg4 | seg5 | seg7 , ENABLE_LED);
				HAL_GPIO_WritePin(led7Port, seg3 | seg6 , DISABLE_LED);
				break;
			case 3:
				HAL_GPIO_WritePin(led7Port, seg1 | seg2 | seg3 | seg4  | seg7 , ENABLE_LED);
				HAL_GPIO_WritePin(led7Port, seg5 | seg6 , DISABLE_LED);
				break;
			case 4:
				HAL_GPIO_WritePin(led7Port, seg2 | seg3 | seg6 | seg7 , ENABLE_LED);
				HAL_GPIO_WritePin(led7Port, seg1 | seg4 | seg5 , DISABLE_LED);
				break;
			case 5:
				HAL_GPIO_WritePin(led7Port, seg1 | seg3  | seg4 | seg6 | seg7 , ENABLE_LED);
				HAL_GPIO_WritePin(led7Port, seg5 | seg2 , DISABLE_LED);
				break;
			case 6:
				HAL_GPIO_WritePin(led7Port, seg1 | seg3 | seg4 | seg5 | seg6 | seg7 , ENABLE_LED);
				HAL_GPIO_WritePin(led7Port, seg2 , DISABLE_LED);
				break;
			case 7:
				HAL_GPIO_WritePin(led7Port, seg1 | seg2 | seg3 , ENABLE_LED);
				HAL_GPIO_WritePin(led7Port, seg4 | seg5 | seg6 | seg7 , DISABLE_LED);
				break;
			case 8:
				HAL_GPIO_WritePin(led7Port, seg1 | seg2 | seg3 | seg4 | seg5 | seg6 | seg7, ENABLE_LED);
				break;
			case 9:
				HAL_GPIO_WritePin(led7Port, seg1 | seg2 | seg3 | seg4 | seg6 | seg7, ENABLE_LED);
				HAL_GPIO_WritePin(led7Port, seg5 , DISABLE_LED);
				break;
		}
}

int randomNumber(int min, int max){
	return min + rand() % (max + 1 - min);
}

void update7Seg(){
	HAL_GPIO_WritePin(enPort, EN1 | EN2 | EN3 , 1);
	for(int i = 0; i < 3; i++)
	led_buffer[i] = randomNumber(0,9);
//	led_buffer[i] = 9;
}

int is_Equal(){
	if(led_buffer[0] == 0 && led_buffer[1] == 0 && led_buffer[2] == 0) return 0;
	return (led_buffer[0] == led_buffer[1] && led_buffer[1] == led_buffer[2]);
}

int flag = 1;
void fsm_control_7Seg(){
	if(is_Equal()){
		if(timer1_flag){
			setTimer1(500);
			timer1_flag = 0;
			HAL_GPIO_TogglePin(ledPort,singleLed);
			HAL_GPIO_TogglePin(enPort, EN1 | EN2 | EN3);
			display7Seg(led_buffer[0]);
		}
	}
	else{
		if(timer2_flag){
			setTimer2(500);
			timer2_flag = 0;
			HAL_GPIO_WritePin(enPort, EN1 | EN2 | EN3 , 1);
			switch(flag){
				case 1:
					HAL_GPIO_WritePin(enPort, EN1, 0);
			  		display7Seg(led_buffer[flag - 1]);
			  		flag = 2;
			  		break;
			  	case 2:
			  		HAL_GPIO_WritePin(enPort, EN2, 0);
			  		display7Seg(led_buffer[flag - 1]);
			  		flag = 3;
			  		break;
			  	case 3:
			  		HAL_GPIO_WritePin(enPort, EN3, 0);
			  		display7Seg(led_buffer[flag - 1]);
			  		flag = 1;
			  		break;
			  	default: break;
			}
		}
	}
}
