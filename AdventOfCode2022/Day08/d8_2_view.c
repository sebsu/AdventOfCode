#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER 101

int visible(int forest[BUFFER][BUFFER], int y, int x, int max_y, int max_x) {
  int h = forest[y][x];
  int score = 1;
  int len = 0;
  for (int i = y - 1; i >= 0; --i) { // Up
    ++len;
    if (forest[i][x] >= h) {
      break;
    }
  }
  score *= len;
  len = 0;
  for (int i = y + 1; i < max_y; ++i) { // Down
    ++len;
    if (forest[i][x] >= h) {
      break;
    }
  }
  score *= len;
  len = 0;
  for (int i = x - 1; i >= 0; --i) { // Left
    ++len;
    if (forest[y][i] >= h) {
      break;
    }
  }
  score *= len;
  len = 0;
  for (int i = x + 1; i < max_x; ++i) { // Right
    ++len;
    if (forest[y][i] >= h) {
      break;
    }
  }
  score *= len;
  return score;
}

int count_trees(int forest[BUFFER][BUFFER], int max_y, int max_x) {
  int best_view = 0;
  for (int y = 1; y < max_y; ++y) {
    for (int x = 1; x < max_x; ++x) {
      int view = visible(forest, y, x, max_y + 1, max_x + 1);
      best_view = (view > best_view) ? view : best_view;
    }
  }
  return best_view;
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

  int best_view = count_trees(forest, y - 1, x - 1);

  printf("\nResult: %i\n", best_view);

  return 0;
}
