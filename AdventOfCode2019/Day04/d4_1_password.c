#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pr(char* str){
    for(int i=0; i<6; ++i){
        printf("%c", str[i]);
    }
    printf("\n");
}

bool valid(char *str){
    char prev = str[0];
    bool has_double = false;
    bool is_incr = true;
    for(int i=1; i<6; ++i){
        has_double = (prev == str[i]) || has_double;
        is_incr = (prev <= str[i]) && is_incr;
        prev = str[i];
    }
    return (is_incr && has_double);
}

void incr_i(char *str, int pos){
    assert(pos >= 0);
    if (str[pos] < '9') {
        str[pos] += 1;
        return;
    }
    str[pos] = '0';
    incr_i(str, pos-1);
}

void incr(char *str){
    if (str[5] < '9') {
        str[5] += 1;
        return;
    }
    str[5] = '0';
    incr_i(str, 4);
}

int main(int argc, char **argv) {
  assert(argc > 1);

  FILE *f;
  const int size = 64;
  char str[size];
  f = fopen(argv[1], "r");

  fgets(str, size, f);

  char start[6] = {str[0],str[1],str[2],str[3],str[4],str[5]};
  char end[6] = {str[7],str[8],str[9],str[10],str[11],str[12]};
  int n_valid = 0;
  pr(start);
  pr(end);
  char test[6] = {'1', '2', '3', '4', '4', '5'};
  pr(test);
  printf("Result: %i\n", valid(test));

  for (char *curr = start; strcmp(curr, end)<0; incr(curr)) {
      n_valid += valid(curr);
  }
  
  fclose(f);
  printf("Result: %i\n", n_valid);

  return 0;
}
