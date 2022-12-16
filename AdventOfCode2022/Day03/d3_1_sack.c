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

int main(int argc, char **argv) {
  (void)argc;
  FILE *fd = fopen(argv[1], "r");
  char input[BUFFER];

  int sum_prio = 0;
  while (fgets(input, BUFFER, fd) != NULL) {
    size_t len = (strlen(input)) >> 1; // -1 not needed, shifted away.
    uint64_t bitmask_1 = 0;
    uint64_t bitmask_2 = 0;

    for (unsigned i = 0; i < len; ++i) {
      bitmask_1 |= get_bit(input[i]);
      bitmask_2 |= get_bit(input[i + len]);
    }
    uint64_t error_bit = bitmask_1 & bitmask_2;
    int prio = 0;
    while (error_bit > 0) {
      ++prio;
      error_bit >>= 1;
    }
    --prio;
    /* printf("prio: %i\n", prio); */
    sum_prio += prio;
  }

  printf("Result: %i\n", sum_prio);

  return 0;
}
