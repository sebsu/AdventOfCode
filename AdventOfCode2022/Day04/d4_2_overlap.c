#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 64

int get_int(char *str, int *p) {
  int i = 0;
  while (('0' <= str[*p]) && (str[*p] <= '9')) {
    i = i * 10 + str[*p] - '0';
    *p += 1;
  }
  *p += 1;
  return i;
}

int main(int argc, char **argv) {
  (void)argc;
  FILE *fd = fopen(argv[1], "r");
  char input[BUFFER];

  int sum_overlap = 0;
  while (fgets(input, BUFFER, fd) != NULL) {
    int p = 0;
    int min1 = get_int(input, &p);
    int max1 = get_int(input, &p);
    int min2 = get_int(input, &p);
    int max2 = get_int(input, &p);

    if (((min1 <= min2) && (max1 >= min2)) ||
        ((min2 <= min1) && (max2 >= min1))) {
      ++sum_overlap;
    }
  }

  printf("Result: %i\n", sum_overlap);

  return 0;
}
