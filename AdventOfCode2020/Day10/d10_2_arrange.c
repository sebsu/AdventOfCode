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
#define COMBI_SIZE 10

struct Adapter {
  int jolt;
  struct Adapter *next;
};

void add_adapter(int jolt, struct Adapter *current) {
  /* Insertion sort to a linked list. */
  struct Adapter *adapter = NULL;
  adapter = (struct Adapter *)malloc(sizeof(struct Adapter));
  adapter->jolt = jolt;
  while ((current->next != NULL) && (current->next->jolt < adapter->jolt)) {
    current = current->next;
  }
  adapter->next = current->next;
  current->next = adapter;
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  uint64_t result = 1;
  int max = 0;
  struct Adapter *outlet = NULL;
  outlet = (struct Adapter *)malloc(sizeof(struct Adapter));
  outlet->jolt = 0;
  outlet->next = NULL;
  while (fgets(str, STR_SIZE, f) != NULL) {
    int jolt = atoi(str);
    add_adapter(jolt, outlet);
    max = (jolt > max) ? jolt : max;
  }
  /* Add the device to the list. */
  add_adapter(max + 3, outlet);

  int combi[COMBI_SIZE] = {0};
  /* First three values calculated by hand. */
  combi[0] = 2; /* 1, 4, 5, 6, 9: 5 can be part or not -> 2 combinations. */
  combi[1] = 4; /* 1, 4, 5, 6, 7, 10: 5/6 -> 4 combinations */
  combi[2] = 7; /* ... */
  /* 10 is overkill, I actually only need the first 3 values. */
  for (int i = 3; i < COMBI_SIZE; ++i) {
    /* Fibonacci like sequence. */
    combi[i] = combi[i - 1] + combi[i - 2] + combi[i - 3];
  }

  struct Adapter *current = outlet;
  while (current->next != NULL) {
    int con = 0;
    while (current->next->jolt - current->jolt == 1) {
      ++con;
      current = current->next;
    }
    current = current->next;

    /* If a sequence of more than 1 concurrent diffs by 1 occur,
     * then some adapters can be ignored. */
    if (con > 1) {
      /* Since each sequence can be modified regardless of the other sequences,
       * then all variations of that sequence should be multiplied by all
       * variations of all other sequences. */
      result *= combi[con - 2];
    }
  }

  /* Free memory? Naaaah! */

  fclose(f);
  printf("\nResult: %li\n", result);

  return 0;
}
