#include "HashTable.h"

HashTable::HashTable(size_t size) {
    size_ = size;
    table_ = new Line[size];
    number_ = 0;
    collisions_ = 0;

    for (size_t i = 0; i < size; ++i) {
        table_[i].key_ = nullptr;
        table_[i].status_ = EMPTY;
    }
}

HashTable::~HashTable() {
    for (size_t i = 0; i < size_; ++i) {
        if (table_[i].status_ == OCCUPIED) {
            delete table_[i].key_;
        }
    }
    delete[] table_;
}

size_t HashTable::hash(double key) const {
    double absKey = std::abs(key);
    double normalized = absKey / (absKey + 1);

    return static_cast<size_t>(normalized * size_);
}

void HashTable::insert(double key, double value) {
    double alpha = static_cast<double>(number_) / static_cast<double>(size_);

    if (alpha >= 0.7) {
        return;
    }

    size_t i = 0;
    size_t idx = hash(key);

    while (i < size_) {
        size_t current = (idx + i) % size_;

        if (table_[current].status_ != OCCUPIED) {
            table_[current].key_ = new double(key);
            table_[current].value_ = value;
            table_[current].status_ = OCCUPIED;
            number_++;
            return;
        }

        if (table_[current].status_ == OCCUPIED) {
            if (*table_[current].key_ == key) {
                return;
            }
            else {
                collisions_++;
            }
        }
        i++;
    }
}
