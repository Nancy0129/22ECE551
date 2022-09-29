#include "pandemic.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

country_t parseLine(char * line) {
  //Check and print error for empty input
  if (line == NULL || *line == '\0' || *line == '\n') {
    fprintf(stderr, "Invalid Input in 1: Empty input!\n");
    exit(EXIT_FAILURE);
  }
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;
  // To save the length of name and population later
  int nameL = 0;
  int popuL = 0;
  char max_uin64[] = "18446744073709551615";
  // Get country name before ','
  while (line[nameL] != ',') {
    if (line[nameL] == '\n' || line[nameL] == '\0') {
      fprintf(stderr, "Invalid Input in 1: expect comma but did not find!\n");
      exit(EXIT_FAILURE);
    }
    // Make sure the country name is not too long (>63, leaving a position for '\0')
    if (nameL > 62) {
      fprintf(stderr, "Invalid Input in 1: line is too long!\n");
      exit(EXIT_FAILURE);
    }
    ans.name[nameL] = line[nameL];
    nameL++;
  }
  // Put the '\0' at the end of name to indicate the end
  ans.name[nameL] = '\0';
  // Use this to allocate the beginning of population number (after ',')
  nameL++;
  // Get the population value
  while (line[nameL + popuL] != '\n' && line[nameL + popuL] != '\0') {
    // Make sure the input is number
    if (line[nameL + popuL] < 48 || line[nameL + popuL] > 57) {
      fprintf(stderr,
              "Invalid Input in 1: %c is invalid number character!\n",
              line[nameL + popuL]);
      exit(EXIT_FAILURE);
    }
    // Make sure the value is not larger than the maximum of unsigned int64
    if (popuL > 19) {
      fprintf(stderr, "Invalid Input in 1: too large  number!\n");
      exit(EXIT_FAILURE);
    }
    if (popuL == 19) {
      for (int i = 0; i < 20; i++) {
        if (line[nameL + i] > max_uin64[i]) {
          fprintf(stderr, "Invalid Input in 1: too large  number!\n");
          exit(EXIT_FAILURE);
        }
      }
    }
    popuL++;
  }
  // Make sure there is a value for population
  if (popuL < 1) {
    fprintf(stderr, "Invalid Input in 1: no number input!\n");
    exit(EXIT_FAILURE);
  }
  // The input for strtoull to store invalid characters
  char * endptr;
  ans.population = strtoull(line + nameL, &endptr, 10);
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
