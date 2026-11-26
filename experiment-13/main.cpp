#include <iostream>
#include <vector>

import pipeline;

int main() {
    const std::vector<int> data{-5, 10, 20, -3, 15, 30};
    const std::vector<int> result = processData(data);

    std::cout << "Original Data: ";
    for (int value : data)
        std::cout << value << ' ';

    std::cout << "\nProcessed Data: ";
    for (int value : result)
        std::cout << value << ' ';
    std::cout << '\n';
}
