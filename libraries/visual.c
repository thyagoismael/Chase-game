#include "visual.h" 

void printGame(t_game g)
{
    static bool windowsCreated = false;
    static WINDOW *fieldWin, *scoreWin, *helpWin;

    if(!windowsCreated)
    {
        fieldWin = newwin(FIELD_HEIGHT, FIELD_WIDTH, FIELD_START_Y, FIELD_START_X);
        scoreWin = newwin(SCOREBOARD_HEIGHT, SCOREBOARD_WIDTH, SCOREBOARD_START_Y, SCOREBOARD_START_X);
        helpWin = newwin(HELP_HEIGHT, HELP_WIDTH, HELP_START_Y, HELP_START_X);
    }
    box(fieldWin, 0, 0);
    box(scoreWin, 0, 0);
    box(helpWin, 0, 0);

    printField(g, fieldWin);
    printScore(g, scoreWin);
    printHelp(helpWin);
    
    doupdate();
}

void printField(t_game g, WINDOW *win)
{
    int i;

    clear();

    wnoutrefresh(stdscr);
    for(i = 0; i < NUM_PLAYERS; i++)
        mvwprintw(win, g.player[i].pos.y, g.player[i].pos.x, "%c", 'A' + i);
    mvwprintw(win, g.gold.y, g.gold.x, "$");

    wnoutrefresh(win);
}

void printScore(t_game g, WINDOW *win)
{
    int i;

    wnoutrefresh(stdscr);
    
    printh(win, 1, SCOREBOARD_WIDTH, "-> SCORE <-");
    for(i = 0; i < NUM_PLAYERS; i++)
    {
        mvwprintw(win, 3 + i, 2, "Player %c: %d", 'A' + i, g.player[i].score);
        if(g.player[i].turnWon)
            wprintw(win, " (%d)", g.player[i].turnWon);
    }

    wnoutrefresh(win);
}

void printHelp(WINDOW *win)
{
    wnoutrefresh(stdscr);
    printh(win, 1, HELP_WIDTH, "-> COMANDS <-");
    printh(win, 3, HELP_WIDTH, "Player A");
    printh(win, 4, HELP_WIDTH, "w");
    printh(win, 5, HELP_WIDTH, "a d s");
    wnoutrefresh(win); 
}


// print centralized horizontaly
void printh(WINDOW *win, int y, int width, char *text)
{
    int len = strlen(text);
    int x = (width - len) / 2;

    mvwprintw(win, y, x, text);
}
