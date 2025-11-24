#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#define MYLIMIT 16384

int main (int argc, char *argv[]) {
  FILE *fp; // pointer to file stream
  char *line; // pointer for storing the current line
  int line_max; // for checking line limits
  char *file_name;
  char *term;
  char *input;

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
  else if (argc == 2) { // user wants to search some text in stdin
    term = argv[1]; 
    printf("\n"); // new line for user to enter their input
    fgets(input, line_max, stdin); // read from stdin until user sends newline (enter)
    
  }
  else if (argc >= 3) {
    line = malloc(line_max + 1): // allocate worst case line size of bytes
    if (line == NULL) { // check if for valid ptr
      printf("malloc failed, exiting\n");
      return -1;
    }
    
  }
  
  while (fgets(line, line_max + 1, fp)) {
    char *found = strstr(line, argv[1]);
    if (found) { // strstr returned some offset occurence
      printf("%s", line);
    }
  }
  
  

  free(line);
  return 0;
  
}
