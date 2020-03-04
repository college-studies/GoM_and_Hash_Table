#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Runs the GoM game
#include "startGoM.c"

int runGoM(gPlayers *gp, int dice);

int main()
{
    gBoard *gb;
    gPlayers *gp;

    int i, N, playerQtt, dice, turn = 0; //N = number of players
    char name[20];

    gb = NULL;
    gp = NULL;   

    startBoard (&gb);
    printBoard(gb);

    printf("\nNumber of players: ");    
    scanf("%d",&N);
    for(i = 0; i < N; i++)
    {
        printf("\nPlayer [%d]: ",i+1);
        scanf("%s",name);   
        allocPlayers(&gp, i+1, name, gb->value, gb);
    }
    playerQtt = N;
    srand(time(NULL));
    printf("\n");
    while(playerQtt > 1)
    {
        printf("\nTurn %d\n",turn);        
        dice = rand() % 6 + 1;
        playerQtt += runGoM(gp,dice);
        gp = gp->next; 
        turn++;
    }
    printf("\n\nWinner: Player %d (%s)\n %d points\n",gp->idPlayer,gp->name,gp->points);

    return 1;
}


int runGoM(gPlayers *gp, int dice)
{
    int i;
    if(gp->direction)
    {
        printf("Player %d (%s) advances %d positions clockwise ",gp->idPlayer, gp->name, dice);
        for(i = 0; i < dice; i++)
            gp->position = gp->position->next;
    }
    else
    {
        printf("Player %d (%s) advances %d positions counterclockwise ",gp->idPlayer, gp->name, dice);
        for(i = 0; i < dice; i++)
            gp->position = gp->position->back;
    }
    printf("falls into box %c and ", gp->position->idBoard);
    gp->points += gp->position->value;
    if (gp->position->value > 0)
        printf("wins %d points (%d total).",gp->position->value
        , gp->points);
    else
    {
        gp->direction--;
        printf("loses %d points.", abs(gp->position->value));
        if(gp->points <= 0)
        {
            printf(" His score is negative and he's removed from the game.");
            removePlayer(gp, gp->name);
            return -1;
        }
        else
        {
            printf("(%d total)\n",gp->points);
            if (!gp->direction)
                printf("On his next move he'll advance counterclockwise.");
            else
                printf("On his next move he'll advance clockwise.");
        }
    }
    return 0; 
}


