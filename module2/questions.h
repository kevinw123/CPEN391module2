/*
 * questions.h
 *
 *  Created on: Mar 15, 2017
 *      Author: Gina
 */

#ifndef QUESTIONS_H_
#define QUESTIONS_H_

#define DATASIZE 128
#define NUM_QUESTIONS 4

// Question box bounds

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

struct Question{
	char *question;
	char *question2;
	char *answerA;
	char *answerB;
	char *answerC;
	char *answerD;
	char *correctChoice;
};

// Placeholders to hold the index value of the question presented in a box.
int qbox1_index;
int qbox2_index;
int qbox3_index;
int qbox4_index;

struct Question questions[NUM_QUESTIONS];
int questions_asked;

void init_questions();
void send_question_command();
void ask_question();

struct Question questionArray [NUM_QUESTIONS];

#endif /* QUESTIONS_H_ */
