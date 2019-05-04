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
    int y = (TOTAL_HEIGHT - 13) / 2; // 13 is the image height
    WINDOW *win = newwin(TOTAL_HEIGHT, TOTAL_WIDTH, FIELD_START_Y, FIELD_START_X);

    refresh();
    printh(win, y     , TOTAL_WIDTH, " ______   __                                   ");
    printh(win, y +  1, TOTAL_WIDTH, "/      \\ /  |                                  ");
    printh(win, y +  2, TOTAL_WIDTH, "/$$$$$$  |$$ |____    ______    _______   ______ ");
    printh(win, y +  3, TOTAL_WIDTH, "$$ |  $$/ $$      \\  /      \\  /       | /      \\");
    printh(win, y +  4, TOTAL_WIDTH, "$$ |      $$$$$$$  | $$$$$$  |/$$$$$$$/ /$$$$$$  |");
    printh(win, y +  5, TOTAL_WIDTH, "$$ |   __ $$ |  $$ | /    $$ |$$      \\ $$    $$ |");
    printh(win, y +  6, TOTAL_WIDTH, "$$ \\__/  |$$ |  $$ |/$$$$$$$ | $$$$$$  |$$$$$$$$/");
    printh(win, y +  7, TOTAL_WIDTH, "$$    $$/ $$ |  $$ |$$    $$ |/     $$/ $$       |");
    printh(win, y +  8, TOTAL_WIDTH, " $$$$$$/  $$/   $$/  $$$$$$$/ $$$$$$$/   $$$$$$$/");
    printh(win, y + 12, TOTAL_WIDTH, "(1) START (1)");
    printh(win, y + 13, TOTAL_WIDTH, "(2) QUIT  (2)");
    printh(win, y + 17, TOTAL_WIDTH, "Developed by Thyago Ismael");

    wrefresh(win);
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
