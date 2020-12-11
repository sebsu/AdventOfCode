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
#define DIFF_SIZE 4

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
  uint64_t result = 0;
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

  int diff[DIFF_SIZE] = {0};

  struct Adapter *current = outlet;
  printf("--------\n");
  while (current->next != NULL) {
    diff[current->next->jolt - current->jolt] += 1;
    current = current->next;
    printf("%i\n", current->jolt);
  }

  printf("--------\n");
  for (int i = 0; i < DIFF_SIZE; ++i) {
    printf(" %i\n", diff[i]);
  }
  result = diff[1] * diff[3];

  /* Free memory? Naaaah! */

  fclose(f);
  printf("\nResult: %li\n", result);

  return 0;
}
// 3 + 2 + 2
