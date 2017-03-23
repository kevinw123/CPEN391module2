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
	questionArray[0].answerA = "1";
	questionArray[0].answerB = "2";
	questionArray[0].answerC = "3";
	questionArray[0].answerD = "4";
	questionArray[0].correctChoice = "B";

	questionArray[1].question = "What is the capital city of Canada?";
	questionArray[1].answerA = "Vancouver, BC";
	questionArray[1].answerB = "Edmonton, AB";
	questionArray[1].answerC = "Toronto, ON";
	questionArray[1].answerD = "Ottawa, ON";
	questionArray[1].correctChoice = "D";

	questionArray[2].question = "Which object is the largest?";
	questionArray[2].answerA = "Elephant";
	questionArray[2].answerB = "Peanut";
	questionArray[2].answerC = "Moon";
	questionArray[2].answerD = "Eiffel Tower";
	questionArray[2].correctChoice = "C";

	questionArray[3].question = "Where can you find Polar Bears?";
	questionArray[3].answerA = "Antartica";
	questionArray[3].answerB = "Artic";
	questionArray[3].answerC = "Iceland";
	questionArray[3].answerD = "Greenland";
	questionArray[3].correctChoice = "B";

	questions_asked = 0;
}

void drawQuestionsScreen() {
	// Background
	Rectangle(0, 800, 0, 400, BLACK);
	Rectangle(1, 799, 400, 479, BLACK);

	// Title
	//Rectangle(200,600,50,250, WHITE);
	drawStringSmallFont("You approach a gatekeeper.", 25, 415, WHITE, MIDNIGHT_BLUE);
	drawStringSmallFont("It challenges you with a question, answer it to", 25, 430, WHITE, MIDNIGHT_BLUE);
	drawStringSmallFont("gain passage!", 25, 445, WHITE, MIDNIGHT_BLUE);

/*
#define QUESTION_1_TOPLEFT_X 25
#define QUESTION_1_TOPLEFT_Y 25
#define QUESTION_1_BOTRIGHT_X 375
#define QUESTION_1_BOTRIGHT_Y 185

#define QUESTION_2_TOPLEFT_X 425
#define QUESTION_2_TOPLEFT_Y 25
#define QUESTION_2_BOTRIGHT_X 775
#define QUESTION_2_BOTRIGHT_Y 185

#define QUESTION_3_TOPLEFT_X 25
#define QUESTION_3_TOPLEFT_Y 215
#define QUESTION_3_BOTRIGHT_X 375
#define QUESTION_3_BOTRIGHT_Y 375

#define QUESTION_4_TOPLEFT_X 425
#define QUESTION_4_TOPLEFT_Y 215
#define QUESTION_4_BOTRIGHT_X 775
#define QUESTION_4_BOTRIGHT_Y 375
*/

	// Choice Selections
	Rectangle(25,375,QUESTION_1_TOPLEFT_X,QUESTION_1_TOPLEFT_Y, WHITE);
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
	//drawString(questionArray[questions_asked].question, 250, 250, MIDNIGHT_BLUE, BLACK);

	questions_asked++;
	if (questions_asked >= NUM_QUESTIONS)
		questions_asked = 0;
}

