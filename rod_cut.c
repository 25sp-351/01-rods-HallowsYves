#include "rod_cut.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  // Call parse_rod_length to get an integer we can use
  int rodLengthInteger = parse_rod_length(argc, argv);

  // Read pairs (length, value) from input
  int lengths[MAX_LINES];
  int values[MAX_LINES];
  int pieceCount = read_input(lengths, values);

  // if there isn't anything to read, notify user
  if (pieceCount == 0) {
    fprintf(stderr, "No piece definitions read from input!\n");
    return EXIT_FAILURE;
  }
  solve_rod_cutting(rodLengthInteger, lengths, values, pieceCount);
  print_solution(rodLengthInteger, lengths, values, pieceCount);
  
  return EXIT_SUCCESS;
}