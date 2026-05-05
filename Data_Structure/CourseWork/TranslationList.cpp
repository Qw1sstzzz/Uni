#include "TranslationList.h"

TranslationList::TranslationList() : head_(nullptr) {}

TranslationList::~TranslationList() {
    clear();
}

bool TranslationList::insert(const std::string& word) {
    if (head_ == nullptr) {
        head_ = new Node(word);
        return true;
    }

    if (word < head_->word_) {
        Node* newNode = new Node(word);
        newNode->next_ = head_;
        head_ = newNode;
        return true;
    }

    if (word == head_->word_) {
        return false;
    }

    Node* current = head_;
    while (current->next_ != nullptr) {
        if (word == current->next_->word_) {
            return false;
        }
        if (word < current->next_->word_) {
            Node* newNode = new Node(word);
            newNode->next_ = current->next_;
            current->next_ = newNode;
            return true;
        }
        current = current->next_;
    }

    current->next_ = new Node(word);
    return true;
}
