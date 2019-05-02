#ifndef CONTROL
#define CONTROL

#include "definitions.h"

bool gameOver(t_per*);
void printField(t_game g);
void autoMovement(t_per *, t_pos);
void manualMovement(t_per*);
void movePlayers(t_game*);
float calculateDistance(t_pos, t_pos);
t_pos searchClosestPos(t_per player, t_pos nextPos);
bool someoneGetsGold(t_game*);
void regenGold(t_pos*);
void startGame(t_game*);
int readInput(void);

#endif
