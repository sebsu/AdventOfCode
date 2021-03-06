#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 8192
#define INPUT_SIZE 350

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  int64_t tree_map[INPUT_SIZE] = {0}; // Bit map.
  int result = 0;
  int n_rows = 0;
  int width = 0;
  while (fgets(str, STR_SIZE, f) != NULL) {
    size_t pos = 0;
    int64_t row = 0;
    while (str[pos] != '\n') {
      row <<= 1;
      if (str[pos] == '#') {
        row |= 1;
      }
      ++pos;
    }
    tree_map[n_rows] = row;
    ++n_rows;
    width = pos;
  }
  printf("Rows: %i\n", n_rows);
  printf("Width: %i\n", width);

  int step_right = 3;
  for (int i = 0; i < n_rows; ++i) {
    int n_shift = width - ((step_right * i) % width) - 1;
    result += (tree_map[i] & (1 << n_shift)) > 0 ? 1 : 0;
  }

  fclose(f);
  printf("Result: %i\n", result);

  return 0;
}
