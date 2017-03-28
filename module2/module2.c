#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Module1 Definitions
#include "drawmap.h"
#include "states.h"
#define MAIN_FILE
#include "mapdesign.h"
#include "bluetooth.h"
#include "drawmenu.h"
#include "graphics.h"
#include "questions.h"

void init_module2()
{
	printf("Initializing module2 stuff...\n");
	initializeColours();
	printf("test\n");
	initBluetooth();
	printf("test\n");
	//Init_Touch();
	printf("test\n");
	init_game();
	printf("test\n");
}

void state_menu()
{
	draw_menu();
	curState = STATE_RECEIVE_BLUETOOTH_COMMAND;
}

void state_redraw()
{
	drawArea(MAX_HORI_SQUARES, MAX_VERT_SQUARES, curArea);
	curState = STATE_RECEIVE_BLUETOOTH_COMMAND;
	Point playerCoords;
	playerCoords = getCoord(player_current_x_pos, player_current_y_pos);
	drawPlayer(playerCoords);
}

void state_receive_bluetooth_command()
{
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
}

void state_question()
{
	ask_question();
	usleep(5000000);
	int choice = 1;//choose_question();
	printf("Chose: %d\n", choice);
	// Send qbox index to the android according to the question selection
	printf("Sending: %c\n",qbox_index[choice]);
	sendStringBluetooth(&qbox_index[choice]);
	// Redraw map and character (when running drawmap, it redraws the initial starting map, so we need to redraw
	// the player in the right location
	// set state to receive bluetooth then break
	if (1){
		printf("test!\n");
		char nextSpaceUp = map[curArea][player_current_y_pos - 1 ][player_current_x_pos];
		printf("Up: %c\n", nextSpaceUp);
		char nextSpaceRight = map[curArea][player_current_y_pos][player_current_x_pos + 1];
		printf("Right: %c\n", nextSpaceRight);
		char nextSpaceDown = map[curArea][player_current_y_pos + 1][player_current_x_pos];
		printf("Down: %c\n", nextSpaceDown);
		if (nextSpaceUp == 'X') {
			map[curArea][player_current_y_pos - 1][player_current_x_pos] = 'O';
			printf("testbdasd: %c\n", map[curArea][player_current_y_pos - 1][player_current_x_pos]);
		}
		else if (nextSpaceRight == 'X')
			map[curArea][player_current_y_pos][player_current_x_pos + 1] = 'O';
		else if (nextSpaceDown == 'X')
			map[curArea][player_current_y_pos + 1][player_current_x_pos] = 'O';
		else
			map[curArea][player_current_y_pos][player_current_x_pos - 1] = 'O';
	}
	curState = STATE_REDRAW;
}

void state_finish()
{
	draw_finish_screen();
}

void state_machine()
{
	printf("Initializing state machine...\n");
	while (1) {
		printf("Current State: %d\n", curState);
		switch (curState)
		{
		case (STATE_MENU) :
				state_menu();
		break;
		case (STATE_REDRAW) :
				state_redraw();
		break;
		case (STATE_RECEIVE_BLUETOOTH_COMMAND) :
				state_receive_bluetooth_command();
		break;
		case (STATE_QUESTION) :
				state_question();
		break;
		case (STATE_FINISH) :
				state_finish();
		break;
		}
	}
}

int main()
{
	init_module2();
	curState = STATE_REDRAW;
	state_machine();
	return 0;
}


