#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "document_list.h"
#include "query.h"

extern void searchDocuments(DocumentList* docs, Query* q);



int main() {
  DocumentList docs;
  DocumentListInit(&docs);
  DocumentListLoadFromDir(&docs, "datasets/wikipedia12");

  char input[256];

  while (1) {
    printf("\nSearch (leave empty to exit): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if (strlen(input) == 0) break;

    Query* q = QueryInit(input);
    searchDocuments(&docs, q);
    queryFree(q);
  }

  DocumentListFree(&docs);
  return 0;
}

