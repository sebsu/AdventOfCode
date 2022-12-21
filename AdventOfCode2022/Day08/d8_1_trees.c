#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER 101

int visible(int forest[BUFFER][BUFFER], int y, int x, int max_y, int max_x) {
  int h = forest[y][x];
  int higher = 0;
  for (int i = y - 1; i >= 0; --i) { // Up
    higher += forest[i][x] >= h;
  }
  if (higher == 0) {
    return 1;
  }
  higher = 0;
  for (int i = y + 1; i < max_y; ++i) { // Down
    higher += forest[i][x] >= h;
  }
  if (higher == 0) {
    return 1;
  }
  higher = 0;
  for (int i = x - 1; i >= 0; --i) { // Left
    higher += forest[y][i] >= h;
  }
  if (higher == 0) {
    return 1;
  }
  higher = 0;
  for (int i = x + 1; i < max_x; ++i) { // Down
    higher += forest[y][i] >= h;
  }
  if (higher == 0) {
    return 1;
  }
  return 0;
}

int count_trees(int forest[BUFFER][BUFFER], int max_y, int max_x) {
  int sum = 0;
  for (int y = 1; y < max_y; ++y) {
    for (int x = 1; x < max_x; ++x) {
      sum += visible(forest, y, x, max_y + 1, max_x + 1);
    }
  }
  return sum;
}

int main(int argc, char **argv) {
  (void)argc;
  FILE *fd = fopen(argv[1], "r");
  char input[BUFFER];

  int forest[BUFFER][BUFFER];
  int y = 0;
  int x = 0;
  while (fgets(input, BUFFER, fd) != NULL) {
    x = 0;
    while (input[x] != '\n') {
      forest[y][x] = input[x] - '0';
      ++x;
    }
    ++y;
  }

  int num_trees = x + x + (y - 2) + (y - 2);
  num_trees += count_trees(forest, y - 1, x - 1);

  printf("\nResult: %i\n", num_trees);

  return 0;
}
