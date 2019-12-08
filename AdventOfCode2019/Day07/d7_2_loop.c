#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4096

int stoi(char *str, size_t *pos) {
    int out = 0;
    int sign = 1;
    if (str[*pos] == '-') {
        sign = -1;
        *pos += 1;
    }
    /* Might have added a , at the end of the input for this to work... */
    while (str[*pos] != ',') {
        out = (out * 10) + (str[*pos] - 48);
        *pos += 1;
    }
    *pos += 1;
    return sign * out;
}

void read_prog(char *str, int *prog) {
    size_t len = strlen(str) - 1;
    size_t pos = 0;
    size_t i = 0;
    for (i = 0; pos < len; ++i) {
        prog[i] = stoi(str, &pos);
    }
}

bool run_prog(int *prog, int phase, int *var, int *pos) {
    bool read_phase = false;
    while (prog[*pos] != 99) {
        int mode1 = 0;
        int mode2 = 0;
        int op = prog[(*pos)++];
        if (op > 10) {
            mode1 = (int)floor(op / 100) % 2;
            mode2 = (int)floor(op / 1000) % 2;
            op = op % 10;
        }
        int param1;
        int param2;
        int param3;
        switch (op) {
        case 1: /* Addition: prog[c]=a+b */
            param1 = prog[(*pos)++]; /* a */
            param2 = prog[(*pos)++]; /* b */
            param3 = prog[(*pos)++]; /* c */
            param1 = (mode1) ? param1 : prog[param1];
            param2 = (mode2) ? param2 : prog[param2];
            prog[param3] = param1 + param2; /* Execute op */
            break;
        case 2: /* Multiplication: prog[c]=a*b */
            param1 = prog[(*pos)++]; /* a */
            param2 = prog[(*pos)++]; /* b */
            param3 = prog[(*pos)++]; /* c */
            param1 = (mode1) ? param1 : prog[param1];
            param2 = (mode2) ? param2 : prog[param2];
            prog[param3] = param1 * param2; /* Execute op */
            break;
        case 3: /* Save input: prog[a]=input */
            param1 = prog[(*pos)++]; /* a */
            param2 = (read_phase) ? *var : phase; /* input */
            read_phase = true;
            prog[param1] = param2; /* Execute op */
            break;
        case 4: /* Return output: prog[a] */
            param1 = prog[(*pos)++]; /* a */
            param1 = (mode1) ? param1 : prog[param1];
            *var = param1; /* Execute op */
            return false; /* Not done */
        case 5: /* Jump if true: jmp to Addr if Flag!=0 */
            param1 = prog[(*pos)++]; /* Flag */
            param2 = prog[(*pos)++]; /* Addr */
            param1 = (mode1) ? param1 : prog[param1];
            param2 = (mode2) ? param2 : prog[param2];
            *pos = (param1 != 0) ? param2 : *pos; /* Execute op */
            break;
        case 6: /* Jump if false: jmp to Addr if Flag==0 */
            param1 = prog[(*pos)++]; /* Flag */
            param2 = prog[(*pos)++]; /* Addr */
            param1 = (mode1) ? param1 : prog[param1];
            param2 = (mode2) ? param2 : prog[param2];
            *pos = (param1 == 0) ? param2 : *pos; /* Execute op */
            break;
        case 7: /* Store if less than */
            param1 = prog[(*pos)++]; /* Var 1 */
            param2 = prog[(*pos)++]; /* Var 2 */
            param3 = prog[(*pos)++]; /* *Pos */
            param1 = (mode1) ? param1 : prog[param1];
            param2 = (mode2) ? param2 : prog[param2];
            prog[param3] = (param1 < param2) ? 1 : 0; /* Execute op */
            break;
        case 8: /* Store if eq */
            param1 = prog[(*pos)++]; /* Var 1 */
            param2 = prog[(*pos)++]; /* Var 2 */
            param3 = prog[(*pos)++]; /* *Pos */
            param1 = (mode1) ? param1 : prog[param1];
            param2 = (mode2) ? param2 : prog[param2];
            prog[param3] = (param1 == param2) ? 1 : 0; /* Execute op */
            break;
        }
    }
    return true; /* Program fully executed */
}

int main(int argc, char **argv) {
    assert(argc > 1);

    FILE *f;
    f = fopen(argv[1], "r");

    char str[SIZE];
    int prog[SIZE] = {0};

    fgets(str, SIZE, f);
    read_prog(str, prog);

    int best_thrust = 0;
    int min_phase = 5;
    int max_phase = 10;

    /* Looping as a simple way to find different configs */
    for (int a=min_phase; a<max_phase; ++a) {
        for (int b=min_phase; b<max_phase; ++b) {
            if (b==a) continue;
            for (int c=min_phase; c<max_phase; ++c) {
                if (c==a || c==b) continue;
                for (int d=min_phase; d<max_phase; ++d) {
                    if (d==a || d==b || d==c) continue;
                    for (int e=min_phase; e<max_phase; ++e) {
                        if (e==a || e==b || e==c || e==d) continue;

                        int out = 0;
                        int progs[5][SIZE];
                        int phases[5] = {a, b, c, d, e};
                        int poss[5] = {0};
                        bool done = false;

                        for (int i=0; i<5; ++i) {
                            memcpy(progs[i], prog, SIZE);
                            done = run_prog(progs[i], phases[i], &out, &poss[i]);
                        }      

                        while (!done) {
                            for (int i=0; i<5; ++i) {
                                done = run_prog(progs[i], out, &out, &poss[i]);
                            }
                        }

                        if (out > best_thrust) {
                            best_thrust = out;
                            printf(" BEST Phases (%i): %i,%i,%i,%i,%i\n", best_thrust, a, b, c, d, e);
                        }

                    }
                }
            }
        }
    }
  

    fclose(f);
    printf("Result: %i\n", best_thrust);

    return 0;
}
