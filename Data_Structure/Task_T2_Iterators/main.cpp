#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <limits>

struct DataStruct {
    double key1;
    long long key2;
    std::string key3;
} ;

struct DelimiterIO {
    char expected;
} ;

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    char c = '0';
    in >> c;

    if (in && c != dest.expected) {
        in.setstate(std::ios::failbit);
    }

    return in;
}


struct StringIO {
    std::string& ref;
} ;

std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    in >> DelimiterIO{'"'};
    if (!in) {
        return in;
    }

    std::getline(in, dest.ref, '"');

    return in;
}


struct DoubleSciIO {
    double& ref;
} ;

std::istream& operator>>(std::istream& in, DoubleSciIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    std::streampos pos = in.tellg();

    std::string num;
    in >> num;

    if (!in) {
        return in;
    }

    bool valid = false;

    size_t dotPos = num.find('.');
    if (dotPos != std::string::npos) {
        bool hasDigitBefore = dotPos > 0 && std::isdigit(num[dotPos - 1]);
        bool hasDigitAfter = dotPos + 1 < num.length() && std::isdigit(num[dotPos + 1]);
        
        if (hasDigitBefore && hasDigitAfter) {
            size_t expPos = num.find_first_of("eE");
            if (expPos != std::string::npos && expPos > dotPos) {
                char sign = num[expPos + 1];
                size_t startExp = expPos + 1;
                if (sign == '+' || sign == '-') {
                    startExp++;
                }

                if (startExp < num.length() && std::isdigit(num[startExp])) {
                    valid = true;
                }
            }
        }
    
    }

    if (valid) {
        try {
            dest.ref = std::stod(num);
        }
        catch (...) {
            valid = false;
        }
    }

    if (!valid) {
        in.clear();
        in.seekg(pos);
        in.setstate(std::ios::failbit);
    }

    return in;
}


struct LongLongIO {
    long long& ref;
} ;

std::istream& operator>>(std::istream& in, LongLongIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    std::streampos pos = in.tellg();

    in >> dest.ref;
    if (!in) {
        return in;
    }

    char first = in.get();
    char second = in.get();

    bool isValid = (first == 'l' || first == 'L') && (second == 'l' || second == 'L');

    if (!isValid) {
        in.clear();
        in.seekg(pos);
        in.setstate(std::ios::failbit);
    }

    return in;
}

int main(void) {
    std::cout << "Program started" << std::endl;
    
    std::string testString;
    std::cout << "Enter a string in quotes (like \"hello world\"): ";
    std::cin >> StringIO{testString};
    
    std::cout << "You entered: \"" << testString << "\"" << std::endl;
    
    return 0;
}