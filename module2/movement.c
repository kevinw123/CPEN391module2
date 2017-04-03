/*
 * movement.c
 *
 *  Created on: 2017-03-13
 *      Author: ahboo
 */

#include <stdio.h>
#include "Colours.h"
#include "drawmap.h"
#include "mapdesign.h"
#include "states.h"
#include "tests/test.h"
#include "movement.h"
#include "graphics.h"

bool down_flag = false;
bool up_flag = false;

/*
void movePlayer(Point curPos, Point newPos, int area)
{
	printf("curposx: %d\n", curPos.x);
	printf("curposy: %d\n", curPos.y);
	printf("newposx: %d\n", newPos.x);
	printf("newposy: %d\n", newPos.y);
	//map[area][curPos.x][curPos.y] = SPACE;
	//map[area][newPos.x][newPos.y] = PLAYER;
	//drawArea(MAX_HORI_SQUARES, MAX_VERT_SQUARES, area);
	drawSpace(curPos);
	drawPlayer(newPos);
}
*/

int movePlayerUp(int x, int y, int area)
{
	Point playerCoords;
	playerCoords = getCoord(x, y);
	printf("x: %d\n", playerCoords.x);
	printf("y: %d\n", playerCoords.y);

	if (isValidMovementUp(curArea,x,y)){
		Point old_playerCoords = playerCoords;
		int i;
		up_flag = !up_flag;
		for (i = 0; i < 25; i += FRAME_RATE) {
			playerCoords.y = old_playerCoords.y - i;
			if (up_flag)
				drawPlayerUp1(playerCoords);
			else
				drawPlayerUp2(playerCoords);
			Rectangle(old_playerCoords.x, old_playerCoords.x + SQUARE_WIDTH-1, old_playerCoords.y + SQUARE_WIDTH - FRAME_RATE - i, old_playerCoords.y + SQUARE_WIDTH - 1 - i, BLACK);
		}

		for (i = 25; i < 50; i += FRAME_RATE) {
			playerCoords.y = old_playerCoords.y - i;
			drawPlayerUp0(playerCoords);
			Rectangle(old_playerCoords.x, old_playerCoords.x + SQUARE_WIDTH-1, old_playerCoords.y + SQUARE_WIDTH - FRAME_RATE - i, old_playerCoords.y + SQUARE_WIDTH - 1 - i, BLACK);
		}
		playerCoords.y = old_playerCoords.y - 50;
		drawPlayerUp0(playerCoords);
		player_current_y_pos--;
		printf("debug up y: %d\n", player_current_y_pos);
		return 0;
	}
	else
		return -1;
}

int movePlayerDown(int x, int y, int area)
{
	Point playerCoords;
	playerCoords = getCoord(x, y);
	printf("x: %d\n", playerCoords.x);
	printf("y: %d\n", playerCoords.y);

	if (isValidMovementDown(curArea,x,y)) {
		Point old_playerCoords = playerCoords;
		int i;
		down_flag = !down_flag;
		for (i = 0; i < 25; i += FRAME_RATE) {
			playerCoords.y = old_playerCoords.y + i;
			if (down_flag)
				drawPlayerDown1(playerCoords);
			else
				drawPlayerDown2(playerCoords);
			Rectangle(old_playerCoords.x, old_playerCoords.x + SQUARE_WIDTH-1, old_playerCoords.y + i, old_playerCoords.y + FRAME_RATE + i, BLACK);
		}

		for (i = 25; i < 50; i += FRAME_RATE) {
			playerCoords.y = old_playerCoords.y + i;
			drawPlayerDown0(playerCoords);
			Rectangle(old_playerCoords.x, old_playerCoords.x + SQUARE_WIDTH-1, old_playerCoords.y + i, old_playerCoords.y + FRAME_RATE + i, BLACK);
		}
		playerCoords.y = old_playerCoords.y + 50;
		drawPlayerDown0(playerCoords);
		player_current_y_pos++;
		return 0;
	}
	else
		return -1;
}

int movePlayerLeft(int x, int y, int area)
{
	Point playerCoords;
	playerCoords = getCoord(x, y);
	printf("x: %d\n", playerCoords.x);
	printf("y: %d\n", playerCoords.y);

	if (isValidMovementLeft(curArea,x,y)) {
		Point old_playerCoords = playerCoords;

		int i;
		for (i = 0; i < 25; i += FRAME_RATE) {
			playerCoords.x = old_playerCoords.x - i;
			drawPlayerLeft1(playerCoords);
			VRectangle(old_playerCoords.x + SQUARE_WIDTH - 1 - FRAME_RATE - i, old_playerCoords.x + SQUARE_WIDTH - 1 - i, old_playerCoords.y, old_playerCoords.y + SQUARE_WIDTH - 1, BLACK);
		}

		for (i = 25; i < 50; i += FRAME_RATE) {
			playerCoords.x = old_playerCoords.x - i;
			drawPlayerLeft0(playerCoords);
			VRectangle(old_playerCoords.x + SQUARE_WIDTH - 1 - FRAME_RATE - i, old_playerCoords.x + SQUARE_WIDTH - 1 - i, old_playerCoords.y, old_playerCoords.y + SQUARE_WIDTH - 1, BLACK);
		}
		playerCoords.x = old_playerCoords.x - 50;
		drawPlayerLeft0(playerCoords);

		player_current_x_pos--;
		return 0;
	}
	else
		return -1;
}

int movePlayerRight(int x, int y, int area)
{
	Point playerCoords;
	playerCoords = getCoord(x, y);
	printf("x: %d\n", playerCoords.x);
	printf("y: %d\n", playerCoords.y);

	if (isValidMovementRight(curArea,x,y)) {
		Point old_playerCoords = playerCoords;
		int i;
		for (i = 0; i < 25; i += FRAME_RATE) {
			playerCoords.x = old_playerCoords.x + i;
			drawPlayerRight1(playerCoords);
			VRectangle(old_playerCoords.x + i, old_playerCoords.x + FRAME_RATE + i, old_playerCoords.y, old_playerCoords.y + SQUARE_WIDTH - 1, BLACK);
		}

		for (i = 25; i < 50; i += FRAME_RATE) {
			playerCoords.x = old_playerCoords.x + i;
			drawPlayerRight0(playerCoords);
			VRectangle(old_playerCoords.x + i, old_playerCoords.x + FRAME_RATE + i, old_playerCoords.y, old_playerCoords.y + SQUARE_WIDTH - 1, BLACK);
		}
		playerCoords.x = old_playerCoords.x + 50;
		drawPlayerRight0(playerCoords);

		player_current_x_pos++;
		return 0;
	}
	else
		return -1;
}

int moveEnemyUp(int x, int y, int area)
{
	Point oldPoint, newPoint;

	map[0][y][x] = 'O';
	map[0][y - 1][x] = 'X';

	oldPoint = getCoord(x, y);
	newPoint = getCoord(x, y - 1);

	drawSpace(oldPoint);
	drawEnemy(newPoint);

	return 0;
}

int moveEnemyRight(int x, int y, int area)
{
	Point oldPoint, newPoint;

	map[0][y][x] = 'O';
	map[0][y][x + 1] = 'X';

	oldPoint = getCoord(x, y);
	newPoint = getCoord(x + 1, y);

	drawSpace(oldPoint);
	drawEnemy(newPoint);

	return 0;
}


int moveEnemyDown(int x, int y, int area)
{
	Point oldPoint, newPoint;

	map[0][y][x] = 'O';
	map[0][y + 1][x] = 'X';

	oldPoint = getCoord(x, y);
	newPoint = getCoord(x, y + 1);

	drawSpace(oldPoint);
	drawEnemy(newPoint);

	return 0;
}


int moveEnemyLeft(int x, int y, int area)
{
	Point oldPoint, newPoint;

	map[0][y][x] = 'O';
	map[0][y][x - 1] = 'X';

	oldPoint = getCoord(x, y);
	newPoint = getCoord(x - 1, y);

	drawSpace(oldPoint);
	drawEnemy(newPoint);

	return 0;
}

