#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 8192
#define INPUT_SIZE 1024

void collect_answers(char *str, uint32_t *ans) {
  for (int i = 0; str[i] != '\n'; ++i) {
    *ans |= (1 << (str[i] - 'a'));
  }
}

int count_bits(uint32_t bit_map) {
  int res = 0;
  for (int i = 0; i < 32; ++i) {
    res += (bit_map >> i) & 1;
  }
  return res;
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  int64_t result = 0;
  uint32_t answers = 0;
  while (fgets(str, STR_SIZE, f) != NULL) {
    collect_answers(str, &answers);
    if (str[0] == '\n') {
      printf("Group result: %i\n", count_bits(answers));
      result += count_bits(answers);
      answers = 0;
    }
  }
  printf("Group result: %i\n", count_bits(answers));
  result += count_bits(answers);

  fclose(f);
  printf("Result: %li\n", result);

  return 0;
}
