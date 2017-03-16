/*
 * states.h
 *
 *  Created on: 2017-03-12
 *      Author: ahboo
 */

#ifndef STATES_H_
#define STATES_H_

#define STATE_MENU 0
#define STATE_REDRAW 1
#define STATE_RECEIVE_BLUETOOTH_COMMAND 2

// Bluetooth Command Definitions
#define PLAY 0
#define MOVE_UP 1
#define MOVE_RIGHT 2
#define MOVE_DOWN 3
#define MOVE_LEFT 4


// Global ints
static int curState;
static int curArea;

int execCommand(char command);

#endif /* STATES_H_ */
