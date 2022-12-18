#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 64
#define N_STACKS 10

struct Crate {
  struct Crate *prev;
  struct Crate *next;
  char id;
};
struct Stack {
  struct Crate *top;
  int height;
};

void print_stack(struct Stack s) {
  struct Crate *tmp = s.top;
  for (int i = 0; i < s.height; ++i) {
    printf("%c", tmp->id);
    tmp = tmp->prev;
  }
  printf("\n");
}

int get_int(char *str, int *p) {
  int i = 0;
  while (('0' <= str[*p]) && (str[*p] <= '9')) {
    i = i * 10 + str[*p] - '0';
    *p += 1;
  }
  *p += 1; // To easily get next int in a CSV.
  return i;
}

int main(int argc, char **argv) {
  (void)argc;
  FILE *fd = fopen(argv[1], "r");
  char input[BUFFER];
  struct Stack stacks[N_STACKS];
  int n_stacks = 0;
  for (int i = 0; i < N_STACKS; ++i) {
    stacks[i] = *(struct Stack *)malloc(sizeof(struct Stack));
    stacks[i].height = 0;
    stacks[i].top = NULL;
  }

  // Read initial stack order.
  while (fgets(input, BUFFER, fd) != NULL) {
    if (input[1] == '1') {
      break;
    }
    int len = strlen(input) - 1;
    int p = 1;
    while (p < len) {
      if (input[p] == ' ') {
        p += 4;
        continue;
      }
      int i = p / 4;
      struct Crate *crate = (struct Crate *)malloc(sizeof(struct Crate));
      crate->id = input[p];
      crate->prev = NULL;
      if (stacks[i].height == 0) {
        crate->next = NULL;
        stacks[i].top = crate;
      } else {
        struct Crate *bottom = stacks[i].top;
        while (bottom->prev != NULL) {
          bottom = bottom->prev;
        }
        crate->next = bottom;
        bottom->prev = crate;
      }
      stacks[i].height += 1;
      p += 4;
    }
    n_stacks = p / 4;
  }

  // Read empty line.
  fgets(input, BUFFER, fd);

  // Read movements.
  while (fgets(input, BUFFER, fd) != NULL) {
    int p = 5; // strlen("move ") == 5, ish
    int n = get_int(input, &p);
    p += 5; // strlen("from ") == 5, ish
    int from = get_int(input, &p) - 1;
    p += 3; // strlen("to ") == 3, ish
    int to = get_int(input, &p) - 1;
    /* print_stack(stacks[to]); */
    /* print_stack(stacks[from]); */
    for (int i = 0; i < n; ++i) {
      struct Crate *tmp = stacks[from].top;
      // Resolve "from" stack.
      if (stacks[from].top->prev != NULL) {
        stacks[from].top = stacks[from].top->prev;
      } else {
        stacks[from].top = NULL;
      }
      // Resolve "to" stack.
      if (stacks[to].top != NULL) {
        stacks[to].top->next = tmp;
        tmp->prev = stacks[to].top;
        stacks[to].top = tmp;
      } else {
        tmp->prev = NULL;
        stacks[to].top = tmp;
      }
    }
    stacks[to].height += n;
    stacks[from].height -= n;
    /* print_stack(stacks[to]); */
    /* print_stack(stacks[from]); */
  }

  printf("\nResult: ");
  for (int i = 0; i < n_stacks; ++i) {
    printf("%c", stacks[i].top->id);
  }
  printf("\n");

  // No free, because who cares about memory :)
  return 0;
}
