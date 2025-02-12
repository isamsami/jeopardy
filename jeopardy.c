/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U (Operating Systems)
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

#define BUFFER_LEN 256
#define NUM_PLAYERS 4
#define NUM_CATEGORIES 3
#define NUM_QUESTIONS_PER_CATEGORY 3

void tokenize(char *input, char **tokens);
void show_results(player *players, int num_players);

int main(int argc, char *argv[]) {
    player players[NUM_PLAYERS];
    char buffer[BUFFER_LEN] = {0};

    initialize_questions(); // Initialize questions
    initialize_players(players, NUM_PLAYERS); // Initialize players

    printf("Enter the names of the four players:\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Player %d: ", i + 1);
        fgets(buffer, BUFFER_LEN, stdin);
        strtok(buffer, "\n"); // Remove the newline character
        strcpy(players[i].name, buffer);
        players[i].score = 0;
    }

    int total_questions = NUM_CATEGORIES * NUM_QUESTIONS_PER_CATEGORY;
    int answered_questions = 0;

    while (answered_questions < total_questions) {
        // Display categories and questions
        display_categories();

        // Prompt for player's name
        printf("Enter the name of the player who picks the question: ");
        fgets(buffer, BUFFER_LEN, stdin);
        strtok(buffer, "\n");

        // Validate player's name
        int player_index = player_exists(players, NUM_PLAYERS, buffer);
        if (player_index == -1) {
            printf("Invalid player name. Try again.\n");
            continue;
        }

        // Prompt for category and dollar amount
        char category[BUFFER_LEN];
        int amount;
        printf("Enter the category and dollar amount (e.g., 'Science 100'): ");
        fgets(buffer, BUFFER_LEN, stdin);
        sscanf(buffer, "%s %d", category, &amount);

        // Find and ask the question
        int question_index = find_question_index(category, amount);
        if (question_index == -1 || is_question_answered(question_index)) {
            printf("Invalid category or dollar amount. Try again.\n");
            continue;
        }

        // Display the question
        display_question(category, amount);

        // Prompt for player's answer
        printf("Your answer (start with 'what is' or 'who is'): ");
        fgets(buffer, BUFFER_LEN, stdin);
        strtok(buffer, "\n");

        // Validate and process the answer
        bool correct = valid_answer(category, amount, buffer);
        if (correct) {
            printf("Correct!\n");
            update_score(players, player_index, amount);
        } else {
            printf("Incorrect! The correct answer is: %s\n", get_answer_text(question_index));
        }

        // Mark the question as answered
        mark_question_as_answered(question_index);
        answered_questions++;
    }

    // Display final results
    show_results(players, NUM_PLAYERS);

    return EXIT_SUCCESS;
}

void tokenize(char *input, char **tokens) {
    // Tokenize the input string and store the tokens in the tokens array
    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
        tokens[i++] = token;
        token = strtok(NULL, " ");
    }
}

void show_results(player *players, int num_players) {
    // Sort players based on their scores
    sort_players(players, num_players);

    // Print leaderboard
    printf("\nLeaderboard:\n");
    for (int i = 0; i < num_players; i++) {
        printf("%d. %s - $%d\n", i + 1, players[i].name, players[i].score);
    }
}

