#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 65536

int WIDTH = 0;
int HEIGHT = 0;

typedef enum {
           top = 0,
           right = 1,
           bottom = 2,
           left = 3,
} edge;

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

void find_triangle(int a, int b, int c, edge side) {
    int xa = a % WIDTH;
    int ya = (int)(floor(a/WIDTH));
    int xb = b % WIDTH;
    int yb = (int)(floor(b/WIDTH));
    int xc = c % WIDTH;
    int yc = (int)(floor(c/WIDTH));
    switch (side) {
    case top:
        return;
    case right:
        return;
    case bottom:
        return;
    case left:
        return;
}

int tick(int prev) {
    int x = prev % WIDTH;
    int y = (int)(floor(prev/WIDTH));
    if (y==0 && (x+1)<WIDTH) {  /* TOP */
        /* printf("TOP prev %i (%i,%i), next %i\n", prev, x, y, prev+1); */
        return prev+1;
    } else if (x==(WIDTH-1) && (y+1)<HEIGHT) { /* RIGHT */
        /* printf("RIGHT prev %i (%i,%i), next %i\n", prev, x, y, prev+WIDTH); */
        return prev+WIDTH;
    } else if (y==(HEIGHT-1) && (x-1)>0) { /* BOTTOM */
        /* printf("BOT prev %i (%i,%i), next %i\n", prev, x, y, prev-1); */
        return prev-1;
    } else {                    /* LEFT */
        /* printf("LEFT prev %i (%i,%i), next %i\n", prev, x, y, prev-WIDTH); */
        return prev-WIDTH;
    }
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
    int best_pos = 0;

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
            best_pos = i;
        }
    }

    int xb = best_pos%WIDTH;
    int yb = (int)(floor(best_pos/WIDTH));
    printf("h %i w %i (%i,%i)\n", HEIGHT, WIDTH, xb, yb);

    for (int y=0; y<HEIGHT; ++y) {
        for (int x=0; x<WIDTH; ++x) {
            printf("%i", map[y*WIDTH+x]);
        }
        printf("\n");
    }
    
        printf("\n\n");

    int n_hit = 0;
    int bet_ast = 130;
    int target = best_pos % WIDTH;
    while (n_hit != bet_ast) {
        target = tick(target);
        if (target==best_pos) continue;
        int dx, dy;
        find_step(best_pos, target, &dx, &dy);
        int hit = step(best_pos, dx, dy, map);
        /* printf("  Me %i hit %i\n", best_pos, hit); */
        if (hit != best_pos) {
            /* printf("nhit %i\n", n_hit); */
            ++n_hit;
            map[hit] = 0;
        }
    }

    int xf = target%WIDTH;
    int yf = (int)(floor(target/WIDTH));

    
    for (int y=0; y<HEIGHT; ++y) {
        for (int x=0; x<WIDTH; ++x) {
            printf("%i", map[y*WIDTH+x]);
        }
        printf("\n");
    }
    
    /* for (int i=0; i<n_ast; ++i) { */
    /*     printf("%i, ", asts[i]); */
    /* } */
    
    fclose(f);
    printf("\nResult: %i %i, %i\n%i\n", WIDTH, HEIGHT, n_ast, xf*100+yf);

    return 0;
}
