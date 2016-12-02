#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

int main(){
    string instrLine, instr;
    int posi = 5;
    int code = 0;
    // Get the entire line
    getline(cin, instrLine);
    while (!instrLine.empty()){
        instr = instrLine;
        while (!instr.empty()){
            if (instr[0] == 'U')
                posi = posi <= 3 ? posi : posi-3;
            if (instr[0] == 'D')
                posi = posi >= 7 ? posi : posi+3;
            if (instr[0] == 'R')
                posi = posi%3 == 0 ? posi : posi+1;
            if (instr[0] == 'L')
                posi = posi%3 == 1 ? posi : posi-1;

            instr.erase(0, min(1,(int)instr.length()));
        }

        code = code*10 + posi;
        getline(cin, instrLine);
    }

    cout << code << endl;
    
    return 0;
}
