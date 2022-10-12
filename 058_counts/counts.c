#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->array = NULL;
  counts->len = 0;
  counts->unkown = 0;
  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unkown += 1;
    return;
  }
  int find = 0;
  one_count_t * res = malloc(sizeof(*res));
  res->value = NULL;
  res->count = 1;
  for (int i = 0; i < c->len; i++) {
    int j = 0;
    find = 1;
    while (name[j] != '\0') {
      if (c->array[i]->value[j] == '\0') {
        find = 0;
        break;
      }
      if (c->array[i]->value[j] != name[j]) {
        find = 0;
        break;
      }

      j++;
    }
    if (c->array[i]->value[j] != '\0') {
      find = 0;
    }
    if (find == 1) {
      c->array[i]->count += 1;
      free(res);
      return;
    }
  }
  int k = 0;
  while (name[k] != '\0') {
    res->value = realloc(res->value, (k + 1) * sizeof(*res->value));
    res->value[k] = name[k];
    k++;
  }
  res->value = realloc(res->value, (k + 1) * sizeof(*res->value));
  res->value[k] = '\0';
  c->array = realloc(c->array, (c->len + 1) * sizeof(*c->array));
  c->array[c->len] = res;
  c->len += 1;
  res = NULL;
  return;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME

  for (int i = 0; i < c->len; i++) {
    fprintf(outFile, "%s: %d\n", c->array[i]->value, c->array[i]->count);
  }
  if (c->unkown > 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unkown);
  }
  fclose(outFile);
}

void freeCounts(counts_t * c) {
  for (int i = 0; i < c->len; i++) {
    free(c->array[i]->value);
    free(c->array[i]);
  }
  free(c->array);
  free(c);
}
