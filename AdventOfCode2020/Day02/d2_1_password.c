#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 8192
#define INPUT_SIZE 250
#define ASCII_OFFSET 48

/* String to int. */
int stoi(char *str, size_t *pos) {
  int out = 0;
  int sign = 1;
  if (str[*pos] == '-') {
    sign = -1;
    ++(*pos);
  }
  while (str[*pos] != '-' && str[*pos] != ' ') {
    out = (out * 10) + (str[*pos] - ASCII_OFFSET);
    ++(*pos);
  }
  ++(*pos);
  return sign * out;
}

int is_valid(char *pw) {
  size_t pos = 0;
  int min = stoi(pw, &pos);
  int max = stoi(pw, &pos);
  char c = pw[pos];
  int occ = 0;
  while (pw[++pos] != '\n') {
    occ += (int)(pw[pos] == c);
  }
  return (int)((min <= occ) && (occ <= max));
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  int result = 0;
  while (fgets(str, STR_SIZE, f) != NULL) {
    result += is_valid(str);
  }

  fclose(f);
  printf("Result: %i\n", result);

  return 0;
}
