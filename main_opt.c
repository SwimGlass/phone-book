#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include IMPL

#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

#ifdef MAX_HASH_SIZE
    /* initial hash table */
#include "phonebook_opt.h"
    int a;
    for (a = 0; a < MAX_HASH_SIZE; a++) {
        hash_table[a] = NULL;
    }
#endif

    /* build the entry */
    lastNameEntry *nameHead,*e;
    nameHead = (lastNameEntry *) malloc(sizeof(lastNameEntry));
    printf("orig size of entry : %lu bytes\n", sizeof(lastNameEntry));
    e = nameHead;
    e->pNext = NULL;

#if defined(__GNUC__)
    __builtin___clear_cache((char *) nameHead, (char *) nameHead + sizeof(lastNameEntry));
#endif
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0') i++;
        line[i - 1] = '\0';
        i = 0;
        e = append_opt(line, e);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);

    e = nameHead;

    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";
    e = nameHead;

    assert(findName_opt(input, e) &&
            "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName_opt(input, e)->lastName, "zyxel"));

#if defined(__GNUC__)
    __builtin___clear_cache((char *) nameHead, (char *) nameHead + sizeof(lastNameEntry));
#endif
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findName_opt(input, e);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

    printf("execution time of append_opt() : %lf sec\n", cpu_time1);
    printf("execution time of findName_opt() : %lf sec\n", cpu_time2);

    /* FIXME: release all allocated entries */
    free(nameHead);
    return 0;
}
