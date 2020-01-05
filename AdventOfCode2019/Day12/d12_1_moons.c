#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 65536
#define N_MOONS 4
#define N_AXIS 3

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

void update_vel(int pos[N_MOONS][N_AXIS], int vel[N_MOONS][N_AXIS]) {
   /* GRAVITY */
    for (int i=0; i<N_MOONS; ++i) {
        for (int j=i+1; j<N_MOONS; ++j) {
            for (int k=0; k<N_AXIS; ++k) {
                if (pos[i][k] < pos[j][k]) {
                    ++vel[i][k];
                    --vel[j][k];
                } else if (pos[i][k] > pos[j][k]) {
                    --vel[i][k];
                    ++vel[j][k];
                }
            }
        }
    }
}

void update_pos(int pos[N_MOONS][N_AXIS], int vel[N_MOONS][N_AXIS]) {
    /* UPDATE POS */
    for (int i=0; i<N_MOONS; ++i) {
        for (int j=0; j<N_AXIS; ++j) {
            pos[i][j] += vel[i][j];
        }
    }
}

void print_moons(int pos[N_MOONS][N_AXIS], int vel[N_MOONS][N_AXIS]) {
    for (int i=0; i<N_MOONS; ++i) {
        printf("pos=<x=%4i, y=%4i, z=%4i>,\t", pos[i][0], pos[i][1], pos[i][2]);
        printf("vel=<x=%4i, y=%4i, z=%4i>", vel[i][0], vel[i][1], vel[i][2]);
        printf("\n");
    }
}

int main(int argc, char **argv) {
    assert(argc > 1);

    FILE *f;
    f = fopen(argv[1], "r");

    char str[SIZE];
    const int max_ticks = 1000;

    int vel[N_MOONS][N_AXIS] = {0};
    int pos[N_MOONS][N_AXIS] = {0};

    for (int i=0; i<N_MOONS; ++i) {
        fgets(str, SIZE, f);
        size_t p = 0;
        for (int j=0; j<N_AXIS; ++j) {
            pos[i][j] = extract_int(str, &p);
        }
    }

    printf("After 0 steps:\n");
    print_moons(pos, vel);
    printf("\n");

    for (int i=0; i<max_ticks; ++i) {
        update_vel(pos, vel);
        update_pos(pos, vel);

        /* printf("After %i steps:\n", i+1); */
        /* print_moons(pos, vel); */
        /* printf("\n"); */

    }

    int tot_e = 0;
    for (int i=0; i<N_MOONS; ++i) {
        int pot = 0;
        int kin = 0;
        for (int j=0; j<N_AXIS; ++j) {
            pot += abs(pos[i][j]);
            kin += abs(vel[i][j]);
        }
        /* printf("pot: %i , kin: %i , tot: %i\n", pot, kin, pot*kin); */
        tot_e += pot*kin;
    }

    printf("After %i steps:\n", max_ticks);
    print_moons(pos, vel);
    printf("\n");
    
    fclose(f);
    printf("\nResult: %i\n", tot_e);

    return 0;
}
