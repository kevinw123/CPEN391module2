/*
 * questions.c
 *
 *  Created on: Mar 15, 2017
 *      Author: Gina
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "questions.h"
#include "bluetooth.h"
#include "Colours.h"
#include "graphics.h"
#include "touchscreen.h"
#include "tests/test.h"

void init_questions(){

	int i;
	for (i = 0; i < NUM_QUESTIONS; i++) {
		struct Question q;
		questionArray[i] = q;
	}

	questionArray[0].question = "What is 1 + 1?";
	questionArray[0].question2 = "";
	questionArray[0].answerA = "1";
	questionArray[0].answerB = "2";
	questionArray[0].answerC = "3";
	questionArray[0].answerD = "4";
	questionArray[0].correctChoice = "B";
	questionArray[0].index = '0';

	questionArray[1].question = "What is the capital ";
	questionArray[1].question2 = "";
	questionArray[1].question2 = "city of Canada?";
	questionArray[1].answerA = "Vancouver, BC";
	questionArray[1].answerB = "Edmonton, AB";
	questionArray[1].answerC = "Toronto, ON";
	questionArray[1].answerD = "Ottawa, ON";
	questionArray[1].correctChoice = "D";
	questionArray[1].index = '1';

	questionArray[2].question = "Which object is the largest?";
	questionArray[2].question2 = "";
	questionArray[2].answerA = "Elephant";
	questionArray[2].answerB = "Peanut";
	questionArray[2].answerC = "Moon";
	questionArray[2].answerD = "Eiffel Tower";
	questionArray[2].correctChoice = "C";
	questionArray[2].index = '2';

	questionArray[3].question = "Where can you find Polar Bears?";
	questionArray[3].question2 = "";
	questionArray[3].answerA = "Antartica";
	questionArray[3].answerB = "Artic";
	questionArray[3].answerC = "Iceland";
	questionArray[3].answerD = "Greenland";
	questionArray[3].correctChoice = "B";
	questionArray[3].index = '3';

	questions_asked = 0;
}

void drawQuestionsScreen() {
	// Background
	Rectangle(0, 800, 0, 399, BLACK);
	Rectangle(1, 799, 401, 478, BLACK);

	// Title
	//Rectangle(200,600,50,250, WHITE);
	drawStringSmallFont("You approach a gatekeeper.", 25, 415, WHITE, MIDNIGHT_BLUE);
	drawStringSmallFont("It challenges you with a question, answer it to", 25, 430, WHITE, MIDNIGHT_BLUE);
	drawStringSmallFont("gain passage!", 25, 445, WHITE, MIDNIGHT_BLUE);

	// Choice Selections
	Rectangle(25,375,25,185, WHITE);
	Rectangle(26,374,26,184, BLACK);
	Rectangle(425,775,25,185, WHITE);
	Rectangle(426,774,26,184, BLACK);
	Rectangle(25,375,215,375, WHITE);
	Rectangle(26,374,216,374, BLACK);
	Rectangle(425,775,215,375, WHITE);
	Rectangle(426,774,216,374, BLACK);
}

void ask_question(){
	drawQuestionsScreen();

	int r = rand() % NUM_QUESTIONS;

	//q1 box
	qbox_index[0] = questionArray[r].index;
	drawStringSmallFont(questionArray[r].question, 50, 50, WHITE, MIDNIGHT_BLUE);
	drawStringSmallFont(questionArray[r].question2, 50, 75, WHITE, MIDNIGHT_BLUE);
	r = (r + 1) % NUM_QUESTIONS;
	//q2 box
	qbox_index[1] = questionArray[r].index;
	drawStringSmallFont(questionArray[r].question, 460, 50, WHITE, MIDNIGHT_BLUE);
	drawStringSmallFont(questionArray[r].question2, 460, 75, WHITE, MIDNIGHT_BLUE);
	r = (r + 1) % NUM_QUESTIONS;
	//q3 box
	qbox_index[2] = questionArray[r].index;
	drawStringSmallFont(questionArray[r].question, 50, 240, WHITE, MIDNIGHT_BLUE);
	drawStringSmallFont(questionArray[r].question2, 50, 265, WHITE, MIDNIGHT_BLUE);
	r = (r + 1) % NUM_QUESTIONS;
	//q4 box
	qbox_index[3] = questionArray[r].index;
	drawStringSmallFont(questionArray[r].question, 460, 240, WHITE, MIDNIGHT_BLUE);
	drawStringSmallFont(questionArray[r].question2, 460, 265, WHITE, MIDNIGHT_BLUE);
}

bool isWithinBounds(p,b1,b2) {
	if ((p >= b1) && (p <= b2))
		return true;
	else
		return false;
}

int choose_question() {
	Point p;
	while(1) {
		p = Get_Touch_Point();
		printf("Touched x: %d, y: %d\n", p.x, p.y);

		// is q1?
		if (isWithinBounds(p.y,QUESTION_1_TOPLEFT_X,QUESTION_1_BOTRIGHT_X) && isWithinBounds(p.x,QUESTION_1_TOPLEFT_Y,QUESTION_1_BOTRIGHT_Y))
			return 0;
		// is q2?
		if (isWithinBounds(p.y,QUESTION_2_TOPLEFT_X,QUESTION_2_BOTRIGHT_X) && isWithinBounds(p.x,QUESTION_2_TOPLEFT_Y,QUESTION_2_BOTRIGHT_Y))
			return 1;
		// is q3?
		if (isWithinBounds(p.y,QUESTION_3_TOPLEFT_X,QUESTION_3_BOTRIGHT_X) && isWithinBounds(p.x,QUESTION_3_TOPLEFT_Y,QUESTION_3_BOTRIGHT_Y))
			return 2;
		// is q4?
		if (isWithinBounds(p.y,QUESTION_4_TOPLEFT_X,QUESTION_4_BOTRIGHT_X) && isWithinBounds(p.x,QUESTION_4_TOPLEFT_Y,QUESTION_4_BOTRIGHT_Y))
			return 3;

		// Check the touched point and compare it to bounds of the four question boxes
		// if a match with one of the four bounds, break and obtain qbox index
	}
	return 0;
}

