#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <stdio.h>

#include "provided.h"

//3 tools to check the common errors (argc, open a file ...) in main
void checkArgc(int argc, int expect);
FILE * OpenCheckFile(const char * name);
void checkCloseFile(FILE * f);

/* Store information about a blank, including its category, position
 (the index of first _),and the lenth of the blank (include _).
 e.g. "aaa _bb_ ccc\n" has a blank_t with
 cat = bb, ind=4, len=4.
*/
struct blank_tag {
  char * cat;
  size_t ind;
  size_t len;
};
typedef struct blank_tag blank_t;

// An array of "blank_t"s defined above
struct blankarr_tag {
  blank_t * arr;
  size_t n;
};
typedef struct blankarr_tag blankarr_t;

// Free the blankarr_t
void freeblank(blankarr_t * blanks);

// After replace a blank in the line, updates the index in following blanks
void updateBlank(blankarr_t * blanks, size_t ind, size_t change);

/*
 Check the format of one line in the story template according the rule.
 It returns a blank_t arry that cotain all blank information in this line.
 Return NULL if there is a formating error. 
 */
blankarr_t * checkStory(char * line);

// Replace a blank in the line with the word returned by getWord.
char * replaceWord(char * line, blank_t blank, const char * word);

// Initialize a catarray object.
catarray_t * initialCat();

// Free all parts of the catarray_t cats
void freeCat(catarray_t * cats);

// Generatecat catarray_t according to the input file
catarray_t * generateCat(const char * fileName);

// Add a category or a word in a category in the catarray_t
void addCatOne(catarray_t * cats, char * category, char * word);

// Free all allocated memory and close the file to exit
void freeCloseAll(char * line, FILE * f, category_t * tracker, catarray_t * cats);

/* 
Check if the input word contains only a positive number.
   If so, return  a positive number, otherwise return 0.
 */
size_t checkPosInt(const char * word);

// Initialize a category object to track used words
category_t * initTracker();

/*
Get a word to replace the blank.
If the type of blank is a number -> use previouly used word.
  If the number exceed the number of previouly used word -> NULL
Otherwise, find the type in the category
If cannot find -> NULL (indicates failure)
*/
const char * getWord(blank_t blank, category_t * tracker, catarray_t * cat);

/*
Process the story file line by line.
Replace the blanks in each line as corresponging word.
Initialize a tracker to track the previouly used words.
The int "del" indicates whether to delete already used words.
Print each line after processed.
*/
void updateStory(FILE * story, catarray_t * cats, int del);

//Delete a used word in the catarray
void deleteWord(catarray_t * cats, const char * category, const char * word);

#endif
