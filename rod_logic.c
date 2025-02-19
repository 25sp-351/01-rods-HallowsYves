#include "rod_cut.h"
#include <stdio.h>

int bestValueForLength[MAX_ROD_LENGTH + 1];
int chosenPiece[MAX_ROD_LENGTH + 1];

void solve_rod_cutting(int rodLength, int lengths[], int values[], int pieceCount) {
    for (int i = 0; i <= rodLength; i++) {
        bestValueForLength[i] = 0;
        chosenPiece[i] = -1;
    }

    for (int i = 0; i < pieceCount; i++) {
        int pieceLength = lengths[i];
        int pieceValue = values[i];

        for (int currentLength = pieceLength; currentLength <= rodLength; currentLength++) {
            int candidateValue = bestValueForLength[currentLength - pieceLength] + pieceValue;

            if (candidateValue > bestValueForLength[currentLength]) {
                bestValueForLength[currentLength] = candidateValue;
                chosenPiece[currentLength] = i;
            }
        }
    }
}

void print_solution(int rodLength, int lengths[], int values[], int pieceCount) {
    int usage[MAX_LINES] = {0};
    int currentLength = rodLength;

    while (currentLength > 0 && chosenPiece[currentLength] != -1) {
        int chosenIndex = chosenPiece[currentLength];
        usage[chosenIndex]++;
        currentLength -= lengths[chosenIndex];
    }

    int remainder = currentLength;

    for (int i = 0; i < pieceCount; i++) {
        if (usage[i] > 0) {
            printf("%d @ %d = %d\n", usage[i], lengths[i], usage[i] * values[i]);
        }
    }

    printf("Remainder: %d\n", remainder);
    printf("Value: %d\n", bestValueForLength[rodLength]);
}
