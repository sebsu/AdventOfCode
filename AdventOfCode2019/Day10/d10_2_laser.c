#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 65536

typedef struct {
    int pos;
    double angle;
    double dist;
} asteroid;

int WIDTH = 0;
int HEIGHT = 0;

int get_x(int pos) {
    return pos % WIDTH;
}

int get_y(int pos) {
    return (int)(floor(pos/WIDTH));
}

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
    int x1 = get_x(pos_a);
    int x2 = get_x(pos_b);
    int y1 = get_y(pos_a);
    int y2 = get_y(pos_b);
    int dx = x2 - x1;
    int dy = y2 - y1;
    int gcd = find_gcd(dx, dy);
    /* printf("\n(%i,%i) (%i,%i), %i %i, %i\n", x1, y1, x2, y2, dx, dy, gcd); */
    *x = dx/gcd;
    *y = dy/gcd;
}

int step(int orig, int dx, int dy, int *map) {
    int x = get_x(orig);
    int y = get_y(orig);
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

double get_dist(int a, int b) {
    int xa = get_x(a);
    int ya = get_y(a);
    int xb = get_x(b);
    int yb = get_y(b);
    int dx = abs(xa - xb);
    int dy = abs(ya - yb);
    return sqrt(dx*dx + dy*dy);
}

double get_angle(int orig, int target) {
    int xo = get_x(orig);
    int yo = get_y(orig);
    int xt = get_x(target);
    int yt = get_y(target);
    if (xt >= xo && yt < yo) { /* Top right */
        return atan2(xt-xo, yo-yt);
    } else if (xt > xo && yt >= yo) { /* Bottom right */
        return atan2(yt-yo, xt-xo) + M_PI/2.0;
    } else if (xt <= xo && yt > yo) { /* Bottom left */
        return atan2(xo-xt, yt-yo) + M_PI;
    } else {                    /* Top left */
        return atan2(yo-yt, xo-xt) + 3.0*M_PI/2.0;
    }
}

bool double_eq(double a, double b) {
    int epsilon = 100000;
    int a_i = (int)floor(a*epsilon);
    int b_i = (int)floor(b*epsilon);
    return a_i == b_i;
}

int compare(const void *elem1, const void *elem2) {
    asteroid a = *((asteroid *)elem1);
    asteroid b = *((asteroid *)elem2);
    if (double_eq(a.angle, b.angle)) {
        if (a.dist < b.dist) {
            return -1;
        }
    }
    if (a.angle < b.angle) {
        return -1;
    }
    return 1;
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
    asteroid asts_sorted[SIZE];
    int orig = 0;

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
        /* printf("Me %i (%i,%i) hit %i asts\n", asts[i], get_x(asts[i]), get_y(asts[i]), in_line); */
        if (in_line >= max_in_line) {
            max_in_line = in_line;
            orig = asts[i];
        }
    }

    /* orig=59; */
    /* map[orig] = 3; */
    /* printf("orig: %i %i\n", get_x(orig), get_y(orig)); */

    for (int i=0; i<n_ast; ++i) {
        if (asts[i] == orig) continue;
        asts_sorted[i].pos = asts[i];
        asts_sorted[i].angle = get_angle(orig, asts[i]);
        asts_sorted[i].dist = get_dist(orig, asts[i]);
    }

    qsort(asts_sorted, n_ast, sizeof(asteroid), compare);

    int n_destroyed = 1;
    int target = -1;
    int goal = 200;
    while (n_destroyed < goal) {
        for (int i=1; i<n_ast; ++i) {
            /* printf("%i %f\n", n_destroyed, asts_sorted[i].angle); */
            if (double_eq(asts_sorted[i-1].angle, asts_sorted[i].angle)) continue;
            ++n_destroyed;

    /*         map[asts_sorted[i].pos] = n_destroyed%10; */
    /* for (int y=0; y<HEIGHT; ++y) { */
    /*     for (int x=0; x<WIDTH; ++x) { */
    /*         printf("%i", map[y*WIDTH+x]); */
    /*     } */
    /*     printf("\n"); */
    /* } */
    /* printf("\n"); */

            if (n_destroyed == goal) {
                target = asts_sorted[i].pos;
                break;
            }
        }
        qsort(asts_sorted, n_ast, sizeof(asteroid), compare);
        n_ast -= n_destroyed;
    }

    int result = get_x(target)*100 + get_y(target);

    /* Print map */
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
    printf("\nResult: %i %i, %i\n%i\n%i\n", n_destroyed, result, n_ast, max_in_line, target);

    return 0;
}
