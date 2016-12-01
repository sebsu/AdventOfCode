#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

int main(){
    string instr;
    // How far in each direction.
    int path[4] = {0,0,0,0};
    // The starting direction is "up"
    int dir = 0;
    
    // Get the entire line
    getline(cin, instr);
    while (!instr.empty()){
        //cout << "Instruction: " <<instr << endl;
        // Can only turn right or left.
        if (instr[0] == 'R'){
            dir = (dir+1)%4;
        }
        if (instr[0] == 'L'){
            dir = (dir+4-1)%4;
        }
        // Extract the number.
        string num = instr;
        int next = num.find_first_of(',');
        next = next==-1 ? num.length() : next;
        num.erase(next, num.length());
        num.erase(0,1); // Delete the 'L' or 'R'
        //cout << num << endl;
        int dist = stoi(num, nullptr); // Convert to an int
        path[dir] += dist;

        // Deletes the current instruction
        next = instr.find_first_of(' ')+1;
        next = next==0 ? instr.length() : next;
        instr.erase(0, next);
    }
    //cout << path[0] << " " << path[1] << " " << path[2] << " " << path[3] << endl;
    // Add the lengths
    int vert = abs(path[0]-path[2]);
    int horiz = abs(path[1]-path[3]);
    int len = vert + horiz;
    cout << len << endl;
    
    return 0;
}
