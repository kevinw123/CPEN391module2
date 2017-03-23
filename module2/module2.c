#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Module1 Definitions
#include "drawmap.h"
#include "states.h"
#include "mapdesign.h"
#include "bluetooth.h"
#include "drawmenu.h"
#include "graphics.h"
#include "questions.h"

void init_module2()
{
	printf("Initializing module2 stuff...\n");
	initializeColours();
	initBluetooth();
	init_game();
}

void state_machine()
{
	printf("Initializing state machine...\n");
	while (1) {
		printf("Current State: %d\n", curState);
		switch (curState)
		{
		case (STATE_MENU) :
			draw_menu();
			curState = STATE_RECEIVE_BLUETOOTH_COMMAND;
			break;
		case (STATE_REDRAW) :
			drawArea(MAX_HORI_SQUARES, MAX_VERT_SQUARES, curArea);
			curState = STATE_RECEIVE_BLUETOOTH_COMMAND;
			Point playerCoords;
			playerCoords = getCoord(player_current_x_pos, player_current_y_pos);
			drawPlayer(playerCoords);
			break;
		case (STATE_RECEIVE_BLUETOOTH_COMMAND) :
			printf("Waiting for bluetooth commands...\n");
			int command;
			while (1) {
				char a = getcharBluetooth();
				if ((a - '0') < 100 && (a - '0') >= 0) {
					command = a - '0';
					printf("Receiving : %c %d\n", a, command);
					break;
				}
			}

			int nextState = execCommand(command);
			curState = nextState;

			break;
		case (STATE_QUESTION) :
			printf("Landed on question...\n");
			// Draw Question Screen

			// Draw four questions? Maybe in a 2x2 grid fashion.

			// Wait for a touch response on any of the four grid options

			// Send a character index to the android according to the question selection

			// Redraw map and character (when running drawmap, it redraws the initial starting map, so we need to redraw
			// the player in the right location

			// set state to receive bluetooth then break
			ask_question();
			usleep(5000000);
			curState = STATE_REDRAW;
			break;
		}
	}
}

int main()
{
	init_module2();
	curState = STATE_REDRAW;
	state_machine();
}


