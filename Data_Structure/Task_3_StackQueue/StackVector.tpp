#include "StackVector.h"

template<typename T>
StackVector<T>::StackVector(size_t size) : data(nullptr), capacity(size), topIndex(-1) {
    if (size <= 0) {
        throw WrongStackSize("ERROR: size must be positive");
    }
    data = new T[size];
}

template<typename T>
StackVector<T>::StackVector(const StackVector& other) : capacity(other.capacity), topIndex(other.topIndex) {
    data = new T[capacity];
    for (int i = 0; i <= topIndex; ++i) {
        data[i] = other.data[i];
    }   
}

template<typename T>
StackVector<T>::StackVector(StackVector&& other) : data(other.data), capacity(other.capacity), topIndex(other.topIndex) {
    other.data = nullptr;
    other.capacity = 0;
    other.topIndex = -1;    
}

template <typename T>
StackVector<T>::~StackVector() {
    delete[] data;
}