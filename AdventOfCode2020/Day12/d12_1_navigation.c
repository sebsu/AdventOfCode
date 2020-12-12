#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 8192
#define INPUT_SIZE 128

enum DIR { N = 0, E = 1, S = 2, W = 3 };

struct Position {
  int x;
  int y;
  enum DIR dir;
};

void update_pos(char *action, struct Position *pos) {
  char dir = action[0];
  int val = atoi(&action[1]);
  if (dir == 'N') {
    pos->y += val;
  } else if (dir == 'E') {
    pos->x += val;
  } else if (dir == 'S') {
    pos->y -= val;
  } else if (dir == 'W') {
    pos->x -= val;
  } else if (dir == 'L') {
    int n_turns = val / 90;
    pos->dir = (pos->dir - n_turns) % 4;
  } else if (dir == 'R') {
    int n_turns = val / 90;
    pos->dir = (pos->dir + n_turns) % 4;
  } else if (dir == 'F') {
    switch (pos->dir) {
    case N:
      pos->y += val;
      break;
    case E:
      pos->x += val;
      break;
    case S:
      pos->y -= val;
      break;
    case W:
      pos->x -= val;
      break;
    }
  }
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  uint64_t result = 0;
  struct Position pos = {0, 0, E};
  while (fgets(str, STR_SIZE, f) != NULL) {
    update_pos(str, &pos);
  }

  result = abs(pos.x) + abs(pos.y);

  fclose(f);
  printf("\nResult: %li\n", result);

  return 0;
}
