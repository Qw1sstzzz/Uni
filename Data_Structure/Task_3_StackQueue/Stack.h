#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <exception>

class StackOverflow : public std::exception {
private:
    const char* message;
public:
    StackOverflow(const char* msg) : message(msg) {}
    const char* what() const noexcept override {
        return message;
    }
} ;

class StackUnderflow : public std::exception {
private:
    const char* message;
public:
    StackUnderflow(const char* msg) : message(msg) {}
    const char* what() const noexcept override {
        return message;
    }
} ;

class WrongStackSize : public std::exception {
private:
    const char* message;
public:
    WrongStackSize(const char* msg) : message(msg) {}
    const char* what() const noexcept override {
        return message;
    }
} ;

template<typename T>
class Stack {
public:
    virtual void push(const T& e) = 0;
    virtual T pop() = 0;
    virtual bool isEmpty() = 0;
    virtual ~Stack() {};
} ;


#endif //STACK_H