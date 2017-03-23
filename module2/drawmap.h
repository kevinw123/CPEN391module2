/*
 * drawmap.h
 *
 *  Created on: 2017-03-12
 *      Author: ahboo
 */

#ifndef DRAWMAP_H_
#define DRAWMAP_H_

#include "touchscreen.h"

// Functions
void movePlayer(int curPosX, int curPosY, int newPosX, int newPosY, int area);
int movePlayerUp(int x, int y, int area);
int movePlayerRight(int x, int y, int area);
int movePlayerDown(int x, int y, int area);
int movePlayerLeft(int x, int y, int area);
void drawArea(int map_width, int map_height, int area);
void drawSquare(char square, Point point);
Point getCoord(int x, int y);
void drawWall(Point p);
void drawSpace(Point p);
void drawFinish(Point p);
void drawEnemy(Point p);
void drawPlayer(Point p);

#endif /* DRAWMAP_H_ */
