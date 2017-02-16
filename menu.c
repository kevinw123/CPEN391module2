#include "Gps.h"
#include "graphics.h"
#include "touchscreen.h"
#include "Colours.h"
#include "wifi.h"
#include "jsmn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Home Menu Bounds
#define CURS_BOUND_1_Y		2
#define CURS_BOUND_1_X		2
#define CURS_BOUND_2_Y		397
#define CURS_BOUND_2_X		237

#define CALL_BOUND_1_Y		2
#define CALL_BOUND_1_X		242
#define CALL_BOUND_2_Y		397
#define CALL_BOUND_2_X		477

#define ACHIEVE_BOUND_1_Y		402
#define ACHIEVE_BOUND_1_X		242
#define ACHIEVE_BOUND_2_Y		797
#define ACHIEVE_BOUND_2_X		477

#define PREV_BOUND_1_Y		407
#define PREV_BOUND_1_X		2
#define PREV_BOUND_2_Y		797
#define PREV_BOUND_2_X		237

// Current Session Bounds
#define CURRENT_HOME_BOUND_1_Y		2
#define CURRENT_HOME_BOUND_1_X		429
#define CURRENT_HOME_BOUND_2_Y		400
#define CURRENT_HOME_BOUND_2_X		477

#define CURRENT_START_BOUND_1_Y		402
#define CURRENT_START_BOUND_1_X		429
#define CURRENT_START_BOUND_2_Y		797
#define CURRENT_START_BOUND_2_X		477

// Call Bounds
#define CALLMENU_HOME_BOUND_1_Y		2
#define CALLMENU_HOME_BOUND_1_X		429
#define CALLMENU_HOME_BOUND_2_Y		399
#define CALLMENU_HOME_BOUND_2_X		477

#define CALLMENU_CALL_BOUND_1_Y		403
#define CALLMENU_CALL_BOUND_1_X		429
#define CALLMENU_CALL_BOUND_2_Y		797
#define CALLMENU_CALL_BOUND_2_X		477

#define CALLMENU_CALL_CLEAR_BOUND_1_Y   530
#define CALLMENU_CALL_CLEAR_BOUND_1_X	349
#define CALLMENU_CALL_CLEAR_BOUND_2_Y   791
#define CALLMENU_CALL_CLEAR_BOUND_2_X   425

#define CALLMENU_CALL_0_BOUND_1_Y   265
#define CALLMENU_CALL_0_BOUND_1_X	349
#define CALLMENU_CALL_0_BOUND_2_Y   526
#define CALLMENU_CALL_0_BOUND_2_X   425

#define CALLMENU_CALL_1_BOUND_1_Y   2
#define CALLMENU_CALL_1_BOUND_1_X	263
#define CALLMENU_CALL_1_BOUND_2_Y   261
#define CALLMENU_CALL_1_BOUND_2_X   345

#define CALLMENU_CALL_2_BOUND_1_Y   265
#define CALLMENU_CALL_2_BOUND_1_X	263
#define CALLMENU_CALL_2_BOUND_2_Y   526
#define CALLMENU_CALL_2_BOUND_2_X   345

#define CALLMENU_CALL_3_BOUND_1_Y   530
#define CALLMENU_CALL_3_BOUND_1_X	263
#define CALLMENU_CALL_3_BOUND_2_Y   791
#define CALLMENU_CALL_3_BOUND_2_X   345

#define CALLMENU_CALL_4_BOUND_1_Y   2
#define CALLMENU_CALL_4_BOUND_1_X	177
#define CALLMENU_CALL_4_BOUND_2_Y   261
#define CALLMENU_CALL_4_BOUND_2_X   259

#define CALLMENU_CALL_5_BOUND_1_Y   265
#define CALLMENU_CALL_5_BOUND_1_X	177
#define CALLMENU_CALL_5_BOUND_2_Y   526
#define CALLMENU_CALL_5_BOUND_2_X   259

#define CALLMENU_CALL_6_BOUND_1_Y   530
#define CALLMENU_CALL_6_BOUND_1_X	177
#define CALLMENU_CALL_6_BOUND_2_Y   791
#define CALLMENU_CALL_6_BOUND_2_X   259

#define CALLMENU_CALL_7_BOUND_1_Y   2
#define CALLMENU_CALL_7_BOUND_1_X	85
#define CALLMENU_CALL_7_BOUND_2_Y   261
#define CALLMENU_CALL_7_BOUND_2_X   173

#define CALLMENU_CALL_8_BOUND_1_Y   265
#define CALLMENU_CALL_8_BOUND_1_X	85
#define CALLMENU_CALL_8_BOUND_2_Y   526
#define CALLMENU_CALL_8_BOUND_2_X   173

#define CALLMENU_CALL_9_BOUND_1_Y   530
#define CALLMENU_CALL_9_BOUND_1_X	85
#define CALLMENU_CALL_9_BOUND_2_Y   791
#define CALLMENU_CALL_9_BOUND_2_X   173

// Achievement Bounds
#define ACHIEVE_HOME_BOUND_1_Y		202
#define ACHIEVE_HOME_BOUND_1_X		429
#define ACHIEVE_HOME_BOUND_2_Y		599
#define ACHIEVE_HOME_BOUND_2_X		477

// Previous Session Bounds
#define PREV_HOME_BOUND_1_Y		2
#define PREV_HOME_BOUND_1_X		429
#define PREV_HOME_BOUND_2_Y		399
#define PREV_HOME_BOUND_2_X		477

#define PREV_NEXT_PAGE_BOUND_1_Y		403
#define PREV_NEXT_PAGE_BOUND_1_X		429
#define PREV_NEXT_PAGE_BOUND_2_Y		797
#define PREV_NEXT_PAGE_BOUND_2_X		477
// Home States
#define STATE_CALL			1
#define STATE_CURS			2
#define STATE_ACHIEVE		3
#define STATE_PRES			4
#define STATE_HOME			5


// Current Session States
#define STATE_CURRENT_INIT		1
#define STATE_CURRENT_STARTED	2
#define STATE_CURRENT_SESSION	3
#define STATE_CURRENT_STOPPED	4
#define STATE_CURRENT_HOME		5

// Call States
#define STATE_CALLMENU_HOME			1
#define STATE_CALLMENU_CALL			2
#define STATE_CALLMENU				3
#define STATE_CALLMENU_0			4
#define STATE_CALLMENU_1			5
#define STATE_CALLMENU_2			6
#define STATE_CALLMENU_3			7
#define STATE_CALLMENU_4			8
#define STATE_CALLMENU_5			9
#define STATE_CALLMENU_6			10
#define STATE_CALLMENU_7			11
#define STATE_CALLMENU_8			12
#define STATE_CALLMENU_9			13
#define STATE_CALLMENU_CLEAR		14
// Achievement States
#define STATE_ACHIEVE_HOME 1

// Previos Session States
#define STATE_PREV_HOME 1
#define STATE_PREV_NEXT_PAGE 2

void init_all(void)
{
	Init_Touch();
	Init_WiFi();
	Init_GPS();
}

int is_Within_Boundary(Point cursor, Point bound1, Point bound2)
{
	return ((cursor.x >= bound1.x && cursor.x <= bound2.x) && (cursor.y >= bound1.y && cursor.y <= bound2.y));
}

// Home Menu State Functions

int pressed_Call(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CALL_BOUND_1_X;
	bound1.y = CALL_BOUND_1_Y;
	bound2.x = CALL_BOUND_2_X;
	bound2.y = CALL_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_Current_Session(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CURS_BOUND_1_X;
	bound1.y = CURS_BOUND_1_Y;
	bound2.x = CURS_BOUND_2_X;
	bound2.y = CURS_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_Achievements(Point cursor) {
	Point bound1, bound2;
	bound1.x = ACHIEVE_BOUND_1_X;
	bound1.y = ACHIEVE_BOUND_1_Y;
	bound2.x = ACHIEVE_BOUND_2_X;
	bound2.y = ACHIEVE_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_Previous_Session(Point cursor)
{
	Point bound1, bound2;
	bound1.x = PREV_BOUND_1_X;
	bound1.y = PREV_BOUND_1_Y;
	bound2.x = PREV_BOUND_2_X;
	bound2.y = PREV_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int Get_State_Home(Point cursor)
{
	if (pressed_Call(cursor))
		return STATE_CALL;
	else if (pressed_Current_Session(cursor))
		return STATE_CURS;
	else if (pressed_Achievements(cursor))
		return STATE_ACHIEVE;
	else if (pressed_Previous_Session(cursor))
		return STATE_PRES;
	else
		return STATE_HOME;
}

// Current Session State Functions

int pressed_Current_Home(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CURRENT_HOME_BOUND_1_X;
	bound1.y = CURRENT_HOME_BOUND_1_Y;
	bound2.x = CURRENT_HOME_BOUND_2_X;
	bound2.y = CURRENT_HOME_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_Current_Start(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CURRENT_START_BOUND_1_X;
	bound1.y = CURRENT_START_BOUND_1_Y;
	bound2.x = CURRENT_START_BOUND_2_X;
	bound2.y = CURRENT_START_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int Get_State_Current(Point cursor)
{
	if (pressed_Current_Home(cursor)) {
		return STATE_CURRENT_HOME;
	}
	else if (pressed_Current_Start(cursor)) {
		if (session_started == 0) {
			return STATE_CURRENT_STARTED;
		} else {
			return STATE_CURRENT_STOPPED;
		}
	}
	else {
		if (session_started == 0) {
			return STATE_CURRENT_INIT;
		} else {
			return STATE_CURRENT_SESSION;
		}
	}
}

void Current_Session(void)
{
	session_started = 0;
	extracted_first_log = 0;

	drawStartSession();
	Init_GPS();
	PrintLog();
	drawLog();

	Point Cursor;
	while (1) {

		if ((TouchScreen_Status & 1) == 0) {
			Cursor.x = 0;
			Cursor.y = 0;
		} else {
			Cursor = Get_Touch_Point();
			printf("x: %d, y: %d\n", Cursor.x, Cursor.y);
		}
		int state = Get_State_Current(Cursor);

CURRENT_SESSION_STATES:
		switch (state)
		{
		case (STATE_CURRENT_SESSION) :
			//printf("IN SESSION\n");
			break;
		case (STATE_CURRENT_INIT) :
			//printf("INIT\n");
			break;
		case (STATE_CURRENT_STARTED) :
			printf("STARTED");
			session_started = 1;
			extracted_first_log = 0;
			drawStopButton();
			break;
		case (STATE_CURRENT_STOPPED) :
			printf("STOPPED\n");
			session_started = 0;
			getSessionData();
			drawStartButton();
			break;
		case (STATE_CURRENT_HOME) :
			printf("YOU PRESSED HOME\n");
			session_started = 0;
			extracted_first_log = 0;
			getSessionData();
			return;
			break;
		default :
			printf("YOU PRESSED NOTHING\n");
			break;
		}

		if (session_started == 1) {
			PrintLog();
			eraseLogGUI();
			drawLog();
		}
	}
}


// Previous Sessions Functions
int pressed_Previous_Home(Point cursor)
{
	Point bound1, bound2;
	bound1.x = PREV_HOME_BOUND_1_X;
	bound1.y = PREV_HOME_BOUND_1_Y;
	bound2.x = PREV_HOME_BOUND_2_X;
	bound2.y = PREV_HOME_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_Previous_Next_Page(Point cursor)
{
	Point bound1, bound2;
	bound1.x = PREV_NEXT_PAGE_BOUND_1_X;
	bound1.y = PREV_NEXT_PAGE_BOUND_1_Y;
	bound2.x = PREV_NEXT_PAGE_BOUND_2_X;
	bound2.y = PREV_NEXT_PAGE_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int Get_State_Previous(Point cursor) {
	if (pressed_Previous_Home(cursor))
		return STATE_PREV_HOME;
	else if (pressed_Previous_Next_Page(cursor))
		return STATE_PREV_NEXT_PAGE;
	else
		return STATE_PRES;
}


void Previous_Session(void)
{
	// Draw screen that says "Loading..."

	drawPreviouSession();
	Point Cursor;
	while (1)
	{
		Cursor = Get_Touch_Point();
		printf("x: %d, y: %d\n", Cursor.x, Cursor.y);
		int state = Get_State_Previous(Cursor);

PREVIOUS_SESSION_STATES:
		switch (state)
		{
		case (STATE_PREV_HOME) :
			printf("YOU PRESSED HOME\n");
			return;
			break;
		case (STATE_PREV_NEXT_PAGE) :
			printf("PRESSED NEXT PAGE\n");
			break;
		default :
			printf("YOU PRESSED NOTHING\n");
			break;
		}
	}
}

// Call Menu State Functions
int pressed_CallMenu_Home(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CALLMENU_HOME_BOUND_1_X;
	bound1.y = CALLMENU_HOME_BOUND_1_Y;
	bound2.x = CALLMENU_HOME_BOUND_2_X;
	bound2.y = CALLMENU_HOME_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_CallMenu_Call(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CALLMENU_CALL_BOUND_1_X;
	bound1.y = CALLMENU_CALL_BOUND_1_Y;
	bound2.x = CALLMENU_CALL_BOUND_2_X;
	bound2.y = CALLMENU_CALL_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_CallMenu_0(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CALLMENU_CALL_0_BOUND_1_X;
	bound1.y = CALLMENU_CALL_0_BOUND_1_Y;
	bound2.x = CALLMENU_CALL_0_BOUND_2_X;
	bound2.y = CALLMENU_CALL_0_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_CallMenu_1(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CALLMENU_CALL_1_BOUND_1_X;
	bound1.y = CALLMENU_CALL_1_BOUND_1_Y;
	bound2.x = CALLMENU_CALL_1_BOUND_2_X;
	bound2.y = CALLMENU_CALL_1_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_CallMenu_2(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CALLMENU_CALL_2_BOUND_1_X;
	bound1.y = CALLMENU_CALL_2_BOUND_1_Y;
	bound2.x = CALLMENU_CALL_2_BOUND_2_X;
	bound2.y = CALLMENU_CALL_2_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_CallMenu_3(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CALLMENU_CALL_3_BOUND_1_X;
	bound1.y = CALLMENU_CALL_3_BOUND_1_Y;
	bound2.x = CALLMENU_CALL_3_BOUND_2_X;
	bound2.y = CALLMENU_CALL_3_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_CallMenu_4(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CALLMENU_CALL_4_BOUND_1_X;
	bound1.y = CALLMENU_CALL_4_BOUND_1_Y;
	bound2.x = CALLMENU_CALL_4_BOUND_2_X;
	bound2.y = CALLMENU_CALL_4_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_CallMenu_5(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CALLMENU_CALL_5_BOUND_1_X;
	bound1.y = CALLMENU_CALL_5_BOUND_1_Y;
	bound2.x = CALLMENU_CALL_5_BOUND_2_X;
	bound2.y = CALLMENU_CALL_5_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_CallMenu_6(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CALLMENU_CALL_6_BOUND_1_X;
	bound1.y = CALLMENU_CALL_6_BOUND_1_Y;
	bound2.x = CALLMENU_CALL_6_BOUND_2_X;
	bound2.y = CALLMENU_CALL_6_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_CallMenu_7(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CALLMENU_CALL_7_BOUND_1_X;
	bound1.y = CALLMENU_CALL_7_BOUND_1_Y;
	bound2.x = CALLMENU_CALL_7_BOUND_2_X;
	bound2.y = CALLMENU_CALL_7_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_CallMenu_8(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CALLMENU_CALL_8_BOUND_1_X;
	bound1.y = CALLMENU_CALL_8_BOUND_1_Y;
	bound2.x = CALLMENU_CALL_8_BOUND_2_X;
	bound2.y = CALLMENU_CALL_8_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_CallMenu_9(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CALLMENU_CALL_9_BOUND_1_X;
	bound1.y = CALLMENU_CALL_9_BOUND_1_Y;
	bound2.x = CALLMENU_CALL_9_BOUND_2_X;
	bound2.y = CALLMENU_CALL_9_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int pressed_CallMenu_Clear(Point cursor)
{
	Point bound1, bound2;
	bound1.x = CALLMENU_CALL_CLEAR_BOUND_1_X;
	bound1.y = CALLMENU_CALL_CLEAR_BOUND_1_Y;
	bound2.x = CALLMENU_CALL_CLEAR_BOUND_2_X;
	bound2.y = CALLMENU_CALL_CLEAR_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int Get_State_Call(Point cursor)
{
	if (pressed_CallMenu_Home(cursor))
		return STATE_CALLMENU_HOME;
	else if (pressed_CallMenu_Call(cursor))
		return STATE_CALLMENU_CALL;
	else if (pressed_CallMenu_0(cursor))
		return STATE_CALLMENU_0;
	else if (pressed_CallMenu_1(cursor))
		return STATE_CALLMENU_1;
	else if (pressed_CallMenu_2(cursor))
		return STATE_CALLMENU_2;
	else if (pressed_CallMenu_3(cursor))
		return STATE_CALLMENU_3;
	else if (pressed_CallMenu_4(cursor))
		return STATE_CALLMENU_4;
	else if (pressed_CallMenu_5(cursor))
		return STATE_CALLMENU_5;
	else if (pressed_CallMenu_6(cursor))
		return STATE_CALLMENU_6;
	else if (pressed_CallMenu_7(cursor))
		return STATE_CALLMENU_7;
	else if (pressed_CallMenu_8(cursor))
		return STATE_CALLMENU_8;
	else if (pressed_CallMenu_9(cursor))
		return STATE_CALLMENU_9;
	else if (pressed_CallMenu_Clear(cursor))
		return STATE_CALLMENU_CLEAR;
	else
		return STATE_CALLMENU;
}

void Call(void)
{
	drawKeypad();
	// implement keypad polling...
	dialIndex = 10;
	dialNumber = "";
	Point Cursor;
	while (1)
	{
		Cursor = Get_Touch_Point();
		printf("x: %d, y: %d\n", Cursor.x, Cursor.y);
		int state = Get_State_Call(Cursor);

CALL_STATES:
		switch (state)
		{
		case (STATE_CALL) :
			printf("YOU PRESSED HOME\n");
			dialNumber = strcpy(dialNumber, "");
			return;
			break;
		case (STATE_CURS) :
			printf("YOU PRESSED CALL\n");
			// invoke wifi function here
			char *command;
			command = createCallCommand(dialNumber);
			sendCommand(command);
			dialNumber = strcpy(dialNumber, "");
			break;
		case (STATE_CALLMENU_0) :
			if(dialIndex < 700){
				printDialNumber('0', dialIndex);
				dialIndex += 15;
				dialNumber = strcat(dialNumber, "0");
			}
			break;
		case (STATE_CALLMENU_1) :
			if(dialIndex < 700){
				printDialNumber('1', dialIndex);
				dialIndex += 15;
				dialNumber = strcat(dialNumber, "1");
			}
			break;
		case (STATE_CALLMENU_2) :
			if(dialIndex < 700){
				printDialNumber('2', dialIndex);
				dialIndex += 15;
				dialNumber = strcat(dialNumber, "2");
			}
			break;
		case (STATE_CALLMENU_3) :
			if(dialIndex < 700){
				printDialNumber('3', dialIndex);
				dialIndex += 15;
				dialNumber = strcat(dialNumber, "3");
			}
			break;
		case (STATE_CALLMENU_4) :
			if(dialIndex < 700){
				printDialNumber('4', dialIndex);
				dialIndex += 15;
				dialNumber = strcat(dialNumber, "4");
			}
			break;
		case (STATE_CALLMENU_5) :
			if(dialIndex < 700){
				printDialNumber('5', dialIndex);
				dialIndex += 15;
				dialNumber = strcat(dialNumber, "5");
			}
			break;
		case (STATE_CALLMENU_6) :
			if(dialIndex < 700){
				printDialNumber('6', dialIndex);
				dialIndex += 15;
				dialNumber = strcat(dialNumber, "6");
			}
			break;
		case (STATE_CALLMENU_7) :
			if(dialIndex < 700){
				printDialNumber('7', dialIndex);
				dialIndex += 15;
				dialNumber = strcat(dialNumber, "7");
			}
			break;
		case (STATE_CALLMENU_8) :
			if(dialIndex < 700){
				printDialNumber('8', dialIndex);
				dialIndex += 15;
				dialNumber = strcat(dialNumber, "8");
			}
			break;
		case (STATE_CALLMENU_9) :
			if(dialIndex < 700){
				printDialNumber('9', dialIndex);
				dialIndex += 15;
				dialNumber = strcat(dialNumber, "9");
			}
			break;
		case (STATE_CALLMENU_CLEAR) :
			clearNumberScreen();
			dialIndex = 10;
			dialNumber = strcpy(dialNumber, "");
			break;
		default :
			printf("YOU PRESSED NOTHING\n");
			break;
		}
	}
}

// Achievements State Functions
int pressed_Achievements_Home(Point cursor)
{
	Point bound1, bound2;
	bound1.x = ACHIEVE_HOME_BOUND_1_X;
	bound1.y = ACHIEVE_HOME_BOUND_1_Y;
	bound2.x = ACHIEVE_HOME_BOUND_2_X;
	bound2.y = ACHIEVE_HOME_BOUND_2_Y;

	return is_Within_Boundary(cursor, bound1, bound2);
}

int Get_State_Achievements(Point cursor) {
	if (pressed_Achievements_Home(cursor))
		return STATE_ACHIEVE_HOME;
	else
		return STATE_ACHIEVE;
}

void Achievements(void) {
	// All updated, draw screen
	drawAchievementsScreen();
	Point Cursor;
	while (1)
	{
		Cursor = Get_Touch_Point();
		printf("x: %d, y: %d\n", Cursor.x, Cursor.y);
		int state = Get_State_Achievements(Cursor);

ACHIEVEMENT_STATES:
		switch (state)
		{
		case (STATE_ACHIEVE_HOME) :
			printf("YOU PRESSED HOME\n");
			return;
			break;
		default :
			printf("YOU PRESSED NOTHING\n");
			break;
		}
	}
}

int main()
{
	printf("Initializing serial ports...\n");
	init_all();

	printf("Drawing home screen...\n");
HOME:
	printf("Drawing Home Screen...\n");
	drawHome();

	printf("Awaiting touch command...\n");
	Point Cursor;
	while (1) {
		Cursor = Get_Touch_Point();
		printf("x: %d, y: %d\n", Cursor.x, Cursor.y);
		int state = Get_State_Home(Cursor);

STATES:
		switch (state)
		{
		case (STATE_CALL) :
			printf("YOU PRESSED CALL\n");
			Call();
			break;
		case (STATE_CURS) :
			printf("YOU PRESSED CURRENT SESSION\n");
			Current_Session();
			break;
		case (STATE_ACHIEVE) :
			printf("YOU PRESSED ACHIEVEMENTS\n");
			Achievements();
			break;
		case (STATE_PRES) :
			printf("YOU PRESSED PREVIOUS SESSION\n");
			Previous_Session();
			break;
		default :
			printf("YOU PRESSED NOTHING\n");
			break;
		};

		goto HOME;
	}
	printf("Done");

	return 0;
}

/*
 * A small example of jsmn parsing when JSON structure is known and number of
 * tokens is predictable.
 */

static const char *JSON_STRING =
/*"{\"user2\": \"johndoe23423333\", \"admin\": false, \"uid\": 1000,\n  "
"\"groups\": [\"users\", \"wheel\", \"audio\", \"video\"]}";*/

"{\"sub\": \"1234567890\", \"name\": \"John Doe\",\"admin\": true}";

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
    if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
        strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
        return 0;
    }
    return -1;
}

int main3() {
    int i;
    int r;
    jsmn_parser p;
    jsmntok_t t[128]; /* We expect no more than 128 tokens */

    jsmn_init(&p);
    r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t)/sizeof(t[0]));
    if (r < 0) {
        printf("Failed to parse JSON: %d\n", r);
        return 1;
    }

    /* Assume the top-level element is an object */
    if (r < 1 || t[0].type != JSMN_OBJECT) {
        printf("Object expected\n");
        return 1;
    }

    /* Loop over all keys of the root object */
    for (i = 1; i < r; i++) {
        if (jsoneq(JSON_STRING, &t[i], "sub") == 0) {
            /* We may use strndup() to fetch string value */
            printf("- Sub: %.*s\n", t[i+1].end-t[i+1].start,
                   JSON_STRING + t[i+1].start);
            i++;
        } else if (jsoneq(JSON_STRING, &t[i], "name") == 0) {
            /* We may additionally check if the value is either "true" or "false" */
            printf("- Name: %.*s\n", t[i+1].end-t[i+1].start,
                   JSON_STRING + t[i+1].start);
            i++;
        } else if (jsoneq(JSON_STRING, &t[i], "uid") == 0) {
            /* We may want to do strtol() here to get numeric value */
            printf("- UID: %.*s\n", t[i+1].end-t[i+1].start,
                   JSON_STRING + t[i+1].start);
            i++;
        } else if (jsoneq(JSON_STRING, &t[i], "groups") == 0) {
            int j;
            printf("- Groups:\n");
            if (t[i+1].type != JSMN_ARRAY) {
                continue; /* We expect groups to be an array of strings */
            }
            for (j = 0; j < t[i+1].size; j++) {
                jsmntok_t *g = &t[i+j+2];
                printf("  * %.*s\n", g->end - g->start, JSON_STRING + g->start);
            }
            i += t[i+1].size + 1;
        } else {
            printf("Unexpected key: %.*s\n", t[i].end-t[i].start,
                   JSON_STRING + t[i].start);
        }
    }
    return EXIT_SUCCESS;
}

