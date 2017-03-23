/*
 * questions.c
 *
 *  Created on: Mar 15, 2017
 *      Author: Gina
 */

#include <string.h>
#include "questions.h"
#include "bluetooth.h"
#include "Colours.h"
#include "graphics.h"

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

	questionArray[1].question = "What is the capital ";
	questionArray[1].question2 = "";
	questionArray[1].question2 = "city of Canada?";
	questionArray[1].answerA = "Vancouver, BC";
	questionArray[1].answerB = "Edmonton, AB";
	questionArray[1].answerC = "Toronto, ON";
	questionArray[1].answerD = "Ottawa, ON";
	questionArray[1].correctChoice = "D";

	questionArray[2].question = "Which object is the largest?";
	questionArray[2].question2 = "";
	questionArray[2].answerA = "Elephant";
	questionArray[2].answerB = "Peanut";
	questionArray[2].answerC = "Moon";
	questionArray[2].answerD = "Eiffel Tower";
	questionArray[2].correctChoice = "C";

	questionArray[3].question = "Where can you find Polar Bears?";
	questionArray[3].question2 = "";
	questionArray[3].answerA = "Antartica";
	questionArray[3].answerB = "Artic";
	questionArray[3].answerC = "Iceland";
	questionArray[3].answerD = "Greenland";
	questionArray[3].correctChoice = "B";

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
	qbox1_index = r;
	drawStringSmallFont(questionArray[r].question, 50, 50, WHITE, MIDNIGHT_BLUE);
	drawStringSmallFont(questionArray[r].question2, 50, 75, WHITE, MIDNIGHT_BLUE);
	r = (r + 1) % NUM_QUESTIONS;
	//q2 box
	qbox2_index = r;
	drawStringSmallFont(questionArray[r].question, 460, 50, WHITE, MIDNIGHT_BLUE);
	drawStringSmallFont(questionArray[r].question2, 460, 75, WHITE, MIDNIGHT_BLUE);
	r = (r + 1) % NUM_QUESTIONS;
	//q3 box
	qbox3_index = r;
	drawStringSmallFont(questionArray[r].question, 50, 240, WHITE, MIDNIGHT_BLUE);
	drawStringSmallFont(questionArray[r].question2, 50, 265, WHITE, MIDNIGHT_BLUE);
	r = (r + 1) % NUM_QUESTIONS;
	//q4 box
	qbox4_index = r;
	drawStringSmallFont(questionArray[r].question, 460, 240, WHITE, MIDNIGHT_BLUE);
	drawStringSmallFont(questionArray[r].question2, 460, 265, WHITE, MIDNIGHT_BLUE);
}

