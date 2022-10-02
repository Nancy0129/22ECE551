#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void showRes(char ** lines, size_t len) {
  for (size_t i = 0; i < len; i++) {
    printf("%s", lines[i]);
    free(lines[i]);
  }
  free(lines);
  return;
}

int main(int argc, char ** argv) {
  size_t len = 0;
  size_t data_len = 0;
  char * data = NULL;
  char ** lines = NULL;
  FILE * f;
  if (argc == 1) {
    while (getline(&data, &data_len, stdin) >= 0) {
      if (data[0] == '\n' || data[0] == '\0') {
        break;
      }
      lines = realloc(lines, (len + 1) * sizeof(*lines));
      lines[len] = data;
      data = NULL;
      len++;
    }
    free(data);
    sortData(lines, len);
    showRes(lines, len);
  }
  else {
    for (int i = 1; i < argc; i++) {
      f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Could not open file!\n");
        return EXIT_FAILURE;
      }
      while (getline(&data, &data_len, f) >= 0) {
        lines = realloc(lines, (len + 1) * sizeof(*lines));
        lines[len] = data;
        data = NULL;
        len++;
      }
      //free(data);
      //if (len < 1) {
      //perror("no input in file!\n");
      //free(lines);
      //fclose(f);
      //return EXIT_FAILURE;
      //}
      sortData(lines, len);
      showRes(lines, len);
      lines = NULL;
      if (fclose(f) != 0) {
        perror("Failed to close the input file!\n");

        return EXIT_FAILURE;
      }
      len = 0;
    }
    free(data);
  }
  return EXIT_SUCCESS;
}
