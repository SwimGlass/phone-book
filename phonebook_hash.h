#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* original version */
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

typedef struct __NAME_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    entry *detail;
    struct __PHONE_NAME_ENTRY *pNext;
}lastNameEntry;

lastNameEntry *findName_opt(char lastname[], lastNameEntry *pHead);
lastNameEntry *append_opt(char lastName[], lastNameEntry *e);

#endif
