/*
 * drawmap.c
 *
 *  Created on: 2017-03-12
 *      Author: ahboo
 */

#include "mapdesign.h"
#include "states.h"
#include "graphics.h"
#include "touchscreen.h"
#include "Colours.h"
#include "bluetooth.h"
#include "playerSprite.h"

void init_game() {
	init_questions();

	curArea = 0;
	player_current_y_pos = startPos[curArea][1];
	player_current_x_pos = startPos[curArea][0];
	printf("Player x pos: %d\n", player_current_x_pos);
	printf("Player y pos: %d\n", player_current_y_pos);
}

Point getCoord(int x, int y)
{
	Point point;
	point.x = x * SQUARE_WIDTH;
	point.y = y * SQUARE_HEIGHT;
	return point;
}

void drawWall(Point p)
{
	Rectangle(p.x, p.x + SQUARE_WIDTH-1, p.y, p.y + SQUARE_HEIGHT-1, MIDNIGHT_BLUE);
	WriteHLine (p.x, p.x + SQUARE_WIDTH-1, p.y, BLACK);
	Rectangle(p.x, p.x + SQUARE_WIDTH-1, p.y + 11, p.y + 12, BLACK);
	Rectangle(p.x, p.x + SQUARE_WIDTH-1, p.y + 24, p.y + 25, BLACK);
	Rectangle(p.x, p.x + SQUARE_WIDTH-1, p.y + 37, p.y + 38, BLACK);
	WriteHLine (p.x, p.x + SQUARE_WIDTH-1, p.y + SQUARE_HEIGHT-1, BLACK);

	WriteVLine(p.x, p.y, p.y + 10, BLACK);
	VRectangle(p.x + 24, p.x + 25, p.y, p.y + 10, BLACK);
	WriteVLine(p.x + SQUARE_WIDTH-1, p.y, p.y + 10, BLACK);

	WriteVLine(p.x, p.y + 26, p.y + 36, BLACK);
	VRectangle(p.x + 24, p.x + 25, p.y + 26, p.y + 36, BLACK);
	WriteVLine(p.x + SQUARE_WIDTH-1, p.y + 26, p.y + 36, BLACK);

	VRectangle(p.x + 11, p.x + 12, p.y + 13, p.y + 23, BLACK);
	VRectangle(p.x + 37, p.x + 38, p.y + 13, p.y + 23, BLACK);

	VRectangle(p.x + 11, p.x + 12, p.y + 39, p.y + SQUARE_HEIGHT - 2, BLACK);
	VRectangle(p.x + 37, p.x + 38, p.y + 39, p.y + SQUARE_HEIGHT - 2, BLACK);
}

void drawSpace(Point p)
{
	Rectangle(p.x, p.x + SQUARE_WIDTH-1, p.y, p.y + SQUARE_HEIGHT-1, BLACK);
}

void drawFinish(Point p)
{
	//Rectangle(p.x, p.x + SQUARE_WIDTH-1, p.y, p.y + SQUARE_HEIGHT-1, PINK);
	int i, j;

			for (j = 0; j < 50; j++) {
				for (i = 0; i < 50; i++) {
					WriteAPixel(p.x + i, p.y + j, princess[i + 50 * j]);
				}
	}
}

void drawEnemy(Point p)
{
	//Rectangle(p.x, p.x + SQUARE_WIDTH-1, p.y, p.y + SQUARE_HEIGHT-1, BLACK);
	//Rectangle(p.x+1, p.x + SQUARE_WIDTH-2, p.y+1, p.y + SQUARE_HEIGHT-2, RED);
	int i, j;

		for (j = 0; j < 50; j++) {
			for (i = 0; i < 50; i++) {
				WriteAPixel(p.x + i, p.y + j, bear[i + 50 * j]);
			}
	}
}

void drawPlayer(Point p)
{
	//Rectangle(p.x, p.x + SQUARE_WIDTH-1, p.y, p.y + SQUARE_HEIGHT-1, BLACK);
	//Rectangle(p.x+1, p.x + SQUARE_WIDTH-2, p.y+1, p.y + SQUARE_HEIGHT-2, FOREST_GREEN);
	int i, j;

	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, ness[i + 50 * j]);
		}
	}
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
	Rectangle(0, 800, 400, 479, WHITE);
	Rectangle(1, 799, 401, 478, BLACK);
	drawStringSmallFont("The dungeon warden is keeping the princess prisoner!", 25, 415, WHITE, MIDNIGHT_BLUE);
	drawStringSmallFont("You need to save her!", 25, 430, WHITE, MIDNIGHT_BLUE);
}

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
