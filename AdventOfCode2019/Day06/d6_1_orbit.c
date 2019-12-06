#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4096
static int orbits[1000000][SIZE];

int get_hash(char *str, int pos) {
  int out = 0;
  for (int i = pos; i < pos + 3; ++i) {
    out = (out * 100) + str[i];
  }
  return out;
}

int sum(int hash, int depth) {
  int out = depth;
  int n_sat = orbits[hash][0];
  for (int i = 1; i < n_sat + 1; ++i) {
    out += sum(orbits[hash][i], depth + 1);
  }
  return out;
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  char str[SIZE];
  f = fopen(argv[1], "r");

  for (int i = 0; i < 1000000; ++i) {
    orbits[i][0] = 0;
  }

  while (fgets(str, SIZE, f) != NULL) {
    int steady = get_hash(str, 0);
    int satellite = get_hash(str, 4);
    int n_sat = orbits[steady][0] + 1;
    orbits[steady][n_sat] = satellite;
    orbits[steady][0] = n_sat;
  }

  int res = sum(get_hash("COM", 0), 0);

  fclose(f);
  printf("Result: %i\n", res);

  return 0;
}
