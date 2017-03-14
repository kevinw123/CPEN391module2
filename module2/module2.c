#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Module1 Definitions
#include "drawmap.h"
#include "states.h"
#include "mapdesign.h"
#include "bluetooth.h"

void init_module2()
{
	printf("Initializing module2 stuff...\n");
	curState = STATE_REDRAW;
	curArea = 0;
	player_current_y_pos = startPos[curArea][1];
	player_current_x_pos = startPos[curArea][0];
	printf("Player x pos: %d\n", player_current_x_pos);
	printf("Player y pos: %d\n", player_current_y_pos);

	initBluetooth();
}

void state_machine()
{
	printf("Initializing state machine...\n");
	while(1) {
		switch (curState)
		{
		case (STATE_REDRAW) :
			drawArea(MAX_HORI_SQUARES, MAX_VERT_SQUARES, curArea);

		/*
			printf("Valid move up? %d\n", isValidMovementUp(curArea));
			printf("Valid move right? %d\n", isValidMovementRight(curArea));
			printf("Valid move down? %d\n", isValidMovementDown(curArea));
			printf("Valid move left? %d\n", isValidMovementLeft(curArea));

			usleep(10000000);
			printf("%d\n", movePlayerUp(player_current_x_pos, player_current_y_pos, curArea));
			usleep(10000000);
			printf("%d\n", movePlayerRight(player_current_x_pos, player_current_y_pos, curArea));
			usleep(10000000);
			printf("%d\n", movePlayerDown(player_current_x_pos, player_current_y_pos, curArea));
		*/

			curState = STATE_RECEIVE_BLUETOOTH_COMMAND;
			break;
		case (STATE_RECEIVE_BLUETOOTH_COMMAND) :
			printf("Waiting for bluetooth commands...\n");
			char command = getBluetoothCommand();
			int result = execCommand(command);






			while(1) {
				printf("%c\n", getBluetoothCommand());
			}
			break;
		}
	}
}

int main()
{
	init_module2();
	state_machine();
}
