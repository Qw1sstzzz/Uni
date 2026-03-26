#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

int main(void) {
    std::vector<int> v = {1, 2, 0, 4};
    std::vector<int>::iterator it = v.begin();
    std::cout << *it << " ";
    ++it;
    std::cout << *it << std::endl;
    return 0;
}