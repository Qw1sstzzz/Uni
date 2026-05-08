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

bool TranslationList::find(const std::string& word) const {
    Node* current = head_;
    while (current != nullptr) {
        if (current->word_ == word) {
            return true;
        }
        current = current->next_;
    }
    return false;
}

bool TranslationList::remove(const std::string& word) {
    if (head_ == nullptr) {
        return false;
    }

    if (head_->word_ == word) {
        Node* temp = head_;
        head_ = head_->next_;
        delete temp;
        return true;
    }

    Node* current = head_;
    while (current->next_ != nullptr) {
        if (current->next_->word_ == word) {
            Node* temp = current->next_;
            current->next_ = current->next_->next_;
            delete temp;
            return true;
        }
        current = current->next_;
    }
    return false;
}

bool TranslationList::empty() const {
    return head_ == nullptr;
}

void TranslationList::print() const {
    Node* current = head_;
    bool first = true;
    while (current != nullptr) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << current->word_;
        first = false;
        current = current->next_;
    }
}

void TranslationList::clear() {
    while (head_ != nullptr) {
        Node* temp = head_;
        head_ = head_->next_;
        delete temp;
    }
}
