/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    strcpy(questions[0].category, "Science");
    strcpy(questions[0].question, "What is the capital of France?");
    strcpy(questions[0].answer, "Paris");
    questions[0].answered = false;

    // Initialize other questions similarly


    for (int i = 0; i < NUM_CATEGORIES * NUM_QUESTIONS_PER_CATEGORY; i++) {
        questions[i].answered = false;
    }
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    printf("Remaining Categories:\n");
    for (int i = 0; i < NUM_CATEGORIES * NUM_QUESTIONS_PER_CATEGORY; i++) {
        if (!questions[i].answered) {
            printf("%s - $%d\n", questions[i].category, (i % NUM_QUESTIONS_PER_CATEGORY + 1) * 100);
        }
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    // Find the question index
    int questionIndex = -1;
    for (int i = 0; i < NUM_CATEGORIES * NUM_QUESTIONS_PER_CATEGORY; i++) {
        if (strcmp(questions[i].category, category) == 0 && 
            (i % NUM_QUESTIONS_PER_CATEGORY + 1) * 100 == value &&
            !questions[i].answered) {
            questionIndex = i;
            break;
        }
    }

    // Display the question
    if (questionIndex != -1) {
        printf("Question: %s\n", questions[questionIndex].question);
    } else {
        printf("Invalid category or value.\n");
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Find the question index
    int questionIndex = -1;
    for (int i = 0; i < NUM_CATEGORIES * NUM_QUESTIONS_PER_CATEGORY; i++) {
        if (strcmp(questions[i].category, category) == 0 && 
            (i % NUM_QUESTIONS_PER_CATEGORY + 1) * 100 == value &&
            !questions[i].answered) {
            questionIndex = i;
            break;
        }
    }

    // Check if the answer is correct
    if (questionIndex != -1) {
        return strcmp(answer, questions[questionIndex].answer) == 0;
    } else {
        return false;
    }
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
     // Find the question index
    int questionIndex = -1;
    for (int i = 0; i < NUM_CATEGORIES * NUM_QUESTIONS_PER_CATEGORY; i++) {
        if (strcmp(questions[i].category, category) == 0 && 
            (i % NUM_QUESTIONS_PER_CATEGORY + 1) * 100 == value) {
            questionIndex = i;
            break;
        }
    }

    // Check if the question has been answered
    if (questionIndex != -1) {
        return questions[questionIndex].answered;
    } else {
        return false;
    }
}
