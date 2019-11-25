#include <stdio.h>
#include <string.h>
#include <assert.h>

int calc(char* str) {
    size_t len = strlen(str)-1;
    int sign = (str[0]=='+') ? 1 : -1;
    int out = 0;
    for (int i=1; i<len; ++i) {
        out = out*10 + str[i] - 48;
    }
    return sign*out;
}

int main(int argc, char** argv){
    assert(argc>1);
    FILE* f;
    f = fopen(argv[1], "r");
    int size = 32;
    char num[size];
    int tot = 0;
    while (fgets(num, size, f) != NULL) {
        tot += calc(num);
    }
    fclose(f);
    printf("%i\n", tot);
    return 0;
}
