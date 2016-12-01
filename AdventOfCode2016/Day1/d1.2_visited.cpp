#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

int main(){
    // Is a grid really needed?
    // ugh, fine...
    int grid[1000][1000] = {};
    int x = 500, y = 500;
    grid[x][y] = 1;
    
    string instr;
    // How far in each direction.
    int path[4] = {0,0,0,0};
    // The starting direction is "up"
    int dir = 0;
    
    // Get the entire line
    getline(cin, instr);
    while (!instr.empty()){
        cout << "Instruction: " <<instr << endl;
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

        // The position to go to
        int newy = 500 + path[0]-path[2];
        int newx = 500 + path[1]-path[3];

        if (newy != y){
            // Going up or down
            int step = y<newy ? 1 : -1;
            for (int j=y+step; j!=newy; j+=step){
                //cout << x << " " << j << endl;
                if (grid[x][j] == 1){
                    //cout << path[0] << " " << path[1] << " " << path[2] << " " << path[3] << endl;
                    cout << abs(x-500)+abs(j-500) << endl;
                    return 0;
                }
                grid[x][j] = 1;
            }
            grid[x][newy] = 1;
        }else{
            // Going right or left
            int step = x<newx ? 1 : -1;
            for (int i=x+step; i!=newx; i+=step){
                //cout << i << " " << y << endl;
                if (grid[i][y] == 1){
                    //cout << path[0] << " " << path[1] << " " << path[2] << " " << path[3] << endl;
                    cout << abs(i-500)+abs(y-500) << endl;
                    return 0;
                }
                grid[i][y] = 1;
            }
            grid[newx][y] = 1;
        }

        y = newy;
        x = newx;

        // Deletes the current instruction
        next = instr.find_first_of(' ')+1;
        next = next==0 ? instr.length() : next;
        instr.erase(0, next);
    }
    //cout << path[0] << " " << path[1] << " " << path[2] << " " << path[3] << endl;

    // All places were unique
    // Add the lengths
    int vert = abs(path[0]-path[2]);
    int horiz = abs(path[1]-path[3]);
    int len = vert + horiz;
    cout << len << endl;
    
    return 0;
}
