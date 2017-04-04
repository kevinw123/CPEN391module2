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
void init_game(void);
void drawArea(int map_width, int map_height, int area);
void drawSquare(char square, Point point);
Point getCoord(int x, int y);
void drawWall(Point p);
void drawSpace(Point p);
void drawFinish(Point p);
void drawEnemy(Point p);
void drawPlayer(Point p);
void redrawEnemies(void);
void printMap(void);
void resetEnemyLocation(void);

#endif /* DRAWMAP_H_ */
