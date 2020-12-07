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
#define BAG_SIZE 32
#define RULE_SIZE 10

typedef struct {
  char name[BAG_SIZE];
} Bag;

typedef struct {
  char key[BAG_SIZE];
  Bag val[RULE_SIZE];
} Pair;

void extract_rules(char *rule, int n_rules, Pair *rules) {
  /* Extract outer bag. */
  size_t size = strstr(rule, " bags") - rule;
  strncpy(rules[n_rules].key, rule, size);

  /* Can we contain bags? */
  if (strstr(rule, "no other bags") != NULL) {
    strcpy(rules[n_rules].val[0].name, "");
    return;
  }

  /* Extract inner bags. */
  int i = 0;
  char *find = "contain ";
  char contain[STR_SIZE];
  strcpy(contain, strstr(rule, find) + strlen(find));
  char *start = strchr(contain, ' ') + 1;
  while (true) {
    char *end = strchr(strchr(start, ' ') + 1, ' ') + 1;
    strncpy(rules[n_rules].val[i++].name, start, end - start - 1);
    if (strpbrk(end, " .")[0] == '.') { /* Find first of ' ' or '.', */
      break;                            /* if '.' then break.*/
    }
    start = strchr(strchr(end, ' ') + 1, ' ') + 1;
  }
}

int find_valid(Pair *rules, Bag *valid_bags, int n_rules, int n_valid) {
  for (int i = 0; i < n_rules; ++i) {     /* For each rule, */
    for (int j = 0; j < RULE_SIZE; ++j) { /* check each contained bag. */
      if (strcmp(rules[i].val[j].name, "") == 0) {
        break;
      }

      /* If this bag has already been added to the valid bags list, ignore. */
      int exist = 0;
      for (int l = 0; l < n_valid; ++l) {
        if (strcmp(rules[i].key, valid_bags[l].name) == 0) {
          exist = 1;
          break;
        }
      }
      if (exist == 1) {
        continue;
      }

      /* If a new bag type, that can include any already valid bag type, */
      /* is found, add it. */
      for (int k = 0; k < n_valid; ++k) {
        if (strcmp(rules[i].val[j].name, valid_bags[k].name) == 0) {
          strcpy(valid_bags[n_valid++].name, rules[i].key);
          break;
        }
      }
    }
  }
  return n_valid;
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  f = fopen(argv[1], "r");

  char str[STR_SIZE];
  Pair *rules = (Pair *)malloc(sizeof(Pair) * INPUT_SIZE);
  Bag *valid_bags = (Bag *)malloc(sizeof(Bag) * INPUT_SIZE);
  int n_rules = 0;
  strcpy(valid_bags[0].name, "shiny gold");
  while (fgets(str, STR_SIZE, f) != NULL) {
    extract_rules(str, n_rules, rules);
    ++n_rules;
  }

  int n_valid = 0;
  int new_valid = 1;
  do {
    n_valid = new_valid;
    new_valid = find_valid(rules, valid_bags, n_rules, n_valid);
  } while (new_valid != n_valid);

  free(rules);
  free(valid_bags);

  fclose(f);
  printf("\nResult: %i\n", --n_valid);

  return 0;
}
