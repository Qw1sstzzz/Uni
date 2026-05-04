#ifndef HASHDICTIONARY_H
#define HASHDICTIONARY_H

#include <iostream>
#include <string>
#include <vector>

enum Status {
    EMPTY = 0,
    OCCUPIED = 1,
    DELETED = 2,
} ;

struct Line {
    std::string key_;
    std::vector<std::string> translations_;
    Status status_;
} ;

class HashDictionary {
private:
    static constexpr double MAX_LOAD_FACTOR = 0.7;
    static const size_t DEFAULT_SIZE = 11;

    size_t size_;
    Line* table_;
    size_t count_;
    size_t collisions_;

    static bool isPrime(size_t n);
    static size_t nextPrime(size_t n);
    void resize();
    void insertTranslation(std::vector<std::string>& translations, const std::string& translation) const;
public:
    HashDictionary(size_t size = DEFAULT_SIZE);
    ~HashDictionary();

    HashDictionary(const HashDictionary& other) = delete;
    HashDictionary(HashDictionary&& other) = delete;
    HashDictionary& operator=(const HashDictionary& other) = delete;
    HashDictionary& operator=(HashDictionary&& other) = delete;

    size_t hash(const std::string& key) const;
    bool insert(const std::string& key, const std::string& translation);
    const std::vector<std::string>* search(const std::string& key) const;
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
