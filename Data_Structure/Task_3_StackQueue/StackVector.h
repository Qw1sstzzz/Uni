#ifndef STACK_VECTOR_H
#define STACK_VECTOR_H

#include <iostream>
#include "Stack.h"

template <typename T>
class StackVector : public Stack<T> {
private:
    T* data;
    size_t capacity;
    int topIndex;
public:
    StackVector();
    StackVector(size_t size);
    StackVector(const StackVector& other);
    StackVector(StackVector&& other) noexcept;
    ~StackVector();

    StackVector& operator=(const StackVector& other);
    StackVector& operator=(StackVector&& other) noexcept;

    void push(const T& e) override;
    T pop() override;
    bool isEmpty() const override;

    size_t size() const;

    T& top();
    const T& top() const;

    void swap(StackVector& other) noexcept;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const StackVector<U>& st);
} ;

template<typename T>
std::ostream& operator<<(std::ostream& os, const StackVector<T>& st) {
    os << "[bottom] ";
    T* temp = new T[st.size()];
    StackVector<T> copy = st;
    
    int i = 0;
    while (!copy.isEmpty()) {
        temp[i++] = copy.pop();
    }

    for (int j = i - 1; j >= 0; --j) {
        os << temp[j];
        if (j > 0) os << " ";
    }
    
    delete[] temp;
    os << " [top]";
    return os;
}

#include "StackVector.tpp"

#endif // STACK_VECTOR_H