#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>
#include <vector>

using namespace std::placeholders;

int sum(int a, int b) {
    return a + b;
}

struct Counter {
    int count = 0;
    void operator()(int) {
        count++;
    }
} ;

int main(void) {
    auto plusFive = std::bind(sum, 5, _1);

    std::cout << plusFive(10) << std::endl;


    auto expr = std::bind(
        std::multiplies<int>(),
        std::bind(std::plus<int>(), _1, _2),
        std::bind(std::minus<int>(), _1, _2)
    );

    std::cout << expr(5, 2) << std::endl;

    std::vector<int> v{1, 2, 3, 4};
    std::for_each(v.begin(), v.end(), [](int x){
        std::cout << x << " ";
    });
    std::cout << std::endl;

    Counter c = std::for_each(v.begin(), v.end(), Counter());
    std::cout << c.count << std::endl;


    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << sum << std::endl;
}
