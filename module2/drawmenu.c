/*
 * drawmenu.c
 *
 *  Created on: Mar 15, 2017
 *      Author: Gina
 */

#include "graphics.h"
#include "Colours.h"

/*
 * Draw the text for the menu screen
 */
void draw_menu_prompt() {
	Rectangle(100, 699, 100, 379, WHITE);

	char *menu_prompt_line1 = "Press PLAY on your phone";
	char *menu_prompt_line2 = "to start the game!";
	int x = 220;
	int y = 230;
	drawString(menu_prompt_line1, x, y, MIDNIGHT_BLUE, BLACK);
	drawString(menu_prompt_line2, x + 40, y + 20, MIDNIGHT_BLUE, BLACK);
}

/*
 *  Draw the menu screen to tell player to play game on Android
 */
void draw_menu() {
	Rectangle(0, 800, 0, 480, MIDNIGHT_BLUE);
	draw_menu_prompt();
}

/*
 * Draws the screen for last games when player reaches princess
 */
void draw_last_question() {
	Rectangle(0,800,0,480,BLACK);
	drawString("LAST QUESTION SCREEN", 250, 200, TEAL, TEAL);
}

/*
 * Draws the final win screen
 */
void draw_finish_screen() {
	Rectangle(0,800,0,480,BLACK);
	while(1) {
		drawString("A WINNER IS YOU!", 250, 200, DARK_SEA_GREEN, MIDNIGHT_BLUE);
		drawString("A WINNER IS YOU!", 250, 200, MIDNIGHT_BLUE, MIDNIGHT_BLUE);
		drawString("A WINNER IS YOU!", 250, 200, TEAL, MIDNIGHT_BLUE);
		drawString("A WINNER IS YOU!", 250, 200, BROWN, MIDNIGHT_BLUE);
		drawString("A WINNER IS YOU!", 250, 200, FOREST_GREEN, MIDNIGHT_BLUE);
		drawString("A WINNER IS YOU!", 250, 200, MAROON, MIDNIGHT_BLUE);
		drawString("A WINNER IS YOU!", 250, 200, MEDIUM_VIOLET_RED, MIDNIGHT_BLUE);
		drawString("A WINNER IS YOU!", 250, 200, RED, MIDNIGHT_BLUE);
		drawString("A WINNER IS YOU!", 250, 200, PINK, MIDNIGHT_BLUE);
		drawString("A WINNER IS YOU!", 250, 200, WHITE, MIDNIGHT_BLUE);
	}
}


