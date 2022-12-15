#include <stdio.h>
#include <stdlib.h>

#define BUFFER 64

int choise(char c) { return c - 'A' + 1; }

int rigged(char champ, char cheat) {
  int res = 0;
  int normilize = champ - 'A';
  char pick;
  if (cheat == 'X') {
    pick = (normilize + 2) % 3 + 'A';
    res = 0;
  } else if (cheat == 'Y') {
    pick = champ;
    res = 3;
  } else {
    pick = (normilize + 1) % 3 + 'A';
    res = 6;
  }
  return res + choise(pick);
}

int main(int argc, char **argv) {
  (void)argc;
  FILE *fd = fopen(argv[1], "r");
  char input[BUFFER];

  int sum_score = 0;
  while (fgets(input, BUFFER, fd) != NULL) {
    sum_score += rigged(input[0], input[2]);
  }

  printf("Result: %i\n", sum_score);

  return 0;
}
