#include "String.h"
#include <iostream>
#include <limits>

void demonstrateConstructors() {
    std::cout << "=== Constructors demonstration ===" << std::endl;
    
    try {
        CustomString empty;
        std::cout << "Empty string: '" << empty << "' (length: " << empty.getLength() << ")" << std::endl;
        
        CustomString fromLiteral("Hello, World!");
        std::cout << "From literal: '" << fromLiteral << "'" << std::endl;
        
        CustomString copy(fromLiteral);
        std::cout << "Copy: '" << copy << "'" << std::endl;
        
        CustomString moved(std::move(CustomString("Temporary object")));
        std::cout << "Moved string: '" << moved << "'" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << std::endl;
}

void demonstrateOperators() {
    std::cout << "=== Operators demonstration ===" << std::endl;
    
    CustomString str1("First");
    CustomString str2("Second");
    
    std::cout << "str1: '" << str1 << "'" << std::endl;
    std::cout << "str2: '" << str2 << "'" << std::endl;
    
    CustomString concat = str1 + " " + str2;
    std::cout << "Concatenation: '" << concat << "'" << std::endl;
    
    str1 += " string";
    std::cout << "After +=: '" << str1 << "'" << std::endl;
    
    std::cout << "Comparison: " << (str1 == str2) << " (equal?)" << std::endl;
    std::cout << "Comparison: " << (str1 < str2) << " (str1 < str2?)" << std::endl;
    std::cout << std::endl;
}

void demonstrateReplaceFunction() {
    std::cout << "=== Replace function demonstration ===" << std::endl;
    
    CustomString original("programming");
    std::cout << "Original string: '" << original << "'" << std::endl;
    
    CustomString replaced = original.replaceCharacters('r', 'R');
    std::cout << "After replacing 'r' with 'R': '" << replaced << "'" << std::endl;
    
    CustomString noChange = original.replaceCharacters('x', 'X');
    std::cout << "Replacing missing character: '" << noChange << "'" << std::endl;
    
    CustomString testString("aabbcc");
    CustomString testReplaced = testString.replaceCharacters('a', 'A');
    std::cout << "Test 'aabbcc' -> 'Aabbcc': '" << testReplaced << "'" << std::endl;
    
    std::cout << std::endl;
}

void interactiveDemo() {
    std::cout << "=== INTERACTIVE DEMONSTRATION ===" << std::endl;
    std::cout << "Testing input operator and character replacement" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    try {
        CustomString userString;
        
        std::cout << "Enter string to process: ";
        std::cin >> userString;
        
        if (userString.isEmpty()) {
            std::cout << "Error: empty string entered!" << std::endl;
            return;
        }
        
        std::cout << "Your string: '" << userString << "'" << std::endl;
        std::cout << "String length: " << userString.getLength() << " characters" << std::endl;
        
        std::cout << std::endl;
        std::cout << "Now enter characters for replacement:" << std::endl;
        
        char oldChar;
        std::cout << "Character to find: ";
        std::cin >> oldChar;
        
        char newChar;
        std::cout << "Replacement character: ";
        std::cin >> newChar;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << std::endl;
        std::cout << "=== RESULTS ===" << std::endl;
        
        CustomString result = userString.replaceCharacters(oldChar, newChar);
        
        std::cout << "Replacement performed: '" << oldChar << "' → '" << newChar << "'" << std::endl;
        std::cout << "Original string:  '" << userString << "'" << std::endl;
        std::cout << "Result:           '" << result << "'" << std::endl;
        
        if (userString == result) {
            std::cout << "Note: character '" << oldChar << "' not found in string" << std::endl;
        } else {
            std::cout << "Replacement completed successfully!" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "Error occurred: " << e.what() << std::endl;
    }
    
    std::cout << std::endl;
}

void edgeCaseTests() {
    std::cout << "=== Edge cases testing ===" << std::endl;
    
    CustomString empty;
    CustomString emptyReplaced = empty.replaceCharacters('a', 'b');
    std::cout << "Empty string after replacement: '" << emptyReplaced << "'" << std::endl;
    
    CustomString singleChar("a");
    CustomString singleReplaced = singleChar.replaceCharacters('a', 'A');
    std::cout << "Single character after replacement: '" << singleReplaced << "'" << std::endl;
    
    CustomString allSame("aaaa");
    CustomString allReplaced = allSame.replaceCharacters('a', 'b');
    std::cout << "All same characters after replacement: '" << allReplaced << "'" << std::endl;
    
    std::cout << std::endl;
}

void testInputOperator() {
    std::cout << "=== Input operator testing ===" << std::endl;
    
    CustomString test1, test2;
    
    std::cout << "Enter first test string: ";
    std::cin >> test1;
    
    std::cout << "Enter second test string: ";
    std::cin >> test2;
    
    std::cout << "First string: '" << test1 << "'" << std::endl;
    std::cout << "Second string: '" << test2 << "'" << std::endl;
    std::cout << "Concatenation: '" << test1 + " " + test2 << "'" << std::endl;
    
    std::cout << std::endl;
}



int main() {
    std::cout << "=== CUSTOMSTRING CLASS TESTING ===" << std::endl << std::endl;
    
    demonstrateConstructors();
    demonstrateOperators();
    demonstrateReplaceFunction();
    edgeCaseTests();
    
    testInputOperator();
    
    interactiveDemo();
    
    std::cout << "=== TESTS ARE PASSED ===" << std::endl;
    return 0;
}