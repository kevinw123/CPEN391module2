/*
 * drawmenu.c
 *
 *  Created on: Mar 15, 2017
 *      Author: Gina
 */

#include "graphics.h"
#include "Colours.h"

void draw_menu_prompt() {
	Rectangle(100, 699, 100, 379, WHITE);

	char *menu_prompt_line1 = "Press PLAY on your phone";
	char *menu_prompt_line2 = "to start the game!";
	int x = 220;
	int y = 230;
	drawString(menu_prompt_line1, x, y, MIDNIGHT_BLUE, BLACK);
	drawString(menu_prompt_line2, x + 40, y + 20, MIDNIGHT_BLUE, BLACK);
}

void draw_menu() {
	Rectangle(0, 799, 0, 479, MIDNIGHT_BLUE);
	draw_menu_prompt();
}


