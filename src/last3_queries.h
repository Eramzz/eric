//
// Created by sofia on 08/05/2025.
//

#ifndef LAST3_QUERIES_H
#define LAST3_QUERIES_H

#include"query.h"

typedef struct QueryNode{
    Query*query;
    struct QueryNode*next;
}QueryNode;

typedef struct{
    QueryNode*head;
    QueryNode*tail;
    int size;
}QueryQueue;

void InitQueue_query
void PushQueue_query
void


#endif //LAST3_QUERIES_H

    void queryQueueInit(QueryQueue* q);
    void queryQueuePush(QueryQueue* q, Query* query);
    void queryQueuePrint(QueryQueue* q);
    void queryQueueFree(QueryQueue* q);

#endif
