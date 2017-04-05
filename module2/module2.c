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

/*
 * Initialize everything needed for project
 * Colors, questions, touch screen and bluetooth
 */
void init_module2()
{
	printf("Initializing module2 stuff...\n");
	initializeColours();
	initBluetooth();
	init_questions();
	printf("test\n");
	Init_Touch();
	printf("test\n");
}

/*
 * State to draw the menu screen and then switch to reading bluetooth commands
 */
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
	drawPlayerUp0(playerCoords);
}

/*
 * Read the character from the bluetooth dongle
 */
void state_receive_bluetooth_command()
{
	printf("Waiting for bluetooth commands...\n");
	int command;
	while (1) {
		// There's a bluetooth command
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

/*
 * State to display the question and user needs to select the question
 */
void state_question()
{
	ask_question();
	//usleep(5000000);
	// User selects question
	int choice = choose_question();
	printf("Chose: %d\n", choice);

	printf("Sending: %c\n",qbox_index[choice]);
	sendStringBluetooth(&qbox_index[choice]);
	if (1){
		printf("test!\n");
		char nextSpaceUp = map[curArea][player_current_y_pos - 1 ][player_current_x_pos];
		printf("Up: %c\n", nextSpaceUp);
		char nextSpaceRight = map[curArea][player_current_y_pos][player_current_x_pos + 1];
		printf("Right: %c\n", nextSpaceRight);
		char nextSpaceDown = map[curArea][player_current_y_pos + 1][player_current_x_pos];
		printf("Down: %c\n", nextSpaceDown);

		// Checks for valid movements
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

/*
 * State for the last stage where player touches princess
 */
void state_last_question()
{
	draw_last_question();
	sendStringBluetooth("L");
	curState = STATE_RECEIVE_BLUETOOTH_COMMAND;
}

/*
 * Draw the finished screen
 */
void state_finish()
{
	draw_finish_screen();
	curState = STATE_RECEIVE_BLUETOOTH_COMMAND;
}

/*
 * Set up the state machine for the game
 */
void state_machine()
{
	printf("Initializing state machine...\n");
	while (1) {
		printf("Current State: %d\n", curState);
		switch (curState)
		{
		// State for being in the menu
		case (STATE_MENU) :
				state_menu();
		break;
		// State for displaying the story
		case (STATE_STORY_TEXT) :
				init_game();
				curState = STATE_REDRAW;
		break;
		// State for redrawing the map
		case (STATE_REDRAW) :
				state_redraw();
		break;
		// State for reading bluetooth commands
		case (STATE_RECEIVE_BLUETOOTH_COMMAND) :
				state_receive_bluetooth_command();
		break;
		// State for questions
		case (STATE_QUESTION) :
				state_question();
		break;
		// State for last game where player reaches princess
		case (STATE_LAST_QUESTION) :
				state_last_question();
		break;
		// State to draw finished state
		case (STATE_FINISH) :
				state_finish();
		break;
		}
	}
}

int main()
{

	init_module2();
	curState = STATE_MENU;
	state_machine();
	return 0;
}


