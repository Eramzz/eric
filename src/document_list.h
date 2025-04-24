#ifndef DOCUMENT_LIST_H
#define DOCUMENT_LIST_H

#include "document.h"

typedef struct DocumentList {
    Document* head;
} DocumentList;

void documentListInit(DocumentList* list);
void documentListLoadFromDir(DocumentList* list, const char* dirpath);
void documentListPrint(DocumentList* list);
void documentListFree(DocumentList* list);

#endif