/*
 * questions.c
 *
 *  Created on: Mar 15, 2017
 *      Author: Gina
 */

#include <string.h>
#include "questions.h"
#include "bluetooth.h"

void init_questions(){
	strcpy(questions[0].question, "What is 1 + 1?");
	strcpy(questions[0].answerA, "1");
	strcpy(questions[0].answerB, "2");
	strcpy(questions[0].answerC, "3");
	strcpy(questions[0].answerD, "4");
	strcpy(questions[0].correctChoice, "B");

	strcpy(questions[1].question, "What is the capital city of Canada?");
	strcpy(questions[1].answerA, "Vancouver, BC");
	strcpy(questions[1].answerB, "Edmonton, AB");
	strcpy(questions[1].answerC, "Toronto, ON");
	strcpy(questions[1].answerD, "Ottawa, ON");
	strcpy(questions[1].correctChoice, "D");

	strcpy(questions[2].question, "Which object is the largest?");
	strcpy(questions[2].answerA, "Elephant");
	strcpy(questions[2].answerB, "Peanut");
	strcpy(questions[2].answerC, "Moon");
	strcpy(questions[2].answerD, "Eiffel Tower");
	strcpy(questions[2].correctChoice, "C");

	questions_asked = 0;
}

void ask_question(){
	struct Question curQuestion = questions[questions_asked];

	char *question_to_DE2 = "$";
	strcat(question_to_DE2, curQuestion.question);
	strcat(question_to_DE2, ",");
	strcat(question_to_DE2, curQuestion.answerA);
	strcat(question_to_DE2, ",");
	strcat(question_to_DE2, curQuestion.answerB);
	strcat(question_to_DE2, ",");
	strcat(question_to_DE2, curQuestion.answerC);
	strcat(question_to_DE2, ",");
	strcat(question_to_DE2, curQuestion.answerD);
	strcat(question_to_DE2, ",");
	strcat(question_to_DE2, curQuestion.correctChoice);
	printf("Question: %s\n", question_to_DE2);
	sendStringBluetooth(question_to_DE2);

	questions_asked++;
}

