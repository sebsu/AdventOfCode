#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 64

/*
// Print bits backwards.
// abcdefghijklmnopqrstuvwxyzABCDEFGHIJLKMNOPQRSTUVWXYZ
void bprint(uint64_t n) {
  while (n) {
    if (n & 1) {
      printf("1");
    } else {
      printf("0");
    }
    n >>= 1;
  }
  printf("\n");
}
*/

uint64_t get_bit(char c) {
  uint64_t bit = 1;
  if (c >= 'a') {
    bit <<= (c - 'a' + 1);
  } else {
    bit <<= (c - 'A' + 27);
  }
  /* printf("%c ", c); */
  /* bprint(bit); */
  return bit;
}

uint64_t get_mask(FILE *fd) {
  uint64_t bitmask = -1;
  char input[BUFFER];
  if (fgets(input, BUFFER, fd) != NULL) {
    size_t len = (strlen(input) - 1);
    bitmask = 0;
    for (unsigned i = 0; i < len; ++i) {
      bitmask |= get_bit(input[i]);
    }
  }
  return bitmask;
}

int main(int argc, char **argv) {
  (void)argc;
  FILE *fd = fopen(argv[1], "r");

  int sum_prio = 0;
  uint64_t bitmask_1 = get_mask(fd);
  while (bitmask_1 != UINT64_MAX) {
    uint64_t bitmask_2 = get_mask(fd);
    uint64_t bitmask_3 = get_mask(fd);

    uint64_t common_bit = (bitmask_1 & bitmask_2) & bitmask_3;

    int prio = 0;
    while (common_bit > 0) {
      ++prio;
      common_bit >>= 1;
    }
    --prio;
    /* printf("prio: %i\n", prio); */
    sum_prio += prio;

    bitmask_1 = get_mask(fd);
  }

  printf("Result: %i\n", sum_prio);

  return 0;
}
