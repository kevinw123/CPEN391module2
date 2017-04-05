/*
 * test.h
 *
 *  Created on: 2017-03-13
 *      Author: ahboo
 */

#ifndef TEST_H_
#define TEST_H_

typedef int bool;
#define true 1
#define false 0

bool isValidMovementUp(int area, int playerX, int playerY);
bool isValidMovementRight(int area, int playerX, int playerY);
bool isValidMovementDown(int area, int playerX, int playerY);
bool isValidMovementLeft(int area, int playerX, int playerY);
bool isValidMovement(int direction, int area);
bool enemy_isValidMovement(int direction, int area, int enemyPosX, int enemyPosY);

#endif /* TEST_H_ */
