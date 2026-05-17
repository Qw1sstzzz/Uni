#ifndef HASHDICTIONARY_H
#define HASHDICTIONARY_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <functional>

enum Status {
    EMPTY = 0,
    OCCUPIED = 1,
    DELETED = 2,
} ;


struct KeyEquals {
    const std::string& target_;
    KeyEquals(const std::string& t) : target_(t) {}
    bool operator()(const Line& line) const {
        return line.status_ == OCCUPIED && line.key_ == target_;
    }
} ;


struct Line {
    std::string key_;
    std::set<std::string> translations_;
    Status status_;
} ;

class HashDictionary {
private:
    static constexpr double MAX_LOAD_FACTOR = 0.7;
    static const size_t DEFAULT_SIZE = 11;

    size_t size_;
    std::vector<Line> table_;
    size_t count_;
    size_t collisions_;

    static bool isPrime(size_t n);
    static size_t nextPrime(size_t n);
    void resize();
    size_t hash(const std::string& key) const;
public:
    HashDictionary(size_t size = DEFAULT_SIZE);
    ~HashDictionary();

    HashDictionary(const HashDictionary& other) = delete;
    HashDictionary(HashDictionary&& other) = delete;
    HashDictionary& operator=(const HashDictionary& other) = delete;
    HashDictionary& operator=(HashDictionary&& other) = delete;

    bool insert(const std::string& key, const std::string& translation);
    bool removeTranslation(const std::string& key, const std::string& translation);
    const std::set<std::string>* search(const std::string& key) const;
    bool remove(const std::string& key);
    void print() const;

    size_t getCount() const {
        return count_;
    }
    size_t getCollisions() const {
        return collisions_;
    }
} ;

#endif // HASHDICTIONARY_H
