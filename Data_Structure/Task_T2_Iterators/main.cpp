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
    if (in.get(c) && std::isalnum(static_cast<unsigned char>(c))) {
        dest.ref += c;
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

    if (!valid) {
        in.setstate(std::ios::failbit);
        return in;
    }


    try {
        dest.ref = std::stod(num);
    }
    catch (...) {
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

    bool lastIsL = (temp.back() == 'l' || temp.back() == 'L');
    bool preLastIsL = (temp[temp.size() - 2] == 'l' || temp[temp.size() - 2] == 'L');
    if (temp.size() >= 2 && lastIsL && preLastIsL) {
        temp.pop_back();
        temp.pop_back();
        try {
            dest.ref = std::stoll(temp);
            return in;
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
        return in;
    }

    DataStruct temp;

    if (!(in >> DelimiterIO{'('} >> DelimiterIO{':'})) {
        return in;
    }

    for (int i = 0; i < 3; ++i) {
        std::string key;
        in >> KeyIO{key};

        if (key == "key1") {
            in >> DoubleSciIO{temp.key1};
        }
        else if (key == "key2") {
            in >> LongLongIO{temp.key2};
        }
        else if (key == "key3") {
            in >> StringIO{temp.key3};
        }
        else {
            in.setstate(std::ios::failbit);
            break;
        }

        if (i < 2) {
            in >> DelimiterIO{':'};
            if (!in) {
                break;
            }
        }
    }

    if (in >> DelimiterIO{')'}) {
        dest = temp;
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

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        DataStruct temp;

        if (iss >> temp) {
            data.push_back(temp);
        }
    }

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
