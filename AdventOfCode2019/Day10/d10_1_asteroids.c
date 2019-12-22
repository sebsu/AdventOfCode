#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 65536

int WIDTH = 0;
int HEIGHT = 0;

/* Find greatest common divisor */
int find_gcd(int a, int b) {
        /* printf("  0 a:%i, b%i\n", a, b); */
    a = abs(a);
    b = abs(b);
    int gcd = 1;
    if (a==0 || b==0) {
        return (a>b) ? a : b;
    }
    for (int i=1; i<=a && i<=b; ++i) {
        /* printf("gcd %i, %i %i", i, a%i==0, b%i==0); */
        if (a%i==0 && b%i==0) {
            gcd = i;
        }
    }
    return gcd;
}

void find_step(int pos_a, int pos_b, int *x, int *y) {
    int x1 = pos_a % WIDTH;
    int x2 = pos_b % WIDTH;
    int y1 = (int)(floor(pos_a/WIDTH));
    int y2 = (int)(floor(pos_b/WIDTH));
    int dx = x2 - x1;
    int dy = y2 - y1;
    int gcd = find_gcd(dx, dy);
    /* printf("\n(%i,%i) (%i,%i), %i %i, %i\n", x1, y1, x2, y2, dx, dy, gcd); */
    *x = dx/gcd;
    *y = dy/gcd;
}

int step(int orig, int dx, int dy, int *map) {
    int x = orig % WIDTH;
    int y = (int)(floor(orig/WIDTH));
    /* printf("\ndx %i dy %i, x %i, y %i\n", dx, dy, x+dx, y+dy); */
    while ((0 <= x+dx && x+dx < WIDTH) &&
           (0 <= y+dy && y+dy < HEIGHT)) {
        x = x+dx;
        y = y+dy;
        /* printf("orig %i, (%i,%i)\n", orig, x, y); */
        if (map[y*WIDTH + x]) {
            return y*WIDTH + x;
        }
    }
    return orig;
}

int main(int argc, char **argv) {
    assert(argc > 1);

    FILE *f;
    f = fopen(argv[1], "r");

    char str[SIZE];
    int map[SIZE] = {0};
    int asts[SIZE] = {0};
    int n_ast = 0;
    int max_in_line = 0;

    fgets(str, SIZE, f);
    WIDTH = strlen(str)-1;
    do {
        for (int i=0; i<WIDTH; ++i) {
            map[HEIGHT*WIDTH + i] = (str[i] == '#');
            if (str[i] == '#') {
                asts[n_ast++] = HEIGHT*WIDTH + i;
            }
        }
        ++HEIGHT;
    } while(fgets(str, SIZE, f));

    /* int x, y; */
    /* find_step(19, 1, &x, &y); */
    /* step(19, x, y, map); */
    
    for (int i=0; i<n_ast; ++i) {
        int in_line = 0;
        for (int j=0; j<n_ast; ++j) {
            if (i==j) continue;
            int dx, dy;
            find_step(asts[i], asts[j], &dx, &dy);
            int hit = step(asts[i], dx, dy, map);
            if (hit == asts[j]) {
                /* printf("  Me %i hit %i\n", asts[i], hit); */
                ++in_line;
            }
        }
        /* printf("Me %i hit %i asts\n", asts[i], in_line); */
        if (in_line > max_in_line) {
            max_in_line = in_line;
        }
    }
    
    /* for (int y=0; y<HEIGHT; ++y) { */
    /*     for (int x=0; x<WIDTH; ++x) { */
    /*         printf("%i", map[y*WIDTH+x]); */
    /*     } */
    /*     printf("\n"); */
    /* } */
    /* for (int i=0; i<n_ast; ++i) { */
    /*     printf("%i, ", asts[i]); */
    /* } */
    
    fclose(f);
    printf("\nResult: %i %i, %i\n%i\n", WIDTH, HEIGHT, n_ast, max_in_line);

    return 0;
}
