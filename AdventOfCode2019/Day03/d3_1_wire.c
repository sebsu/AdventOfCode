#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point {
  int x;
  int y;
};

struct line {
  struct point s; // start
  struct point e; // end
};

int stoi(char *str, size_t len, size_t *pos, char *dir) {
  int out = 0;
  if (str[*pos]=='R'){
      *dir = 0;
  }else if (str[*pos]=='D'){
      *dir = 1;
  }else if (str[*pos]=='L'){
      *dir = 2;
  }else if (str[*pos]=='U'){
      *dir = 3;
  }
  *pos += 1;
  for (int i = *pos; (str[i] != ',') && (i!=len); ++i) {
    out = (out * 10) + (str[i] - 48);
    *pos = i + 1;
  }
  *pos += 1;
  return out;
}

void read_wire(char *str, int *grid) {
  size_t len = strlen(str) - 1;
  size_t pos = 0;
  int dir = 0;
  int dist = 0;
  while (pos < len) {
      dist = stoi(str, len, &pos, &dir);
    ++i;
    switch (dir) {
    case 'R':
      p.x = wire[i - 1].x + dist;
      p.y = wire[i - 1].y;
      break;
    case 'D':
      p.x = wire[i - 1].x;
      p.y = wire[i - 1].y + dist;
      break;
    case 'L':
      p.x = wire[i - 1].x - dist;
      p.y = wire[i - 1].y;
      break;
    case 'U':
      p.x = wire[i - 1].x;
      p.y = wire[i - 1].y - dist;
      break;
    }
    wire[i] = p;
  }
  return i;
}

int min(int a, int b) { return (a < b) ? a : b; }

bool is_hori(struct line l) { return (l.s.y == l.e.y); }

bool is_crossing(struct line l1, struct line l2) {
  /* Assume that parallell lines don't cross */
  if ((is_hori(l1) && is_hori(l2)) || (!is_hori(l1) && !is_hori(l2))) {
    return false;
  }

  /* Make sure l1 is the horisontal one. */
  if (!is_hori(l1)) {
    return is_crossing(l2, l1);
  }

  if ((((l1.s.x < l2.s.x) && (l2.s.x < l1.e.x)) ||
       ((l1.e.x < l2.s.x) && (l2.s.x < l1.s.x))) &&
      (((l2.s.y < l1.s.y) && (l1.s.y < l2.e.y)) ||
       ((l2.e.y < l1.s.y) && (l1.s.y < l2.s.y)))) {
    /* printf("HIT:\n l1 (%i,%i)-(%i,%i)\n", l1.s.x, l1.s.y, l1.e.x, l1.e.y); */
    /* printf(" l2 (%i,%i)-(%i,%i)\n", l2.s.x, l2.s.y, l2.e.x, l2.e.y); */
    return true;
  }

  return false;
}

struct point find_intersect(struct line l1, struct line l2) {
  struct point p = {0, 0};
  p.x = (min(l1.s.y, l1.e.y) < min(l2.s.y, l2.e.y)) ? l1.s.x : l2.s.x;
  p.y = (min(l1.s.x, l1.e.x) < min(l2.s.x, l2.e.x)) ? l1.s.y : l2.s.y;
  return p;
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  const int size = 512;
  char str[size];
  int grid[512] = {0};
  f = fopen(argv[1], "r");

  fgets(str, size, f);
  int N1 = read_wire(str, wire1);
  fgets(str, size, f);
  int N2 = read_wire(str, wire2);

  unsigned int nearest_dist = 4294967295;

  for (int i = 0; i < N1; ++i) {
    struct line l1 = {wire1[i], wire1[i + 1]};
    /* printf("\nl1 (%i,%i)-(%i,%i)\n", l1.s.x, l1.s.y, l1.e.x, l1.e.y); */
    for (int j = 0; j < N2; ++j) {
      struct line l2 = {wire2[j], wire2[j + 1]};
      /* printf("l2 (%i,%i)-(%i,%i)\n", l2.s.x, l2.s.y, l2.e.x, l2.e.y); */
      if (is_crossing(l1, l2)) {
        struct point p = find_intersect(l1, l2);
        unsigned int dist = abs(p.x) + abs(p.y);
        /* printf(" p (%i,%i)\n", p.x, p.y); */
        if (dist < nearest_dist) {
          /* printf("near:\n  l1 (%i,%i)-(%i,%i)\n", l1.s.x, l1.s.y, l1.e.x, l1.e.y); */
          /* printf("  l2 (%i,%i)-(%i,%i)\n\n", l2.s.x, l2.s.y, l2.e.x, l2.e.y); */
          nearest_dist = dist;
        }
      }
    }
  }

  fclose(f);
  printf("Result: %i\n", nearest_dist);

  return 0;
}
