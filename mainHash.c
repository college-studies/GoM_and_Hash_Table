#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 10

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
int insertDictionary (hashSt **hs, char *word, char *definition);
defCmp compareDefinition(hashSt **hs, char *word);


int main()
{
    hashSt *hs[SIZE];
    defCmp result_query;

    startHash(hs);

    insertDictionary(hs, "Kaio", "Teste de definicao 1");
    insertDictionary(hs, "Fillipe", "Teste de definicao 2");
    insertDictionary(hs, "oiaK", "Teste de definicao 3");
    insertDictionary(hs, "Benjamim", "Teste de definicao 4");
    insertDictionary(hs, "Benjamim", "Teste de definicao 4");



    return 1;
}

void startHash(hashSt **hs)
{
    int i;
    for(i = 0; i < SIZE; i++)
        hs[i] = NULL;
}

int hashIndex(char *word)
{
    int id, i, charQuant = 0, sumAscii = 0;

    for(i = 0; strlen(word); i++)
    {
        charQuant++;
        sumAscii += (int) word[i];
    }
    id = floor(sumAscii/charQuant);

    return id;
}

int insertDictionary (hashSt **hs, char *word, char *definition)
{
    hashSt *new, *aux;
    int id;

    new = (hashSt*) malloc (sizeof(hashSt));
    new->word = word;
    new->definition = definition;
    new->next = NULL;

    if(hs[id] == NULL)
        hs[id] = new;
    else
    {
        aux = hs[id];
        while(aux->next != NULL)
            aux = aux->next;
        aux->next = new;
    }

    return 1;
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
            aux->next;
        if(!strcmp(word, aux->word))
        {
            result.status = 1;
            result.definition = aux->definition;
        }
    }

    return result;
}
