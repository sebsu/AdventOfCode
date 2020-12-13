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

/* String to int. */
uint64_t stoi(char *str, size_t *pos) {
  uint64_t out = 0;
  int sign = 1;
  if (str[*pos] == '-') {
    sign = -1;
    ++(*pos);
  } else if (str[*pos] == '+') {
    ++(*pos);
  }

  while ('0' <= str[*pos] && str[*pos] <= '9') {
    out = (out * 10) + (str[*pos] - '0');
    ++(*pos);
  }
  ++(*pos);
  return sign * out;
}

/* Greatest common divisor */
uint64_t gcd(uint64_t a, uint64_t b) { return (b == 0) ? a : gcd(b, a % b); }

/* Least common multiple */
uint64_t lcm(uint64_t a, uint64_t b) { return (a * b) / gcd(a, b); }

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  uint64_t result = 0;

  fgets(str, STR_SIZE, f); /* Trash. */
  fgets(str, STR_SIZE, f);
  size_t len = strlen(str);
  size_t p = 0;
  uint64_t ids[INPUT_SIZE] = {0};
  int n = 0;
  while (p < len) {
    if (str[p] == 'x') {
      ++n;
      p += 2;
    } else {
      int val = stoi(str, &p);
      ids[n] = val;
      ++n;
    }
  }

  uint64_t step = ids[0];
  uint64_t val = step;
  for (int i = 1; i < n; ++i) {
    /* If no restrictions, then ignore. */
    if (ids[i] == 0) {
      continue;
    }
    /* Find the value that fits the requirement. */
    while (((val + i) % ids[i]) != 0) {
      val += step;
    }
    /* Step size is based on how many minutes it takes to sync up the 'i' first
     * buses. After 'x*step' minutes, the 'i' first buses will depart at the
     * same time. This also means that 'val+step' will fulfill the same
     * requirements as 'val'. */
    step = lcm(step, ids[i]); /* lcm(lcm(a, b), c) == lcm(a, b, c) */
  }
  result = val;

  fclose(f);
  printf("\nResult: %li\n", result);

  return 0;
}
