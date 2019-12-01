#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int fuel(int m) {
    return floor(m/3)-2;
}

int main(int argc, char** argv){
    assert(argc>1);

    FILE* f;
    const int size = 32;    /* Could be smaller. */
    char num[size];
    int mass = 0;
    f = fopen(argv[1], "r");

    while (fgets(num, size, f) != NULL) {
        int fm = fuel(atoi(num));
        while (fm > 0) {
            mass += fm;
            fm = fuel(fm);
        }
    }
    fclose(f);
    printf("%i\n", mass);


    return 0;
}
