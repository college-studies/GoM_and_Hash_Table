//Defines all GoM functions 
#ifndef startGoM_c
#define startGoM_c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define T 8 //number of board positions

typedef struct GoMboard
{
    char idBoard;
    int value;
    struct GoMboard *next;
    struct GoMboard *back;
}gBoard;

typedef struct GoMPlayers
{
    int idPlayer;
    char name[25];
    int points;
    int direction;
    gBoard *position;
    struct GoMPlayers *next;
}gPlayers;

gBoard *allocBoard(int id, int flag,int value)//Working
{
    gBoard *alloc;
    alloc = (gBoard*) malloc (sizeof(gBoard)*1);
    if (alloc == NULL)
        printf("Error");
    else
    {
        alloc->idBoard = id;
        if(flag)
            alloc->value = value;
        else
            alloc->value = -value;
    }
    return (alloc);

}

void startBoard (gBoard **gb)
{
    if (T <= 25)
    {
        int i, id = 97, value, flag;
        gBoard *new, *aux;
        srand((unsigned) time(NULL));

        for(i = 0; i < T; i++)
        {
            value = rand() % 40 + 1;
            flag = rand() % 2;
            if((*gb) == NULL)
            {
                new = allocBoard(id,flag,value);
                new->value = abs(new->value);
                (*gb) = new;
                new->next = (*gb);
                new->back = (*gb);
            }
            else
            {
                new = allocBoard(id, flag, value);
                new->back = (*gb)->back;
                new->next = (*gb);
                (*gb)->back->next = new;
                (*gb)->back = new;
            }          
            id++;
        }
    }
}

void allocPlayers(gPlayers **gp, int idPlayer, char *name, int points, gBoard *pos)
{
    gPlayers *new, *aux;
    new = (gPlayers*) malloc (sizeof(gPlayers)*1);
    if (new == NULL)
        printf("Error");
    else
    {
        strcpy(new->name,name);
        new->points = points;
        new->position = pos;
        new->direction = 1;
        new->idPlayer = idPlayer;
        if((*gp) == NULL)
        {           
            (*gp) = new;
            new->next = (*gp);
        }
        else
        {
            aux = (*gp);
            while(aux->next != (*gp))
                aux = aux->next;
            new->next = (*gp);
            aux->next = new;
        }
    }
}

void removePlayer(gPlayers *gp, char *name)
{
    gPlayers *aux1, *aux2;
    aux1 = gp;
    while(aux1->next->name != name)
        aux1 = aux1->next;
    aux2 = aux1->next;
    free(aux2);
    aux1->next = aux1->next->next;   

}

void printBoard(gBoard *gb)
{
    gBoard *aux;
    aux = gb;
    if ((gb) == NULL)
        printf("Empty Board\n");
    else
    {
        while (aux->next != gb)
        {
            printf("Position: %c\nValue: %d\n",aux->idBoard,aux->value);
            aux = aux->next;
        }
    }
}

#endif
