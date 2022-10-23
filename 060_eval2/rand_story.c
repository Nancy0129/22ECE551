#include "rand_story.h"

#include <string.h>

void checkArgc(int argc, int expect) {
  if (argc != expect) {
    fprintf(stderr, "Invalid number of arguments!\n");
    exit(EXIT_FAILURE);
  }
}

FILE * OpenCheckFile(const char * name) {
  FILE * f = fopen(name, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open the file!\n");
    exit(EXIT_FAILURE);
  }
  return f;
}
void freeblank(blankarr_t * blanks) {
  for (size_t i = 0; i < blanks->n; i++) {
    free(blanks->arr[i].cat);
  }
  free(blanks->arr);
  free(blanks);
  blanks = NULL;
}

blankarr_t * checkStory(char * line) {
  blankarr_t * blanks = malloc(sizeof(*blanks));
  blanks->n = 0;
  blanks->arr = NULL;
  int i = 0;
  size_t ind, len;
  len = 0;
  int hasLeft = 0;  // indicates whether we find an unmatched _
  while (line[i] != '\0' && line[i] != '\n') {
    if (hasLeft == 1) {
      if (line[i] == '_') {
        // Copy the category name into cat of the blank
        blanks->arr[blanks->n - 1].cat = strndup(line + ind + 1, len);
        blanks->arr[blanks->n - 1].len = len + 2;  //include the two '_'s
        len = 0;
        hasLeft = 0;  //eliminated an unmatted _
      }
      else {
        len++;  // the length of the category name increases
      }
    }
    else {
      if (line[i] == '_') {
        blanks->arr = realloc(blanks->arr, (blanks->n + 1) * sizeof(*blanks->arr));
        blanks->arr[blanks->n].ind = i;
        blanks->n++;
        ind = i;      // points to the first _
        hasLeft = 1;  // found an unmatted _
      }
    }
    i++;
  }
  if (hasLeft == 1) {   // it means there remains an  unmatched _
    freeblank(blanks);  // clear all mallocated values
    return NULL;        // indicate the faliure
  }
  return blanks;
}

void updateBlank(blankarr_t * blanks, size_t ind, size_t change) {
  for (size_t i = ind; i < blanks->n; i++) {
    blanks->arr[i].ind += change;
  }
  return;
}

char * replaceWord(char * line, blank_t blank, const char * word) {
  size_t len = strlen(line) + strlen(word) - blank.len;   // len of newline
  char * newline = malloc((len + 1) * sizeof(*newline));  // create newline
  //copy the part precedes the indicated blank
  for (size_t i = 0; i < blank.ind; i++) {
    newline[i] = line[i];
  }
  //copy the word to replace the blank
  for (size_t i = 0; i < strlen(word); i++) {
    newline[blank.ind + i] = word[i];
  }
  //copy the remaining part of the old line
  for (size_t i = 0; i < (strlen(line) - (blank.ind + blank.len)); i++) {
    newline[blank.ind + strlen(word) + i] = line[blank.ind + blank.len + i];
  }
  newline[len] = '\0';
  free(line);  // free the old line
  line = NULL;
  return newline;  // output the newline
}

void freeCat(catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    free(cats->arr[i].name);
    for (size_t j = 0; j < cats->arr[i].n_words; j++) {
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].words);
  }
  free(cats->arr);
  free(cats);
}

catarray_t * generateCat(FILE * f) {
  catarray_t * cats = malloc(sizeof(*cats));
  cats->arr = NULL;
  cats->n = 0;
  char * line = NULL;
  size_t size = 0;
  while (getline(&line, &size, f) != -1) {
    char * category = NULL;
    char * word = NULL;
    for (size_t i = 0; i < strlen(line); i++) {
      if (line[i] == ':') {
        category = strndup(line, i);
        if (line[strlen(line) - 1] == '\n') {
          word = strndup(line + i + 1, strlen(line) - (i + 2));
        }
        else {  // if the line does not end with '\n'
          word = strndup(line + i + 1, strlen(line) - (i + 1));
        }
        break;
      }
    }
    if (category == NULL || word == NULL) {
      freeCat(cats);
      fprintf(stderr, "Wrong input in line: %s", line);
      return NULL;
    }
    free(line);
    line = NULL;
    addCatOne(cats, category, word);
  }
  free(line);
  return cats;
}

void addCatOne(catarray_t * cats, char * category, char * word) {
  int find = 0;
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(category, cats->arr[i].name) == 0) {
      cats->arr[i].words = realloc(
          cats->arr[i].words, (cats->arr[i].n_words + 1) * sizeof(*cats->arr[i].words));
      cats->arr[i].words[cats->arr[i].n_words] = word;
      cats->arr[i].n_words++;
      free(category);
      category = NULL;
      find = 1;
      break;
    }
  }
  if (find != 1) {
    cats->arr = realloc(cats->arr, (cats->n + 1) * sizeof(*cats->arr));
    cats->arr[cats->n].n_words = 1;
    cats->arr[cats->n].name = category;
    cats->arr[cats->n].words = malloc(1 * sizeof(*cats->arr[cats->n].words));
    cats->arr[cats->n].words[0] = word;
    cats->n++;
  }
}
