#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stoi(char *str, size_t *pos, int *dir) {
  int out = 0;
  if (str[*pos]=='R'){
      *dir = 0;
  }else if (str[*pos]=='D'){
      *dir = 1;
  }else if (str[*pos]=='L'){
      *dir = 2;
  }else if (str[*pos]=='U'){
      *dir = 3;
  }
  *pos += 1;
  for (int i = *pos; str[i] != ','; ++i) {
    out = (out * 10) + (str[i] - 48);
    *pos = i + 1;
  }
  *pos += 1;
  return out;
}

void read_wire(char *str, int *grid) {
  size_t len = strlen(str) - 1;
  size_t pos = 0;
  int dir = 0;
  int dist = 0;
  while (pos < len) {
    dist = stoi(str, &pos, &dir);
  /* TODO: Save info to a data thing */
  }
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  const int size = 512;
  char str[size];
  int grid[512] = {0};
  f = fopen(argv[1], "r");

  fgets(str, size, f);

  /* int noun = 0; */
  /* int verb = 0; */
  /* int output = 19690720; */
  /* for (; noun <= 99 && grid[0] != output; ++noun) { */
  /*   for (verb = 0; verb <= 99 && grid[0] != output; ++verb) { */
  /*     read_grid(str, grid); */
  /*     grid[1] = noun; */
  /*     grid[2] = verb; */
  /*     run_grid(grid); */
  /*   } */
  /* } */
  /* noun -= 1; */
  /* verb -= 1; */

  fclose(f);
  printf("%i %i %i %i\n", grid[0], noun, verb, (100 * noun + verb));

  return 0;
}
