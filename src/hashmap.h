//
// Created by sofia on 22/05/2025.
//

#ifndef HASHMAP_H

typedef struct _Node{
    struct _Node *next;
    char *key;
    Element element;

} *Node;

typedef struct _HashMap{
    Node *hashTable;
    uint64 size, count;

} *HashMap;




#define HASHMAP_H

#endif //HASHMAP_H
