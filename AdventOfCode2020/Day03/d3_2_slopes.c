#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 8192
#define INPUT_SIZE 350

struct Map {
  int64_t trees[INPUT_SIZE];
  int n_rows;
  int width;
};

int trees_hit(struct Map *map, int dx, int dy) {
  int n_trees = 0;
  for (int i = 0; i * dy < map->n_rows; ++i) {
    int n_shift = map->width - ((i * dx) % map->width) - 1;
    n_trees += (map->trees[i * dy] & (1 << n_shift)) > 0;
  }
  return n_trees;
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  struct Map map;
  int64_t result = 1;
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
    map.trees[map.n_rows] = row;
    ++map.n_rows;
    map.width = pos;
  }
  printf("Rows: %i\n", map.n_rows);
  printf("Width: %i\n", map.width);

  for (int x = 1; x < 8; x += 2) {
    result *= trees_hit(&map, x, 1);
  }
  result *= trees_hit(&map, 1, 2);

  fclose(f);
  printf("Result: %li\n", result);

  return 0;
}
