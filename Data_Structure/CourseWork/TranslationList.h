#ifndef TRANSLATIONLIST_H
#define TRANSLATIONLIST_H

#include <iostream>
#include <string>

class TranslationList {
private:
    struct Node {
        std::string word_;
        Node* next_;

        Node(const std::string& word) : word_(word), next_(nullptr) {}
    } ;

    Node* head_;

public:
    TranslationList();
    ~TranslationList();

    TranslationList(const TranslationList& other) = delete;
    TranslationList& operator=(const TranslationList& other) = delete;

    bool insert(const std::string& word);
    bool find(const std::string& word) const;
    bool remove(const std::string& word);
    bool empty() const;
    void print() const;
    void clear();
} ;

#endif // TRANSLATIONLIST_H
