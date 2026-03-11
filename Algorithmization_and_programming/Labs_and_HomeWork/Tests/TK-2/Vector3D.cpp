// Variant - 1

#include "Vector3D.h"
#include <cmath>
#include <stdexcept>


Vector3D::Vector3D() : data_(nullptr) {
    try {
        data_ = new float[SIZE];
        data_[0] = 0.0;
        data_[1] = 0.0;
        data_[2] = 0.0;
    } 
    catch (const std::bad_alloc& e) {
        throw std::runtime_error("ERROR!!! Failed to allocate memory for vector");
    }
}

Vector3D::Vector3D(float x_, float y_, float z_) : data_(nullptr) {
    try {
        data_ = new float[SIZE];
        data_[0] = x_;
        data_[1] = y_;
        data_[2] = z_;
    } 
    catch (const std::bad_alloc& e) {
        throw std::runtime_error("ERROR!!! Failed to allocate memory for vector");
    }
}

Vector3D::Vector3D(const Vector3D& other) : data_(nullptr) {
    try {
        data_ = new float[SIZE];
        data_[0] = other.data_[0];
        data_[1] = other.data_[1];
        data_[2] = other.data_[2];
    } 
    catch (const std::bad_alloc& e) {
        throw std::runtime_error("ERROR!!! Failed to copy vector");
    }
}

Vector3D::Vector3D(Vector3D&& other) noexcept 
    : data_(other.data_) {
    other.data_ = nullptr;
}

Vector3D& Vector3D::operator=(const Vector3D& other) {
    if (this != &other) {
        Vector3D temp(other);
        swap(temp);
    }
    return *this;
}

Vector3D& Vector3D::operator=(Vector3D&& other) noexcept {
    if (this != &other) {
        clean();
        data_ = other.data_;
        other.data_ = nullptr;
    }
    return *this;
}

Vector3D::~Vector3D() {
    clean();
}

float Vector3D::length() const {
    return std::sqrt(data_[0] * data_[0] + data_[1] * data_[1] + data_[2] * data_[2]);
}

Vector3D Vector3D::operator+(const Vector3D& other) const {
    return Vector3D(data_[0] + other.data_[0], data_[1] + other.data_[1], data_[2] + other.data_[2]);
}

bool Vector3D::operator==(const Vector3D& other) const {
    return (data_[0] == other.data_[0]) && 
           (data_[1] == other.data_[1]) && 
           (data_[2] == other.data_[2]);
}

float Vector3D::getX() const {
    return data_[0];
}
float Vector3D::getY() const {
    return data_[1];
}
float Vector3D::getZ() const {
    return data_[2];
}

void Vector3D::setX(float x_) {
    data_[0] = x_;
}
void Vector3D::setY(float y_) {
    data_[1] = y_;
}
void Vector3D::setZ(float z_) {
    data_[2] = z_;
}


void Vector3D::swap(Vector3D& other) noexcept {
    std::swap(data_, other.data_);
}

void Vector3D::clean() {
    delete[] data_;
    data_ = nullptr;
}

std::ostream& operator<<(std::ostream& os, const Vector3D& vec) {
    os << "(" << vec.data_[0] << ", " << vec.data_[1] << ", " << vec.data_[2] << ")";
    return os;
}