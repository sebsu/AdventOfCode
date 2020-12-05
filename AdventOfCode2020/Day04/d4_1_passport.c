#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 8192
#define INPUT_SIZE 350

int find_substr(char *substr, char *str) {
  int n = strlen(str);
  int m = strlen(substr);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if ((substr[j] == str[i]) && (substr[j + 1] == str[i + 1]) &&
          (substr[j + 2] == str[i + 2])) {
        return 1;
      }
    }
    while (str[i] != ' ' && str[i] != '\n') {
      ++i;
    }
  }
  return 0;
}

int validate_passport(char *passport) {
  char *required[7] = {"byr", "ecl", "eyr", "hcl", "hgt", "iyr", "pid"};
  for (int i = 0; i < 7; ++i) {
    if (find_substr(required[i], passport) == 0) {
      return 0;
    }
  }
  return 1;
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  int64_t result = 0;
  while (fgets(str, STR_SIZE, f) != NULL) {
    char passport[STR_SIZE];
    strncat(passport, str, strlen(str));
    while (fgets(str, STR_SIZE, f) != NULL) {
      if (str[0] == '\n') {
        break;
      }
      strncat(passport, str, strlen(str));
    }
    result += validate_passport(passport);
    *passport = NULL;
  }

  fclose(f);
  printf("Result: %li\n", result);

  return 0;
}
