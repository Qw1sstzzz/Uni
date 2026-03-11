#ifndef SHAPECOLLECTION_H
#define SHAPECOLLECTION_H

#include "Shape.h"

#include <iostream>
#include <string>


class ShapeCollection {
private:
    Shape** figures_;          
    int maxFigures_;          
    int currentFigures_;      

    void clear() noexcept;
    void swap(ShapeCollection& other) noexcept;

public:
    ShapeCollection(); 
    ShapeCollection(const ShapeCollection& other); 
    ShapeCollection(ShapeCollection&& other) noexcept; 
    ShapeCollection& operator=(const ShapeCollection& other); 
    ShapeCollection& operator=(ShapeCollection&& other) noexcept; 
    ~ShapeCollection();
    
    ShapeCollection& operator+(Shape* shape);
    
    void printAreas() const; 
    void printNames() const; 
    int getNumberRepetitionsName(const std::string& name) const;
    const Shape* findSmallestArea() const;
    
    int getCurrentFigures() const { 
        return currentFigures_; 
    }
    int getMaxFigures() const { 
        return maxFigures_; 
    }
    
    friend std::ostream& operator<<(std::ostream& out, const ShapeCollection& collection);
};

#endif