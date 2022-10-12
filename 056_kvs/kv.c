#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f;
  f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file!\n");
    return NULL;
  }
  size_t data_len = 0;
  char * data = NULL;

  kvpair_t * pair;
  pair = NULL;
  kvarray_t * array = malloc(sizeof(*array));
  size_t j;
  array->len = 0;
  array->array = NULL;
  while (getline(&data, &data_len, f) >= 0) {
    j = 0;
    pair = malloc(sizeof(*pair));
    pair->key = NULL;
    pair->value = NULL;
    while (data[j] != '=') {
      if (data[j] == '\0' || data[j] == '\n') {
        free(pair->key);
        pair->key = NULL;
        pair->value = NULL;
        break;
      }
      pair->key = realloc(pair->key, (j + 1) * sizeof(*pair->key));
      pair->key[j] = data[j];
      j++;
    }
    if (pair->key != NULL) {
      pair->key = realloc(pair->key, (j + 1) * sizeof(*pair->key));
      pair->key[j] = '\0';
      j++;
      size_t i = 0;
      while (data[j + i] != '\n' && data[j + i] != '\0') {
        pair->value = realloc(pair->value, (i + 1) * sizeof(*pair->value));
        pair->value[i] = data[j + i];
        i++;
      }
      pair->value = realloc(pair->value, (i + 1) * sizeof(*pair->value));
      pair->value[i] = '\0';
    }
    array->array = realloc(array->array, (array->len + 1) * sizeof(*array->array));
    array->array[array->len] = pair;
    pair = NULL;
    array->len += 1;
    free(data);
    data = NULL;
    data_len = 0;
  }
  free(pair);
  free(data);
  fclose(f);
  return array;
}

void freeKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->len; i++) {
    free(pairs->array[i]->key);
    free(pairs->array[i]->value);
    free(pairs->array[i]);
  }
  free(pairs->array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->len; i++) {
    printf("key = '%s' value = '%s'\n", pairs->array[i]->key, pairs->array[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  int j;
  int is_match;
  for (int i = 0; i < pairs->len; i++) {
    is_match = 1;
    j = 0;
    while (pairs->array[i]->key[j] != '\0') {
      if (key[j] == '\0') {
        is_match = 0;
        break;
      }
      else if (pairs->array[i]->key[j] != key[j]) {
        is_match = 0;
        break;
      }
      j++;
    }
    if (key[j] == '\0' && is_match > 0) {
      return pairs->array[i]->value;
    }
  }
  return NULL;
}
