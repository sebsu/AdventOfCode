//#include <sstream>
#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
#include <string>

using namespace std;

int main(){
    string instrLine;
    unsigned long int sumReal = 0;
    int roomId;
    string roomName;
    // Get the entire line
    getline(cin, instrLine);
    while (!instrLine.empty()){
        int alphabet[26] = {};

        // Extract the data and store them as strings.
        string name = instrLine.substr(0, instrLine.find_first_of("0123456789"));
        string idStr = instrLine.substr(instrLine.find_first_of("0123456789"),
                                     instrLine.find_first_of("["));
        string checksum = instrLine.substr(instrLine.find_first_of("[")+1, 5);

        // Convert the id string to an int
        int id = stoi(idStr, nullptr);

        // Save the number of letters
        for (unsigned int i=0; i<name.length(); ++i){
            if (name[i]=='-')
                continue;
            alphabet[name[i]-97] += 1;
        }

        // Rotate name
        string rotatedName = "";
        for (unsigned int i=0; i<name.length(); ++i){
            if (name[i]=='-'){
                rotatedName += " ";
                continue;
            }
            rotatedName += 'a' + ((name[i]-97)+id)%26;
        }
        
        // Save the most common letters
        int maxVal[5] = {};
        int maxChar[5] = {};
        for (int i=0; i<26; ++i){
            for (int j=0; j<5; ++j){
                if (alphabet[i]>maxVal[j]){
                    if (j==0){
                        maxVal[j] = alphabet[i];
                        maxChar[j] = i;
                    } else {
                        maxVal[j-1] = maxVal[j];
                        maxChar[j-1] = maxChar[j];
                        maxVal[j] = alphabet[i];
                        maxChar[j] = i;
                    }
                }
            }
        }

        // Build the verify string
        string verify = "";
        for (int i=4; i>=0; --i){
            verify += 'a' + maxChar[i];
        }

        // Add to the total count if the checksum is correct
        if (verify.compare(checksum) == 0){
            if (rotatedName.find("north")!=string::npos && rotatedName.find("pole")!=string::npos){
                roomId = id;
                roomName = rotatedName;
            }
            sumReal += id;
        }

        // Go to the next line
        getline(cin, instrLine);
    }

    cout << roomId << " " << roomName << endl;
    cout << sumReal << endl;
    
    return 0;
}
