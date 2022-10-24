#include "rand_story.h"

#include <string.h>

void checkArgc(int argc, int expect) {
  if (argc != expect) {  //check the number of arguments
    fprintf(stderr, "Invalid number of arguments!\n");
    exit(EXIT_FAILURE);
  }
}

FILE * OpenCheckFile(const char * name) {
  FILE * f = fopen(name, "r");
  if (f == NULL) {  //if cannot open the file->exit failure
    fprintf(stderr, "Cannot open the file!\n");
    exit(EXIT_FAILURE);
  }
  return f;
}

void checkCloseFile(FILE * f) {
  if (fclose(f) != 0) {  //try closing the file, if cannot -> exit failure
    perror("Failed to close the input file!\n");
    exit(EXIT_FAILURE);
  }
}

void freeblank(blankarr_t * blanks) {
  if (blanks == NULL) {  //if the blanks is NULL -> do not need to free
    return;
  }
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
      if (line[i] == '_') {  // find a new unmatched _
        blanks->arr = realloc(blanks->arr, (blanks->n + 1) * sizeof(*blanks->arr));
        blanks->arr[blanks->n].cat = NULL;
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
    fprintf(stderr, "Invalid format story format:\n %s ", line);
    return NULL;  // indicate the faliure
  }
  return blanks;
}

void updateBlank(blankarr_t * blanks, size_t ind, size_t change) {
  for (size_t i = ind; i < blanks->n; i++) {
    blanks->arr[i].ind += change;
  }  //update the ind in each block based on the change of its position
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

catarray_t * initialCat() {  //initialize a catarray_t object
  catarray_t * cats = malloc(sizeof(*cats));
  cats->arr = NULL;
  cats->n = 0;
  return cats;
}

void freeCat(catarray_t * cats) {
  if (cats == NULL) {
    return;
  }
  for (size_t i = 0; i < cats->n; i++) {
    free(cats->arr[i].name);  // free the category name
    for (size_t j = 0; j < cats->arr[i].n_words; j++) {
      free(cats->arr[i].words[j]);  // free all words in this category
    }
    free(cats->arr[i].words);  // free the category object
  }
  free(cats->arr);  // free the array of categories
  free(cats);       // free the catarray_t object
}

catarray_t * generateCat(const char * fileName) {
  FILE * f = fopen(fileName, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open the words file!\n");
    return NULL;
  }
  catarray_t * cats = initialCat();
  char * line = NULL;
  size_t size = 0;
  while (getline(&line, &size, f) != -1) {
    char * category = NULL;
    char * word = NULL;
    for (size_t i = 0; i < strlen(line); i++) {
      if (line[i] == ':') {  // get the category name before ':'
        category = strndup(line, i);
        if (line[strlen(line) - 1] == '\n') {  // do not copy '\n'
          word = strndup(line + i + 1, strlen(line) - (i + 2));
        }
        else {  // if the line does not end with '\n'-> copy all
          word = strndup(line + i + 1, strlen(line) - (i + 1));
        }
        break;
      }
    }
    if (category == NULL || word == NULL) {  // did not find ':'
      freeCat(cats);
      fprintf(stderr, "Wrong input in line: %s\n", line);
      free(line);
      fclose(f);
      return NULL;  // indicate failure
    }
    free(line);
    line = NULL;
    addCatOne(cats, category, word);  // update the catarray
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "File close error!\n");
    freeCat(cats);
    return NULL;  // indicate failure
  }
  return cats;
}

void addCatOne(catarray_t * cats, char * category, char * word) {
  int find = 0;
  // Find if the category is already exist
  for (size_t i = 0; i < cats->n; i++) {
    // If so, add the word to its word list
    if (strcmp(category, cats->arr[i].name) == 0) {
      cats->arr[i].words = realloc(
          cats->arr[i].words, (cats->arr[i].n_words + 1) * sizeof(*cats->arr[i].words));
      cats->arr[i].words[cats->arr[i].n_words] = word;
      cats->arr[i].n_words++;
      free(category);  // the input category string no longer needed
      category = NULL;
      find = 1;
      break;
    }
  }
  // If not found, create a new category and put word in it.
  if (find != 1) {
    cats->arr = realloc(cats->arr, (cats->n + 1) * sizeof(*cats->arr));
    cats->arr[cats->n].n_words = 1;
    cats->arr[cats->n].name = category;
    cats->arr[cats->n].words = malloc(1 * sizeof(*cats->arr[cats->n].words));
    cats->arr[cats->n].words[0] = word;
    cats->n++;
  }
}

void freeCloseAll(char * line, FILE * f, category_t * tracker, catarray_t * cats) {
  free(line);
  // free the tracker (category object)
  for (size_t i = 0; i < tracker->n_words; i++) {
    free(tracker->words[i]);
  }
  free(tracker->name);
  free(tracker->words);
  free(tracker);
  freeCat(cats);      // free the cats
  checkCloseFile(f);  //now all is free -> try and close file
}

size_t checkPosInt(const char * word) {
  char * endtr;  // store the non-number characters
  long number = strtol(word, &endtr, 10);
  if (number > 0) {                    // It is positive number
    if (endtr[0] == '\0') {            //The string contains only numbers
      return strtoul(word, NULL, 10);  // return the unsigned value
    }
  }
  return 0;  // indicates it is not a postive number
}

category_t * initTracker() {  //initialize a categories object as tracker
  category_t * tracker = malloc(sizeof(*tracker));
  tracker->n_words = 0;
  tracker->name = NULL;
  tracker->words = NULL;
  return tracker;
}

// Update tracker
void addTrackOne(category_t * tracker, const char * word) {
  tracker->words =
      realloc(tracker->words, (tracker->n_words + 1) * sizeof(*tracker->words));
  tracker->words[tracker->n_words] = strdup(word);
  tracker->n_words++;
}

const char * getWord(blank_t blank, category_t * tracker, catarray_t * cats) {
  if (cats == NULL) {  // for step 1
    return chooseWord(blank.cat, NULL);
  }
  size_t number = 0;  // whether the value in the blank is number
  if ((number = checkPosInt(blank.cat)) > 0) {
    if (number > tracker->n_words) {  //exceed the #pre-used words
      fprintf(stderr, "Invalid number of previously used word!\n");
      return NULL;  // indicate faliure
    }
    char * preword = tracker->words[tracker->n_words - number];
    addTrackOne(tracker, preword);
    return preword;
  }
  else {  // the value in the blank is not a valid number
    for (size_t i = 0; i < cats->n; i++) {
      if (strcmp(blank.cat, cats->arr[i].name) == 0 &&
          cats->arr[i].n_words > 0) {  // whether it is in the catarray
        const char * newword = chooseWord(blank.cat, cats);
        addTrackOne(tracker, newword);
        return newword;
      }
    }
    fprintf(stderr, "The category %s does not exist or have usable words!\n", blank.cat);
    return NULL;  // the value is not in the catarray
  }
}

void updateStory(FILE * story, catarray_t * cats, int del) {
  char * line = NULL;
  size_t size = 0;
  category_t * tracker = initTracker();
  while (getline(&line, &size, story) != -1) {  // process line by line
    blankarr_t * blanks = checkStory(line);
    size_t pre = strlen(line);
    if (blanks == NULL) {  // if a line has format error -> exit faliure
      freeCloseAll(line, story, tracker, cats);
      exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < blanks->n; i++) {  // replace the blanks
      const char * word = getWord(blanks->arr[i], tracker, cats);
      if (word == NULL) {  // NULL indicates faliure
        freeblank(blanks);
        freeCloseAll(line, story, tracker, cats);
        exit(EXIT_FAILURE);  // The error has already printed, just exit
      }
      line = replaceWord(line, blanks->arr[i], word);  //replace a blank
      if (del > 0) {
        deleteWord(cats, blanks->arr[i].cat, word);
      }
      // Update the position in the following blanks in the new line
      updateBlank(blanks, i + 1, strlen(line) - pre);
      pre = strlen(line);  // update the length of the new line
    }
    printf("%s", line);  // print the output line
    free(line);
    freeblank(blanks);
    line = NULL;
  }
  freeCloseAll(line, story, tracker, cats);
}

void deleteWord(catarray_t * cats, const char * category, const char * word) {
  // Find the corresponding category
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(category, cats->arr[i].name) == 0) {
      // Find the corresponding word
      for (size_t j = 0; j < cats->arr[i].n_words; j++) {
        if (strcmp(word, cats->arr[i].words[j]) == 0) {
          free(cats->arr[i].words[j]);  //delete the word
          cats->arr[i].words[j] = NULL;
          // Move the words behind it forward
          for (size_t k = j + 1; k < cats->arr[i].n_words; k++) {
            cats->arr[i].words[k - 1] = cats->arr[i].words[k];
            cats->arr[i].words[k] = NULL;
          }                        //last element  becomes NULL
          cats->arr[i].n_words--;  //decreases the length of word list
          return;                  // break the loop by return
        }
      }
    }
  }
}
