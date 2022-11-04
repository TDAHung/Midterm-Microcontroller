/*
 * timer.h
 *
 *  Created on: Nov 3, 2022
 *      Author: Mr.HUNG
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"
#define TIMER_CYCLE 10
extern int timer1_flag;
extern int timer2_flag;

void setTimer1(int);
void setTimer2(int);
void timerRun();


#endif /* INC_TIMER_H_ */
