#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    size_t x, y;
    char c;
    const int SIZE = 10000;
    std::vector<std::vector<size_t>> input;
    input.resize(2);

    while (std::cin >> x >> c >> y) {
        input[0].push_back(x);
        input[1].push_back(y);
    }

    size_t N = input[0].size();
    int nSafeCoords = 0;
    for (int i=0; i<SIZE; ++i) {
        for (int j=0; j<SIZE; ++j) {
            std::vector<int> distances;
            for (int k=0; k<N; ++k) {
                int dx = i-input[0][k];
                int dy = j-input[1][k];
                int dist = abs(dx) + abs(dy);
                distances.push_back(dist);
            }
            
            int dist = 0;
            for (int k=0; k<N; ++k) {
                dist += distances[k];
            }

            if (dist < 10000) {
                nSafeCoords++;
            }
        }
    }

    std::cout << "Safe zone " << nSafeCoords << std::endl;
    
    // for (int i=0; i<grid.size(); ++i) {
    //     for (int j=0; j<grid[0].size(); ++j) {
    //         std::cout << grid[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}
