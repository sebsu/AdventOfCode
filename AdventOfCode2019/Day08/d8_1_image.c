#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4096
#define WIDTH 25
#define HEIGHT 6

bool read_layer(FILE *f, int *best_zero, int *best_one, int *best_two) {
    char c;
    int n_zero = 0;
    int n_one = 0;
    int n_two = 0;
    for (int i=0; i<HEIGHT; ++i) {
        for (int j=0; j<WIDTH; ++j) {
            if ((c = fgetc(f)) == EOF) {
                return true;
            }
            switch (c) {
            case '0':
                ++n_zero;
                break;
            case '1':
                ++n_one;
                break;
            case '2':
                ++n_two;
                break;
            default:
                break;
            }
        }
    }
    /* printf("layer result 0: %i, 1: %i, 2: %i\n", n_zero, n_one, n_two); */
    if (n_zero < *best_zero) {
        *best_zero = n_zero;
        *best_one = n_one;
        *best_two = n_two;
    }
    return false;
}
int main(int argc, char **argv) {
    assert(argc > 1);

    FILE *f;
    int n_zero = SIZE;
    int n_one = 0;
    int n_two = 0;
    f = fopen(argv[1], "r");

    bool done = false;
    while (!done){
        done = read_layer(f, &n_zero, &n_one, &n_two);
    }

    fclose(f);
    printf("Result: %i\n", n_one*n_two);

    return 0;
}
