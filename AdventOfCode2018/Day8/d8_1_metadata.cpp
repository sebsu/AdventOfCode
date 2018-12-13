#include <iostream>

void getMetadata(int* sum) {
    int nChildren;
    int nMetadata;
    std::cin >> nChildren >> nMetadata;
    for (int i=0; i<nChildren; ++i) {
        getMetadata(sum);
    }
    for (int i=0; i<nMetadata; ++i) {
        int m;
        std::cin >> m;
        *sum += m;
    }
}

int main() {
    int sum = 0;
    getMetadata(&sum);
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}
