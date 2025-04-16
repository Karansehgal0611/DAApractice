#include <iostream>
#include <vector>
#include <sstream>

void printArray(const std::vector<int>& arr) {
    for (int element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    int T;
    std::cin >> T;
    std::cin.ignore();


    std::vector<std::vector<int>> arrays(T);


    for (int i = 0; i < T; ++i) {
        std::string line;
        std::getline(std::cin, line);

        std::stringstream ss(line);
        int num;
        while (ss >> num) {
            arrays[i].push_back(num);
        }
    }

    for (int i = 0; i < T; ++i) {
        printArray(arrays[i]);
    }

    return 0;
}
