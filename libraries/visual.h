#ifndef VISUAL
#define VISUAL

#include "definitions.h"

#define FIELD_START_Y 0
#define FIELD_START_X 0
#define SCOREBOARD_START_Y 0
#define SCOREBOARD_START_X (FIELD_START_X + FIELD_WIDTH + 1)

#define IMAGE_HEIGHT 13
#define IMAGE_WIDTH 51

void printGame(t_game);
void printField(t_game, WINDOW*);
void printScore(t_game, WINDOW*);
void printHelp(WINDOW*);
void printh(WINDOW*, int, int, char*);


#endif
