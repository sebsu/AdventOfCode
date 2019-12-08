#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 16384
#define WIDTH 25
#define HEIGHT 6

int look(char *str, int pos) {
    while (str[pos] == '2') {
        pos += WIDTH*HEIGHT;
    }
    return (str[pos] - '0');
}

int main(int argc, char **argv) {
    assert(argc > 1);

    FILE *f;
    char str[SIZE];
    f = fopen(argv[1], "r");

    fgets(str, SIZE, f);

    for (int i=0; i<WIDTH*HEIGHT; ++i) {
        if (i%WIDTH == 0) {
            printf("\n");
        }
        printf("%i", look(str, i));
    }    

    fclose(f);
    printf("\nResult: %i\n", 0);

    return 0;
}
