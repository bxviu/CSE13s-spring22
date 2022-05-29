#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  // You're going to have to use argc to decide whether to open up a file, or to
  // read from stdin.
  // If you haven't seen them before, you will likely want to use the functions
  // `fgetc()` and `fputc()`.
  FILE* infile;
  if (argc > 2) {
    fprintf(stderr, "usage: ./yelling <file name>\n");
    exit(1);
  }
  else if (argc == 2) {
    infile = fopen(argv[1], "r");
  }
  int c = 0;
  while ((c = getchar()) != EOF) {
    if (c >= 'a' && c <= 'z'){
      putchar(c - ('a' - 'A'));
    }
    else {
      putchar(c);
    }
  }
  if (argc == 2) fclose(infile);
  return 0;
}
