#include <iostream>
#include <limits>
#include <fstream>
#include <iomanip>
#include <string>

void enterNum() {
    int num;
    std::cin >> num;
    if (std::cin.good()) {
        std::cout << "Entered: " << num << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else if (std::cin.eof()) {
        std::cerr << "EOF\n";
    }
    else if (std::cin.fail()) {
        std::cerr << "ERROR: Enter int\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else if (std::cin.bad()) {
        std::cerr << "BAD STREAM ERROR\n";
    }
}

std::ostream& customManipulatorBrackets(std::ostream& os) {
    os << std::unitbuf;
    return os;
}

void process_word_with_braces(std::istream& is, std::ostream& os) {
    std::string word;
    while (is >> word) {
        os << "{" << word << "} ";
    }
}

int main(void) {
    enterNum();

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::string input;
    std::cout << "Enter text: ";
    std::getline(std::cin, input);
    
    if (!input.empty()) {
        std::stringstream str(input);
        std::cout << "Text before Manipulator: ";
        process_word_with_braces(str, std::cout);
        std::cout << customManipulatorBrackets << " text after." << std::endl;
    } 
    else {
        std::cout << "No text entered." << std::endl;
    }
    return 0;
}