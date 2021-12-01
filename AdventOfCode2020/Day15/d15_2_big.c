#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 8192
#define INPUT_SIZE 30000000

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
  int turn[INPUT_SIZE] = {0};
  uint64_t result = 0;
  size_t i = 0;
  if (fgets(str, STR_SIZE, f) != NULL) {
    size_t p = 0;
    size_t len = strlen(str);
    while (p < len) {
      turn[i++] = stoi(str, &p);
      //      printf("Turn: %i, %i\n", i - 1, turn[i - 1]);
    }
  }

  while (i < INPUT_SIZE) {
    int last = turn[i - 1];
    //    printf("Last: %i\n", last);
    int j = i - 2;
    while (j >= 0) {
      if (turn[j--] == last) {
        //  printf("j: %i\n", j);
        ++j;
        break;
      }
    }
    if (j < 0) {
      turn[i] = 0;
    } else {
      turn[i] = i - j - 1;
    }
    //    printf("Turn: %i, %i, %i\n", i, turn[i], j);
    ++i;
  }

  result = turn[INPUT_SIZE - 1];

  fclose(f);
  printf("\nResult: %li\n", result);

  return 0;
}
