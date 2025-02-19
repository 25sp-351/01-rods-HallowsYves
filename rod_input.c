#include "rod_cut.h"
#include <stdio.h>

// INPUT READING LOGIC

int read_input(int rodLengths[], int values[]) {
  int pieceCount = 0;
  while (scanf("%d, %d", &rodLengths[pieceCount], &values[pieceCount]) == 2) {
    pieceCount++;
    if (pieceCount >= MAX_LINES) {
      fprintf(stderr, "Warning: reached maximum number of input lines (%d).\n",
              MAX_LINES);
      break;
    }
  }
  return pieceCount;
}
