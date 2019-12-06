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
    /* printf("OP: %i, addr: %i\n", op, pos); */
    if (op > 10) {
      mode1 = (int)floor(op / 100) % 2;
      mode2 = (int)floor(op / 1000) % 2;
      /* mode3 = (int)floor(op / 10000) % 2; */ /* Not used */
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
      /* param3 = (mode3) ? param3 : prog[param3]; */
      prog[param3] = param1 + param2; /* Execute op */
      /* printf("1. Sum: %i + %i = %i, in addr %i\n", param1, param2,
       * prog[param3], param3); */
      break;
    case 2:                 /* Multiplication */
      param1 = prog[pos++]; /* Input var 1 */
      param2 = prog[pos++]; /* Input var 2 */
      param3 = prog[pos++]; /* Output var */
      param1 = (mode1) ? param1 : prog[param1];
      param2 = (mode2) ? param2 : prog[param2];
      /* param3 = (mode3) ? param3 : prog[param3]; */
      prog[param3] = param1 * param2; /* Execute op */
      /* printf("2. Product: %i * %i = %i, in addr %i\n", param1, param2,
       * prog[param3], param3);*/
      break;
    case 3:                 /* Save input */
      param1 = prog[pos++]; /* Output var */
      {
        char input[256] = {0};
        printf("Input integer: ");
        fgets(input, 256, stdin);
        param2 = atoi(input); /* Input var */
      }
      /* printf("3. Saved %i to add %i\n", param2, param1); */
      prog[param1] = param2; /* Execute op */
      break;
    case 4:                 /* Print input */
      param1 = prog[pos++]; /* Output var */
      param1 = (mode1) ? param1 : prog[param1];
      printf(" 4. PrintOP: %i\n", param1); /* Execute op */
      break;
    case 5:                 /* Jump if true */
      param1 = prog[pos++]; /* Flag */
      param2 = prog[pos++]; /* Addr */
      param1 = (mode1) ? param1 : prog[param1];
      param2 = (mode2) ? param2 : prog[param2];
      /* printf("5. If flag %i == '1' jump from addr %i", param1, pos); */
      pos = (param1 != 0) ? param2 : pos; /* Execute op */
      /* printf(" to addr %i\n", param2); */
      break;
    case 6:                 /* Jump if false */
      param1 = prog[pos++]; /* Flag */
      param2 = prog[pos++]; /* Addr */
      param1 = (mode1) ? param1 : prog[param1];
      param2 = (mode2) ? param2 : prog[param2];
      /* printf("6. If flag %i == '0' jump from %i", param1, pos); */
      pos = (param1 == 0) ? param2 : pos; /* Execute op */
      /* printf(" to %i\n", param2); */
      break;
    case 7:                 /* Store if less than */
      param1 = prog[pos++]; /* Var 1 */
      param2 = prog[pos++]; /* Var 2 */
      param3 = prog[pos++]; /* Pos */
      param1 = (mode1) ? param1 : prog[param1];
      param2 = (mode2) ? param2 : prog[param2];
      /* param3 = (mode3) ? param3 : prog[param3]; */
      /* printf("7. If %i < %i save 1 to addr %i\n", param1, param2, param3); */
      prog[param3] = (param1 < param2) ? 1 : 0; /* Execute op */
      /* printf("7saved: %i to %i\n", prog[param3], param3); */
      break;
    case 8:                 /* Store if eq */
      param1 = prog[pos++]; /* Var 1 */
      param2 = prog[pos++]; /* Var 2 */
      param3 = prog[pos++]; /* Pos */
      param1 = (mode1) ? param1 : prog[param1];
      param2 = (mode2) ? param2 : prog[param2];
      /* param3 = (mode3) ? param3 : prog[param3]; */
      /* printf("8. If %i == %i save 1 to addr %i\n", param1, param2, param3);
       */
      prog[param3] = (param1 == param2) ? 1 : 0; /* Execute op */
      /* printf("8saved: %i to %i\n", prog[param3], param3); */
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
