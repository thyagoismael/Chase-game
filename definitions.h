#ifndef DEFINITIONS
#define DEFINITIONS

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

#define NUM_PLAYERS 1
#define NUM_ACTIVE_PLAYERS 0
#define SLEEP_TIME 100000 // 0.1 second
#define SCREEN_Y 20
#define SCREEN_X 40
#define DIFFICULTY 100


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

#endif