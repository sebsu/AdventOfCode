#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 8192
#define INPUT_SIZE 250

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  int num[INPUT_SIZE];
  int n_input = 0;
  while (fgets(str, STR_SIZE, f) != NULL) {
    num[n_input++] = atoi(str);
  }

  int i_num;
  int j_num;
  int k_num;
  int result = -1;
  for (int i = 0; i < n_input; ++i) {
    i_num = num[i];
    for (int j = i + 1; j < n_input; ++j) {
      j_num = num[j];
      for (int k = j + 1; k < n_input; ++k) {
        k_num = num[k];
        if (i_num + j_num + k_num == 2020) {
          result = i_num * j_num * k_num;
          break;
        }
      }
      if (result > 0) {
        break;
      }
    }
    if (result > 0) {
      break;
    }
  }

  fclose(f);
  printf("Result: %i\n", result);

  return 0;
}
