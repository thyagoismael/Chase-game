#ifndef VISUAL
#define VISUAL

#include "definitions.h"

#define FIELD_START_Y 10
#define FIELD_START_X 10
#define BORDER_SIZE 3 // prevents the players from go beyong the walls

void printGame(t_game);
void printField(t_game, WINDOW*);

#endif
