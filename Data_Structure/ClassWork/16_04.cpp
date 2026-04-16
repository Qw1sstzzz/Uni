#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std::placeholders;


int main() {
    std::vector<int> data = {15, 8, 23, 4, 42, 7, 16, 3, 9, 12};

    auto it1 = std::find_if(data.begin(), data.end(),
        std::bind(std::greater<int>(), _1, 20));
    std::cout << *it1 << std::endl;

    struct isEven {
        bool operator()(int x) const {
            return x % 2 == 0;
        }
    } ;

    int evenCount = std::count_if(data.begin(), data.end(), isEven());
    std::cout << evenCount << std::endl;


    struct isNegative {
        bool operator()(int x) const {
            return x < 0;
        }
    } ;

    bool noNegative = std::none_of(data.begin(), data.end(), isNegative());
    std::cout << "Have we got any negative?: " << noNegative << std::endl;
}
