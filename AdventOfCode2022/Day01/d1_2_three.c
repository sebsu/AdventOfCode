#include <stdio.h>
#include <stdlib.h>

#define BUFFER 64
#define N_ELF 3

void replace_top(int new, int top[N_ELF]) {
  int min_i = 0;
  for (int i = 1; i < N_ELF; ++i) {
    if (top[min_i] > top[i]) {
      min_i = i;
    }
  }
  if (new > top[min_i]) {
    /* printf("%i %i %i\n", new, min_i, top[min_i]); */
    top[min_i] = new;
  }
}

int main(int argc, char **argv) {
  (void)argc;
  FILE *fd = fopen(argv[1], "r");
  char input[BUFFER];

  int elf_load = 0;
  int elf_top[N_ELF];
  for (int i = 0; i < N_ELF; ++i) {
    elf_top[i] = 0;
  }

  while (fgets(input, BUFFER, fd) != NULL) {
    if (input[0] == '\n') {
      replace_top(elf_load, elf_top);
      elf_load = 0;
    } else {
      elf_load += atoi(input);
    }
    /* printf("%s", input); */
  }
  replace_top(elf_load, elf_top);

  int elf_sum_load = 0;
  for (int i = 0; i < N_ELF; ++i) {
    printf("Top: %i %i\n", i, elf_top[i]);
    elf_sum_load += elf_top[i];
  }
  printf("Result: %i\n", elf_sum_load);

  return 0;
}
