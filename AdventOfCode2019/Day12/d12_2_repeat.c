#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 65536
#define SIZE 131072
#define N_MOONS 4
#define N_AXIS 3

struct axis {
    int p;
    int v;
};

struct moon {
    struct axis a[N_AXIS];
};

bool cmp_axis(struct axis* a, struct axis* b){
    return (a->p == b->p) && (a->v == b->v);
}

bool cmp_moon(struct moon* a, struct moon* b){
    return cmp_axis(&a->a[0], &b->a[0])
        && cmp_axis(&a->a[1], &b->a[1])
        && cmp_axis(&a->a[2], &b->a[2]);
}

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

int extract_int(char *str, size_t *pos) {
    while (str[*pos] != '=') {
        ++(*pos);
    }
    ++(*pos);
    return stoi(str, pos);
}

void update_axis(struct axis* a, struct axis* b) {
    if (a->p < b->p) {
        ++(a->v);
        --(b->v);
    } else if (a->p > b->p) {
        --(a->v);
        ++(b->v);
    }
}

void update_vel(struct moon m[N_MOONS]) {
    /* GRAVITY */
    for (int i=0; i<N_MOONS; ++i) {
        for (int j=i+1; j<N_MOONS; ++j) {
            for (int k=0; k<N_AXIS; ++k) {
                update_axis(&m[i].a[k], &m[j].a[k]);
            }
        }
    }
}

void update_pos(struct moon m[N_MOONS]) {
    /* UPDATE POS */
    for (int i=0; i<N_MOONS; ++i) {
        for (int j=0; j<N_AXIS; ++j) {
            m[i].a[j].p += m[i].a[j].v;
        }
    }
}

void save_cmp_state(struct moon m[N_MOONS], uint64_t t,
                    struct axis a[N_MOONS][SIZE],
                    uint64_t* l, int n) {
    for (uint64_t j=0; j<t; ++j) {
            bool same = true;
            for (int i=0; i<N_MOONS; ++i) {
                same = same && cmp_axis(&m[i].a[n], &a[i][j]);
            }
            if (same) {
                *l = t;
                break;
            }
    }
    for (int i=0; i<N_MOONS; ++i) {
        a[i][t] = m[i].a[n];
    }
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

void print_axis(struct axis a[N_MOONS][SIZE], uint64_t t) {
    for (int i=0; i<N_MOONS; ++i) {
        printf("Moon %i history\n", i);
        printf("p=%4i v=%4i\n", a[i][t].p, a[i][t].v);
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

    printf("After 0 steps:\n");
    print_moons(moons);
    printf("\n");

    uint64_t loops[N_AXIS] = {0};
    
    for (int axis=0; axis<N_AXIS; ++axis) {
        struct axis states[N_MOONS][SIZE] = {0};
        uint64_t loop = 0;
        uint64_t i = 0;
        while (!loop) {
            save_cmp_state(moons, i, states, &loop, axis);
            update_vel(moons);
            update_pos(moons);
            ++i;
        }
        loops[axis] = loop;
        printf("After %lu steps:\n", i-1);
        print_moons(moons);
        printf("\n");
    }
    
    /* save_cmp_state(moons, i, */
    /*                states_x, states_y, states_z, */
    /*                &loop_x, &loop_y, &loop_z); */
    /* printf("X\n"); */
    /* print_axis(states_x, 2771); */
    /* printf("Y\n"); */
    /* print_axis(states_y, 2771); */
    /* printf("Z\n"); */
    /* print_axis(states_z, 2771); */

    
    uint64_t res = lcm(loops[0] , loops[1], loops[2]);
    fclose(f);
    printf("\nResult: %lu,%lu,%lu, %lu, %lu\n", loops[0], loops[1], loops[2],
           loops[0]*loops[1]*loops[2], res);

    return 0;
}
