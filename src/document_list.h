#ifndef DOCUMENT_LIST_H
#define DOCUMENT_LIST_H

#include <stdbool.h>
#include "document.h"

typedef struct Node {
    Document* document;
    struct Node* next;
} Node;

typedef struct DocumentsList {
    int size;
    Node* head;
    Node* tail;
} DocumentsList;

Document* DocumentsListInit();
void documentFree(DocumentsList* list, bool freeDocs);
void documentsListAppend(DocumentsList* list, Document* document);
bool DocumentsListContains(DocumentsList* list, int id);
Document* documentsListGet(DocumentsList* list, int index);
Document* DocumentsListFromFolder(char* folderPath, int count);
Document* DocumentListSortedDescending(DocumentsList* list, int max);

#endif
