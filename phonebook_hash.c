#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "phonebook_opt.h"


/* FILL YOUR OWN IMPLEMENTATION HERE! */
lastNameEntry *findName_opt(char lastname[],lastNameEntry *pHead)
{
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
}

lastNameEntry *append_opt(char lastName[], lastNameEntry *e)
{
    strcpy(e->lastName,lastName);
    e->pNext = (lastNameEntry *)malloc(sizeof(lastNameEntry));
    e = e->pNext;
    e->pNext = NULL;
    return e;
}
