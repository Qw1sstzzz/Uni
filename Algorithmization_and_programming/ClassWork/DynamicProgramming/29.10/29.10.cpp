#include <iostream>
#include <cstring>
#include <cctype>

const int MAX_SIZE = 1000;

void commonChars(char* dest, const char* s1, const char* s2) {
    bool seen[256] = {};
    int dest_cnt = 0;

    for (int i = 0; s1[i] != '\0'; i++) {
        char symb_s1 = s1[i];
        if (seen[static_cast<unsigned char>(symb_s1)]) {
                continue;
        }

        bool found = false;
        for (int j = 0; s2[j] != '\0'; j++) {
            if (s2[j] == symb_s1) {
                found = true;
                break;
            }
        }


        if (found) {
            if (dest_cnt >= MAX_SIZE - 1) {
                break;
            }

            dest[dest_cnt++] = symb_s1;
            seen[symb_s1] = true;
        }
    }

    dest[dest_cnt] = '\0';
}   


bool isOrderedString(const char* str) {
    if ((str[0] == '\0') || (str[1] == '\0')) {
        return true;
    }
    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i] < str[i - 1]) {
            return false;
        }
    }
    return true;    
}


bool isHexadecimalNumber(const char* str) {
    int i = 0;
    if (str[i] == '\0') {
        return false;
    }

    if ((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X')) && (str[2] != '0')) {
        i = 2;
    }

    while (str[i] != '\0') {
        char symb_s = isupper(str[i]);
        if ((symb_s >= 'F') || (symb_s < '0')) {
            return false;
        }   
        i++;
    }
    return true;
}


int main(void) {
    char str1[MAX_SIZE], str2[MAX_SIZE], result[MAX_SIZE];
    std::cout << "Enter your first string:\n";
    std::cin >> str1;
    
    std::cout << "Enter your second string:\n";
    std::cin >> str2;

    commonChars(result, str1, str2);

    std::cout << "Result:\n" << result << std::endl;

    bool is_ordered = isOrderedString(result);
    std::cout << "\nString is ordered?\n";
    (is_ordered == 1 ? std::cout << "True!!!\n" : std::cout << "False(((\n");

    bool is_hexade = isHexadecimalNumber(result);
    std::cout << "\nString is written in 16 sys?\n";
    (is_hexade == 1 ? std::cout << "True!!!\n" : std::cout << "False(((\n");

    return 0;
}