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
	char index;
};

// Placeholders to hold the index value of the question presented in a box.
//char qbox1_index;
//char qbox2_index;
//char qbox3_index;
//char qbox4_index;
char qbox_index[4];

struct Question questions[NUM_QUESTIONS];
int questions_asked;


void init_questions(void);
void send_question_command(void);
void ask_question(void);
int choose_question(void);

struct Question questionArray [NUM_QUESTIONS];

#endif /* QUESTIONS_H_ */
