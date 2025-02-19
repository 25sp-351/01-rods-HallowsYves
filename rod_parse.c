#include "rod_cut.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// INPUT PARSING LOGIC

int parse_rod_length(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Missing Rod Length!\n");
    exit(EXIT_FAILURE);
  }

  char *endPointer = 0;
  errno = 0;
  long rodLength = strtol(argv[1], &endPointer, 10);

  if (errno != 0 || *endPointer != '\0') {
    perror("strlol");
    exit(EXIT_FAILURE);
  }

  if (rodLength > INT_MAX || rodLength < INT_MIN) {
    fprintf(stderr, "rod length out of integer range. \n");
    return EXIT_FAILURE;
  }

  int rodLengthInteger = (int)rodLength;
  if (rodLengthInteger <= 0) {
    fprintf(stderr, "Error: rod length must be a positive integer.\n");
    return (EXIT_FAILURE);
  }
  return rodLengthInteger;
}