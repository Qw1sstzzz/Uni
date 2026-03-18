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

template<typename T>
StackVector<T>::~StackVector() {
    delete[] data;
}


template<typename T>
void StackVector<T>::swap(StackVector& other) noexcept {
    std::swap(data, other.data);
    std::swap(capacity, other.capacity);
    std::swap(topIndex, other.topIndex);
}


template<typename T>
StackVector<T>& StackVector<T>::operator=(const StackVector& other) {
    if (this != &other) {
        StackVector<T> temp(other);
        swap(temp);
    }
    return *this;
}

template<typename T>
StackVector<T>& StackVector<T>::operator=(StackVector&& other) noexcept {
    if (this != &other) {
        swap(other);
    }
    return *this;
}


template<typename T>
bool StackVector<T>::isEmpty() const {
    return topIndex == -1;
}

template<typename T>
void StackVector<T>::push(const T& e) {
    if (topIndex + 1 >= capacity) {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = nullptr;
        try {
            newData =new T[newCapacity];
            for (size_t i = 0; i <= topIndex; ++i) {
                newData[i] = data[i];
            }
        }
        catch (const std::bad_alloc& ba) {
            delete[] newData;
            throw StackOverflow("ERROR: Can't allocate memory");
        }
        catch (...) {
            delete[] newData;
            throw;
        }

        delete[] data;

        data = newData;
        capacity = newCapacity;
    }
    data[++topIndex] = e;
}


template<typename T>
T StackVector<T>::pop() {
    if (isEmpty()) {
        throw StackUnderflow("Can't pop from empty stack(");
    }
    return data[topIndex--];
}

template<typename T>
T& StackVector<T>::top() {
    if (isEmpty()) {
        throw StackUnderflow("Can't get top from empty stack(");
    }
    return data[topIndex];
}

template<typename T>
const T& StackVector<T>::top() const {
    if (isEmpty()) {
        throw StackUnderflow("Can't get top from empty stack(");
    }
    return data[topIndex];
}