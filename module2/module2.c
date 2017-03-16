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

void init_module2()
{
	printf("Initializing module2 stuff...\n");
	initializeColours();
	initBluetooth();
}

void state_machine()
{
	printf("Initializing state machine...\n");
	while (1) {
		switch (curState)
		{
		case (STATE_MENU) :
			draw_menu();
			curState = STATE_RECEIVE_BLUETOOTH_COMMAND;
			break;

		case (STATE_REDRAW) :
			drawArea(MAX_HORI_SQUARES, MAX_VERT_SQUARES, curArea);


			printf("Valid move up? %d\n", isValidMovementUp(curArea));
			printf("Valid move right? %d\n", isValidMovementRight(curArea));
			printf("Valid move down? %d\n", isValidMovementDown(curArea));
			printf("Valid move left? %d\n", isValidMovementLeft(curArea));


			/*execCommand(1);
			usleep(300000);
			execCommand(1);
			usleep(300000);
			execCommand(1);
			usleep(300000);
			execCommand(1);
			usleep(300000);
			execCommand(1);
			usleep(300000);
			execCommand(1);
			usleep(300000);
			execCommand(3);
			usleep(300000);
			execCommand(3);
			usleep(300000);
			execCommand(3);
			usleep(300000);
			execCommand(3);
			usleep(300000);
			execCommand(2);
			usleep(300000);
			execCommand(2);
			usleep(300000);
			execCommand(2);
			usleep(300000);
			execCommand(4);
			usleep(300000);
			execCommand(4);
			usleep(300000);
			execCommand(4);
			usleep(300000);
			execCommand(4);*/

			curState = STATE_RECEIVE_BLUETOOTH_COMMAND;
			break;
		case (STATE_RECEIVE_BLUETOOTH_COMMAND) :
			printf("Waiting for bluetooth commands...\n");
			char command;
			while (1) {
				char a = getcharBluetooth();
				if ((a - '0') < 5 && (a - '0') >= 0) {
					printf("Receiving : %c\n", a);
					command = a - '0';
					if (command == PLAY){
						curState = STATE_REDRAW;
					}
				}
				if (a == '$') {
					printf("Receiving : %c\n", a);
					break;
				}
			}
			execCommand(command);

			break;
		}
		printf("Current State: %d\n", curState);
	}
}

int main()
{
	init_module2();
	state_machine();
}


