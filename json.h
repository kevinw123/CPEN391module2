/*
 * jsonParse.h
 *
 *  Created on: 2017-02-15
 *      Author: ahboo
 */

#ifndef JSONPARSE_H_
#define JSONPARSE_H_

#include "jsmn.h"

int distance1_achieved;
int distance2_achieved;
int session1_achieved;
int session2_achieved;
int speed1_achieved;
int speed2_achieved;
int achievementsRadius;



void parseAchievements(char *JSON_STRING);



#endif /* JSONPARSE_H_ */
