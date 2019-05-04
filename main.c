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
        showStartMenu();
        opt = getMenuOpt();

        switch(opt)
        {
            case play:
                opt = playGame();
                break;
            default:
                break;
        }
    }while(opt != quit);

    endwin();
    return 0;
}

void showStartMenu(void)
{
    int x = (TOTAL_WIDTH - 51) / 2; // 51 is the image width
    int y = (TOTAL_HEIGHT - 13) / 2; // 13 is the image height
    mvprintw(y     ,  x, " ______   __");
    mvprintw(y +  1,  x, "/      \\ /  |");
    mvprintw(y +  2,  x, "/$$$$$$  |$$ |____    ______    _______   ______");
    mvprintw(y +  3,  x, "$$ |  $$/ $$      \\  /      \\  /       | /      \\");
    mvprintw(y +  4,  x, "$$ |      $$$$$$$  | $$$$$$  |/$$$$$$$/ /$$$$$$  |");
    mvprintw(y +  5,  x, "$$ |   __ $$ |  $$ | /    $$ |$$      \\ $$    $$ |");
    mvprintw(y +  6,  x, "$$ \\__/  |$$ |  $$ |/$$$$$$$ | $$$$$$  |$$$$$$$$/");
    mvprintw(y +  7,  x, "$$    $$/ $$ |  $$ |$$    $$ |/     $$/ $$       |");
    mvprintw(y +  8,  x, " $$$$$$/  $$/   $$/  $$$$$$$/ $$$$$$$/   $$$$$$$/");
    mvprintw(y + 12,  x, "                  (1) START (1)                  ");
    mvprintw(y + 13,  x, "                  (2) QUIT  (2)                  ");

    refresh();
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
