#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stoi(char *str, size_t *pos) {
  int out = 0;
  for (int i = *pos; str[i] != ','; ++i) {
    out = (out * 10) + (str[i] - 48);
    *pos = i + 1;
  }
  *pos += 1;
  return out;
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
    int op = prog[pos];
    int in1 = prog[pos + 1];
    int in2 = prog[pos + 2];
    int out = prog[pos + 3];
    if (op == 1) {
      prog[out] = prog[in1] + prog[in2];
    } else if (op == 2) {
      prog[out] = prog[in1] * prog[in2];
    }
    pos += 4;
  }
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  const int size = 512;
  char str[size];
  int prog[512] = {0};
  f = fopen(argv[1], "r");

  fgets(str, size, f);

  int noun = 0;
  int verb = 0;
  int output = 19690720;
  for (; noun <= 99 && prog[0] != output; ++noun) {
    for (verb = 0; verb <= 99 && prog[0] != output; ++verb) {
      read_prog(str, prog);
      prog[1] = noun;
      prog[2] = verb;
      run_prog(prog);
    }
  }
  noun -= 1;
  verb -= 1;

  fclose(f);
  printf("%i %i %i %i\n", prog[0], noun, verb, (100 * noun + verb));

  return 0;
}
