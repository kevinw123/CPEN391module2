/*
 * testMovement.c
 *
 *  Created on: 2017-03-13
 *      Author: ahboo
 */
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "../mapdesign.h"
#include "../graphics.h"
#include "../touchscreen.h"
#include "../Colours.h"
#include "../drawmap.h"
#include "../states.h"
#include "../movement.h"
#include "../questions.h"
#include "../bluetooth.h"

//static player_current_x_pos;
//static player_current_y_pos;

bool isValidMovementUp(int area)
{
	// Player is already at the top of the map
	if (player_current_y_pos == 0){
		sendStringBluetooth(MOVE_COMMAND);
		return false;
	}

	char nextSpace = map[area][player_current_y_pos - 1 ][player_current_x_pos];
	printf("Next space: %c\n", nextSpace);

	// Direction is headed towards a wall.
	if (nextSpace == '#'){
		sendStringBluetooth(MOVE_COMMAND);
		return false;
	}
	// Direction is headed towards an enemy.
	if (nextSpace == 'X'){
		sendStringBluetooth(QUESTION_COMMAND);
		return false;
	}

	// Direction is empty
	if (nextSpace == 'O' || nextSpace == 'P'){
		sendStringBluetooth(MOVE_COMMAND);
		return true;
	}

	return false;
}

bool isValidMovementRight(int area)
{
	// Player is already at rightmost of map.
	if (player_current_x_pos == 15){
		sendStringBluetooth(MOVE_COMMAND);
		return false;
	}

	char nextSpace = map[area][player_current_y_pos][player_current_x_pos + 1];
	printf("Next space: %c\n", nextSpace);

	// Direction is headed towards a wall.
	if (nextSpace == '#'){
		sendStringBluetooth(MOVE_COMMAND);
		return false;
	}
	// Direction is headed towards an enemy.
	if (nextSpace == 'X'){
		sendStringBluetooth(QUESTION_COMMAND);
		return false;
	}

	// Direction is empty
	if (nextSpace == 'O' || nextSpace == 'P'){
		sendStringBluetooth(MOVE_COMMAND);
		return true;
	}

	return false;
}

bool isValidMovementDown(int area)
{
	// Player is already at bottom
	if (player_current_y_pos == 7){
		sendStringBluetooth(MOVE_COMMAND);
		return false;
	}

	char nextSpace = map[area][player_current_y_pos + 1][player_current_x_pos];
	printf("Next space: %c\n", nextSpace);

	// Direction is headed towards a wall.
	if (nextSpace == '#'){
		sendStringBluetooth(MOVE_COMMAND);
		return false;
	}
	// Direction is headed towards an enemy.
	if (nextSpace == 'X'){
		sendStringBluetooth(QUESTION_COMMAND);
		return false;
	}

	// Direction is empty
	if (nextSpace == 'O' || nextSpace == 'P'){
		sendStringBluetooth(MOVE_COMMAND);
		return true;
	}

	return false;
}

bool isValidMovementLeft(int area)
{
	// Player is already at rightmost of map.
	if (player_current_x_pos == 0){
		sendStringBluetooth(MOVE_COMMAND);
		return false;
	}

	char nextSpace = map[area][player_current_y_pos][player_current_x_pos - 1];
	printf("Next space: %c\n", nextSpace);

	// Direction is headed towards a wall.
	if (nextSpace == '#'){
		sendStringBluetooth(MOVE_COMMAND);
		return false;
	}
	// Direction is headed towards an enemy.
	if (nextSpace == 'X'){
		sendStringBluetooth(QUESTION_COMMAND);
		return false;
	}

	// Direction is empty
	if (nextSpace == 'O' || nextSpace == 'P'){
		sendStringBluetooth(MOVE_COMMAND);
		return true;
	}

	return false;
}

bool isValidMovement(int direction, int area)
{
	if (direction == DIRECTION_UP)
		return isValidMovementUp(area);
	else if (direction == DIRECTION_RIGHT)
		return isValidMovementRight(area);
	else if (direction == DIRECTION_DOWN)
		return isValidMovementDown(area);
	else if (direction == DIRECTION_LEFT)
		return isValidMovementLeft(area);
}

bool isValidBluetoothCommand()
{
	return false;
}





