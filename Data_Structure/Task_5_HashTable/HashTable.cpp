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
