/*
 * movement.h
 *
 *  Created on: 2017-03-13
 *      Author: ahboo
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#define DIRECTION_UP 0
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3

#define FRAME_RATE 3

//void movePlayer(int curPosX, int curPosY, int newPosX, int newPosY, int area);
int movePlayerUp(int x, int y, int area);
int movePlayerRight(int x, int y, int area);
int movePlayerDown(int x, int y, int area);
int movePlayerLeft(int x, int y, int area);
int moveEnemyUp(int x, int y, int area);
int moveEnemyRight(int x, int y, int area);
int moveEnemyDown(int x, int y, int area);
int moveEnemyLeft(int x, int y, int area);

#endif /* MOVEMENT_H_ */
