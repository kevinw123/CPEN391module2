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

bool enemy_down_flag = false;
bool enemy_up_flag = false;

/*
 * Moves the player one tile up
 * Ensure to do animation and valid checks
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
	else {
		drawPlayerUp0(playerCoords);
		return -1;
	}

}

/*
 * Moves the player one tile down
 * Ensure to do animation and valid checks
 */
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
	else {
		drawPlayerDown0(playerCoords);
		return -1;
	}

}

/*
 * Moves the player one tile left
 * Ensure to do animation and valid checks
 */
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
	else {
		drawPlayerLeft0(playerCoords);
		return -1;
	}
}

/*
 * Moves the player one tile right
 * Ensure to do animation and valid checks
 */
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
	else {
		drawPlayerRight0(playerCoords);
		return -1;
	}

}

/*
 * Moves the enemy one tile up
 * Ensure to do animation and valid checks
 */
int moveEnemyUp(int x, int y, int area)
{
	Point old_enemyCoords, enemyCoords;

	enemyCoords = getCoord(x, y);
	old_enemyCoords = enemyCoords;

	int i;
	enemy_up_flag = !enemy_up_flag;
	for (i = 0; i < 25; i += FRAME_RATE) {
		enemyCoords.y = old_enemyCoords.y - i;
		if (enemy_up_flag)
			drawEnemyUp1(enemyCoords);
		else
			drawEnemyUp2(enemyCoords);
		Rectangle(old_enemyCoords.x, old_enemyCoords.x + SQUARE_WIDTH-1, old_enemyCoords.y + SQUARE_WIDTH - FRAME_RATE - i, old_enemyCoords.y + SQUARE_WIDTH - 1 - i, BLACK);
	}

	for (i = 25; i < 50; i += FRAME_RATE) {
		enemyCoords.y = old_enemyCoords.y - i;
		drawEnemyUp0(enemyCoords);
		Rectangle(old_enemyCoords.x, old_enemyCoords.x + SQUARE_WIDTH-1, old_enemyCoords.y + SQUARE_WIDTH - FRAME_RATE - i, old_enemyCoords.y + SQUARE_WIDTH - 1 - i, BLACK);
	}
	enemyCoords.y = old_enemyCoords.y - 50;
	drawEnemyUp0(enemyCoords);

	map[0][y][x] = 'O';
	map[0][y - 1][x] = 'X';
	return 0;
}

/*
 * Moves the enemy one tile right
 * Ensure to do animation and valid checks
 */
int moveEnemyRight(int x, int y, int area)
{
	Point old_enemyCoords, enemyCoords;

	enemyCoords = getCoord(x, y);
	old_enemyCoords = enemyCoords;

	int i;
	for (i = 0; i < 25; i += FRAME_RATE) {
		enemyCoords.x = old_enemyCoords.x + i;
		drawEnemyRight1(enemyCoords);
		VRectangle(old_enemyCoords.x + i, old_enemyCoords.x + FRAME_RATE + i, old_enemyCoords.y, old_enemyCoords.y + SQUARE_WIDTH - 1, BLACK);
	}

	for (i = 25; i < 50; i += FRAME_RATE) {
		enemyCoords.x = old_enemyCoords.x + i;
		drawEnemyRight0(enemyCoords);
		VRectangle(old_enemyCoords.x + i, old_enemyCoords.x + FRAME_RATE + i, old_enemyCoords.y, old_enemyCoords.y + SQUARE_WIDTH - 1, BLACK);
	}
	enemyCoords.x = old_enemyCoords.x + 50;
	drawEnemyRight0(enemyCoords);

	map[0][y][x] = 'O';
	map[0][y][x + 1] = 'X';
	return 0;
}

/*
 * Moves the enemy one tile down
 * Ensure to do animation and valid checks
 */
int moveEnemyDown(int x, int y, int area)
{
	Point old_enemyCoords, enemyCoords;
	enemyCoords = getCoord(x, y);
	old_enemyCoords = enemyCoords;

	int i;
	enemy_down_flag = !enemy_down_flag;
	for (i = 0; i < 25; i += FRAME_RATE) {
		enemyCoords.y = old_enemyCoords.y + i;
		if (enemy_down_flag)
			drawEnemyDown1(enemyCoords);
		else
			drawEnemyDown2(enemyCoords);
		Rectangle(old_enemyCoords.x, old_enemyCoords.x + SQUARE_WIDTH-1, old_enemyCoords.y + i, old_enemyCoords.y + FRAME_RATE + i, BLACK);
	}

	for (i = 25; i < 50; i += FRAME_RATE) {
		enemyCoords.y = old_enemyCoords.y + i;
		drawEnemyDown0(enemyCoords);
		Rectangle(old_enemyCoords.x, old_enemyCoords.x + SQUARE_WIDTH-1, old_enemyCoords.y + i, old_enemyCoords.y + FRAME_RATE + i, BLACK);
	}
	enemyCoords.y = old_enemyCoords.y + 50;
	drawEnemyDown0(enemyCoords);

	map[0][y][x] = 'O';
	map[0][y + 1][x] = 'X';
	return 0;
}

/*
 * Moves the enemy one tile left
 * Ensure to do animation and valid checks
 */
int moveEnemyLeft(int x, int y, int area)
{
	Point old_enemyCoords, enemyCoords;
	enemyCoords = getCoord(x, y);
	old_enemyCoords = enemyCoords;

	int i;
	for (i = 0; i < 25; i += FRAME_RATE) {
		enemyCoords.x = old_enemyCoords.x - i;
		drawEnemyLeft1(enemyCoords);
		VRectangle(old_enemyCoords.x + SQUARE_WIDTH - 1 - FRAME_RATE - i, old_enemyCoords.x + SQUARE_WIDTH - 1 - i, old_enemyCoords.y, old_enemyCoords.y + SQUARE_WIDTH - 1, BLACK);
	}

	for (i = 25; i < 50; i += FRAME_RATE) {
		enemyCoords.x = old_enemyCoords.x - i;
		drawEnemyLeft0(enemyCoords);
		VRectangle(old_enemyCoords.x + SQUARE_WIDTH - 1 - FRAME_RATE - i, old_enemyCoords.x + SQUARE_WIDTH - 1 - i, old_enemyCoords.y, old_enemyCoords.y + SQUARE_WIDTH - 1, BLACK);
	}
	enemyCoords.x = old_enemyCoords.x - 50;
	drawEnemyLeft0(enemyCoords);

	map[0][y][x] = 'O';
	map[0][y][x - 1] = 'X';
	return 0;
}
