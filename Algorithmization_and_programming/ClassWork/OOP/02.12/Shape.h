#ifndef SHAPE_H
#define SHAPE_H


#include <iostream>


const double PI = 3.14159;

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string name() const = 0;
} ;

class Circle : public Shape {
    double radius_;
public:
    Circle(double r) : radius_(r) {}
    std::string name() const override {
        return "Circle";
    }
    
    double area() const override {
        return PI * radius_ * radius_;
    }
    
    double perimeter() const override {
        return 2 * PI * radius_;
    }
} ;

class Rectangle : public Shape {
    double width_, height_;
public:
    Rectangle(double w, double h) : width_(w), height_(h) {}
    std::string name() const override {
        return "Rectangle";
    }

    double area() const override {
        return width_ * height_;
    }
    
    double perimeter() const override {
        return 2 * (width_ + height_);
    }


    double aspectRatio() {
        return width_ / height_;
    }
} ;


#endif