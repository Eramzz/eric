#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "links.h"

typedef struct Document {
    int id;
    char* title;
    char* body;
    Link* links;
    float relevance_score;
    struct Document* next;
} Document;




Document* documentDeserialize(const char* path);
void documentFree(Document* doc);
void documentPrintFull(Document* doc);
char** tokenizeDocument(Document* doc, int* count);
#endif


