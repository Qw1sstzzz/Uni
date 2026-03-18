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

    T& top();
    const T& top() const;

    void swap(StackVector& other) noexcept;
} ;

#include "StackVector.tpp"

#endif // STACK_VECTOR_H