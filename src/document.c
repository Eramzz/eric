#include "document.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_LINKS_CAPACITY 10

Document* documentDeserialize(const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) return NULL;

    Document* doc = malloc(sizeof(Document));
    doc->links = linksInit();
    doc->relevance = 0;

    fscanf(file, "%d\n", &doc->id);

    char title[512];
    fgets(title, sizeof(title), file);
    title[strcspn(title, "\n")] = 0;
    doc->title = strdup(title);

    char* body = malloc(8192);
    body[0] = '\0';

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        strcat(body, line);

        char* ptr = line;
        while ((ptr = strchr(ptr, '['))) {
            char* endText = strchr(ptr, ']');
            if (!endText) break;
            char* startId = strchr(endText, '(');
            char* endId = strchr(endText, ')');
            if (startId && endId && startId < endId) {
                int linkId = atoi(startId + 1);
                linkAppend(doc->links, linkId);
            }
            ptr = endId ? endId + 1 : endText + 1;
        }
    }
    doc->body = body;
    fclose(file);
    return doc;
}

void documentFree(Document* doc) {
    if (!doc) return;
    free(doc->title);
    free(doc->body);
    linksFree(doc->links);
    free(doc);
}

void documentPrintFull(Document* doc) {
    if (!doc) return;
    printf("ID\n%d\nTITLE\n%s\nRELEVANCE SCORE\n%.0f\nBODY\n%s\n",
           doc->id, doc->title, doc->relevance, doc->body);
}

char** tokenizeDocument(Document* doc, int* count) {
    char* copy = strdup(doc->body);
    char* token = strtok(copy, " ,.!?;:\n\"()[]{}");
    char** words = malloc(1024 * sizeof(char*));
    int idx = 0;

    while (token) {
        for (char* p = token; *p; p++) *p = tolower(*p);
        words[idx++] = strdup(token);
        token = strtok(NULL, " ,.!?;:\n\"()[]{}");
    }
    *count = idx;
    free(copy);
    return words;
}
