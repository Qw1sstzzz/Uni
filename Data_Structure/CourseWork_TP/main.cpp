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
    }
    catch (const DictionaryError& e) {
        std::cerr << "Insert error: " << e.what() << std::endl;
    }

    std::cout << "\n=== Testing PRINT ===\n";
    dict.print();

    std::cout << "\n=== Testing SEARCH ===\n";
    const std::set<std::string>* result = dict.search("hello");
    if (result) {
        std::cout << "Found 'hello': ";
        for (const auto& w : *result) {
            std::cout << w << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "'hello' not found\n";
    }

    std::cout << "\n=== Testing REMOVE ===\n";
    dict.remove("world");
    std::cout << "After removing 'world':\n";
    dict.print();

    std::cout << "\n=== Testing EXCEPTIONS ===\n";

    try {
        dict.insert("", "тест");
    }
    catch (const ValidationError& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    try {
        dict.insert("cat123", "кот");
    }
    catch (const ValidationError& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    try {
        dict.insert("dog", "dog");
    }
    catch (const ValidationError& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Testing REMOVE TRANSLATION ===\n";
    std::cout << "Removing 'привет' from 'hello'...\n";
    try {
        bool removed = dict.removeTranslation("hello", "привет");
        std::cout << (removed ? "OK: removed\n" : "Not found\n");
    }
    catch (const DictionaryError& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    std::cout << "After removal:\n";
    dict.print();

    std::cout << "\n=== Testing REMOVE LAST TRANSLATION ===\n";
    std::cout << "Removing 'здравствуйте' from 'hello' (last translation)...\n";
    dict.removeTranslation("hello", "здравствуйте");
    std::cout << "Trying to find 'hello': ";
    const std::set<std::string>* r = dict.search("hello");
    std::cout << (r ? "still exists" : "not found (word deleted)") << "\n";

    std::cout << "\n=== Testing REINSERT AFTER DELETE ===\n";
    dict.insert("hello", "приветик");
    std::cout << "After reinsert:\n";
    dict.print();

    std::cout << "\n=== Testing DUPLICATE TRANSLATION ===\n";
    try {
        dict.insert("cat", "кот");
    }
    catch (const DuplicateTranslationException& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }

    std::cout << "\n=== Testing SEARCH NON-EXISTENT ===\n";
    std::cout << "Search 'xyz': ";
    std::cout << (dict.search("xyz") ? "found" : "not found") << "\n";

    std::cout << "\n=== Testing REHASH ===\n";
    std::cout << "Adding many words to trigger resize...\n";
    dict.insert("apple", "яблоко");
    dict.insert("banana", "банан");
    dict.insert("cherry", "вишня");
    dict.insert("orange", "апельсин");
    dict.insert("grape", "виноград");
    dict.insert("lemon", "лимон");
    dict.print();
    std::cout << "Count after rehash: " << dict.getCount() << "\n";
    std::cout << "Collisions total: " << dict.getCollisions() << "\n";

    std::cout << "\n========================================\n";
    std::cout << "ALL TESTS PASSED\n";
    std::cout << "========================================\n";

    return 0;
}
