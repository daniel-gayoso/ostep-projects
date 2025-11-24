#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

#define MY_LINE_LIMIT 16384

int main (int argc, char *argv[]) {
  FILE *fp; // pointer to the file stream
  char *line; // for holding the result of fgets
  int line_max;
  
  if (argc < 2) { // no args, return success
    return 0;
  }

  if (LINE_MAX >= MY_LINE_LIMIT) {
    line_max = MY_LINE_LIMIT;
  } else {
    long limit = sysconf(_SC_LINE_MAX);
    if (limit < 0 || limit > MY_LINE_LIMIT) {
      line_max = MY_LINE_LIMIT;
    } else {
      line_max = (int)limit;
    }
  }

  line = malloc(line_max + 1);
  if (line == NULL) {
    printf("malloc failed, exiting\n");
    return -1;
  }
  
  if (argc >= 2) { // we have args, need to go through each file
    for (int i = 1; i < argc; i++) {
      fp = fopen(argv[i], "r");
      if (fp == NULL) { // make sure file opened
	printf("wcat: cannot open file\n");
	return 1;
      }
      while (fgets(line, line_max + 1, fp)) {
	printf("%s", line);
      }
    }
  }
  free(line);
  return 0;
}
