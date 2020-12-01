#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 65536
#define N_MOONS 4
#define N_AXIS 3

struct axis {
    int p;
    int v;
};

struct moon {
    struct axis a[N_AXIS];
};

/* Compare the position and velocity of two points on an axis, true if same. */
bool cmp_axis(struct axis* a, struct axis* b){
    return (a->p == b->p) && (a->v == b->v);
}

/* Compare the position and velocity of two moons, true if same. */
bool cmp_moon(struct moon* a, struct moon* b){
    return cmp_axis(&a->a[0], &b->a[0])  /* I know I can make a loop. */
        && cmp_axis(&a->a[1], &b->a[1])  /* I don't want to. */
        && cmp_axis(&a->a[2], &b->a[2]); /* Fuck you. */
}

/* String to int. */
int stoi(char *str, size_t *pos) {
    int out = 0;
    int sign = 1;
    if (str[*pos] == '-') {
        sign = -1;
        ++(*pos);
    }
    while (str[*pos] != ',' && str[*pos] != '>') {
        out = (out * 10) + (str[*pos] - 48);
        ++(*pos);
    }
    ++(*pos);
    return sign * out;
}

/* Find the integer in a string. */
int extract_int(char *str, size_t *pos) {
    while (str[*pos] != '=') {
        ++(*pos);
    }
    ++(*pos);
    return stoi(str, pos);
}

/* Update the x/y/z-axis on moons a and b based on each others' gravity. */
void update_axis(struct axis* a, struct axis* b) {
    if (a->p < b->p) {
        ++(a->v);
        --(b->v);
    } else if (a->p > b->p) {
        --(a->v);
        ++(b->v);
    }
}

/* Update the velocity of all moons. */
void update_vel(struct moon m[N_MOONS]) {
    for (int i=0; i<N_MOONS; ++i) {
        for (int j=i+1; j<N_MOONS; ++j) {
            for (int k=0; k<N_AXIS; ++k) {
                update_axis(&m[i].a[k], &m[j].a[k]);
            }
        }
    }
}

/* Update the position of all moons based on their velocity. */
void update_pos(struct moon m[N_MOONS]) {
    for (int i=0; i<N_MOONS; ++i) {
        for (int j=0; j<N_AXIS; ++j) {
            m[i].a[j].p += m[i].a[j].v;
        }
    }
}

/* Compare the current state with the initial state on axis n.  */
bool cmp_state(struct moon m[N_MOONS], struct moon origin[N_MOONS], int n) {
    bool same = true;
    for (int i=0; i<N_MOONS; ++i) {
        same = same && cmp_axis(&m[i].a[n], &origin[i].a[n]);
    }
    return same;
}

/* Least common multiple
 * https://en.wikipedia.org/wiki/Least_common_multiple#Using_a_simple_algorithm
 */
uint64_t lcm(uint64_t ai, uint64_t bi, uint64_t ci) {
    uint64_t a = ai;
    uint64_t b = bi;
    uint64_t c = ci;
    while (!((a == b) && (b == c))) {
        if ((a <= b) && (a <= c)) {
            a = a + ai;
        } else if ((b <= c) && (b <= a)) {
            b = b + bi;
        } else {
            c = c + ci;
        }
    }
    return a;
}

void print_moons(struct moon m[N_MOONS]) {
    for (int i=0; i<N_MOONS; ++i) {
        printf("pos=<x=%4i, y=%4i, z=%4i>,\t", m[i].a[0].p, m[i].a[1].p, m[i].a[2].p);
        printf("vel=<x=%4i, y=%4i, z=%4i>", m[i].a[0].v, m[i].a[1].v, m[i].a[2].v);
        printf("\n");
    }    
}

int main(int argc, char **argv) {
    assert(argc > 1);

    FILE *f;
    f = fopen(argv[1], "r");

    char str[STR_SIZE];
    
    struct moon moons[N_MOONS] = {0};

    for (int i=0; i<N_MOONS; ++i) {
        fgets(str, STR_SIZE, f);
        size_t p = 0;
        moons[i].a[0].p = extract_int(str, &p);
        moons[i].a[1].p = extract_int(str, &p);
        moons[i].a[2].p = extract_int(str, &p);
    }

    /* printf("After 0 steps:\n"); */
    /* print_moons(moons); */
    /* printf("\n"); */

    uint64_t loops[N_AXIS] = {0};
    struct moon init_moon[N_MOONS] = {0};
    for (int i=0; i<N_MOONS; ++i) {
        for (int j=0; j<N_AXIS; ++j) {
            init_moon[i].a[j] = moons[i].a[j];
        }
    }
    
    for (int axis=0; axis<N_AXIS; ++axis) {
        uint64_t i = 0;
        uint64_t loop = 0;
        while (!loop) {
            update_vel(moons);
            update_pos(moons);
            ++i;
            loop = cmp_state(moons, init_moon, axis) ? i : 0;
        }
        /* Save the amount of iterations it took to reach the initial state. */
        loops[axis] = loop;
        
        /* printf("After %lu steps:\n", i); */
        /* print_moons(moons); */
        /* printf("\n"); */
        
        /* Reset for next axis */
        for (int i=0; i<N_MOONS; ++i) {
            for (int j=0; j<N_AXIS; ++j) {
                moons[i].a[j] = init_moon[i].a[j];
            }
        }
    }

    uint64_t res = lcm(loops[0] , loops[1], loops[2]);
    fclose(f);
    printf("\nResult: %lu,%lu,%lu, %lu, %lu\n", loops[0], loops[1], loops[2],
           loops[0]*loops[1]*loops[2], res);

    return 0;
}
