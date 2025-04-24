#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "document.h"

char* readLine(FILE* fp) {
    char buffer[1024];
    if (!fgets(buffer, sizeof(buffer), fp)) return NULL;
    size_t len = strlen(buffer);
    if (buffer[len - 1] == '\n') buffer[len - 1] = '\0';
    return strdup(buffer);
}

void extractLinks(char* line, Link** links) {
    char* ptr = line;
    while ((ptr = strchr(ptr, '['))) {
        char* end = strchr(ptr, ']');
        if (!end) break;
        char* idStart = strchr(end, '(');
        char* idEnd = strchr(end, ')');
        if (idStart && idEnd && idEnd > idStart) {
            int id = atoi(idStart + 1);
            linkAppend(links, id);
        }
        ptr = end + 1;
    }
}

Document* documentDeserialize(const char* path) {
    FILE* fp = fopen(path, "r");
    if (!fp) return NULL;

    Document* doc = (Document*)malloc(sizeof(Document));
    doc->links = NULL;
    doc->next = NULL;

    char* line = readLine(fp);
    doc->id = atoi(line);
    free(line);

    doc->title = readLine(fp);

    size_t bodySize = 1024;
    doc->body = (char*)malloc(bodySize);
    doc->body[0] = '\0';

    while ((line = readLine(fp))) {
        extractLinks(line, &doc->links);
        if (strlen(doc->body) + strlen(line) + 2 > bodySize) {
            bodySize *= 2;
            doc->body = (char*)realloc(doc->body, bodySize);
        }
        strcat(doc->body, line);
        strcat(doc->body, "\n");
        free(line);
    }

    fclose(fp);
    return doc;
}

void documentPrint(Document* doc) {
    printf("ID: %d\nTitle: %s\n\n%s", doc->id, doc->title, doc->body);
}

void documentFree(Document* doc) {
    if (!doc) return;
    free(doc->title);
    free(doc->body);
    linkFree(doc->links);
    free(doc);
}