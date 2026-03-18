#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "Errors.h"

template<typename T>
class Queue {
public:
    virtual ~Queue() {}
    virtual void enQueue(const T& el) = 0;
    virtual T deQueue() = 0;
    virtual bool isEmpty() = 0;
} ;

#endif //QUEUE_H
