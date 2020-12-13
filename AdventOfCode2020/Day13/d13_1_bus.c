#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 8192
#define INPUT_SIZE 1024

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

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  uint64_t result = 0;

  fgets(str, STR_SIZE, f);
  int time = atoi(str);
  fgets(str, STR_SIZE, f);
  size_t len = strlen(str);
  uint32_t min = -1;
  size_t p = 0;
  int id = 0;
  while (p < len) {
    if (str[p] == 'x') {
      p += 2;
    } else {
      int val = stoi(str, &p);
      uint32_t eta = val - (time % val);
      if (eta < min) {
        min = eta;
        id = val;
      }
    }
  }

  result = id * min;

  fclose(f);
  printf("\nResult: %li\n", result);

  return 0;
}
