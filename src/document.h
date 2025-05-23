#ifndef DOCUMENT_H
#define DOCUMENT_H


typedef struct Document {
    int id;
    char* title;
    char* body;
    Link* links;
    float relevance_score;
    struct Document* next;
} Document;


void documentFree(Document* doc);
#endif


