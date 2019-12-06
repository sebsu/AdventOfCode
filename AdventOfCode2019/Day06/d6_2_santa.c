#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 2048
static int orbits[1000000][SIZE];

int get_hash(char *str, int pos) {
  int out = 0;
  for (int i = pos; i < pos + 3; ++i) {
    out = (out * 100) + str[i];
  }
  return out;
}

int *find(int hash, int goal, int *path, int depth) {
  if (hash == goal) {
    return path;
  }
  path[depth] = hash;
  int n_sat = orbits[hash][0];
  for (int i = 1; i < n_sat + 1; ++i) {
    return find(orbits[hash][i], goal, path, depth + 1);
  }
  return path; /*Shouldn't reach this */
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

  static int path[100];
  int *a = find(get_hash("COM", 0), get_hash("YOU", 0), path, 0);
  int *b = find(get_hash("COM", 0), get_hash("SAN", 0), path, 0);

  fclose(f);
  printf("Result: %i\n", 0);

  return 0;
}
