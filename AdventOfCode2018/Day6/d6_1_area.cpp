#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <stdlib.h>
#include <map>

int main(int argc, char* argv[]) {
    size_t x, y;
    char c;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<size_t>> input;
    input.resize(2);

    while (std::cin >> x >> c >> y) {
        size_t x_max = std::max(x+1, grid.size());
        grid.resize(x_max);
        
        size_t y_max = std::max(y+1, grid[0].size());
        for (int i=0; i<grid.size(); ++i) {
            grid[i].resize(y_max);
        }
        input[0].push_back(x);
        input[1].push_back(y);
    }

    size_t N = grid.size();
    size_t M = grid[0].size();
    size_t L = input[0].size();
    std::map<int, int> areas;

    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            std::vector<int> distances;
            int shortest = INT_MAX;
            int name = -1;
            for (int k=0; k<L; ++k) {
                int dx = i-input[0][k];
                int dy = j-input[1][k];
                int dist = abs(dx) + abs(dy);
                if (dist < shortest) {
                    shortest = dist;
                    name = k;
                }
                distances.push_back(dist);
            }
            
            int nSameDist = 0;
            for (int k=0; k<L; ++k) {
                nSameDist += (distances[k] == shortest)*1;
            }

            if (nSameDist > 1) {
                grid[i][j] = -1;
            } else {
                grid[i][j] = name;
                if (areas.find(name) != areas.end()) {
                    areas[name]++;
                } else {
                    areas.emplace(name, 1);
                }
            }
        }
    }

    for (int i=0; i<N; i += N-1) {
        for (int j=0; j<M; ++j) {
            areas.erase(grid[i][j]);
        }
    }
    for (int j=0; j<M; j += M-1) {
        for (int i=0; i<N; ++i) {
            areas.erase(grid[i][j]);
        }
    }

    int biggest = 0;
    for (auto pair : areas) {
        int name = pair.first;
        int size = pair.second;
        if (size > biggest) {
            biggest = size;
        }
    }

    std::cout << "Biggest " << biggest << std::endl;
    
    // for (int i=0; i<grid.size(); ++i) {
    //     for (int j=0; j<grid[0].size(); ++j) {
    //         std::cout << grid[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}
