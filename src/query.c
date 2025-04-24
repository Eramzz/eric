#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "query.h"

QueryItem* queryItemCreate(const char* word) {
    QueryItem* item = (QueryItem*)malloc(sizeof(QueryItem));
    item->word = strdup(word);
    item->next = NULL;
    return item;
}

Query* queryInit(const char* input) {
    Query* q = (Query*)malloc(sizeof(Query));
    q->head = NULL;
    char* inputCopy = strdup(input);
    char* token = strtok(inputCopy, " ");
    QueryItem** current = &q->head;

    while (token) {
        *current = queryItemCreate(token);
        current = &((*current)->next);
        token = strtok(NULL, " ");
    }
    free(inputCopy);
    return q;
}

void queryFree(Query* query) {
    QueryItem* curr = query->head;
    while (curr) {
        QueryItem* next = curr->next;
        free(curr->word);
        free(curr);
        curr = next;
    }
    free(query);
}
