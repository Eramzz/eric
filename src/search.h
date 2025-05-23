//
// Created by sofia on 08/05/2025.
//

#ifndef SEARCH_H
#define SEARCH_H

DocumentsList* searchDocumentsWithQuery(ReverseIndex* index, Query* query);

int containsAllWords(Document* doc, Query* q);
void searchDocuments(DocumentList* docs, Query* q);

#endif //SEARCH_H