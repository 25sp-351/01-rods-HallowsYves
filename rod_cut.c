#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_ROD_LENGTH 10000
#define MAX_LINES 100

int main(int argc, char *argv[]) {
  // Check if the input is valid, if it isn't throw an error
  if (argc != 2) {
    fprintf(stderr, "Missing Rod Length!\n");
    return 1;
  }

  // Convert input string into integer that we can actually use
  char *endPointer = 0;
  errno = 0;
  long rodLength = strtol(argv[1], &endPointer, 10);

  if (errno != 0 || *endPointer != '\0') {
    perror("strtol");
    exit(EXIT_FAILURE);
  }

  if (rodLength > INT_MAX || rodLength < INT_MIN) {
    fprintf(stderr, "rodLength out of int range\n");
    return EXIT_FAILURE;
  }

  int rodLengthInteger = (int)rodLength;

  if (rodLengthInteger <= 0) {
    fprintf(stderr, "Error: rod length must be a positive integer.\n");
    return 1;
  }

  // Read pairs (length, value) from input
  int lengths[MAX_LINES];
  int values[MAX_LINES];
  int pieceCount = 0;

  while (scanf("%d, %d", &lengths[pieceCount], &values[pieceCount]) == 2) {
    pieceCount++;
    if (pieceCount >= MAX_LINES) {
      fprintf(stderr, "Warning: reached maximum number of input lines (%d).\n",
              MAX_LINES);
      break;
    }
  }

  // if there isn't anything to read, notify user
  if (pieceCount == 0) {
    fprintf(stderr, "No piece definitions read from input!\n");
    return 1;
  }

  // Create two arrays,
  // One to hold the maximum value / profit achievable for every possible rod
  // length, from 0 to the length given from the user Second to record which
  // piece was chosen to achieve that maximum value for each rod length
  static int bestValueForLength[MAX_ROD_LENGTH + 1];
  static int chosenPiece[MAX_ROD_LENGTH + 1];

  // Loop through the length of the rod, if no choice has been made yet,
  // initialize to -1
  for (int index = 0; index <= rodLengthInteger; index++) {
    chosenPiece[index] = -1;
  }

  for (int index = 0; index < pieceCount; index++) {
    int pieceLength = lengths[index];
    int pieceValue = values[index];

    // Only update from pieceLen up to rodLength
    for (int currentLength = pieceLength; currentLength <= rodLengthInteger;
         currentLength++) {
      int candidateValue =
          bestValueForLength[currentLength - pieceLength] + pieceValue;

      if (candidateValue > bestValueForLength[currentLength]) {
        bestValueForLength[currentLength] = candidateValue;
        chosenPiece[currentLength] = index; // record which piece we used
      }
    }
  }

  // Reconstruct, so we can see which pieces we actually cut
  int currentLength = rodLengthInteger;
  int remainder = rodLengthInteger;

  // Usage count for each piece
  int usage[MAX_LINES];
  for (int index = 0; index < pieceCount; index++) {
    usage[index] = 0;
  }

  // Walk backwards from rodLength, using the chosenPiece[] array
  while (currentLength > 0 && chosenPiece[currentLength] != -1) {
    int chosenIndex = chosenPiece[currentLength];
    usage[chosenIndex]++;
    currentLength -= lengths[chosenIndex];
  }

  remainder = currentLength; // whatever is left

  // Print the cutting list
  for (int index = 0; index < pieceCount; index++) {
    if (usage[index] > 0) {
      printf("%d @ %d = %d\n", usage[index], lengths[index],
             usage[index] * values[index]);
    }
  }

  // Print remainder and total value
  printf("Remainder: %d\n", remainder);
  printf("Value: %d\n", bestValueForLength[rodLengthInteger]);
  return 0;
}