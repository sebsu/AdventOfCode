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
#define PRE_SIZE 25

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

/* Validates and return 0 if valid, and "val" if not valid. */
uint64_t validate(uint64_t val, uint64_t *preamble) {
  for (int i = 0; i < PRE_SIZE - 1; ++i) {
    for (int j = i + 1; j < PRE_SIZE; ++j) {
      if (preamble[i] + preamble[j] == val) {
        return 0;
      }
    }
  }
  return val;
}

uint64_t find_sum(int start, int end, uint64_t *all) {
  uint64_t res = 0;
  for (int i = start; i <= end; ++i) {
    res += all[i];
  }
  return res;
}

uint64_t sum_min_max(int start, int end, uint64_t *all) {
  uint64_t min = -1;
  uint64_t max = 0;
  for (int i = start; i <= end; ++i) {
    min = (min < all[i]) ? min : all[i];
    max = (max > all[i]) ? max : all[i];
  }
  return min + max;
}

uint64_t find_weakness(uint64_t val, int size, uint64_t *all) {
  for (int i = 0; i < size - 1; ++i) {
    for (int j = i + 1; j < size; ++j) {
      uint64_t sum = find_sum(i, j, all);
      if (sum == val) {
        return sum_min_max(i, j, all);
      }
    }
  }
  return 0;
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  uint64_t result = 0;
  uint64_t preamble[PRE_SIZE] = {0};
  uint64_t all_numbers[INPUT_SIZE] = {0};
  uint64_t invalid = 0;
  int i = 0;
  int j = 0;

  while ((i < PRE_SIZE) && (fgets(str, STR_SIZE, f) != NULL)) {
    size_t p = 0;
    preamble[i] = stoi(str, &p);
    all_numbers[j] = preamble[i];
    ++i;
    ++j;
  }
  i = 0;
  while (fgets(str, STR_SIZE, f) != NULL) {
    size_t p = 0;
    uint64_t val = stoi(str, &p);
    if (validate(val, preamble) != 0) {
      invalid = val;
      break;
    }
    preamble[i] = val;
    all_numbers[j] = val;
    i = (i + 1) % PRE_SIZE;
    ++j;
  }

  /* I am lucky that the correct set is listed before the invalid number.
   * If that hadn't been the case, this would not have worked.
   * This can be solved by continue to read and add to all_numbers after the
   * invalid value has been found. */
  /*
  while (fgets(str, STR_SIZE, f) != NULL) {
    size_t p = 0;
    uint64_t val = stoi(str, &p);
    all_numbers[j] = val;
    ++j;
  }
  */

  result = find_weakness(invalid, j, all_numbers);

  fclose(f);
  printf("\nResult: %li\n", result);

  return 0;
}
