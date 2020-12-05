#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 8192
#define INPUT_SIZE 350

int find_row(char *seat) {
  int min = 0;
  int max = 127;
  for (int i = 0; i < 7; ++i) {
    int mid = min + (max - min) / 2;
    if (seat[i] == 'F') {
      max = mid;
    } else {
      min = mid;
    }
  }
  return max;
}
int find_col(char *seat) {
  int min = 0;
  int max = 7;
  for (int i = 7; i < 10; ++i) {
    int mid = min + (max - min) / 2;
    if (seat[i] == 'L') {
      max = mid;
    } else {
      min = mid;
    }
  }
  return max;
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  int64_t result = 0;
  while (fgets(str, STR_SIZE, f) != NULL) {
    int row = find_row(str);
    int col = find_col(str);
    int id = row * 8 + col;
    result = (result > id) ? result : id;
  }

  fclose(f);
  printf("Result: %li\n", result);

  return 0;
}
