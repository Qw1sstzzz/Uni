#include <iostream>
#include <functional>

using namespace std::placeholders;

int sum(int a, int b) {
    return a + b;
}

int main(void) {
    auto plusFive = std::bind(sum, 5, _1);

    std::cout << plusFive(10) << std::endl;


    auto expr = std::bind(
        std::multiplies<int>(),
        std::bind(std::plus<int>(), _1, _2),
        std::bind(std::minus<int>(), _1, _2)
    );

    std::cout << expr(5, 2);
}
