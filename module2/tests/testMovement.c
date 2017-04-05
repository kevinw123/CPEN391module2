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

bool isValidMovementUp(int area, int playerX, int playerY)
{
	// Player is already at the top of the map
	if (playerY == 0){
		//sendStringBluetooth(MOVE_COMMAND);
		return false;
	}

	char nextSpace = map[area][playerY - 1 ][playerX];
	printf("Next space: %c\n", nextSpace);

	// Direction is headed towards a wall.
	if (nextSpace == '#'){
		//sendStringBluetooth(MOVE_COMMAND);
		return false;
	}
	// Direction is headed towards an enemy.
	if (nextSpace == 'X'){
		//sendStringBluetooth(QUESTION_COMMAND);
		return false;
	}

	// Direction is empty
	if (nextSpace == 'O' || nextSpace == 'P'){
		//sendStringBluetooth(MOVE_COMMAND);
		return true;
	}

	return false;
}

bool isValidMovementRight(int area, int playerX, int playerY)
{
	// Player is already at rightmost of map.
	if (playerX == 15){
		//sendStringBluetooth(MOVE_COMMAND);
		return false;
	}

	char nextSpace = map[area][playerY][playerX + 1];
	printf("Next space: %c\n", nextSpace);

	// Direction is headed towards a wall.
	if (nextSpace == '#'){
		//sendStringBluetooth(MOVE_COMMAND);
		return false;
	}
	// Direction is headed towards an enemy.
	if (nextSpace == 'X'){
		//sendStringBluetooth(QUESTION_COMMAND);
		return false;
	}

	// Direction is empty
	if (nextSpace == 'O' || nextSpace == 'P'){
		//sendStringBluetooth(MOVE_COMMAND);
		return true;
	}

	return false;
}

bool isValidMovementDown(int area, int playerX, int playerY)
{
	// Player is already at bottom
	if (playerY == 7){
		//sendStringBluetooth(MOVE_COMMAND);
		return false;
	}

	char nextSpace = map[area][playerY + 1][playerX];
	printf("Next space: %c\n", nextSpace);

	// Direction is headed towards a wall.
	if (nextSpace == '#'){
		//sendStringBluetooth(MOVE_COMMAND);
		return false;
	}
	// Direction is headed towards an enemy.
	if (nextSpace == 'X'){
		//sendStringBluetooth(QUESTION_COMMAND);
		return false;
	}

	// Direction is empty
	if (nextSpace == 'O' || nextSpace == 'P'){
		//sendStringBluetooth(MOVE_COMMAND);
		return true;
	}

	return false;
}

bool isValidMovementLeft(int area, int playerX, int playerY)
{
	// Player is already at rightmost of map.
	if (playerX == 0){
		//sendStringBluetooth(MOVE_COMMAND);
		return false;
	}

	char nextSpace = map[area][playerY][playerX - 1];
	printf("Next space: %c\n", nextSpace);

	// Direction is headed towards a wall.
	if (nextSpace == '#'){
		//sendStringBluetooth(MOVE_COMMAND);
		return false;
	}
	// Direction is headed towards an enemy.
	if (nextSpace == 'X'){
		//sendStringBluetooth(QUESTION_COMMAND);
		return false;
	}

	// Direction is empty
	if (nextSpace == 'O' || nextSpace == 'P'){
		//sendStringBluetooth(MOVE_COMMAND);
		return true;
	}

	return false;
}

bool isValidMovement(int direction, int area)
{
	if (direction == DIRECTION_UP)
		return isValidMovementUp(area, player_current_x_pos, player_current_y_pos);
	else if (direction == DIRECTION_RIGHT)
		return isValidMovementRight(area, player_current_x_pos, player_current_y_pos);
	else if (direction == DIRECTION_DOWN)
		return isValidMovementDown(area, player_current_x_pos, player_current_y_pos);
	else if (direction == DIRECTION_LEFT)
		return isValidMovementLeft(area, player_current_x_pos, player_current_y_pos);

	return false;
}

bool enemy_isValidMovement(int direction, int area, int enemyPosX, int enemyPosY)
{
	if (direction == DIRECTION_UP)
		return isValidMovementUp(area, enemyPosX, enemyPosY);
	else if (direction == DIRECTION_RIGHT)
		return isValidMovementRight(area, enemyPosX, enemyPosY);
	else if (direction == DIRECTION_DOWN)
		return isValidMovementDown(area, enemyPosX, enemyPosY);
	else if (direction == DIRECTION_LEFT)
		return isValidMovementLeft(area, enemyPosX, enemyPosY);

	return false;
}

bool isValidBluetoothCommand()
{
	return false;
}





