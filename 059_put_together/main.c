#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * f;
  f = fopen(filename, "r");
  if (f == NULL) {
    perror("File does not exist!\n");
    return NULL;
  }
  counts_t * counts = createCounts();
  size_t data_len = 0;
  char * data = NULL;
  char * value = NULL;
  while (getline(&data, &data_len, f) >= 0) {
    value = lookupValue(kvPairs, data);
    addCount(counts, value);
    free(data);
    //value = NULL;
    data = NULL;
    data_len = 0;
  }
  free(data);
  fclose(f);
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    perror("Too few inputs (<2)!\n");
    exit(EXIT_FAILURE);
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv_array = readKVs(argv[1]);
  if (kv_array == NULL) {
    exit(EXIT_FAILURE);
  }
  counts_t * counts = NULL;
  char * outFile = NULL;
  FILE * f;
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    counts = countFile(argv[i], kv_array);
    //   (call this result c)
    if (counts == NULL) {
      continue;
    }
    //compute the output file name from argv[i] (call this outName)
    outFile = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    f = fopen(outFile, "w");
    //print the counts from c into the FILE f
    printCounts(counts, f);
    //close f

    //free the memory for outName and c
    free(outFile);
    outFile = NULL;
    freeCounts(counts);
    counts = NULL;
  }
  //free the memory for kv
  freeKVs(kv_array);

  return EXIT_SUCCESS;
}
