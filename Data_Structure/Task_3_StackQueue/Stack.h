#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "Errors.h"

template<typename T>
class Stack {
public:
    virtual void push(const T& e) = 0;
    virtual T pop() = 0;
    virtual bool isEmpty() const = 0;
    virtual ~Stack() {};
} ;


#endif //STACK_H