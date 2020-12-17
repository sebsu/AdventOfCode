#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 8192
#define INPUT_SIZE 65536
#define MASK_SIZE 36

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

void apply_mask(size_t index, int64_t value, int64_t *mem, char *mask) {
  int64_t val = 0;
  for (int i = 0; i < MASK_SIZE; ++i) {
    if (mask[i] == '0') {
      val = (val << 1);
    } else if (mask[i] == '1') {
      val = (val << 1) | 1;
    } else if (mask[i] == 'X') {
      val = (val << 1) | ((value >> (MASK_SIZE - (i + 1))) % 2);
    }
  }
  mem[index] = val;
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  uint64_t result = 0;
  char mask[MASK_SIZE];
  int64_t mem[INPUT_SIZE] = {0};
  while (fgets(str, STR_SIZE, f) != NULL) {
    if (str[1] == 'a') { /* mask */
      strncpy(mask, &str[7], MASK_SIZE);
    } else { /* mem */
      size_t p = 4;
      size_t index = stoi(str, &p);
      p += 3;
      int64_t val = stoi(str, &p);
      apply_mask(index, val, mem, mask);
    }
  }

  for (int i = 0; i < INPUT_SIZE; ++i) {
    result += mem[i];
  }

  fclose(f);
  printf("\nResult: %li\n", result);

  return 0;
}
