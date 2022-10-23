#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <stdio.h>

#include "provided.h"

void checkArgc(int argc, int expect);
FILE * OpenCheckFile(const char * name);

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

/*
 Replace a blank in the line with the word returned by chooseWord.
 */
char * replaceWord(char * line, blank_t blank, const char * word);

#endif
