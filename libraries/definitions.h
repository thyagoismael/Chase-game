#ifndef DEFINITIONS
#define DEFINITIONS

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define NUM_PLAYERS 4
#define NUM_ACTIVE_PLAYERS 1  // change it for multiplayer
#define NUM_WINDOWS 2
#define GAME_SPEED 180 // the lower the number, the faster it runs 
#define DIFFICULTY 60 // percentage of difficulty
#define SCORE_TO_WIN 5

#define BORDER_SIZE 2 // prevents the player from go beyond the walls
#define FIELD_HEIGHT 25
#define FIELD_WIDTH 60
#define SCOREBOARD_HEIGHT (FIELD_HEIGHT / 2)
#define SCOREBOARD_WIDTH 20
#define HELP_HEIGHT (FIELD_HEIGHT - SCOREBOARD_HEIGHT)
#define HELP_WIDTH SCOREBOARD_WIDTH

#define FIELD_START_Y 0
#define FIELD_START_X 0 
#define SCOREBOARD_START_Y 0
#define SCOREBOARD_START_X (FIELD_START_X + FIELD_WIDTH + 1)
#define HELP_START_X SCOREBOARD_START_X
#define HELP_START_Y (SCOREBOARD_START_Y + SCOREBOARD_HEIGHT)

#define TOTAL_WIDTH (SCOREBOARD_START_X + SCOREBOARD_WIDTH + 1)
#define TOTAL_HEIGHT FIELD_HEIGHT + 1

typedef struct position
{
    int y, x;
}t_pos;

typedef struct person
{
    int score;
    bool isActive;
    t_pos pos;
    unsigned int turnWon;
}t_per;

typedef struct gameData
{
    t_per player[NUM_PLAYERS];
    t_pos gold;
}t_game;

typedef enum e_directions {left='a', down='s', right='d', up='w'}t_directions;
typedef enum e_windows {field, score} t_windows;

#endif
