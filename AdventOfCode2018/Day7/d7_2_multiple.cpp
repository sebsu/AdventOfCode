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
    
    for (auto pair : steps) {
        std::cout << pair.first << ": ";
        std::vector<char> deps = pair.second;
        for (char dep : deps) {
            std::cout << dep << " ";
        }
        std::cout << std::endl;
    }

    int nWorkers = 2;
    int duration = 0;
    std::string res = "";
    std::vector<int> workers(nWorkers, 0);
    std::vector<char> taken(nWorkers, '.');
    bool isDone = false;
    int time = -1;

    while (!isDone) {
        time++;
        std::cout << res << std::endl << time << "\t";
        for (int i=0; i<nWorkers; ++i) {
            if (workers[i]-- <= 0) {
                if (taken[i] != '.') {
                    res = res + taken[i];
                    cleanSteps(&steps, taken[i]);
                }
            } else {
                std::cout << taken[i] << " ";
                continue;
            }
            taken[i] = '.';

            std::vector<char> avail;
            for (auto pair : steps) {
                step = pair.first;
                bool isTaken = false;
                for (int j=0; j<nWorkers; ++j) {
                    if (step == taken[j]) {
                        isTaken = true;
                        break;
                    }
                }
                if (isTaken) {
                    continue;
                }
                std::vector<char> deps = pair.second;
                if (deps.empty()) {
                    avail.emplace_back(step);
                }
            }

            if (avail.size() > 1) {
                char first = 'Z';
                for (char s : avail) {
                    if (s < first) {
                        first = s;
                    }
                }
                workers[i] = (int)first - (int)'A' + duration;
                taken[i] = first;
            } else if (avail.size() == 1) {
                workers[i] = (int)avail[0] -  (int)'A' + duration;
                taken[i] = avail[0];
            }

            if (steps.size() < 1) {
                isDone = true;
            }
            std::cout << taken[i] << " ";
        }
    }

    std::cout << res << std::endl << "Time: " << time << std::endl;;
    
    return 0;
}
