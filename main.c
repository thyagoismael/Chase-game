#include "libraries/definitions.h"
#include "libraries/control.h"
#include "libraries/visual.h"

enum e_options{start, play, quit};

int playGame(void);
void showStartMenu(void);
void adjustFPS(clock_t startTime);
int getMenuOpt(void);

int main(void)
{
    int opt;

    initscr();
    halfdelay(1);
    curs_set(0);
    noecho();

    do
    {
        opt = getMenuOpt();

        switch(opt)
        {
            case start:
                showStartMenu();
                break;
/*            case play:
                opt = playGame();
                break;*/
            default:
                break;
        }
    }while(opt != quit);

    endwin();
    return 0;
}

void showStartMenu(void)
{
    int i;

    for(i = 0; i < IMAGE_HEIGHT; i++)
        mvprintw(i, 0, image[i]);
}

int getMenuOpt(void)
{
    int input;

    while((input = getch() - '0') != 1 && input != 2)
        flushinp();

    return input;
}


int playGame(void)
{
    t_game g;
    clock_t startTime;
    deleteAllScores(g.player);

    do
    {
        startGame(&g);
        while(!gameOver(g.player))
        {
            startTime = clock();

            printGame(g);
            movePlayers(&g);

            if(someoneGetsGold(&g))
                regenGold(&g.gold);

            adjustFPS(startTime);
        }
    }while(wantToRetry());

    return start;
}

void adjustFPS(clock_t startTime)
{
    clock_t endTime;

    do
    {
        endTime = clock();
    }while((endTime - startTime) * 1000 / CLOCKS_PER_SEC < GAME_SPEED);
}
