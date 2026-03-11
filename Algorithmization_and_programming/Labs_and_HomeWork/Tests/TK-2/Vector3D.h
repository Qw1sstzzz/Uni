// Variant - 1

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

const int SIZE = 3;

class Vector3D {
    float* data_;

public:
    Vector3D();
    Vector3D(float x_, float y_, float z_);
    
    Vector3D(const Vector3D& other);
    Vector3D(Vector3D&& other) noexcept;
    Vector3D& operator=(const Vector3D& other);
    Vector3D& operator=(Vector3D&& other) noexcept;
    ~Vector3D();

    Vector3D operator+(const Vector3D& other) const;
    bool operator==(const Vector3D& other) const;

    float length() const;
    
    float getX() const;
    float getY() const;
    float getZ() const;
    
    void setX(float x_);
    void setY(float y_);
    void setZ(float z_);    
    friend std::ostream& operator<<(std::ostream& os, const Vector3D& vec);

private:
    void swap(Vector3D& other) noexcept;
    void clean();
};

#endif