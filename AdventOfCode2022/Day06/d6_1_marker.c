#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 4096
#define MARKER 4

/*
// Print bits backwards.
// abcdefghijklmnopqrstuvwxyzABCDEFGHIJLKMNOPQRSTUVWXYZ
void bprint(uint32_t n) {
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

uint32_t get_bit(char c) {
  uint32_t bit = 1;
  bit <<= (c - 'a' + 1);
  /* printf("%c ", c); */
  /* bprint(bit); */
  return bit;
}

int main(int argc, char **argv) {
  (void)argc;
  FILE *fd = fopen(argv[1], "r");
  char input[BUFFER];

  int p = MARKER - 1;
  fgets(input, BUFFER, fd);
  int len = strlen(input) - 1;
  while (p < len) {
    uint32_t bitmask = 0;
    for (int i = 0; i < MARKER; ++i) {
      bitmask |= get_bit(input[p - i]);
    }
    ++p;
    int unique = 0;
    while (bitmask > 0) {
      unique += bitmask & 1;
      bitmask >>= 1;
    }
    if (unique == MARKER) {
      break;
    }
  }
  printf("\nResult: %i\n", p);

  return 0;
}
