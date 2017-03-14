/*
 * testMovement.c
 *
 *  Created on: 2017-03-13
 *      Author: ahboo
 */
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "../mapdesign.h"
#include "../../graphics.h"
#include "../../touchscreen.h"
#include "../../Colours.h"
#include "../drawmap.h"
#include "../states.h"
#include "../movement.h"


bool isValidMovementUp(Point playerCoords)
{
	return false;
}

bool isValidMovementRight(Point playerCoords)
{
	return false;
}

bool isValidMovementDown(Point playerCoords)
{
	return false;
}

bool isValidMovementLeft(Point playerCoords)
{
	return false;
}

bool isValidMovement(int direction, Point playerCoords)
{
	if (direction == DIRECTION_UP)
		return isValidMovementUp(playerCoords);
	else if (direction == DIRECTION_RIGHT)
		return isValidMovementRight(playerCoords);
	else if (direction == DIRECTION_DOWN)
		return isValidMovementDown(playerCoords);
	else if (direction == DIRECTION_LEFT)
		return isValidMovementLeft(playerCoords);
}

bool isValidBluetoothCommand()
{
	return false;
}





