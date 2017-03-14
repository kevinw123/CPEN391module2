/*
 * drawmap.c
 *
 *  Created on: 2017-03-12
 *      Author: ahboo
 */

#include "mapdesign.h"
#include "../graphics.h"
#include "../touchscreen.h"
#include "../Colours.h"


Point getCoord(int x, int y)
{
	Point point;
	point.x = x * SQUARE_WIDTH;
	point.y = y * SQUARE_HEIGHT;
	return point;
}

void drawWall(Point p)
{
	Rectangle(p.x, p.x + SQUARE_WIDTH, p.y, p.y + SQUARE_HEIGHT, MIDNIGHT_BLUE);
}

void drawSpace(Point p)
{
	Rectangle(p.x, p.x + SQUARE_WIDTH, p.y, p.y + SQUARE_HEIGHT, WHITE);
}

void drawFinish(Point p)
{
	Rectangle(p.x, p.x + SQUARE_WIDTH, p.y, p.y + SQUARE_HEIGHT, PINK);
}

void drawEnemy(Point p)
{
	Rectangle(p.x, p.x + SQUARE_WIDTH, p.y, p.y + SQUARE_HEIGHT, RED);
}

void drawPlayer(Point p)
{
	Rectangle(p.x, p.x + SQUARE_WIDTH, p.y, p.y + SQUARE_HEIGHT, FOREST_GREEN);
}

void drawSquare(char square, Point point)
{
	if (square == WALL)
		drawWall(point);
	else if (square == SPACE)
		drawSpace(point);
	else if (square == FINISH)
		drawFinish(point);
	else if (square == ENEMY)
		drawEnemy(point);
	else if (square == PLAYER)
		drawPlayer(point);
}

void drawArea(int map_width, int map_height, int area)
{
	int i, j;
	for (i = 0; i < map_height; i++) {
		for (j = 0; j < map_width; j++) {
			char curSquare = map[area][i][j];
			Point point = getCoord(j, i);
			drawSquare(curSquare, point);
		}
	}
	Rectangle(0, 800, 400, 480, BLACK);
}

void movePlayer(Point curPos, Point newPos, int area)
{
	Point space_point, player_point;
	//map[area][curPos.x][curPos.y] = SPACE;
	//map[area][newPos.x][newPos.y] = PLAYER;
	//drawArea(MAX_HORI_SQUARES, MAX_VERT_SQUARES, area);
	drawSpace(curPos);
	drawPlayer(player_point);
}

int movePlayerUp(Point playerCoords, area)
{
	if (isValidMovementUp(Point playerCoords)){
		Point old_playerCoords = playerCoords;
		playerCoords.y--;
		movePlayer(old_playerCoords, playerCoords, area);
		return 0
	}
	else
		return -1;
}

int movePlayerDown(Point playerCoords, area)
{
	if (isValidMovementDown(Point playerCoords)){
		Point old_playerCoords = playerCoords;
		playerCoords.y++;
		movePlayer(old_playerCoords, playerCoords, area);
		return 0
	}
	else
		return -1;
}

int movePlayerLeft(Point playerCoords, area)
{
	if (isValidMovementLeft(Point playerCoords)){
		Point old_playerCoords = playerCoords;
		playerCoords.x--;
		movePlayer(old_playerCoords, playerCoords, area);
		return 0
	}
	else
		return -1;
}

int movePlayerRight(Point playerCoords, area)
{
	if (isValidMovementRight(Point playerCoords)){
		Point old_playerCoords = playerCoords;
		playerCoords.x++;
		movePlayer(old_playerCoords, playerCoords, area);
		return 0
	}
	else
		return -1;
}
