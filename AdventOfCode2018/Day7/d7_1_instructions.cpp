#include <iostream>
#include <string>
#include <map>
#include <vector>

void cleanSteps(std::map<char, std::vector<char>> *steps, char step) {
    steps->erase(step);
    for (auto pair : *steps) {
        char s = pair.first;
        std::vector<char> deps = pair.second;
        for (int i=0; i<deps.size(); ++i) {
            if (deps[i]==step) {
                steps->at(s).erase(steps->at(s).begin()+i);
                break;
            }
        }
    }
}


int main() {
    std::string line;
    std::map<char, std::vector<char>> steps;
    char dep, step;

    while (std::getline(std::cin, line)) {
        dep = line[5];
        step = line[36];
        if (steps.find(step) != steps.end()) {
            steps[step].emplace_back(dep);
        } else {
            steps.emplace(step, std::vector<char>(1, dep));
        }
        if (steps.find(dep) == steps.end()) {
            steps.emplace(dep, std::vector<char>(0, ' '));
        }
    }
    
    // for (auto pair : steps) {
    //     std::cout << pair.first << ": ";
    //     std::vector<char> deps = pair.second;
    //     for (char dep : deps) {
    //         std::cout << dep << " ";
    //     }
    //     std::cout << std::endl;
    // }

    bool isDone = false;
    while (!isDone) {
        std::vector<char> avail;

        for (auto pair : steps) {
            step = pair.first;
            std::vector<char> deps = pair.second;
            if (deps.empty()) {
                avail.emplace_back(step);
            }
        }
        
        if (avail.size()>1) {
            char first = 'Z';
            for (char s : avail) {
                if (s < first) {
                    first = s;
                }
            }
            std::cout << first;
            cleanSteps(&steps, first);
        } else if (avail.size() <= 0) {
            std::cerr << " Avail size <= 0" << std::endl;
            isDone = true;
        } else {
            std::cout << avail[0];
            cleanSteps(&steps, avail[0]);
        }

        if (steps.size() < 1) {
            isDone = true;
        }
    }

    std::cout << std::endl;
    
    return 0;
}
