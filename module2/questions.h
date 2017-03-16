/*
 * questions.h
 *
 *  Created on: Mar 15, 2017
 *      Author: Gina
 */

#ifndef QUESTIONS_H_
#define QUESTIONS_H_

#define DATASIZE 128
#define NUM_QUESTIONS 3

struct Question{
	char question[DATASIZE];
	char answerA[DATASIZE];
	char answerB[DATASIZE];
	char answerC[DATASIZE];
	char answerD[DATASIZE];
	char correctChoice[DATASIZE];
};

struct Question questions[NUM_QUESTIONS];
int questions_asked;

void init_questions();
void send_question_command();
void ask_question();

#endif /* QUESTIONS_H_ */
