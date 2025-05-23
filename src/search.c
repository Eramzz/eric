#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "document.h"
#include "query.h"

DocumentsList* searchDocumentsWithQuery(ReverseIndex* index, Query* query) {
    if (!query || !query->first) return NULL;

    QueryItem* q = query->first;
    DocumentsList* result = reverseIndexGet(index, q->word);
    if (!result) return documentsListInit();

    DocumentsList* filtered = documentsListInit();
    Node* n = result->first;
    while (n) {
        documentsListAppend(filtered, n->document);
        n = n->next;
    }

    for (q = q->next; q != NULL; q = q->next) {
        DocumentsList* current = reverseIndexGet(index, q->word);
        if (!current) {
            documentsListFree(filtered, false);
            return documentsListInit();
        }

        Node* f = filtered->first;
        Node* prev = NULL;
        while (f) {
            if (!documentsListContains(current, f->document->id)) {
                Node* toDelete = f;
                if (prev) prev->next = f->next;
                else filtered->first = f->next;
                if (f == filtered->last) filtered->last = prev;
                f = f->next;
                free(toDelete);
                filtered->size--;
            } else {
                prev = f;
                f = f->next;
            }
        }
    }
    return filtered;
}


int containsAllWords(Document* doc, Query* q) {
    QueryItem* item = q->head;
    while (item) {
        if (!strstr(doc->body, item->word) && !strstr(doc->title, item->word)) {
            return 0;
        }
        item = item->next;
    }
    return 1;
}

void searchDocuments(DocumentList* docs, Query* q) {
    Document* curr = docs->head;
    int found = 0;
    while (curr && found < 5) {
        if (containsAllWords(curr, q)) {
            printf("(%d) %s\n---\n", found, curr->title);
            printf("%.150s%s\n---\n\n", curr->body, strlen(curr->body) > 150 ? "..." : "");
            found++;
        }
        curr = curr->next;
    }
    if (found == 0) printf("No results found.\n");
}