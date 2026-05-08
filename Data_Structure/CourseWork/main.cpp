#include <iostream>
#include <windows.h>
#include "HashDictionary.h"
#include "Errors.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    HashDictionary dict;

    std::cout << "=== Testing INSERT ===\n";

    try {
        dict.insert("hello", "привет");
        dict.insert("hello", "здравствуйте");
        dict.insert("world", "мир");
        dict.insert("cat", "кот");
        std::cout << "Insert successful\n";
    } catch (const DictionaryError& e) {
        std::cerr << "Insert error: " << e.what() << std::endl;
    }

    std::cout << "\n=== Testing PRINT ===\n";
    dict.print();

    std::cout << "\n=== Testing SEARCH ===\n";
    const TranslationList* result = dict.search("hello");
    if (result) {
        std::cout << "Found 'hello': ";
        result->print();
        std::cout << std::endl;
    } else {
        std::cout << "'hello' not found\n";
    }

    std::cout << "\n=== Testing REMOVE ===\n";
    dict.remove("world");
    std::cout << "After removing 'world':\n";
    dict.print();

    std::cout << "\n=== Testing EXCEPTIONS ===\n";

    try { dict.insert("", "тест"); }
    catch (const ValidationError& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    try { dict.insert("cat123", "кот"); }
    catch (const ValidationError& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    try { dict.insert("dog", "dog"); }
    catch (const ValidationError& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== All tests done ===\n";
    return 0;
}
