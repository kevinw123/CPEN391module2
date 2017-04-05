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
#include "PlayerSpritesAnimation.h"
#include "tests/test.h"
#include <stdlib.h>
#include "movement.h"
#include <stdio.h>
#include <string.h>

#define FRAME_RATE 4

void init_game() {
	init_questions();

	curArea = 0;
	player_current_y_pos = startPos[curArea][1];
	player_current_x_pos = startPos[curArea][0];
	printf("Player x pos: %d\n", player_current_x_pos);
	printf("Player y pos: %d\n", player_current_y_pos);
	Point p;
	p.x = 375;
	p.y = 225;

	int count = 0;
	int line1 = 0;
	int line2 = 1;
	int line3 = 2;
	Rectangle(0, 800, 0, 479, BLACK);
	Rectangle(0, 800, 400, 479, WHITE);
	Rectangle(1, 799, 401, 478, BLACK);
	drawPlayerDown0(p);
	drawStringSmallFont(story[line1], 25, 415, WHITE, MIDNIGHT_BLUE);
	drawStringSmallFont(story[line2], 25, 430, WHITE, MIDNIGHT_BLUE);
	drawStringSmallFont(story[line3], 25, 445, WHITE, MIDNIGHT_BLUE);

	while(count < NUM_STORY_LINES) {
		int command;
		while (1) {
				char a = getcharBluetooth();
				if ((a - '0') < 100 && (a - '0') >= 0) {
					command = a - '0';
					printf("Receiving : %c %d\n", a, command);
					break;
				}
		}
		if (command == 6) {
			if ((count%2) == 1)
				drawPlayerDown1(p);
			else
				drawPlayerDown2(p);
			Rectangle(1, 799, 401, 478, BLACK);
			drawStringSmallFont(story[line1], 25, 415, WHITE, MIDNIGHT_BLUE);
			drawStringSmallFont(story[line2], 25, 430, WHITE, MIDNIGHT_BLUE);
			drawStringSmallFont(story[line3], 25, 445, WHITE, MIDNIGHT_BLUE);
			line1++;
			line2++;
			line3++;
			count++;
		}
	}

	int enemy_with_key = rand() % (MAX_ENEMY - 1);
	printf("enemy: %d has key\n", enemy_with_key);
	printf("Init game check enemy pos\n");
	printf(" %d and %d and %d and %d\n", enemyPos[0][0][0],enemyPos[0][0][1],enemyPos[0][0][2],enemyPos[0][0][3]);
	printf(" %d and %d and %d and %d\n", enemyPos[0][1][0],enemyPos[0][1][1],enemyPos[0][1][2],enemyPos[0][1][3]);
	printf(" %d and %d and %d and %d\n", enemyPos[0][2][0],enemyPos[0][2][1],enemyPos[0][2][2],enemyPos[0][2][3]);
	printf(" %d and %d and %d and %d\n", enemyPos[0][3][0],enemyPos[0][3][1],enemyPos[0][3][2],enemyPos[0][3][3]);
	enemyPos[0][enemy_with_key][3] = 1;


	curState = STATE_REDRAW;
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

void drawPlayerDown0(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, down_0[i + 50 * j]);
		}
	}
}

void drawPlayerDown1(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, down_1[i + 50 * j]);
		}
	}
}

void drawPlayerDown2(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, down_2[i + 50 * j]);
		}
	}
}


void drawPlayerLeft0(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, left_0[i + 50 * j]);
		}
	}
}

void drawPlayerLeft1(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, left_1[i + 50 * j]);
		}
	}
}

void drawPlayerRight0(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, right_0[i + 50 * j]);
		}
	}
}

void drawPlayerRight1(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, right_1[i + 50 * j]);
		}
	}
}

void drawPlayerUp0(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, up_0[i + 50 * j]);
		}
	}
}

void drawPlayerUp1(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, up_1[i + 50 * j]);
		}
	}
}

void drawPlayerUp2(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, up_2[i + 50 * j]);
		}
	}
}

void drawEnemyDown0(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, rocket_down_0[i + 50 * j]);
		}
	}
}

void drawEnemyDown1(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, rocket_down_1[i + 50 * j]);
		}
	}
}

void drawEnemyDown2(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, rocket_down_2[i + 50 * j]);
		}
	}
}

void drawEnemyLeft0(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, rocket_left_0[i + 50 * j]);
		}
	}
}

void drawEnemyLeft1(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, rocket_left_1[i + 50 * j]);
		}
	}
}

void drawEnemyRight0(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, rocket_right_0[i + 50 * j]);
		}
	}
}

void drawEnemyRight1(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, rocket_right_1[i + 50 * j]);
		}
	}
}

void drawEnemyUp0(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, rocket_up_0[i + 50 * j]);
		}
	}
}

void drawEnemyUp1(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, rocket_up_1[i + 50 * j]);
		}
	}
}

void drawEnemyUp2(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, rocket_up_2[i + 50 * j]);
		}
	}
}

void drawDoor(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, door[i + 50 * j]);
		}
	}
}

void drawKey(Point p)
{
	int i, j;
	for (j = 0; j < 50; j++) {
		for (i = 0; i < 50; i++) {
			WriteAPixel(p.x + i, p.y + j, key[i + 50 * j]);
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
		drawEnemyDown0(point);
	else if (square == PLAYER)
		drawPlayerUp0(point);
	else if (square == DOOR)
		drawDoor(point);
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
	if (key_flag) {
				Point p;
				p.x = 720;
				p.y = 420;
				drawKey(p);
	}
}
void check_door()
{
	if (key_flag){
		map[0][1][12] = 'O';
	}
}

void printMap()
{
	int i,j;
		for (j = 0; j < MAX_VERT_SQUARES; j++) {
			for (i = 0; i < MAX_HORI_SQUARES; i++) {
				printf("%c ", map[0][j][i]);
			}
			printf("\n");
		}
		//usleep(3000000);
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
}

int enemy_chooseDirection()
{
	return rand() % 4;
}

void enemy_moveDirection(int direction, int x, int y, int index)
{
	if (enemy_isValidMovement(direction, 0, x, y)) {
		// redraw
		switch (direction) {

		case(DIRECTION_UP) :
				moveEnemyUp(x, y, curArea);
				enemyPos[0][index][0]--;
				break;
		case(DIRECTION_RIGHT) :
				moveEnemyRight(x, y, curArea);
				enemyPos[0][index][1]++;
				break;
		case(DIRECTION_DOWN) :
				moveEnemyDown(x, y, curArea);
				enemyPos[0][index][0]++;
				break;
		case(DIRECTION_LEFT) :
				moveEnemyLeft(x, y, curArea);
				enemyPos[0][index][1]--;
				break;

		}
	}
	// invalid move
}

//enemyPos [MAX_AREAS][3][2]
//enemy_isValidMovement(int direction, int area, int enemyPosX, int enemyPosY)
void redrawEnemies()
{
	printf("redraw enemies\n");
	int j;
	for (j = 0; j < MAX_ENEMY; j++) {
		printf("%d and %d and %d and %d\n", enemyPos[0][j][0], enemyPos[0][j][1], enemyPos[0][j][2], enemyPos[0][j][3]);
	}

	int i, curEX, curEY;
	for (i = 0; i < MAX_ENEMY; i++) {
		curEX = enemyPos[0][i][1];
		curEY = enemyPos[0][i][0];
		if (map[0][curEY][curEX] == 'O'){
			enemyPos[0][i][2] = ENEMY_DEAD;
			if (enemyPos[0][i][3] == 1)
				key_flag = 1;
			continue;
		}
		int direction = enemy_chooseDirection();
		enemy_moveDirection(direction, curEX, curEY, i);
	}
	printf("Do i have key: %d\n", key_flag);
	if (key_flag) {
			Point p;
			p.x = 720;
			p.y = 420;
			drawKey(p);
	}
	printMap();
}

//
void resetEnemyLocation()
{
	int enemy_with_key = rand() % (MAX_ENEMY - 1);
	printf("enemy: %d has key\n", enemy_with_key);
	enemyPos[0][enemy_with_key][3] = 1;
	printf("keynumber: %d\n", enemy_with_key);
	int i,j,k;
	for (i = 0; i < MAX_AREAS; i++) {
		printf("reset enemy location check enemy pos\n");
		for (j = 0; j < MAX_ENEMY - 1; j++) {
			printf(" %d and %d and %d and %d\n", enemyPos[i][j][0],enemyPos[i][j][1],enemyPos[i][j][2],enemyPos[i][j][3]);
			for (k = 0; k < 4; k++) {
				enemyPos[i][j][k] = enemyPos_init[i][j][k];
			}
			int x = enemyPos[i][j][1];
			int y = enemyPos[i][j][0];
			map[i][y][x] = 'X';
		}
	}

	int length = sizeof(map) / sizeof(map[0][0][0]) - 1;
	memcpy(&map, &map_init, length * (sizeof(char)));
}
