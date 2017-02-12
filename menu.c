#include "Gps.h"
#include "graphics.h"
#include "touchscreen.h"
#include "Colours.h"

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
#define STATE_CURRENT_SESSION	2
#define STATE_CURRENT_HOME		3

// Call States
#define STATE_CALLMENU_HOME			1
#define STATE_CALLMENU_CALL			2
#define STATE_CALLMENU				3

// Achievement States
#define STATE_ACHIEVE_HOME 1

// Previos Session States
#define STATE_PREV_HOME 1
#define STATE_PREV_NEXT_PAGE 2

void init_all(void)
{
	Init_Touch();
	//Init_WiFi();
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
	else if(pressed_Previous_Session(cursor))
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
	if (pressed_Current_Home(cursor))
		return STATE_CURRENT_HOME;
	else if (pressed_Current_Start(cursor)) {
		if (session_started == 0) {
			session_started = 1;
			drawStopButton();
			return STATE_CURRENT_SESSION;
		} else {
			session_started = 0;
			drawStartButton();
			return STATE_CURRENT_INIT;
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
	drawStartSession();
	Init_GPS();
	PrintLog();
	drawLog();

	Point Cursor;
	while (1) {
		if ((TouchScreen_Status & 1) == 0 && session_started == 1) {
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
			printf("IN SESSION\n");
			break;
		case (STATE_CURRENT_INIT) :
			printf("INIT/STOPPED\n");
			break;
		case (STATE_CURRENT_HOME) :
			printf("YOU PRESSED HOME\n");
			session_started = 0;
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
	else if(pressed_Previous_Next_Page(cursor))
		return STATE_PREV_NEXT_PAGE;
	else
		return STATE_PRES;
}


void Previous_Session(void)
{
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

int Get_State_Call(Point cursor)
{
	if (pressed_CallMenu_Home(cursor))
		return STATE_CALLMENU_HOME;
	else if (pressed_CallMenu_Call(cursor))
		return STATE_CALLMENU_CALL;
	else
		return STATE_CALLMENU;
}

void Call(void)
{
	drawKeypad();
	// implement keypad polling...
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
			return;
			break;
		case (STATE_CURS) :
			printf("YOU PRESSED CALL\n");
			// invoke wifi function here
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
