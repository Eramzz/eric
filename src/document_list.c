#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "document_list.h"

DocumentsList* documentsListInit() {
    DocumentsList* list = malloc(sizeof(DocumentsList));
    list->size = 0;
    list->first = list->last = NULL;
    return list;
}

void documentsListFree(DocumentsList* list, bool freeDocs) {
    Node* curr = list->first;
    while (curr) {
        Node* next = curr->next;
        if (freeDocs) documentFree(curr->document);
        free(curr);
        curr = next;
    }
    free(list);
}

void documentsListAppend(DocumentsList* list, Document* document) {
    Node* node = malloc(sizeof(Node));
    node->document = document;
    node->next = NULL;
    if (!list->first) {
        list->first = list->last = node;
    } else {
        list->last->next = node;
        list->last = node;
    }
    list->size++;
}

bool documentsListContains(DocumentsList* list, int id) {
    Node* curr = list->first;
    while (curr) {
        if (curr->document->id == id) return true;
        curr = curr->next;
    }
    return false;
}

Document* documentsListGet(DocumentsList* list, int index) {
    if (index < 0 || index >= list->size) return NULL;
    Node* curr = list->first;
    while (index--) curr = curr->next;
    return curr->document;
}

DocumentsList* DocumentsListFromFolder(const char* folderPath, int count) {
    DocumentsList* list = documentsListInit();
    DIR* dir = opendir(folderPath);
    if (!dir) return NULL;

    struct dirent* entry;
    char filepath[512];
    int loaded = 0;

    while ((entry = readdir(dir)) && (count < 0 || loaded < count)) {
        if (entry->d_type != DT_REG) continue;

        snprintf(filepath, sizeof(filepath), "%s/%s", folderPath, entry->d_name);
        Document* doc = documentDeserialize(filepath);
        if (doc) {
            documentsListAppend(list, doc);
            loaded++;
        }
    }

    closedir(dir);
    return list;
}

void documentsListPrint(DocumentsList* list, int max) {
    Node* curr = list->first;
    int i = 0;
    while (curr && i < max) {
        printf("(%d) %s\n---\n", i, curr->document->title);
        char* body = curr->document->body;
        int len = strlen(body);
        if (len > 150) {
            char tmp = body[150];
            body[150] = '\0';
            printf("%s...\n", body);
            body[150] = tmp;
        } else {
            printf("%s\n", body);
        }
        printf("---\nrelevance score: %.0f\n\n", curr->document->relevance);
        curr = curr->next;
        i++;
    }
}