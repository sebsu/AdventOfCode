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

int64_t exec(Instruction *prog, int n_lines) {
  int p = 0;
  enum OP op;
  int param;
  int64_t acc = 0;
  int visited[INPUT_SIZE] = {0};
  while (visited[p] == 0 && p < n_lines) {
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

  /* Report error. */
  if (p < n_lines) {
    acc = -1;
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
  int nops[INPUT_SIZE];
  int jmps[INPUT_SIZE];
  int n_nop = 0;
  int n_jmp = 0;
  while (fgets(str, STR_SIZE, f) != NULL) {
    program[n_lines] = str_to_instr(str);
    // printf("read %i, %i\n", program[n_lines].op, program[n_lines].param);
    if (program[n_lines].op == NOP) {
      nops[n_nop++] = n_lines;
    } else if (program[n_lines].op == JMP) {
      jmps[n_jmp++] = n_lines;
    }
    ++n_lines;
  }

  // printf("NOP\n");
  for (int i = 0; i < n_nop; ++i) {
    // printf("-----\n");
    program[nops[i]].op = JMP;
    result = exec(program, n_lines);
    // printf("END %li\n", result);
    if (result != -1) {
      break;
    }
    program[nops[i]].op = NOP;
  }

  if (result == -1) {
    // printf("JMP\n");
    for (int i = 0; i < n_jmp; ++i) {
      // printf("-----\n");
      program[jmps[i]].op = NOP;
      result = exec(program, n_lines);
      // printf("END %li\n", result);
      if (result != -1) {
        break;
      }
      program[jmps[i]].op = JMP;
    }
  }

  fclose(f);
  printf("\nResult: %li\n", result);

  return 0;
}
