#ifndef ROD_CUT_H
#define ROD_CUT_H


#define MAX_ROD_LENGTH 10000
#define MAX_LINES 100

int parse_rod_length(int argc, char*argv[]);
int read_input(int lengths[], int values[]);
void solve_rod_cutting(int rodLength, int lengths[], int values[], int peiceCount);
void print_solution(int rodLength, int lengths[], int values[], int peiceCount);

#endif