#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

int main(){
    string instrLine, instr;
    int avail[] = {0,0,1,0,0,
                   0,1,1,1,0,
                   1,1,1,1,1,
                   0,1,1,1,0,
                   0,0,1,0,0};
    int posi = 10;
    string codeStr = "";
    // Get the entire line
    getline(cin, instrLine);
    while (!instrLine.empty()){
        instr = instrLine;
        while (!instr.empty()){

            if (instr[0] == 'U')
                posi = ((posi-5)>=0 && avail[posi-5]) ? posi-5 : posi;
            if (instr[0] == 'D')
                posi = ((posi+5)<=24 && avail[posi+5]) ? posi+5 : posi;
            if (instr[0] == 'R')
                posi = (((posi+1)%5!=0) && avail[posi+1]) ? posi+1 : posi;
            if (instr[0] == 'L')
                posi = ((posi%5!=0) && avail[posi-1]) ? posi-1 : posi;

            instr.erase(0, min(1,(int)instr.length()));
        }

        int pos = 0;
        for (int i=0; i<=posi; ++i){
            pos+=avail[i];
        }

        stringstream posStr;
        posStr << hex << pos;
        codeStr += posStr.str();
        getline(cin, instrLine);
    }

    cout << codeStr << endl;
    
    return 0;
}
