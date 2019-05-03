#ifndef CONTROL
#define CONTROL

#include "definitions.h"

bool gameOver(t_per*);
void autoMovement(t_per *, t_pos);
void manualMovement(t_per*);
void movePlayers(t_game*);
float calculateDistance(t_pos, t_pos);
t_pos searchClosestPos(t_per, t_pos);
bool someoneGetsGold(t_game*);
void regenGold(t_pos*);
void startGame(t_game*);
int fitOnField(int, int);
void changePosition(t_per*, t_directions);
void deleteAllScores(t_per*);
bool wantToRetry(void);

#endif
