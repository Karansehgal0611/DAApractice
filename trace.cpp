#include <iostream>
#include <vector>

int computeTrace(const std::vector<std::vector<int>>& matrix) {
    int trace = 0;
    for (int i = 0; i < 3; ++i) {
        trace += matrix[i][i];
    }
    return trace;
}

int main() {
    int t;
    std::cin >> t;

    std::cin.ignore();

    std::vector<int> traces;

    for (int testCase = 1; testCase <= t; ++testCase) {
        std::vector<std::vector<int>> matrix(3, std::vector<int>(3));
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cin >> matrix[i][j];
            }
        }
        int trace = computeTrace(matrix);
       std::cout<<trace<<"\n";

    }



    return 0;
}

