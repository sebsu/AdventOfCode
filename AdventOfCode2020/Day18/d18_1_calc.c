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
int64_t stoi(char *str, size_t *pos) {
  int64_t out = 0;
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
  // ++(*pos);
  return sign * out;
}

int64_t eval(char *input, size_t len, size_t *p) {
  int64_t out = 0;
  if (input[*p] == '(') {
    ++(*p);
    out = eval(input, len, p);
  } else {
    out = stoi(input, p);
  }
  ++(*p);
  printf("\np: '%c'\n", input[*p]);
  if (*p >= len) {
    return out;
  }

  if (input[*p] == '+') {
    ++(*p);
    ++(*p);

  } else if (input[*p] == '*') {
  }

  // eval(input, p);
  return out;
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  int64_t result = 0;
  if (fgets(str, STR_SIZE, f) != NULL) {
    size_t p = 0;
    size_t len = strlen(str);
    result += eval(str, len, &p);
  }

  fclose(f);
  printf("\nResult: %li\n", result);

  return 0;
}
