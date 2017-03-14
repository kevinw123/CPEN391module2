#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Module1 Definitions
#include "drawmap.h"
#include "states.h"
#include "mapdesign.h"

void init_module2()
{
	printf("Initializing module2 stuff...\n");
	curState = STATE_REDRAW;
	curArea = 0;
	player_current_x_pos = startPos[curArea][1];
	player_current_y_pos = startPos[curArea][0];
}

void state_machine()
{
	printf("Initializing state machine...\n");
	while(1) {
		switch (curState)
		{
		case (STATE_REDRAW) :
			drawArea(MAX_HORI_SQUARES, MAX_VERT_SQUARES, curArea);
			printf("Valid move up? %d\n", isValidMovementUp(curArea));
			printf("Valid move right? %d\n", isValidMovementRight(curArea));
			printf("Valid move down? %d\n", isValidMovementDown(curArea));
			printf("Valid move left? %d\n", isValidMovementLeft(curArea));
			curState = STATE_RECEIVE_BLUETOOTH_COMMAND;
			break;
		case (STATE_RECEIVE_BLUETOOTH_COMMAND) :
			while(1) {}
			break;
		}
	}
}

int main()
{
	init_module2();
	state_machine();
}
