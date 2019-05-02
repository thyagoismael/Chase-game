#include "control.h"

bool someoneGetsGold(t_game g)
{
    int i;
    for(i = 0; i < NUM_PLAYERS; i++)
        if(g.player[i].pos.y == g.gold.y && g.player[i].pos.x == g.gold.x)
        {
            g.player[i].score++;
            return true;
        }
    return false;
}

void regenGold(t_pos *gold)
{
    gold->y = rand() % SCREEN_Y;
    gold->x = rand() % SCREEN_X;
}
void startGame(t_game *g)
{
    int i;

    srand(time(NULL));
    for(i = 0; i < NUM_PLAYERS; i++)
    {
        g->player[i].score = 0;
        g->player[i].pos.y = rand() % SCREEN_Y;
        g->player[i].pos.x = rand() % SCREEN_X;
        g->player[i].isActive = i < NUM_ACTIVE_PLAYERS;
    }
    regenGold(&g->gold);
}

bool gameOver(t_per player[])
{
    int i;
    for(i = 0; i < NUM_PLAYERS; i++)
        if(player[i].score >= 10)
            return true;
    return false;
}

void printField(t_game g)
{
    int i;

    clear();

    for(i = 0; i < NUM_PLAYERS; i++)
        mvprintw(g.player[i].pos.y, g.player[i].pos.x, "@");
    mvprintw(g.gold.y, g.gold.x, "$");
    refresh();
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
    if(rand() % 100 < DIFFICULTY) // efficint movement
        comp->pos = searchClosestPos(*comp, gold);
    else // random movement
    {
        comp->pos.x += (rand() % 3) - 1;
        comp->pos.y += (rand() % 3) - 1;
    }
}

void manualMovement(t_per *player)
{
    return;
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
