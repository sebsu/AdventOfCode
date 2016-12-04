//#include <sstream>
#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
#include <string>

using namespace std;

int main(){
    string instrLine;
    unsigned long int numTri = 0;
    int side = 0;
    int tri1[3] = {};
    int tri2[3] = {};
    int tri3[3] = {};
    // Get the entire line
    getline(cin, instrLine);
    while (!instrLine.empty()){
        // Extract the numbers and store them as strings.
        instrLine.erase(0, instrLine.find_first_of("0123456789"));
        int numLen = instrLine.find_first_of(' ');
        string side1Str = instrLine.substr(0,numLen);

        instrLine.erase(0, instrLine.find_first_of("0123456789", numLen));
        numLen = instrLine.find_first_of(' ');
        string side2Str = instrLine.substr(0,numLen);

        instrLine.erase(0, instrLine.find_first_of("0123456789", numLen));
        string side3Str = instrLine;

        // Convert the strings to ints.
        tri1[side] = stoi(side1Str, nullptr);
        tri2[side] = stoi(side2Str, nullptr);
        tri3[side] = stoi(side3Str, nullptr);

        if (side == 2){ // Once all three sides has been read, check if valid.
            if (tri1[0]+tri1[1] > tri1[2] &&
                tri1[0]+tri1[2] > tri1[1] &&
                tri1[1]+tri1[2] > tri1[0]){
                ++numTri;
            }
            if (tri2[0]+tri2[1] > tri2[2] &&
                tri2[0]+tri2[2] > tri2[1] &&
                tri2[1]+tri2[2] > tri2[0]){
                ++numTri;
            }
            if (tri3[0]+tri3[1] > tri3[2] &&
                tri3[0]+tri3[2] > tri3[1] &&
                tri3[1]+tri3[2] > tri3[0]){
                ++numTri;
            }
        }

        side = (side+1)%3;
        
        getline(cin, instrLine);
    }

    cout << numTri << endl;
    
    return 0;
}
