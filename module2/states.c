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

int checkEvents(void) {
	char nextSpaceUp = map[curArea][player_current_y_pos - 1 ][player_current_x_pos];
	char nextSpaceRight = map[curArea][player_current_y_pos][player_current_x_pos + 1];
	char nextSpaceDown = map[curArea][player_current_y_pos + 1][player_current_x_pos];
	char nextSpaceLeft = map[curArea][player_current_y_pos][player_current_x_pos - 1];

	int event = 0;

	if ( (nextSpaceUp == '$') ||  (nextSpaceRight == '$') || (nextSpaceDown == '$') || (nextSpaceLeft == '$')){
		event = EVENT_PRINCESS;
	}

	else if ( (nextSpaceUp == 'X') ||  (nextSpaceRight == 'X') || (nextSpaceDown == 'X') || (nextSpaceLeft == 'X')){
		event = EVENT_QUESTION;
	}

	switch (event)
	{
	case(EVENT_PRINCESS) :
			return STATE_FINISH;
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
		init_game();
		ret = STATE_REDRAW;
		break;
	case (MOVE_UP) :
		printf("Moving up: %d\n", movePlayerUp(player_current_x_pos, player_current_y_pos, curArea));
		ret = checkEvents();
		break;
	case (MOVE_RIGHT) :
		printf("Moving right: %d\n", movePlayerRight(player_current_x_pos, player_current_y_pos, curArea));
		ret = checkEvents();
		break;
	case (MOVE_DOWN) :
		printf("Moving down: %d\n", movePlayerDown(player_current_x_pos, player_current_y_pos, curArea));
		ret = checkEvents();
		break;
	case (MOVE_LEFT) :
		printf("Moving left: %d\n", movePlayerLeft(player_current_x_pos, player_current_y_pos, curArea));
		ret = checkEvents();
		break;
	default :
		printf("in default\n");
		ret = STATE_RECEIVE_BLUETOOTH_COMMAND;
		break;
	}
	return ret;
}
