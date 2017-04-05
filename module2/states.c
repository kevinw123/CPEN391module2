/*
 * states.c
 *
 *  Created on: 2017-03-14
 *      Author: ahboo
 */


#include "states.h"
#include "movement.h"
#include "mapdesign.h"
#include "drawmap.h"
#include "movement.h"

/*
 * Function to check if player is next to enemy object or princess object
 */
int checkEvents(void) {
	char nextSpaceUp = map[curArea][player_current_y_pos - 1 ][player_current_x_pos];
	char nextSpaceRight = map[curArea][player_current_y_pos][player_current_x_pos + 1];
	char nextSpaceDown = map[curArea][player_current_y_pos + 1][player_current_x_pos];
	char nextSpaceLeft = map[curArea][player_current_y_pos][player_current_x_pos - 1];

	int event = 0;

	// If princess, then trigger the princess state
	if ( (nextSpaceUp == '$') ||  (nextSpaceRight == '$') || (nextSpaceDown == '$') || (nextSpaceLeft == '$')){
		event = EVENT_PRINCESS;
	}

	// If next to an enemy trigger question screen
	else if ( (nextSpaceUp == 'X') ||  (nextSpaceRight == 'X') || (nextSpaceDown == 'X') || (nextSpaceLeft == 'X')){
		event = EVENT_QUESTION;
	}

	// Trigger event based on which event was detected
	switch (event)
	{
	case(0) :
		printf("Sending movement char\n");
		sendStringBluetooth("M");
		return STATE_RECEIVE_BLUETOOTH_COMMAND;
	case(EVENT_PRINCESS) :
			return STATE_LAST_QUESTION;
	case(EVENT_QUESTION) :
			return STATE_QUESTION;
	default :
		return STATE_RECEIVE_BLUETOOTH_COMMAND;
	}
}

int execCommand(int command)
{
	printf("Executing command...\n");
	int check = 0;
	int ret;
	switch (command)
	{
	case (PLAY) :
		printf("Starting game\n");
		//reset enemy locations
		resetEnemyLocation();
		ret = STATE_STORY_TEXT;
		break;
	// move character up
	case (MOVE_UP) :
		redrawEnemies();
		printf("Moving up: %d\n", movePlayerUp(player_current_x_pos, player_current_y_pos, curArea));
		// check if there is a question
		ret = checkEvents();
		break;
	// move character to the right
	case (MOVE_RIGHT) :
		redrawEnemies();
		printf("Moving right: %d\n", movePlayerRight(player_current_x_pos, player_current_y_pos, curArea));
		// check if there is a question
		ret = checkEvents();
		break;
	// move character down
	case (MOVE_DOWN) :
		redrawEnemies();
		printf("Moving down: %d\n", movePlayerDown(player_current_x_pos, player_current_y_pos, curArea));
		// check if there is a question
		ret = checkEvents();
		break;
	// move character to the left
	case (MOVE_LEFT) :
		redrawEnemies();
		printf("Moving left: %d\n", movePlayerLeft(player_current_x_pos, player_current_y_pos, curArea));
		// check if there is a question
		ret = checkEvents();
		break;
	// If we win go to finished state
	case (WIN) :
			ret = STATE_FINISH;
		break;
	default :
		printf("in default\n");
		ret = STATE_RECEIVE_BLUETOOTH_COMMAND;
		break;
	}
	return ret;
}
