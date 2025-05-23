#include <stdlib.h>
#include "links.h"

Links* linksInit() {
    Links* list = malloc(sizeof(Links));
    list->size = 0;
    list->head = list->tail = NULL;
    return list;
}

void linksFree(Links* list) {
    if (!list) return;
    Link* curr = list->head;
    while (curr) {
        Link* temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(list);
}

void linkAppend(Links* list, int id) {
    Link* newLink = malloc(sizeof(Link));
    newLink->id = id;
    newLink->next = NULL;
    if (!list->head) {
        list->head = list->tail = newLink;
    } else {
        list->tail->next = newLink;
        list->tail = newLink;
    }
    list->size++;
}

bool linksContains(Links* list, int id) {
    Link* curr = list->head;
    while (curr) {
        if (curr->id == id) return true;
        curr = curr->next;
    }
    return false;
}

int linksGet(Links* list, int index) {
    if (index < 0 || index >= list->size) return -1;
    Link* curr = list->head;
    while (index--) curr = curr->next;
    return curr->id;
}
