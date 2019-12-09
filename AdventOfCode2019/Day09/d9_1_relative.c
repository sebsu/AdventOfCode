#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4096

size_t N_OP;

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
    N_OP = i;
}


int with_mode(int mode, int param, int rel_base, int *prog) {
    switch (mode) {
    case 0:
        return prog[param];
    case 1:
        return param;
    case 2:
        return prog[rel_base+param];
    default:
        return prog[param];
    }
}

bool run_prog(int *prog, int phase, int *var, int *pos) {
    static int rel_base = 0;
    bool read_phase = false;
    while (prog[*pos] != 99) {
        int mode1 = 0;
        int mode2 = 0;
        /* int mode3 = 0; */
        int op = prog[(*pos)++];
        printf("OP: %i, addr: %i\n", op, *pos);
        if (op > 10) {
            mode1 = (int)(floor(op / 100))%10 % 3;
            mode2 = (int)(floor(op / 1000))%10 % 3;
            /* mode3 = (int)floor(op / 10000) % 2; */ /* Not used */
            op = op % 10;
        }
        printf("  OP: %i, addr: %i, modes: %i, %i\n", op, *pos, mode1, mode2);
        int param1;
        int param2;
        int param3;
        switch (op) {
        case 1:                 /* Addition */
            param1 = prog[(*pos)++]; /* Input var 1 */
            param2 = prog[(*pos)++]; /* Input var 2 */
            param3 = prog[(*pos)++]; /* Output var */
            param1 = with_mode(mode1, param1, rel_base, prog);
            param2 = with_mode(mode2, param2, rel_base, prog);
            /* param3 = (mode3) ? param3 : prog[param3]; */
            prog[param3] = param1 + param2; /* Execute op */
            /* printf("1. Sum: %i + %i = %i, in addr %i\n", param1, param2, prog[param3], param3); */
            break;
        case 2:                 /* Multiplication */
            param1 = prog[(*pos)++]; /* Input var 1 */
            param2 = prog[(*pos)++]; /* Input var 2 */
            param3 = prog[(*pos)++]; /* Output var */
            param1 = (mode1) ? param1 : prog[param1];
            param2 = (mode2) ? param2 : prog[param2];
            /* param3 = (mode3) ? param3 : prog[param3]; */
            prog[param3] = param1 * param2; /* Execute op */
            /* printf("2. Product: %i * %i = %i, in addr %i\n", param1, param2, prog[param3], param3); */
            break;
        case 3:                 /* Save input */
            param1 = prog[(*pos)++]; /* Output var */
            param2 = (read_phase) ? *var : phase;
            read_phase = true;
            /* printf("3. Saved %i to addr %i\n", param2, param1); */
            prog[param1] = param2; /* Execute op */
            break;
        case 4:                 /* Print input */
            param1 = prog[(*pos)++]; /* Output var */
            param1 = (mode1) ? param1 : prog[param1];
            /* printf(" 4. PrintOP: %i\n", param1); /\* Execute op *\/ */
            *var = param1;
            return false;
        case 5:                 /* Jump if true */
            param1 = prog[(*pos)++]; /* Flag */
            param2 = prog[(*pos)++]; /* Addr */
            param1 = (mode1) ? param1 : prog[param1];
            param2 = (mode2) ? param2 : prog[param2];
            /* printf("5. If %i != '0' jump from addr %i to addr %i\n", param1, *pos, param2); */
            *pos = (param1 != 0) ? param2 : *pos; /* Execute op */
            break;
        case 6:                 /* Jump if false */
            param1 = prog[(*pos)++]; /* Flag */
            param2 = prog[(*pos)++]; /* Addr */
            param1 = (mode1) ? param1 : prog[param1];
            param2 = (mode2) ? param2 : prog[param2];
            /* printf("6. If %i == '0' jump from addr %i to addr %i\n", param1, *pos, param2); */
            *pos = (param1 == 0) ? param2 : *pos; /* Execute op */
            break;
        case 7:                 /* Store if less than */
            param1 = prog[(*pos)++]; /* Var 1 */
            param2 = prog[(*pos)++]; /* Var 2 */
            param3 = prog[(*pos)++]; /* *Pos */
            param1 = (mode1) ? param1 : prog[param1];
            param2 = (mode2) ? param2 : prog[param2];
            /* param3 = (mode3) ? param3 : prog[param3]; */
            /* printf("7. If %i < %i save 1 to addr %i\n", param1, param2, param3); */
            prog[param3] = (param1 < param2) ? 1 : 0; /* Execute op */
            /* printf("7saved: %i to %i\n", prog[param3], param3); */
            break;
        case 8:                 /* Store if eq */
            param1 = prog[(*pos)++]; /* Var 1 */
            param2 = prog[(*pos)++]; /* Var 2 */
            param3 = prog[(*pos)++]; /* *Pos */
            param1 = (mode1) ? param1 : prog[param1];
            param2 = (mode2) ? param2 : prog[param2];
            /* param3 = (mode3) ? param3 : prog[param3]; */
            /* printf("8. If %i == %i save 1 to addr %i\n", param1, param2, param3); */
            prog[param3] = (param1 == param2) ? 1 : 0; /* Execute op */
            /* printf("8saved: %i to %i\n", prog[param3], param3); */
            break;
        }
    }
    return true;
}

void print_array(int in[N_OP]) {
    printf("\nProgram: ");
    for (size_t i=0; i<N_OP; ++i) {
        printf("%i,", in[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    assert(argc > 1);

    FILE *f;
    char str[SIZE];
    int prog[SIZE] = {0};
    f = fopen(argv[1], "r");

    fgets(str, SIZE, f);

    read_prog(str, prog);

    int best_thrust = 0;

    for (int a=5; a<10; ++a) {
        for (int b=5; b<10; ++b) {
            if (b==a) {
                continue;
            }
            for (int c=5; c<10; ++c) {
                if (c==a || c==b) {
                    continue;
                }
                for (int d=5; d<10; ++d) {
                    if (d==a || d==b || d==c) {
                        continue;
                    }
                    for (int e=5; e<10; ++e) {
                        if (e==a || e==b || e==c || e==d) {
                            continue;
                        }

                        /* printf("Phases: %i,\t%i,\t%i,\t%i,\t%i\n", a, b, c, d, e); */
                        int out = 0;
                        /* int phase[] = {a, b, c, d, e}; */
      
                        int prog_a[SIZE];
                        memcpy(prog_a, prog, SIZE);
                        int prog_b[SIZE];
                        memcpy(prog_b, prog, SIZE);
                        int prog_c[SIZE];
                        memcpy(prog_c, prog, SIZE);
                        int prog_d[SIZE];
                        memcpy(prog_d, prog, SIZE);
                        int prog_e[SIZE];
                        memcpy(prog_e, prog, SIZE);
      
                        int poss[5] = {0};
                        bool done = false;
                        done = run_prog(prog_a, a, &out, &poss[0]);
                        done = run_prog(prog_b, b, &out, &poss[1]);
                        done = run_prog(prog_c, c, &out, &poss[2]);
                        done = run_prog(prog_d, d, &out, &poss[3]);
                        done = run_prog(prog_e, e, &out, &poss[4]);
      
                        int *progs[] = {prog_a, prog_b, prog_c, prog_d, prog_e};
                        while (!done) {
                            for (int i=0; i<5; ++i) {
                                /* print_array(progs[i]); */
                                done = run_prog(progs[i], out, &out, &poss[i]);
                                /* printf("amp %i, out %i, pos %i\n", i, out, poss[i]); */
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
