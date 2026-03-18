#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "Errors.h"

template<typename T>
class Queue {
public:
    virtual ~Queue() {}
    virual void enQueue(const T& el) = 0;
    virual T deQueue() = 0;
    virual bool isEmpty() = 0;
} ;

#endif //QUEUE_H
