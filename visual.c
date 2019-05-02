#include "visual.h"

void printField(t_game g)
{
    int i;

    clear();

    for(i = 0; i < NUM_PLAYERS; i++)
        mvprintw(g.player[i].pos.y, g.player[i].pos.x, "%c", 'A' + i);
    mvprintw(g.gold.y, g.gold.x, "$");
    refresh();
}
