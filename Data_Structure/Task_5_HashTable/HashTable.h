#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>

enum Status {
    EMPTY,
    OCCUPIED,
    DELETED,
} ;

struct Line {
    double* key_;
    double value_;
    Status status_;
} ;


class HashTable {
private:
    size_t size_;
    Line* table_;
    size_t number_;
    size_t collisions_;
public:
    HashTable(size_t size);
    ~HashTable();

    HashTable(const HashTable&) = delete;
    HashTable(HashTable&&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    HashTable& operator=(HashTable&&) = delete;

    size_t getCollisions() const;

    size_t hashFuction (double key) const;
    void insert(double key, double value);
    bool find(double key) const;
    void remove(double key);
    void print() const;
} ;

#endif // HASHTABLE_H
