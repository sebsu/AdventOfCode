#include <stdio.h>
#include <stdlib.h>

#define BUFFER 64

int main(int argc, char **argv) {
  (void)argc;
  FILE *fd = fopen(argv[1], "r");
  char input[BUFFER];
  int elf_max_load = 0;
  int elf_load = 0;
  while (fgets(input, BUFFER, fd) != NULL) {
    if (input[0] == '\n') {
      if (elf_load > elf_max_load) {
        elf_max_load = elf_load;
      }
      elf_load = 0;
    }
    elf_load += atoi(input);
  }

  printf("Result: %i", elf_max_load);

  return 0;
}
