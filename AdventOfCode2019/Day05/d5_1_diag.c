#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4096

int stoi(char *str, size_t *pos) {
  int out = 0;
  int sign = 1;
  if (str[*pos] == '-') {
    sign = -1;
    *pos += 1;
  }
  /* Might have added a , at the end of the input for this to work... */
  while (str[*pos] != ',') {
    out = (out * 10) + (str[*pos] - 48);
    *pos += 1;
  }
  *pos += 1;
  return sign * out;
}

void read_prog(char *str, int *prog) {
  size_t len = strlen(str) - 1;
  size_t pos = 0;
  for (int i = 0; pos < len; ++i) {
    prog[i] = stoi(str, &pos);
  }
}

void run_prog(int *prog) {
  int pos = 0;
  while (prog[pos] != 99) {
    int mode1 = 0;
    int mode2 = 0;
    int mode3 = 0;
    int op = prog[pos++];
    /* printf("OP: %i\n", op); */
    if (op > 10) {
      mode1 = (int)floor(op / 100) % 2;
      mode2 = (int)floor(op / 1000) % 2;
      /* mode3 = (int)floor(op / 10000) % 2; */
      op = op % 10;
    }
    int param1;
    int param2;
    int param3;
    switch (op) {
    case 1:                 /* Addition */
      param1 = prog[pos++]; /* Input var 1 */
      param2 = prog[pos++]; /* Input var 2 */
      param3 = prog[pos++]; /* Output var */
      param1 = (mode1) ? param1 : prog[param1];
      param2 = (mode2) ? param2 : prog[param2];
      prog[param3] = param1 + param2; /* Execute op */
      /* printf("sum: %i\n", prog[param3]); */
      break;
    case 2:                 /* Multiplication */
      param1 = prog[pos++]; /* Input var 1 */
      param2 = prog[pos++]; /* Input var 2 */
      param3 = prog[pos++]; /* Output var */
      param1 = (mode1) ? param1 : prog[param1];
      param2 = (mode2) ? param2 : prog[param2];
      prog[param3] = param1 * param2; /* Execute op */
      /* printf("product: %i\n", prog[param3]); */
      break;
    case 3:                 /* Save input */
      param1 = prog[pos++]; /* Output var */
      {
        char input[256] = {0};
        printf("Input integer: ");
        fgets(input, 256, stdin);
        param2 = atoi(input); /* Input var */
      }
      prog[param1] = param2; /* Execute op */
      /* printf("saved: %i\n", prog[param1]); */
      break;
    case 4:                                  /* Print input */
      param1 = prog[pos++];                  /* Output var */
      printf("PrintOP: %i\n", prog[param1]); /* Execute op */
      break;
    }
  }
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  char str[SIZE];
  int prog[SIZE] = {0};
  f = fopen(argv[1], "r");

  fgets(str, SIZE, f);

  read_prog(str, prog);
  run_prog(prog);

  fclose(f);
  printf("Result: %i\n", 0);

  return 0;
}
