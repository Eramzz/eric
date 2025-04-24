#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "link.h"

typedef struct Document {
    int id;
    char* title;
    char* body;
    Link* links;
    struct Document* next;
} Document;

Document* documentDeserialize(const char* path);
void documentPrint(Document* doc);
void documentFree(Document* doc);

#endif