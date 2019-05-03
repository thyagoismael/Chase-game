#include "definitions.h"
#include "control.h"
#include "visual.h"

void adjustFPS(clock_t startTime);

int main(void)
{
    t_game g;
    clock_t startTime;

    initscr();
    halfdelay(1);
    curs_set(0);
    noecho();

    deleteAllScores(g.player);
    while(true)
    {
        startGame(&g);
        while(!gameOver(g.player))
        {
            startTime = clock();

            printGame(g);
            movePlayers(&g);

            if(someoneGetsGold(&g))
                regenGold(&g.gold);


            //getch();
            adjustFPS(startTime);
        }

        if(!wantToRetry())
            break;
    }
    endwin();
    return 0;
}

void adjustFPS(clock_t startTime)
{
    clock_t endTime;

    do
    {
        endTime = clock();
    }while((endTime - startTime) * 1000 / CLOCKS_PER_SEC < GAME_SPEED);
}
