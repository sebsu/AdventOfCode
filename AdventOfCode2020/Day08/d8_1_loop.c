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

enum OP { NOP, ACC, JMP };

typedef struct {
  enum OP op;
  int param;
} Instruction;

/* String to int. */
int stoi(char *str, size_t *pos) {
  int out = 0;
  int sign = 1;
  if (str[*pos] == '-') {
    sign = -1;
    ++(*pos);
  } else if (str[*pos] == '+') {
    ++(*pos);
  }

  while ('0' <= str[*pos] && str[*pos] <= '9') {
    out = (out * 10) + (str[*pos] - 48);
    ++(*pos);
  }
  ++(*pos);
  return sign * out;
}

Instruction str_to_instr(char *str) {
  Instruction res;
  /* Extract operator. */
  if (strncmp(str, "nop", 3) == 0) {
    res.op = NOP;
  } else if (strncmp(str, "acc", 3) == 0) {
    res.op = ACC;
  } else if (strncmp(str, "jmp", 3) == 0) {
    res.op = JMP;
  } else {
    res.op = NOP;
  }

  /* Extract parameter. */
  size_t p = 4;
  res.param = stoi(str, &p);
  return res;
}

int64_t exec(Instruction *prog) {
  int p = 0;
  enum OP op;
  int param;
  int64_t acc = 0;
  int visited[INPUT_SIZE] = {0};
  while (visited[p] == 0) {
    visited[p] += 1;
    op = prog[p].op;
    param = prog[p].param;
    // printf("exec %i: %i, %i\n", p, op, param);
    switch (op) {
    case NOP:
      ++p;
      break;
    case ACC:
      acc += param;
      ++p;
      break;
    case JMP:
      p += param;
      break;
    }
  }

  return acc;
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  int64_t result = 0;
  Instruction program[INPUT_SIZE];
  int n_lines = 0;
  while (fgets(str, STR_SIZE, f) != NULL) {
    program[n_lines] = str_to_instr(str);
    // printf("read %i, %i\n", program[n_lines].op, program[n_lines].param);
    ++n_lines;
  }

  result = exec(program);

  fclose(f);
  printf("\nResult: %li\n", result);

  return 0;
}
