#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

#define MYLIMIT 16384

int main (int argc, char *argv[]) {
  FILE *fp; // pointer to file stream
  char *line; // pointer for storing the current line
  int line_max; // for checking line limits
  char *search_term; // pointer to the pattern to search some file or stdin for
  char *result; // pointer for holding the result of strstr

  if (LINE_MAX >= MYLIMIT) { // bounds check for max length of a line
    line_max = MYLIMIT;
  }
  else { 
    long limit = sysconf(_SC_LINE_MAX);
    if (limit < 0 || limit > MYLIMIT) {
      line_max = MYLIMIT;
    }
    else {
      line_max = (int)limit;
    }
  }
  
  if (argc == 1) { // no args passed
    printf("wgrep: searchterm [file ...]\n");
    return 1;
  }

  if (argc == 2) { // user wants to search some text in stdin
    search_term = argv[1];
    line = malloc(line_max + 1);
    if (line == NULL) {
      printf("malloc failed, exiting\n");
      return -1;
    }
    while (fgets(line, line_max, stdin)) { // read inputs until user hits Ctrl + D (EOF)
      result = strstr(line, search_term);
      if (result) {
	printf("%s", line);
      }
    }
    return 0; 
  }

  if (argc >= 3) {
    search_term = argv[1];
    line = malloc(line_max + 1); // allocate worst case line size of bytes
    if (line == NULL) { // check if for valid ptr
      printf("malloc failed, exiting\n");
      return -1;
    }  
    for (int i = 2; i < argc; i++) {
      fp = fopen(argv[i], "r");
      if (fp == NULL) {
	printf("wgrep: cannot open file\n");
	return 1;
      }
      while (fgets(line, line_max, fp)) {
	result = strstr(line, search_term);
	if (result) {
	  printf("%s", line);
	}
      }
    }
    return 0;
  }
  
  free(line);
  return 0;
  
}
