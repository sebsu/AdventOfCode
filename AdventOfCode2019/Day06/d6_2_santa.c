#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HASH 46656 /* 36^3 */
#define SIZE 2048
#define MAX_DEPTH 262144
static int orbits[MAX_HASH][SIZE];
static int path_you[MAX_DEPTH];
static int path_san[MAX_DEPTH];

int get_hash(char *str, int pos) {
  int out = 0;
  int power = 1;
  int base = 36;
  for (int i = pos; i < pos + 3; ++i) {
      char c = (str[i]>'9') ? (str[i]-'A'+10) : (str[i]-'0');
      out += c * power;
      power = power * base;
  }
  return out;
}

int HASH_YOU;
int HASH_SAN;
int HASH_COM;

void set() {
    HASH_YOU = get_hash("YOU", 0);
    HASH_SAN = get_hash("SAN", 0);
    HASH_COM = get_hash("COM", 0);
}

int find(int goal) {
    int pos = 0;
    int sat = goal;
    while (sat != HASH_COM) {
        bool found = false;
        for (int i=0; i<MAX_HASH; ++i) {
            int n_sat = orbits[i][0];
            for (int j=1; j<n_sat+1; ++j) {
                if (orbits[i][j] == sat) {
                    if (goal == HASH_YOU) {
                        path_you[pos++] = sat;
                    } else if (goal == HASH_SAN) {
                        path_san[pos++] = sat;
                    }
                    found = true;
                    sat = i;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
    }
    
    return pos;
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  char str[SIZE];
  f = fopen(argv[1], "r");

  for (int i = 0; i < MAX_HASH; ++i) {
    orbits[i][0] = 0;
  }

  while (fgets(str, SIZE, f) != NULL) {
    int steady = get_hash(str, 0);
    int satellite = get_hash(str, 4);
    int n_sat = orbits[steady][0] + 1;
    orbits[steady][n_sat] = satellite;
    orbits[steady][0] = n_sat;
    /* printf("%i)%i, %s", steady, satellite,  str); */
  }

  set();
  int depth_you = find(HASH_YOU);
  int depth_san = find(HASH_SAN);

  /* for (int i = 0; i<depth_you; ++i){ */
  /*     printf("%i, ", path_you[i]); */
  /* } */
  /* printf("\n"); */
  /* for (int i = 0; i<depth_san; ++i){ */
  /*     printf("%i, ", path_san[i]); */
  /* } */

  int i=depth_you;
  int j=depth_san;
  while (path_you[i]==path_san[j] && i>=0 && j>=0){
      --i;
      --j;
  }

  fclose(f);
  printf("Result: %i\n", i+j);
  /* printf("Result: %i\n", get_hash("ZZZ", 0)); */

  return 0;
}
