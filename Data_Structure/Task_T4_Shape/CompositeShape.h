#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Point.h"
#include "Shape.h"

class CompositeShape : public Shape {
private: 
    std::vector<std::unique_ptr<Shape>> shapes;

    Point calculateCenter() const;
public:
    CompositeShape() = default;
    
    CompositeShape(const CompositeShape&) = delete;
    CompositeShape& operator=(const CompositeShape&) = delete;
    
    CompositeShape(CompositeShape&&) = default;
    CompositeShape& operator=(CompositeShape&&) = default;
    
    void addShape(std::unique_ptr<Shape> shape);
    
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double fact) override;
    std::string getName() const override;
} ;


#endif // COMPOSITESHAPE_H