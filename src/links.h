#ifndef LINKS_H
#define LINKS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Link {
    int id;
    struct Link* next;
} Link;

typedef struct links {
    int size;
    Link* head;
    Link* tail;
} Links;

Link* linkInit();
void linksFree(Links* list);
void linkAppend(Links* list, int id);
bool LinksContains(Links* list, int id);
int LinksGet(Links* list, int index);
#endif