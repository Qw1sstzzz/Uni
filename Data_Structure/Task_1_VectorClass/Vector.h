#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <cstddef>

template<typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;
public:
    Vector();
    explicit Vector(size_t n);
    Vector(size_t n, const T& value);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();
    
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    
    void swap(Vector& other) noexcept;
    

    size_t size() const;
    size_t capacity() const;
    bool empty() const;


    T& operator[](size_t index);
    T& at(size_t index);
    T& front();
    T& back();

    void push_back(const T& value);
    void push_back(T&& value);

    void pop_back();
    void clear();

    void reserve(size_t new_capacity);
    void resize(size_t new_size);
    void resize(size_t new_size, const T& value);
    void shrink_to_fit();

    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
    bool operator<(const Vector& other) const;
    bool operator<=(const Vector& other) const;
    bool operator>(const Vector& other) const;
    bool operator>=(const Vector& other) const;


    void insert(size_t index, const T& value);
    void insert(size_t index, T&& value);

    void erase(size_t index);
    void erase(size_t first, size_t last);
};

template<typename T>
void insertionSort(Vector<T>& vec);


#include "Vector.tpp" 

#endif // VECTOR_H
