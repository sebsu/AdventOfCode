#include <iostream>
#include <map>

int getMetadata() {
    int sum = 0;
    int nChildren;
    int nMetadata;
    std::map<int, int> children;
    std::cin >> nChildren >> nMetadata;
    for (int i=0; i<nChildren; ++i) {
        children[i] = getMetadata();
    }

    if (nChildren == 0) {
        int m;
        for (int i=0; i<nMetadata; ++i) {
            std::cin >> m;
            sum += m;
        }
    } else {
        int entry;
        for (int i=0; i<nMetadata; ++i) {
            std::cin >> entry;
            if (0 < entry && entry <= nChildren) {
                sum += children[entry-1];
            }
        }
    }

    return sum;
}

int main() {
    int sum;
    sum = getMetadata();
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}
