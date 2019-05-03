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
#define GAME_SPEED 250
#define SLEEP_TIME 100000 // 0.1 second
#define FIELD_SIZE_Y 20
#define FIELD_SIZE_X 40
#define DIFFICULTY 50
#define SCORE_TO_WIN 5
#define BORDER_SIZE 3 // prevents the player from go beyond the walls


typedef struct position
{
    int y, x;
}t_pos;

typedef struct person
{
    int score;
    bool isActive;
    t_pos pos;
}t_per;

typedef struct gameData
{
    t_per player[NUM_PLAYERS];
    t_pos gold;
}t_game;

typedef enum e_directions {left='a', down='s', right='d', up='w'}t_directions;

#endif
