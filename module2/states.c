/*
 * states.c
 *
 *  Created on: 2017-03-14
 *      Author: ahboo
 */


#include "states.h"
#include "movement.h"
#include "mapdesign.h"

int execCommand(char command)
{
	switch (command)
	{
	case(MOVE_UP) :
			printf("Moving up: %d\n", movePlayerUp(player_current_x_pos, player_current_y_pos, curArea));
			break;
	case(MOVE_RIGHT) :
			printf("Moving right: %d\n", movePlayerRight(player_current_x_pos, player_current_y_pos, curArea));
			break;
	case(MOVE_DOWN) :
			printf("Moving down: %d\n", movePlayerDown(player_current_x_pos, player_current_y_pos, curArea));
			break;
	case(MOVE_LEFT) :
			printf("Moving left: %d\n", movePlayerLeft(player_current_x_pos, player_current_y_pos, curArea));
			break;
	}
	return 1;
}
