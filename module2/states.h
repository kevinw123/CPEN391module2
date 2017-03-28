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
#define STATE_QUESTION 3
#define STATE_FINISH 4


// Bluetooth Command Definitions
#define PLAY 0
#define MOVE_UP 1
#define MOVE_RIGHT 2
#define MOVE_DOWN 3
#define MOVE_LEFT 4
#define QUESTION 5
#define SCROLL_TEXT 6

// Events
#define EVENT_PRINCESS 1
#define EVENT_QUESTION 2
#define EVENT_KEY 3


// Global ints
static int curState;
static int curArea;

int execCommand(int command);
int checkCombat(void);

#endif /* STATES_H_ */
