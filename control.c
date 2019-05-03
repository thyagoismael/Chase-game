#include "control.h"

#define abs(x) ((x>=0)?(x):(-(x)))

void startGame(t_game *g)
{
    int i;

    srand(time(NULL));

    // Creating players
    for(i = 0; i < NUM_PLAYERS; i++)
    {
        g->player[i].score = 0;
        g->player[i].pos.y = fitOnField(rand() % FIELD_SIZE_Y, 'y');
        g->player[i].pos.x = fitOnField(rand() % FIELD_SIZE_X, 'x');
        g->player[i].isActive = i < NUM_ACTIVE_PLAYERS;
    }

    regenGold(&g->gold);
}

void createWindows(WINDOW *listWindows[])
{
    listWindows[field] = newwin(FIELD_SIZE_Y, FIELD_SIZE_X, FIELD_START_Y, FIELD_START_X);
    box(listWindows[field], 0, 0);
    listWindows[score] = newwin(SCOREBOARD_SIZE_Y, SCOREBOARD_SIZE_X, SCOREBOARD_START_Y, SCOREBOARD_SIZE_X);
    box(listWindows[score], 0, 0);

}
int fitOnField(int number, int axis)
{
    int limit = FIELD_SIZE_X - BORDER_SIZE;

    if(axis == 'y')
        limit = FIELD_SIZE_Y - BORDER_SIZE;

    if(number < 1)
        number = 1;
    if(number >= limit)
        number = limit;

    return number;
}

bool someoneGetsGold(t_game *g)
{
    int i;
    for(i = 0; i < NUM_PLAYERS; i++)
    {
        if(g->player[i].pos.y == g->gold.y && g->player[i].pos.x == g->gold.x)
        {
            g->player[i].score++;
            return true;
        }
    }
    return false;
}

void regenGold(t_pos *gold)
{
    gold->y = fitOnField(rand() % FIELD_SIZE_Y, 'y');
    gold->x = fitOnField(rand() % FIELD_SIZE_X, 'x');
}

bool gameOver(t_per player[])
{
    int i;
    for(i = 0; i < NUM_PLAYERS; i++)
        if(player[i].score >= SCORE_TO_WIN)
        {
            player[i].turnWon++;
            return true;
        }
    return false;
}

t_pos searchClosestPos(t_per player, t_pos target)
{
    int dx, dy;
    float closest = 8000, tempDis;
    t_pos tempPos = player.pos, bestPos = player.pos;

    for(dx = -1; dx < 2; dx++) // search around the current position
    {
        tempPos.x = player.pos.x + dx;

        for(dy = -1; dy < 2; dy++)
        {
            if(abs(dx) == abs(dy)) // prevent the enemys from walking on diagonals
                continue;
            tempPos.y = player.pos.y + dy;
            if((tempDis = calculateDistance(tempPos, target)) < closest)
            {
                closest = tempDis;
                bestPos = tempPos;
            }
        }
    }

    return bestPos;
}

void autoMovement(t_per *comp, t_pos gold)
{
    int r;
    char possibleDir[5] = {left, up, right, down};

    if(rand() % 100 < DIFFICULTY) // efficient movement
        comp->pos = searchClosestPos(*comp, gold);
    else // random movement
    {
        r = rand() % 5; // the four direction + stand 
        changePosition(comp, possibleDir[r]); 
    }
}

void manualMovement(t_per *player)
{
    int input = getch();

    flushinp(); // clean the buffer

    changePosition(player, input);
}

void changePosition(t_per *player, t_directions dir)
{
    switch(dir)
    {
        case left:
            player->pos.x = fitOnField(player->pos.x - 1, 'x');
            break;
        case up:
            player->pos.y = fitOnField(player->pos.y - 1, 'y');
            break;
        case right:
            player->pos.x = fitOnField(player->pos.x + 1, 'x');
            break;
        case down:
            player->pos.y = fitOnField(player->pos.y + 1, 'y');
            break;
        default:
            break;
    }
}

void movePlayers(t_game *g)
{
    int i;
    for(i = 0; i < NUM_PLAYERS; i++)
        if(g->player[i].isActive)
            manualMovement(&g->player[i]);
        else
            autoMovement(&g->player[i], g->gold);
}

float calculateDistance(t_pos p1, t_pos p2)
{
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

void deleteAllScores(t_per player[])
{
    int i;
    for(i = 0; i < NUM_PLAYERS; i++)
        player[i].turnWon = player[i].score = 0;
}

bool wantToRetry(void)
{
    int input = 'q';
    int size_y = 4, size_x = 12;
    WINDOW *confirmWin;

    refresh();
    
    confirmWin = newwin(size_y, size_x, (FIELD_SIZE_Y - size_y)/2, (FIELD_SIZE_X - size_x)/2);
    wclear(confirmWin);
    box(confirmWin, 0, 0);

    mvwprintw(confirmWin, 1, 1, "  Retry?  ");
    mvwprintw(confirmWin, 2, 1, " yes / no ");
    wrefresh(confirmWin);

    while(input != 'y' && input != 'n')
    {
        input = getch();
        usleep(10000); // wait 10 ms
    }

    return input == 'y';
}
