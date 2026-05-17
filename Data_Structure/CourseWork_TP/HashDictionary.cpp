#include "HashDictionary.h"
#include "Errors.h"

HashDictionary::HashDictionary(size_t size) : size_(nextPrime(size)), table_(size_), count_(0), collisions_(0) {
    for (size_t i = 0; i < size_; ++i) {
        table_[i].status_ = EMPTY;
    }
}

HashDictionary::~HashDictionary() = default;


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
    return std::hash<std::string>{}(key) % size_;
}



static void validateKey(const std::string& key) {
    if (key.empty()) {
        throw ValidationError("Key is empty");
    }

    for (char c : key) {
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            throw ValidationError("Key must contain only English: " + key);
        }
    }
}

static void validateTranslation(const std::string& translation) {
    if (translation.empty()) {
        throw ValidationError("Translation is empty");
    }

    for (char c : translation) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            throw ValidationError("Translation mustn't be in English: " + translation);
        }
        if (c >= '0' && c <= '9') {
            throw ValidationError("Translation mustn't contain digits: " + translation);
        }
    }
}


bool HashDictionary::insert(const std::string& key, const std::string& translation) {
    validateKey(key);
    validateTranslation(translation);

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
            bool inserted = table_[current].translations_.insert(translation);
            if (!inserted) {
                throw DuplicateTranslationException("Translation already exists: \"" + translation + "\" for word \"" + key + "\"");
            }
            return true;
        }

        ++i;
    }
    return false;
}


bool HashDictionary::removeTranslation(const std::string& key, const std::string& translation) {
    size_t idx = hash(key);
    size_t i = 0;
    while (i < size_) {
        size_t current = (idx + i*i) % size_;

        if (table_[current].status_ == EMPTY) {
            return false;
        }

        if (table_[current].status_ == OCCUPIED && table_[current].key_ == key) {
            bool removed = table_[current].translations_.remove(translation);
            if (removed && table_[current].translations_.empty()) {
                table_[current].status_ = DELETED;
                --count_;
            }
            return removed;
        }

        ++i;
    }

    throw KeyNotFoundException("Key not found: " + key);
}


const TranslationList* HashDictionary::search(const std::string& key) const {
    size_t idx = hash(key);
    size_t i = 0;

    while (i < size_) {
        size_t current = (idx + i*i) % size_;

        if (table_[current].status_ == EMPTY) {
            return nullptr;
        }

        if (table_[current].status_ == OCCUPIED && table_[current].key_ == key) {
            return &table_[current].translations_;
        }

        ++i;
    }

    return nullptr;
}


bool HashDictionary::remove(const std::string& key) {
    size_t idx = hash(key);
    size_t i = 0;

    while (i < size_) {
        size_t current = (idx + i*i) % size_;

        if (table_[current].status_ == EMPTY) {
            return false;
        }

        if (table_[current].status_ == OCCUPIED && table_[current].key_ == key) {
            table_[current].translations_.clear();
            table_[current].status_ = DELETED;
            --count_;
            return true;
        }

        ++i;
    }

    return false;
}


void HashDictionary::print() const {
    for (size_t i = 0; i < size_; ++i) {
        if (table_[i].status_ == OCCUPIED) {
            std::cout << table_[i].key_ << ": ";
            table_[i].translations_.print();
            std::cout << std::endl;
        }
    }
}


void HashDictionary::resize() {
    size_t oldSize = size_;
    Line* oldTable = table_;

    size_ = nextPrime(oldSize*2);
    table_ = new Line[size_];
    count_ = 0;
    collisions_ = 0;

    for (size_t i = 0; i < size_; ++i) {
        table_[i].status_ = EMPTY;
    }

    for (size_t i = 0; i < oldSize; ++i) {
        if (oldTable[i].status_ == OCCUPIED) {
            size_t idx = hash(oldTable[i].key_);
            size_t j = 0;

            while (j < size_) {
                size_t current = (idx + j*j) % size_;
                if (table_[current].status_ == EMPTY) {
                    table_[current].key_ = oldTable[i].key_;
                    table_[current].translations_ = std::move(oldTable[i].translations_);
                    table_[current].status_ = OCCUPIED;

                    ++count_;
                    collisions_ += j;
                    break;
                }
                ++j;
            }
        }
    }
    delete[] oldTable;
}
