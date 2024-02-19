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
#include "players.h"

// Returns the index of the player if the player exists, otherwise returns -1
int player_exists(player *players, int num_players, char *name)
{
    for (int i = 0; i < num_players; i++) {
        if (strcmp(players[i].name, name) == 0) {
            return i; // if player found return this index
        }
    }
    return -1;
}

// Update the score for the player given their index
void update_score(player *players, int player_index, int score)
{
    players[player_index].score += score;
}
