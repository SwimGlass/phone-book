#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "phonebook_opt.h"

#ifdef _HASH
int hash31(char *s)
{
    unsigned value = 0;
    for (; (*s) !='\0'; s++)
        value = (value << 5) - (value + (*s));
    return value % MAX_HASH_SIZE;
}
#endif

/* FILL YOUR OWN IMPLEMENTATION HERE! */
lastNameEntry *findName_opt(char lastname[],lastNameEntry *pHead)
{
#ifdef _OPT
    /* TODO: implement */
    while(pHead!=NULL){
        if(strcmp(lastname,pHead->lastName)==0){
            printf(" %12s  is found!\n", lastname);
            return pHead;
        }
        pHead = pHead->pNext;
    } 
    printf(" %12s  is not found!\n", lastname);
    return NULL;
#endif
#ifdef _HASH
    int num = hash31(lastname);
    lastNameEntry *t=hash_table[num];
    while(t!=NULL)
    {    
        if(strcmp(lastname,t->lastName)==0){
            printf(" %12s  is found!\n", lastname);
            return t;
        }
        t = t->pNext;
    }
    printf(" %12s  is not found!\n", lastname);
    return NULL;
#endif
}

lastNameEntry *append_opt(char lastName[], lastNameEntry *e)
{
#ifdef _OPT
    strcpy(e->lastName,lastName);
    e->pNext = (lastNameEntry *)malloc(sizeof(lastNameEntry));
    e = e->pNext;
    e->pNext = NULL;
    return e;
#endif
#if defined (_HASH)
    int num = hash31(lastName);
    lastNameEntry *t = (lastNameEntry *)malloc(sizeof(lastNameEntry));
    strcpy(t->lastName, lastName);
    if(hash_table[num]==NULL){
        hash_table[num] = t;
        return e;
    }
    else{
        t->pNext = hash_table[num];
        hash_table[num] = t;
        return e;
    }
#endif
}
