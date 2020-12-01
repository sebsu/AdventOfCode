#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 65536
#define WIDTH 512
#define HEIGHT 512
#define MAP_SIZE 262144

typedef long long int inst_type;

enum {
      OP_NONE,
      OP_ADD,
      OP_MUL,
      OP_SAVE,
      OP_PRINT,
      OP_JNZ,
      OP_JZ,
      OP_SL,
      OP_SE,
      OP_SETRB,
      OP_END = 99,
};

enum {
      OP_MODE_IMMEDIATE,
      OP_MODE_POSITION,
      OP_MODE_RELATIVE,
};

typedef struct {
    int x;
    int y;
} coord;

size_t N_OP;                    /* Can be removed. Only used for printing. */

inst_type stoi(char *str, size_t *pos) {
    inst_type out = 0;
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

void read_prog(char *str, inst_type *prog) {
    size_t len = strlen(str) - 1;
    size_t pos = 0;
    size_t i = 0;
    for (i = 0; pos < len; ++i) {
        prog[i] = stoi(str, &pos);
    }
    N_OP = i;
}

inst_type with_mode(int mode, inst_type param, int rel_base, int pos) {
    switch (mode) {
    case OP_MODE_IMMEDIATE:
        return param;
    case OP_MODE_POSITION:
        return pos;
    case OP_MODE_RELATIVE:
        return rel_base + param;
    default:
        return param;
    }
}

bool run_prog(inst_type *prog, inst_type *var, int *pos) {
    static int rel_base = 0;
    while (prog[*pos] != 99) {
        int mode1 = 0;
        int mode2 = 0;
        int mode3 = 0;
        int op = prog[(*pos)++];
        /* printf("OP: %i, addr: %i\n", op, *pos); */
        if (op > 10) {
            mode1 = (int)(floor(op / 100)) % 10;
            mode2 = (int)(floor(op / 1000)) % 10;
            mode3 = (int)(floor(op / 10000)) % 10;
            op = op % 10;
        }
        /* printf("  OP: %i, addr: %i, modes: %i, %i, %i\n", op, *pos, mode1, mode2, mode3); */
        inst_type param1 = with_mode(mode1, prog[(*pos)], rel_base, (*pos));
        inst_type param2 = with_mode(mode2, prog[(*pos)+1], rel_base, (*pos)+1);
        inst_type param3 = with_mode(mode3, prog[(*pos)+2], rel_base, (*pos)+2);
        switch (op) {
        case OP_ADD:                    /* Addition */
            prog[param3] = prog[param1] + prog[param2]; /* Execute op */
            /* printf("1. Sum: %lli + %lli = %lli, in addr %lli\n", param1, param2, prog[param3], param3); */
            (*pos) += 3;
            break;
        case OP_MUL:                    /* Multiplication */
            prog[param3] = prog[param1] * prog[param2]; /* Execute op */
            /* printf("2. Product: %lli * %lli = %lli, in addr %lli\n", param1, param2, prog[param3], param3); */
            (*pos) += 3;
            break;
        case OP_SAVE:                    /* Save input */
            prog[param1] = *var; /* Execute op */
            /* printf("3. Saved %lli to addr %lli\n", *var, param1); /\* Execute op *\/ */
            (*pos) += 1;
            break;
        case OP_PRINT:                    /* Print input */
            /* printf(" 4. PrintOP: %lli\n", prog[param1]); /\* Execute op *\/ */
            *var = prog[param1];
            (*pos) += 1;
            return false;
        case OP_JNZ:                    /* Jump if true */
            /* printf("5. If %lli != '0' jump from addr %i to addr %lli\n", param1, *pos, param2); */
            *pos = (prog[param1] != 0) ? prog[param2] : *pos+2; /* Execute op */
            break;
        case OP_JZ:                    /* Jump if false */
            /* printf("6. If %lli == '0' jump from addr %i to addr %lli\n", param1, *pos, param2); */
            *pos = (prog[param1] == 0) ? prog[param2] : *pos+2; /* Execute op */
            break;
        case OP_SL:                    /* Store if less than */
            /* printf("7. If %lli < %lli save 1 to addr %lli\n", param1, param2, param3); */
            prog[param3] = (prog[param1] < prog[param2]) ? 1 : 0; /* Execute op */
            /* printf("7saved: %lli to %lli\n", prog[param3], param3); */
            (*pos) += 3;
            break;
        case OP_SE:                    /* Store if eq */
            /* printf("8. If %lli == %lli save 1 to addr %lli\n", param1, param2, param3); */
            prog[param3] = (prog[param1] == prog[param2]) ? 1 : 0; /* Execute op */
            /* printf("8saved: %lli to %lli\n", prog[param3], param3); */
            (*pos) += 3;
            break;
        case OP_SETRB:                    /* Set relative base */
            /* printf("9. Rel_base was %i", rel_base); */
            rel_base += prog[param1]; /* Adjust rel_base */
            /* printf(" and is now %i\n", rel_base); */
            (*pos) += 1;
            break;
        default:
            return true;
        }
    }
    return true;
}

void print_array(inst_type in[N_OP]) {
    printf("\nProgram: ");
    for (size_t i = 0; i < N_OP; ++i) {
        printf("%lli,", in[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    assert(argc > 1);

    FILE *f;
    f = fopen(argv[1], "r");

    char str[SIZE];
    inst_type prog[SIZE] = {0};
    int map[MAP_SIZE] = {0};
    int visited[MAP_SIZE] = {0};

    fgets(str, SIZE, f);

    read_prog(str, prog);

    inst_type var = 0;          /* Initial input variable. */
    int pos = 0;
    bool done = false;
    inst_type color = 0;
    int dir = 0;
    inst_type turn = 0;
    coord c = {256, 256};

    while (!done) {
        visited[c.y*WIDTH+c.x] = 1;
        color = var;
        turn = var;
        /* printf("color %lli -> ", color); */
        done = run_prog(prog, &color, &pos);
        /* printf("%lli\n", color); */
        map[c.y*WIDTH+c.x] = (int)color;
        done = run_prog(prog, &turn, &pos);
        /* printf("turn %lli -> ", turn); */
        dir = (turn == 0) ? (dir-1+4)%4 : (dir+1)%4;
        /* printf("dir %i\n", dir); */
        switch (dir) {
        case 0:
            --c.y;
            break;
        case 1:
            ++c.x;
            break;
        case 2:
            ++c.y;
            break;
        case 3:
            --c.x;
            break;
        }
        var = map[c.y*WIDTH+c.x];
    }

    int res = 0;
    for (int i=0; i<MAP_SIZE; ++i) {
        res += visited[i];
    }

    fclose(f);
    printf("\nResult: %i\n", res);

    return 0;
}
