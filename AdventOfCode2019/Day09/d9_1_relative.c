#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 65536

size_t N_OP;

long long int stoi(char *str, size_t *pos) {
  long long int out = 0;
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

void read_prog(char *str, long long int *prog) {
  size_t len = strlen(str) - 1;
  size_t pos = 0;
  size_t i = 0;
  for (i = 0; pos < len; ++i) {
    prog[i] = stoi(str, &pos);
  }
  N_OP = i;
}

long long int with_mode(int mode, long long int param, int rel_base, int pos) {
  switch (mode) {
  case 0:
    return param;
  case 1:
    return pos;
  case 2:
    return rel_base + param;
  default:
    return param;
  }
}

bool run_prog(long long int *prog, long long int *var, int *pos) {
  static int rel_base = 0;
  while (prog[*pos] != 99) {
    int mode1 = 0;
    int mode2 = 0;
    int mode3 = 0;
    int op = prog[(*pos)++];
    printf("OP: %i, addr: %i\n", op, *pos);
    if (op > 10) {
      mode1 = (int)(floor(op / 100)) % 10 % 3;
      mode2 = (int)(floor(op / 1000)) % 10 % 3;
      mode3 = (int)(floor(op / 10000)) % 10 % 3;
      op = op % 10;
    }
    printf("  OP: %i, addr: %i, modes: %i, %i\n", op, *pos, mode1, mode2);
    long long int param1;
    long long int param2;
    long long int param3;
    switch (op) {
    case 1:                    /* Addition */
      param1 = prog[(*pos)]; /* Input var 1 */
      param1 = with_mode(mode1, param1, rel_base, (*pos)++);
      param2 = prog[(*pos)]; /* Input var 2 */
      param2 = with_mode(mode2, param2, rel_base, (*pos)++);
      param3 = prog[(*pos)]; /* Output var */
      param3 = with_mode(mode3, param3, rel_base, (*pos)++);
      prog[param3] = prog[param1] + prog[param2]; /* Execute op */
      printf("1. Sum: %lli + %lli = %lli, in addr %lli\n", param1, param2,
             prog[param3], param3);
      break;
    case 2:                    /* Multiplication */
      param1 = prog[(*pos)]; /* Input var 1 */
      param1 = with_mode(mode1, param1, rel_base, (*pos)++);
      param2 = prog[(*pos)]; /* Input var 2 */
      param2 = with_mode(mode2, param2, rel_base, (*pos)++);
      param3 = prog[(*pos)]; /* Output var */
      param3 = with_mode(mode3, param3, rel_base, (*pos)++);
      prog[param3] = prog[param1] * prog[param2]; /* Execute op */
      printf("2. Product: %lli * %lli = %lli, in addr %lli\n", param1, param2,
             prog[param3], param3);
      break;
    case 3:                    /* Save input */
      param1 = prog[(*pos)]; /* Output var */
      param1 = with_mode(mode1, param1, rel_base, (*pos)++);
      param2 = *var;
      prog[param1] = param2; /* Execute op */
      printf("3. Saved %lli to addr %lli\n", param2, param1); /* Execute op */
      break;
    case 4:                    /* Print input */
      param1 = prog[(*pos)]; /* Output var */
      param1 = with_mode(mode1, param1, rel_base, (*pos)++);
      printf(" 4. PrintOP: %lli\n", prog[param1]); /* Execute op */
      *var = param1;
      return false;
    case 5:                    /* Jump if true */
      param1 = prog[(*pos)]; /* Flag */
      param1 = with_mode(mode1, param1, rel_base, (*pos)++);
      param2 = prog[(*pos)]; /* Addr */
      param2 = with_mode(mode2, param2, rel_base, (*pos)++);
      printf("5. If %lli != '0' jump from addr %i to addr %lli\n", param1, *pos,
             param2);
      *pos = (prog[param1] != 0) ? prog[param2] : *pos; /* Execute op */
      break;
    case 6:                    /* Jump if false */
      param1 = prog[(*pos)]; /* Flag */
      param1 = with_mode(mode1, param1, rel_base, (*pos)++);
      param2 = prog[(*pos)]; /* Addr */
      param2 = with_mode(mode2, param2, rel_base, (*pos)++);
      printf("6. If %lli == '0' jump from addr %i to addr %lli\n", param1, *pos,
             param2);
      *pos = (prog[param1] == 0) ? prog[param2] : *pos; /* Execute op */
      break;
    case 7:                    /* Store if less than */
      param1 = prog[(*pos)]; /* Var 1 */
      param1 = with_mode(mode1, param1, rel_base, (*pos)++);
      param2 = prog[(*pos)]; /* Var 2 */
      param2 = with_mode(mode2, param2, rel_base, (*pos)++);
      param3 = prog[(*pos)]; /* *Pos */
      param3 = with_mode(mode3, param3, rel_base, (*pos)++);
      printf("7. If %lli < %lli save 1 to addr %lli\n", param1, param2, param3);
      prog[param3] = (prog[param1] < prog[param2]) ? 1 : 0; /* Execute op */
      printf("7saved: %lli to %lli\n", prog[param3], param3);
      break;
    case 8:                    /* Store if eq */
      param1 = prog[(*pos)]; /* Var 1 */
      param1 = with_mode(mode1, param1, rel_base, (*pos)++);
      param2 = prog[(*pos)]; /* Var 2 */
      param2 = with_mode(mode2, param2, rel_base, (*pos)++);
      param3 = prog[(*pos)]; /* *Pos */
      param3 = with_mode(mode3, param3, rel_base, (*pos)++);
      printf("8. If %lli == %lli save 1 to addr %lli\n", param1, param2,
             param3);
      prog[param3] = (prog[param1] == prog[param2]) ? 1 : 0; /* Execute op */
      printf("8saved: %lli to %lli\n", prog[param3], param3);
      break;
    case 9:                    /* Set relative base */
      param1 = prog[(*pos)]; /* Var 1 */
      param1 = with_mode(mode1, param1, rel_base, (*pos)++);
      printf("9. Rel_base was %i", rel_base);
      rel_base += prog[param1]; /* Adjust rel_base */
      printf(" and is now %i\n", rel_base);
      break;
    default:
        return true;
    }
  }
  return true;
}

void print_array(long long int in[N_OP]) {
  printf("\nProgram: ");
  for (size_t i = 0; i < N_OP; ++i) {
    printf("%lli,", in[i]);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[SIZE];
  long long int prog[SIZE] = {0};

  fgets(str, SIZE, f);

  read_prog(str, prog);

  long long int var = 1;
  int pos = 0;
  bool done = false;

  while (!done) {
    done = run_prog(prog, &var, &pos);
  }

  fclose(f);
  printf("\nResult: %lli\n", var);

  return 0;
}
