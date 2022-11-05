/*
 * global.h
 *
 *  Created on: Oct 29, 2022
 *      Author: Mr.HUNG
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "timer.h"
#include "7segment_control.h"

typedef enum  {
	INIT,
	RST,
	INC,
	DEC,
	HOLD_INC,
	HOLD_DEC,
	AUTO,
	WAIT,
} State;

extern State status;

#endif /* INC_GLOBAL_H_ */
