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
