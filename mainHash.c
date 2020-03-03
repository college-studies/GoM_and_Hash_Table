#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 127

typedef struct hashStruct
{
    char *word, *definition;
    struct hashStruct *next;
}hashSt;

typedef struct defintionComparison
{
    char *definition;
    int status;
}defCmp;

void startHash(hashSt **hs);
int hashIndex(char *word);
void insertDictionary (hashSt **hs, char *word, char *definition);
defCmp compareDefinition(hashSt **hs, char *word);


int main(int argc, char const *argv[])
{

    hashSt *hs[SIZE];
    defCmp result_query;

    startHash(hs);

    insertDictionary(hs, "Kaio", "Definition test 1");
    insertDictionary(hs, "Fillipe", "Definition test 2");
    insertDictionary(hs, "oiaK", "Definition test 3");
    insertDictionary(hs, "Benjamim", "Definition test 4");


    printf("%s\n", compareDefinition(hs, "oiaK").definition);
    printf("%s\n", compareDefinition(hs, "Carlos").definition);
    printf("%s\n", compareDefinition(hs, "Fillipe").definition);
    printf("%s\n", compareDefinition(hs, "Benjamim").definition);



    


    return 1;
}

void startHash(hashSt **hs)
{
    int i;
    for(i = 0; i < SIZE; i++)
    {
        hs[i] = NULL;
    }
}

int hashIndex(char *word)
{
    int id, i, charQuant, sumAscii;
    
    charQuant = 0;
    sumAscii = 0;

    for(i = 0; i < strlen(word); i++)
    {
        charQuant++;
        sumAscii += (int) word[i];
    }
    id = floor (sumAscii/charQuant);

    return id;
}

void insertDictionary (hashSt **hs, char *word, char *definition)
{
    hashSt *new, *aux;
    int id;

    new = (hashSt*) malloc (sizeof(hashSt)*1);
    new->word = word;
    new->definition = definition;
    new->next = NULL;

    id = hashIndex(word);

    if(hs[id] == NULL)
        hs[id] = new;
    else
    {
        aux = hs[id];
        while(aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = new;
    }
}

defCmp compareDefinition(hashSt **hs, char *word)
{
    hashSt *aux;
    defCmp result;
    int id;

    result.status = 0;
    result.definition = "Word not found";
    
    id = hashIndex(word);
    aux = hs[id];

    if(aux != NULL)
    {
        while(strcmp(aux->word, word) && (aux->next != NULL))
            aux = aux->next;
        if(!strcmp(word, aux->word))
        {
            result.status = 1;
            result.definition = aux->definition;
        }
    }

    return result;
}
