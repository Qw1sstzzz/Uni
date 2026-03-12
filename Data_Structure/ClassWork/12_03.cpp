#include <iostream>
#include <limits>
#include <fstream>

void enterNum() {
    int num;
    std::cin >> num;
    if (std::cin.good()) {
        std::cout << "Entered: " << num << std::endl;
    }
    else if (std::cin.eof()) {
        std::cerr << "EOF\n";
    }
    else if (std::cin.fail()) {
        std::cerr << "ERROR: Enter int\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max());
    }
    else if (std::cin.bad()) {
        std::cerr << "BAD STREAM ERROR\n";
    }
}

int main(void) {
    enterNum();
    return 0;
}