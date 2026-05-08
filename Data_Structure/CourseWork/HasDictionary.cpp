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


bool HashDictionary::insert(const std::string& key, const std::string& translation) {
    double alpha = static_cast<double>(count_) / static_cast<double>(size_);

    if (alpha >= MAX_LOAD_FACTOR) {
        resize();
    }

    size_t idx = hash(key);
    size_t i = 0;

    while (i < size_) {
        size_t current = (idx + i*i) % size_;
        if (table_[current].status_ != OCCUPIED) {
            table_[current].key_ = key;
            table_[current].translations_.insert(translation);
            table_[current].status_ = OCCUPIED;
            ++count_;
            collisions_ += i;
            return true;
        }

        if (table_[current].key_ == key) {
            collisions_ += i;
            return table_[current].translations_.insert(translation);
        }

        ++i;
    }
    return false;
}
