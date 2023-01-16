#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  char * outName = NULL;
  int j = 0;
  while (inputName[j] != '\0') {
    outName = realloc(outName, (j + 1) * sizeof(*outName));
    outName[j] = inputName[j];
    j++;
  }
  //if (inputName[j - 1] == 't' && inputName[j - 2] == 'x' && inputName[j - 3] == 't' &&
  //     inputName[j - 4] == '.') {
  char count[8] = ".counts";
  outName = realloc(outName, (j + 8) * sizeof(*outName));
  for (int i = 0; i < 8; i++) {
    outName[j + i] = count[i];
  }
  return outName;
  // }
  //free(outName);
  //return NULL;
}
