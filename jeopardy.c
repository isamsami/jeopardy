/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U (Operating Systems)
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "questions.h"
#include "players.h"

void tokenize(char *input, char **tokens) {
    tokens[0] = strtok(input, " ");
    tokens[1] = strtok(NULL, " ");
    tokens[2] = strtok(NULL, ""); // Capture the rest of the string
}

int main() {
    srand(time(NULL));
    initialize_players();
    initialize_game();

    char player_name[50];
    char category[50];
    int value;
    char answer[256];

    while (1) {
        display_categories();
        printf("\nEnter player's name to select a question (or type 'exit' to quit): ");
        scanf("%49s", player_name);

        if (strcmp(player_name, "exit") == 0) {
            break;
        }

        if (!player_exists(player_name)) {
            printf("Invalid player name. Try again.\n");
            continue;
        }

        printf("Enter category and value (e.g., Anime 100): ");
        scanf(" %49s %d", category, &value);

        if (already_answered(category, value)) {
            printf("This question has already been answered!\n");
            continue;
        }

        display_question(category, value);
        printf("\n%s, enter your answer (start with 'What is' or 'Who is') or type 'skip' to pass: ", player_name);
        scanf(" %[^"]255[^"]s", answer);

        if (strcmp(answer, "skip") == 0) {
            printf("Question skipped!\n");
            continue;
        }

        char *tokens[3] = {NULL, NULL, NULL};
        tokenize(answer, tokens);

        if (tokens[2] != NULL && valid_answer(category, value, tokens[2])) {
            printf("✅ Correct!\n");
            update_score(player_name, value);
        } else {
            printf("❌ Incorrect!\n");
        }
    }

    show_results();
    return 0;
}
