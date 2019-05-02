#include "definitions.h"
#include "control.h"

int main(void)
{
    t_game g;

    initscr();

    startGame(&g);
    while(!gameOver(g.player))
    {
        printField(g);
        movePlayers(&g);

        if(someoneGetsGold(g))
            regenGold(&g.gold);


        //getch();
        usleep(SLEEP_TIME);
    }

    endwin();
    return 0;
}
