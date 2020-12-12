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

struct Position {
  int x;
  int y;
};

void update_pos(char *action, struct Position *pos, struct Position *wp) {
  char dir = action[0];
  int val = atoi(&action[1]);
  if (dir == 'N') {
    wp->y += val;
  } else if (dir == 'E') {
    wp->x += val;
  } else if (dir == 'S') {
    wp->y -= val;
  } else if (dir == 'W') {
    wp->x -= val;
  } else if (dir == 'L') {
    int n_turns = val / 90;
    for (int i = 0; i < n_turns; ++i) {
      int x = wp->x;
      wp->x = -wp->y;
      wp->y = x;
    }
  } else if (dir == 'R') {
    int n_turns = val / 90;
    for (int i = 0; i < n_turns; ++i) {
      int x = wp->x;
      wp->x = wp->y;
      wp->y = -x;
    }
  } else if (dir == 'F') {
    pos->x += val * wp->x;
    pos->y += val * wp->y;
  }
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  uint64_t result = 0;
  struct Position pos = {0, 0};
  struct Position waypoint = {10, 1};
  while (fgets(str, STR_SIZE, f) != NULL) {
    update_pos(str, &pos, &waypoint);
  }

  result = abs(pos.x) + abs(pos.y);

  fclose(f);
  printf("\nResult: %li\n", result);

  return 0;
}
