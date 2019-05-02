#include "control.h"

int abs(int x)
{
    return x < 0 ? x : -x;
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
        if(player[i].score >= SCORE_TO_WIN)
            return true;
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
    if(rand() % 100 < DIFFICULTY) // efficint movement
        comp->pos = searchClosestPos(*comp, gold);
    else // random movement
    {
        if(rand() % 2)
            comp->pos.y += rand() % 3 - 1;
        else
            comp->pos.x += rand() % 3 - 1;
    }
}

int readInput(void)
{
    int input = getch();

    flushinp();

    return input;
}
void manualMovement(t_per *player)
{
    int input = readInput();

    switch(input)
    {
        case 'a':
            if(player->pos.x - 1 >= 0)
                player->pos.x--;
            break;
        case 's':
            if(player->pos.y + 1 <= SCREEN_Y)
                player->pos.y++;
            break;
        case 'd':
            if(player->pos.x - 1 <= SCREEN_X)
                player->pos.x++;
            break;
        case 'w':
            if(player->pos.y - 1 >= 0)
                player->pos.y--;
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
