#ifndef POLYGON_H
#define POLYGON_H

#include "Point.h"
#include <iostream>
#include <cstddef>  // Для size_t

class Polygon {
public:
    Polygon();
    Polygon(const Point* points, size_t size);
    
    // Правило пяти
    Polygon(const Polygon& other);
    Polygon(Polygon&& other) noexcept;
    Polygon& operator=(Polygon other) noexcept;
    ~Polygon();
    
    size_t getSize() const;
    void addVertex(const Point& p);
    void removeVertex(size_t index);
    double perimeter() const;
    double area() const;
    
    bool operator==(const Polygon& other) const;
    Polygon operator+(const Polygon& other) const;
    
    friend std::istream& operator>>(std::istream& in, Polygon& poly);
    friend std::ostream& operator<<(std::ostream& out, const Polygon& poly);

private:
    Point* vertices_;
    size_t size_;
    size_t capacity_;
    
    void reserve(size_t newCapacity);
    void cleanup();
    void swap(Polygon& other) noexcept;
};

#endif // POLYGON_H