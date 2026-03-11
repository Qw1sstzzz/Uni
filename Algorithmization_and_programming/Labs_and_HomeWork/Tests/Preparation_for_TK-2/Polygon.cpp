#include "Polygon.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <cstring>  // Для std::swap

using std::swap;

Polygon::Polygon() : vertices_(nullptr), size_(0), capacity_(0) {}

Polygon::Polygon(const Point* points, size_t size) : vertices_(nullptr), size_(0), capacity_(0) {
    try {
        for (size_t i = 0; i < size; ++i) {
            addVertex(points[i]);
        }
    } catch (...) {
        cleanup();
        throw;
    }
}

Polygon::Polygon(const Polygon& other) : vertices_(nullptr), size_(0), capacity_(0) {
    try {
        for (size_t i = 0; i < other.size_; ++i) {
            addVertex(other.vertices_[i]);
        }
    } catch (...) {
        cleanup();
        throw;
    }
}

Polygon::Polygon(Polygon&& other) noexcept 
    : vertices_(other.vertices_), size_(other.size_), capacity_(other.capacity_) {
    other.vertices_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

Polygon& Polygon::operator=(Polygon other) noexcept {
    swap(other);
    return *this;
}

Polygon::~Polygon() {
    cleanup();
}

size_t Polygon::getSize() const { 
    return size_; 
}

void Polygon::addVertex(const Point& p) {
    if (size_ >= capacity_) {
        reserve(capacity_ == 0 ? 2 : capacity_ * 2);
    }
    vertices_[size_++] = p;
}

void Polygon::removeVertex(size_t index) {
    if (index >= size_) return;
    for (size_t i = index; i < size_ - 1; ++i) {
        vertices_[i] = vertices_[i + 1];
    }
    --size_;
}

double Polygon::perimeter() const {
    if (size_ < 2) return 0.0;
    double p = 0.0;
    for (size_t i = 0; i < size_; ++i) {
        size_t next = (i + 1) % size_;
        p += vertices_[i].distance(vertices_[next]);
    }
    return p;
}

double Polygon::area() const {
    if (size_ < 3) return 0.0;
    double area = 0.0;
    for (size_t i = 0; i < size_; ++i) {
        size_t next = (i + 1) % size_;
        area += vertices_[i].getX() * vertices_[next].getY();
        area -= vertices_[i].getY() * vertices_[next].getX();
    }
    return std::abs(area) / 2.0;
}

bool Polygon::operator==(const Polygon& other) const {
    if (size_ != other.size_) return false;
    for (size_t i = 0; i < size_; ++i) {
        if (vertices_[i] != other.vertices_[i]) return false;
    }
    return true;
}

Polygon Polygon::operator+(const Polygon& other) const {
    Polygon result = *this;
    for (size_t i = 0; i < other.size_; ++i) {
        result.addVertex(other.vertices_[i]);
    }
    return result;
}

std::istream& operator>>(std::istream& in, Polygon& poly) {
    size_t n;
    in >> n;
    if (in.fail()) throw std::invalid_argument("Invalid polygon size");
    
    poly.cleanup();
    for (size_t i = 0; i < n; ++i) {
        Point p;
        in >> p;
        poly.addVertex(p);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Polygon& poly) {
    out << "Polygon[" << poly.size_ << "]: ";
    for (size_t i = 0; i < poly.size_; ++i) {
        out << poly.vertices_[i] << " ";
    }
    return out;
}

void Polygon::reserve(size_t newCapacity) {
    if (newCapacity <= capacity_) return;
    
    Point* newVertices = new Point[newCapacity];
    for (size_t i = 0; i < size_; ++i) {
        newVertices[i] = vertices_[i];
    }
    
    delete[] vertices_;
    vertices_ = newVertices;
    capacity_ = newCapacity;
}

void Polygon::cleanup() {
    delete[] vertices_;
    vertices_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

void Polygon::swap(Polygon& other) noexcept {
    std::swap(vertices_, other.vertices_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}