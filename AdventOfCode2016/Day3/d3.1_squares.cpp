//#include <sstream>
#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
#include <string>

using namespace std;

int main(){
    string instrLine;
    unsigned long int numTri = 0;
    // Get the entire line
    getline(cin, instrLine);
    while (!instrLine.empty()){
        int side1 = 0;
        int side2 = 0;
        int side3 = 0;

        instrLine.erase(0, instrLine.find_first_of("0123456789"));
        int numLen = instrLine.find_first_of(' ');
        string side1Str = instrLine.substr(0,numLen);
        
        instrLine.erase(0, instrLine.find_first_of("0123456789", numLen));
        numLen = instrLine.find_first_of(' ');
        string side2Str = instrLine.substr(0,numLen);
        
        instrLine.erase(0, instrLine.find_first_of("0123456789", numLen));
        string side3Str = instrLine;

        side1 = stoi(side1Str,nullptr);
        side2 = stoi(side2Str,nullptr);
        side3 = stoi(side3Str,nullptr);

        if (side1+side2 > side3 && side1+side3 > side2 && side2+side3 > side1){
            ++numTri;
        }
        
        getline(cin, instrLine);
    }

    cout << numTri << endl;
    
    return 0;
}
