#ifndef DEFINITIONS
#define DEFINITIONS

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

#define NUM_PLAYERS 4
#define NUM_ACTIVE_PLAYERS 1
#define NUM_WINDOWS 2
#define GAME_SPEED 200 // the lower the number, the faster is the game
#define DIFFICULTY 60 // percentage of difficulty
#define SCORE_TO_WIN 5

#define BORDER_SIZE 3 // prevents the player from go beyond the walls
#define FIELD_SIZE_Y 25
#define FIELD_SIZE_X 60
#define SCOREBOARD_SIZE_Y FIELD_SIZE_Y
#define SCOREBOARD_SIZE_X 20

#define FIELD_START_Y 0
#define FIELD_START_X 0 
#define SCOREBOARD_START_Y 0
#define SCOREBOARD_START_X (FIELD_START_X + FIELD_SIZE_X + 1)

#define TOTAL_SIZE_X (SCOREBOARD_START_X + SCOREBOARD_SIZE_X + 1)
#define TOTAL_SIZE_Y FIELD_SIZE_Y + 1


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
