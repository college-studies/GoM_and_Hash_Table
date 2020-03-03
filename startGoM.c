#ifndef startGoM_c
#define startGoM_c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define T 4 //number of board positions

typedef struct GoMboard
{
    char id;
    int value;
    struct GoMboard *next;
    struct GoMboard *back;
}gBoard;

typedef struct GoMPlayers
{
    char name[25];
    int points;
    int direction;
    struct GoMBoard *position;
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
        alloc->id = id;
        if(flag)
            alloc->value = value;
        else
            alloc->value = -value;
    }
    return (alloc);

}

void startBoard (gBoard **gb)//Working
{
    if (T <= 25)
    {
        int i, id = 97, value, flag;
        gBoard *new, *aux;
        srand((unsigned) time(NULL));

        for(i = 0; i < T; i++)
        {
            value = rand() % 50;
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

void allocPlayers(gPlayers **gp, char *name, int points, gBoard *pos)//Working
{
    int playerQtt;
    gPlayers *new, *aux;
    new = (gPlayers*) malloc (sizeof(gPlayers)*1);
    if (new == NULL)
        printf("Error");
    else
    {
        strcpy(new->name,name);
        new->points = points;
        new->position = 0;
        new->direction = 1;
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
        playerQtt = 1;
    }
}

#endif
