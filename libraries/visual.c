#include "visual.h" 

void printGame(t_game g)
{
    static bool windowsCreated = false;
    static WINDOW *fieldWin, *scoreWin;

    if(!windowsCreated)
    {
        fieldWin = newwin(FIELD_HEIGHT, FIELD_WIDTH, FIELD_START_Y, FIELD_START_X);
        scoreWin = newwin(SCOREBOARD_HEIGHT, SCOREBOARD_WIDTH, SCOREBOARD_START_Y, SCOREBOARD_START_X);
    }
    box(fieldWin, 0, 0);
    box(scoreWin, 0, 0);

    printField(g, fieldWin);
    printScore(g, scoreWin);
    
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
    
    mvwprintw(win, 1, 1, " -> SCORE <- ");
    for(i = 0; i < NUM_PLAYERS; i++)
    {
        mvwprintw(win, 3 + i, 2, "Player %c: %d", 'A' + i, g.player[i].score);
        if(g.player[i].turnWon)
            wprintw(win, " (%d)", g.player[i].turnWon);
    }

    wnoutrefresh(win);
}

void printh(WINDOW *win, int y, int width, char *text)
{
    int len = strlen(text);
    int x = (width - len) / 2;

    mvwprintw(win, y, x, text);
}
