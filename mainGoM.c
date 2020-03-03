#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "startGoM.c"


int main()
{
    gBoard *gb;
    gPlayers *gp;

    int i, N; //N = number of players
    char name[20],

    gb = NULL;
    gp = NULL;   


    startBoard (&gb);
    
    scanf("%d\n",&N);
    for(i = 0; i < N; i++)
    {
        printf("\nPlayer [%d]: ",i);
        scanf("%s",name);
        insereJogadornaLista(&gp, i+1, name, gb->value, gb);
    }


    return 1;
}



