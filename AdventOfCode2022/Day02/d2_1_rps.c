#include <stdio.h>
#include <stdlib.h>

#define BUFFER 64

int winner(char champ, char chal) {
  int res = 0;
  char normilize = 'X' - 'A';
  chal -= normilize;
  if (((chal - champ + 3) % 3) == 0) {
    res = 3;
  } else if (((chal - champ + 3) % 3) == 1) {
    res = 6;
  }
  return res;
}

int choise(char c) { return c - 'X' + 1; }

int main(int argc, char **argv) {
  (void)argc;
  FILE *fd = fopen(argv[1], "r");
  char input[BUFFER];

  int sum_score = 0;
  while (fgets(input, BUFFER, fd) != NULL) {
    sum_score += winner(input[0], input[2]) + choise(input[2]);
  }

  printf("Result: %i\n", sum_score);

  return 0;
}
