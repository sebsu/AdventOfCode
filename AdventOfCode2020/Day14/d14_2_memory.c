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

void save_to_mem(size_t addr, int64_t value, size_t index, int64_t *changes,
                 size_t n_changes, int32_t *mem) {
  if (index >= n_changes) {
    return;
  }
  save_to_mem(addr, value, index + 1, changes, n_changes, mem);
  addr = addr | (1 << changes[index]);
  printf("floats: %li\n", addr);
  mem[addr] = value;
  save_to_mem(addr, value, index + 1, changes, n_changes, mem);
}

uint64_t apply_mask(size_t index, int64_t value, int32_t *mem, char *mask) {
  printf("\nvalue: %li\n%s\n", value, mask);
  size_t addr = 0;
  int64_t changes[MASK_SIZE] = {0};
  size_t n_changes = 0;
  for (int i = 0; i < MASK_SIZE; ++i) {
    if (mask[i] == '0') {
      printf("0");
      addr = (addr << 1) | ((index >> (MASK_SIZE - (i + 1))) & 1);
    } else if (mask[i] == '1') {
      printf("1");
      addr = (addr << 1) | 1;
    } else if (mask[i] == 'X') {
      printf("%li", ((value >> (MASK_SIZE - (i + 1))) % 2));
      addr = (addr << 1);
      changes[n_changes++] = MASK_SIZE - (i + 1);
    }
  }
  /* printf("\nafter shift: %li\n", addr); */
  /* mem[addr] = value; */
  /* save_to_mem(addr, value, 0, changes, n_changes, mem); */
  return (uint64_t)powl((long double)2, (long double)n_changes) * value;
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  uint64_t result = 0;
  char mask[MASK_SIZE];
  int32_t mem[INPUT_SIZE] = {0};
  while (fgets(str, STR_SIZE, f) != NULL) {
    if (str[1] == 'a') { /* mask */
      strncpy(mask, &str[7], MASK_SIZE);
    } else { /* mem */
      size_t p = 4;
      size_t index = stoi(str, &p);
      p += 3;
      int64_t val = stoi(str, &p);
      result += apply_mask(index, val, mem, mask);
      // printf("\n");
    }
  }

  /* for (size_t i = 0; i < INPUT_SIZE; ++i) { */
  /*   result += mem[i]; */
  /* } */

  fclose(f);
  printf("\nResult: %li\n", result);

  return 0;
}
