#ifndef ERRORS_H
#define ERRORS_H

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


class QueueOverflow : public std::exception {
private:
    const char* message;
public:
    QueueOverflow(const char* msg) : message(msg) {}
    const char* what() const noexcept override {
        return message;
    }
} ;

class QueueUnderflow : public std::exception {
private:
    const char* message;
public:
    QueueUnderflow(const char* msg) : message(msg) {}
    const char* what() const noexcept override {
        return message;
    }
} ;

class WrongQueueSize : public std::exception {
private:
    const char* message;
public:
    WrongQueueSize(const char* msg) : message(msg) {}
    const char* what() const noexcept override {
        return message;
    }
} ;


#endif //ERRORS_H