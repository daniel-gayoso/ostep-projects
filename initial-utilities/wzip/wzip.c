#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int freq;
  unsigned char c;
}rle_t;

void write_rle (rle_t rle_obj) {
  fwrite((int *)(&(rle_obj.freq)), sizeof(int), 1, stdout);
  fwrite((char *)(&(rle_obj.c)), sizeof(char), 1, stdout);
}

rle_t process (FILE *f, rle_t prev) {
  int curr;
  rle_t rle;
  
  while ((curr = fgetc(f)) != EOF) {
    if (prev.c != '\0' && curr != prev.c) {
      rle.c = prev.c;
      rle.freq = prev.freq;
      prev.freq = 0;

      write_rle(rle);
    }

    prev.freq++;
    prev.c = curr;
  }
  rle.c = prev.c;
  rle.freq = prev.freq;

  return rle;
}

int main (int argc, char *argv[]) {
  FILE *fp; // file stream pointer for file to read from and compress
  
  if (argc < 2) { // case where the executable is ran with no command line args
    fprintf(stdout, "wzip: file1 [file2 ...]\n");
    exit(EXIT_FAILURE);
  }

  rle_t prev;
  prev.c = '\0';
  prev.freq = 0;

  for (int f = 1; f < argc; f++) {
    fp = fopen(argv[f], "r");
    if (!fp) {
      fprintf(stdout, "wzip: cannot open file\n");
      exit(EXIT_FAILURE);
    }
    rle_t rle = process(fp, prev);
    prev.c = rle.c;
    prev.freq = rle.freq;

    fclose(fp);
  }

  write_rle(prev);

  return 0;
}
