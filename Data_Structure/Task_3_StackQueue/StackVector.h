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
    StackVector() : data(nullptr), capacity(0), topIndex(-1) {}
    StackVector(size_t size) : data(nullptr), capacity(size), topIndex(-1) {}
    StackVector(const StackVector& other);
    StackVector(StackVector&& other);
    ~StackVector();

    StackVector& operator=(const StackVector& other);
    StackVector& operator=(StackVector&& other);

    void push(const T& e) override;
    T pop() override;
    bool isEmpty() const override;

    T& top();
    bool T& top() const;

    void swap(StackVector& other) noexcept;
} ;

#endif // STACK_VECTOR_H