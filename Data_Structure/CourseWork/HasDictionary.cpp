#include "HashDictionary.h"


HashDictionary::HashDictionary(size_t size) {
    size_ = nextPrime(size);
    table_ = new Line[size_];
    count_ = 0;
    collisions_ = 0;

    for (size_t i = 0; i < size_; ++i) {
        table_[i].status_ = EMPTY;
    }
}


HashDictionary::~HashDictionary() {
    delete[] table_;
}


bool HashDictionary::isPrime(size_t n) {
    if (n < 2) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }

    for (size_t i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

size_t HashDictionary::nextPrime(size_t n) {
    while (!isPrime(n)) {
        ++n;
    }
    return n;
}

size_t HashDictionary::hash(const std::string& key) const {
    size_t hashValue = 0;
    for (char c : key) {
        hashValue = hashValue * 31 + static_cast<size_t>(c);
    }
    return hashValue % size_;
}

void HashDictionary::insertTranslation(std::vector<std::string>& translations, const std::string& translation) const {
    for (size_t i = 0; i < translations.size(); ++i) {
        if (translation == translations[i]) {
            return;
        }

        if (translation < translations[i]) {
            translations.insert(translations.begin() + i, translation);
            return;
        }
    }
    translations.push_back(translation);
}
