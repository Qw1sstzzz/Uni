#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <string>

const double PI = 3.14159;


class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string name() const = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual Shape* clone() const = 0;

    friend std::ostream& operator<<(std::ostream& out, const Shape* shape);
};



class Circle : public Shape {
    double radius_;
    void validateRadius() const {
        if (radius_ <= 0) {
            throw std::invalid_argument("Radius must be positive");
        }
    }

public:
    Circle() = delete;
    Circle(double r) : radius_(r) { 
        validateRadius(); 
    }
    ~Circle() = default;
    
    std::string name() const override { 
        return "Circle"; 
    }
    double area() const override { 
        return PI * radius_ * radius_; 
    }
    double perimeter() const override { 
        return 2 * PI * radius_; 
    }
    
    void print(std::ostream& out) const override;

    Shape* clone() const override {
        return new Circle(*this);
    }
};



class Rectangle : public Shape {
    double width_, height_;
    
    void validateDimensions() const {
        if (width_ <= 0 || height_ <= 0) {
            throw std::invalid_argument("Width and Height must be positive");
        }
    }

public:
    Rectangle() = delete;
    Rectangle(double w, double h) : width_(w), height_(h) { 
        validateDimensions(); 
    }
    ~Rectangle() = default;
    
    std::string name() const override { 
        return "Rectangle"; 
    }
    double area() const override { 
        return width_ * height_; 
    }
    double perimeter() const override { 
        return 2 * (width_ + height_); 
    }
    double aspectRatio() const { 
        return width_ / height_; 
    }
    
    void print(std::ostream& out) const override;

    Shape* clone() const override {
        return new Rectangle(*this);
    }
};

#endif