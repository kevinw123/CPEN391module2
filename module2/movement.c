/*
 * movement.c
 *
 *  Created on: 2017-03-13
 *      Author: ahboo
 */

#include <stdio.h>
#include "drawmap.h"
#include "mapdesign.h"
#include "states.h"
#include "tests/test.h"

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

int movePlayerUp(int x, int y, int area)
{
	Point playerCoords;
	playerCoords = getCoord(x, y);
	printf("x: %d\n", playerCoords.x);
	printf("y: %d\n", playerCoords.y);

	if (isValidMovementUp(curArea)){
		Point old_playerCoords = playerCoords;
		playerCoords.y = playerCoords.y - 50;
		movePlayer(old_playerCoords, playerCoords, area);

		player_current_y_pos--;
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

	if (isValidMovementDown(curArea)) {
		Point old_playerCoords = playerCoords;
		playerCoords.y = playerCoords.y + 50;
		movePlayer(old_playerCoords, playerCoords, area);

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

	if (isValidMovementLeft(curArea)) {
		Point old_playerCoords = playerCoords;
		playerCoords.x = playerCoords.x - 50;
		movePlayer(old_playerCoords, playerCoords, area);

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

	if (isValidMovementRight(curArea)) {
		Point old_playerCoords = playerCoords;
		playerCoords.x = playerCoords.x + 50;
		movePlayer(old_playerCoords, playerCoords, area);

		player_current_x_pos++;
		return 0;
	}
	else
		return -1;
}



