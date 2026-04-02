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

    char c;
    in >> c;

    if (in && c != dest.expected) {
        in.setstate(std::ios::failbit);
    }

    return in;
}


struct KeyIO {
    std::string& ref;
} ;

std::istream& operator>>(std::istream& in, KeyIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    dest.ref.clear();
    char c;

    // НЕ пропускаем пробелы - читаем следующий символ как есть
    if (in.get(c) && std::isalnum(static_cast<unsigned char>(c))) {
        dest.ref += c;
        while (in.get(c) && std::isalnum(static_cast<unsigned char>(c))) {
            dest.ref += c;
        }
        // Возвращаем последний прочитанный символ обратно, если он не буква/цифра
        if (!std::isalnum(static_cast<unsigned char>(c))) {
            in.putback(c);
        }
    }

    std::cerr << "KeyIO read: [" << dest.ref << "]" << std::endl;

    if (dest.ref.empty()) {
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

    char c;
    if (!(in >> c) || c != '"') {
        in.setstate(std::ios::failbit);
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

    in >> std::ws;
    std::string num;
    char c;

    while (in.get(c) && c != ':') {
        num += c;
    }
    in.putback(':');

    bool valid = false;

    size_t dotPos = num.find('.');
    if (dotPos != std::string::npos) {
        bool hasDigitBefore = dotPos > 0 && std::isdigit(static_cast<unsigned char>(num[dotPos - 1]));
        bool hasDigitAfter = dotPos + 1 < num.length() && std::isdigit(static_cast<unsigned char>(num[dotPos + 1]));

        if (hasDigitBefore && hasDigitAfter) {
            size_t expPos = num.find_first_of("eE");
            if (expPos != std::string::npos && expPos > dotPos) {
                if (expPos + 1 < num.length()) {
                    char sign = num[expPos + 1];
                    size_t startExp = expPos + 1;
                    if (sign == '+' || sign == '-') {
                        startExp++;
                    }
                    if (startExp < num.length() && std::isdigit(static_cast<unsigned char>(num[startExp]))) {
                        valid = true;
                    }
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

    in >> std::ws;
    std::string temp;
    char c;

    while (in.get(c) && c != ':') {
        temp += c;
    }
    in.putback(':');

    char first = in.get();
    char second = in.get();

    bool lastIsL = (temp.back() == 'l' || temp.back() == 'L');
    bool preLastIsL = (temp[temp.size() - 2] == 'l' || temp[temp.size() - 2] == 'L');
    if (temp.size() >= 2 && lastIsL && preLastIsL) {
        temp.pop_back();
        temp.pop_back();
        try {
            dest.ref = std::stoll(temp);
        }
        catch (...) {
            in.setstate(std::ios::failbit);
        }
    }
    else {
        in.setstate(std::ios::failbit);
    }

    return in;
}


std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        std::cerr << "sentry failed" << std::endl;
        return in;
    }

    DataStruct temp;

    std::cerr << "Trying to read '(' and ':'" << std::endl;
    if (!(in >> DelimiterIO{'('} >> DelimiterIO{':'})) {
        std::cerr << "Failed to read '(' or ':'" << std::endl;
        return in;
    }
    std::cerr << "Successfully read '(' and ':'" << std::endl;

    for (int i = 0; i < 3; ++i) {
        std::cerr << "Reading field " << i << std::endl;

        std::string key;
        in >> KeyIO{key};
        std::cerr << "Read key: [" << key << "]" << std::endl;

        if (key == "key1") {
            std::cerr << "Reading key1 as DoubleSciIO" << std::endl;
            in >> DoubleSciIO{temp.key1};
        }
        else if (key == "key2") {
            std::cerr << "Reading key2 as LongLongIO" << std::endl;
            in >> LongLongIO{temp.key2};
        }
        else if (key == "key3") {
            std::cerr << "Reading key3 as StringIO" << std::endl;
            in >> StringIO{temp.key3};
        }
        else {
            std::cerr << "Unknown key: " << key << std::endl;
            in.setstate(std::ios::failbit);
            break;
        }

        if (!in) {
            std::cerr << "Failed to read value for key: " << key << std::endl;
            break;
        }
        std::cerr << "Successfully read value for key: " << key << std::endl;

        if (i < 2) {
            std::cerr << "Reading ':' separator" << std::endl;
            in >> DelimiterIO{':'};
            if (!in) {
                std::cerr << "Failed to read ':' separator" << std::endl;
                break;
            }
        }
    }

    std::cerr << "Trying to read ')'" << std::endl;
    if (in >> DelimiterIO{')'}) {
        std::cerr << "Successfully read ')'" << std::endl;
        dest = temp;
        std::cerr << "DataStruct parsed successfully!" << std::endl;
    } else {
        std::cerr << "Failed to read ')'" << std::endl;
    }

    return in;
}


class iofmtguard {
private:
    std::basic_ios<char>& s_;
    std::streamsize width_;
    char fill_;
    std::streamsize precision_;
    std::ios::fmtflags fmt_;
public:
    iofmtguard(std::basic_ios<char>& s) : s_(s) {
        width_ = s.width();
        fill_ = s.fill();
        precision_ = s.precision();
        fmt_ = s.flags();
    }

    ~iofmtguard() {
        s_.width(width_);
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }
} ;


std::ostream& operator<<(std::ostream& out, const DataStruct& source) {
    iofmtguard guard(out);

    out << "(:key1 ";
    out << std::scientific << std::setprecision(1) << source.key1;

    out << ":key2 " << source.key2 << "ll";
    out << ":key3 \"" << source.key3 << "\":)";

    return out;
}


bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (std::abs(a.key1 - b.key1) > 1e-9) {
        return a.key1 < b.key1;
    }
    if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }
    return a.key3.length() < b.key3.length();
}


int main(void) {
    std::vector<DataStruct> data;
    std::string line;

    std::cerr << "Program started. Enter data:" << std::endl;

    while (std::getline(std::cin, line)) {
        std::cerr << "Read line: [" << line << "]" << std::endl;

        if (line.empty()) {
            std::cerr << "Line is empty, skipping" << std::endl;
            continue;
        }

        std::istringstream iss(line);
        DataStruct temp;

        if (iss >> temp) {
            std::cerr << "Successfully parsed!" << std::endl;
            data.push_back(temp);
        } else {
            std::cerr << "Failed to parse line" << std::endl;
        }
    }

    std::cerr << "Total parsed: " << data.size() << " records" << std::endl;

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
