#ifndef VISUAL
#define VISUAL

#include "definitions.h"

#define FIELD_START_Y 0
#define FIELD_START_X 0
#define SCOREBOARD_START_Y 0
#define SCOREBOARD_START_X (FIELD_START_X + FIELD_SIZE_X + 1)

void printGame(t_game);
void printField(t_game, WINDOW*);
void printScore(t_game, WINDOW*);

#endif
