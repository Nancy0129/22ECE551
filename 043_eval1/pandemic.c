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
  int pos = 0;
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
  while (line[nameL + pos] != '\n' && line[nameL + pos] != '\0') {
    // Make sure the input is number
    if (line[nameL + pos] < 48 || line[nameL + pos] > 57) {
      // Ignore the space in front of the number
      if (line[nameL + pos] == ' ' || line[nameL + pos] == '\t') {
        if (popuL > 0) {
          fprintf(stderr,
                  "Invalid Input in 1: %c is invalid number character!\n",
                  line[nameL + pos]);
          exit(EXIT_FAILURE);
        }
        pos++;
        continue;
      }
      else {
        fprintf(stderr,
                "Invalid Input in 1: %c is invalid number character!\n",
                line[nameL + pos]);
        exit(EXIT_FAILURE);
      }
    }
    // WHen the input is number
    else {
      // Make sure the value is not larger than the maximum of unsigned int64
      if (popuL > 19) {
        fprintf(stderr, "Invalid Input in 1: too large  number!\n");
        exit(EXIT_FAILURE);
      }
      if (popuL == 19) {
        // for digit number (not include space)
        int j = 0;
        // for pos in line (include space)
        int k = 0;
        while (j < 20) {
          //skip whitespace
          if (line[nameL + k] >= 48 && line[nameL + k] <= 57) {
            if (line[nameL + k] > max_uin64[j]) {
              fprintf(stderr, "Invalid Input in 1: too large  number!\n");
              exit(EXIT_FAILURE);
            }
            j++;
          }
          k++;
        }
      }
      pos++;
      popuL++;
    }
  }
  // Make sure there is a value for population
  if (popuL < 1) {
    fprintf(stderr, "Invalid Input in 1: no number input!\n");
    exit(EXIT_FAILURE);
  }
  // The input for strtoull to store invalid characters('/n' or '/0' or ' ')
  char * endptr;
  ans.population = strtoull(line + nameL, &endptr, 10);
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  double sum7 = 0;
  if (data == NULL || avg == NULL) {
    fprintf(stderr, "Invalid Input in 2: No data!\n");
    exit(EXIT_FAILURE);
  }
  // When no running average calculations to do, exit with success
  if (n_days < 7) {
    exit(EXIT_SUCCESS);
  }
  // Calculate the sum of the first 7 days
  for (int i = 0; i < 7; i++) {
    sum7 += data[i];
  }
  avg[0] = sum7 / 7;
  // Each time substract the earliest day and add a new day
  for (unsigned i = 1; i < n_days - 6; i++) {
    sum7 -= data[i - 1];
    sum7 += data[i + 6];
    avg[i] = sum7 / 7;
  }
  return;
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  // No calculations to do, exit with success
  if (n_days < 1) {
    exit(EXIT_SUCCESS);
  }
  // n_days>0 but no data should be error
  else if (data == NULL || cum == NULL) {
    fprintf(stderr, "Invalid Input in 3: No data!\n");
    exit(EXIT_FAILURE);
  }
  // Population cannot be 0
  if (pop <= 0) {
    fprintf(stderr, "Invalid Input in 3: Population cannot be 0!\n");
    exit(EXIT_FAILURE);
  }
  double cumsum = 0;
  // Change the type into double and calculate the value  per 100000 people
  double pop_per = (double)pop / 100000;
  for (unsigned i = 0; i < n_days; i++) {
    // Divide first to reduce the possibility of overflow
    cumsum += data[i] / pop_per;
    cum[i] = cumsum;
  }

  return;
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  // No calculate to do, exit with success
  if (n_countries < 1 || n_days < 1) {
    exit(EXIT_SUCCESS);
  }
  // n_days>0 and n_countries>0 but no data should be error
  else if (countries == NULL || data == NULL) {
    fprintf(stderr, "Invalid Input in 4: No data!\n");
    exit(EXIT_FAILURE);
  }
  int resInd = 0;
  unsigned maxCase = 0;
  for (unsigned i = 0; i < n_countries; i++) {
    if (data[i] == NULL) {
      fprintf(stderr, "Invalid Input in 4: No data!\n");
      exit(EXIT_FAILURE);
    }
    for (unsigned j = 0; j < n_days; j++) {
      if (data[i][j] > maxCase) {
        maxCase = data[i][j];
        resInd = i;
      }
    }
  }
  printf("%s has the most daily cases with %u\n", countries[resInd].name, maxCase);
}
