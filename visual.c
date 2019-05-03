#include "visual.h" 

void printGame(t_game g)
{
    WINDOW *fieldWin;

    fieldWin = newwin(FIELD_SIZE_Y, FIELD_SIZE_X, FIELD_START_Y, FIELD_START_X);
    box(fieldWin, 0, 0);

    printField(g, fieldWin);
    
    doupdate();
}

void printField(t_game g, WINDOW *win)
{
    int i;

    clear();

    refresh();
    for(i = 0; i < NUM_PLAYERS; i++)
        mvwprintw(win, g.player[i].pos.y, g.player[i].pos.x, "%c", 'A' + i);
    mvwprintw(win, g.gold.y, g.gold.x, "$");

    for(i = 0; i < NUM_PLAYERS; i++)
    {
        mvprintw(2*i, 0, "Current position %c: %d, %d", 'A' + i, g.player[i].pos.y, g.player[i].pos.x);
        mvprintw(2*i + 1, 0, "Score player %c: %d", 'A' + i, g.player[i].score);
    }
    refresh();

    //mvwaddstr(10,10, "texto:");
    wrefresh(win);
}
/*
void printEnemy(WINDOW *win, int y, int x, char name)
{
    char skin[2] = {name};
    
    mvaddstr(
}
void createEnemySkin(char name, char *skin)
{
    skin[0] = name;
    skin[1] = '\0';
}
*/
