#include "ShapeCollection.h"

#include <iostream>
#include <limits>
#include <stdexcept>

ShapeCollection::ShapeCollection() : maxFigures_(16), currentFigures_(0) {
    figures_ = new Shape*[maxFigures_];
    for (int i = 0; i < maxFigures_; ++i) {
        figures_[i] = nullptr;
    }
}


ShapeCollection::ShapeCollection(const ShapeCollection& other) 
    : maxFigures_(other.maxFigures_), currentFigures_(other.currentFigures_) {
    
    figures_ = new Shape*[maxFigures_];
    for (int i = 0; i < maxFigures_; ++i) {
        if (i < currentFigures_ && other.figures_[i] != nullptr) {
            figures_[i] = other.figures_[i]->clone();
        } 
        else {
            figures_[i] = nullptr;
        }
    }
}

ShapeCollection& ShapeCollection::operator=(const ShapeCollection& other) {
    if (this != &other) {
        ShapeCollection temp(other);
        swap(temp);
    }
    return *this;
}

ShapeCollection::ShapeCollection(ShapeCollection&& other) noexcept 
    : figures_(other.figures_), maxFigures_(other.maxFigures_), currentFigures_(other.currentFigures_) {
    
    other.figures_ = nullptr;
    other.maxFigures_ = 0;
    other.currentFigures_ = 0;
}

ShapeCollection& ShapeCollection::operator=(ShapeCollection&& other) noexcept {
    if (this != &other) {
        clear();
        
        figures_ = other.figures_;
        maxFigures_ = other.maxFigures_;
        currentFigures_ = other.currentFigures_;
        
        other.figures_ = nullptr;
        other.maxFigures_ = 0;
        other.currentFigures_ = 0;
    }
    return *this;
}

ShapeCollection::~ShapeCollection() {
    clear();
}

void ShapeCollection::clear() noexcept {
    for (int i = 0; i < currentFigures_; ++i) {
        delete figures_[i];
    }
    delete[] figures_;
    figures_ = nullptr;
    currentFigures_ = 0;
    maxFigures_ = 0;
}

void ShapeCollection::swap(ShapeCollection& other) noexcept {
    std::swap(figures_, other.figures_);
    std::swap(maxFigures_, other.maxFigures_);
    std::swap(currentFigures_, other.currentFigures_);
}

ShapeCollection& ShapeCollection::operator+(Shape* shape) {
    if (currentFigures_ >= maxFigures_) {
        throw std::out_of_range("Cannot add more than " + std::to_string(maxFigures_) + " figures");
    }
    
    if (shape == nullptr) {
        throw std::invalid_argument("Cannot add null pointer");
    }
    
    figures_[currentFigures_] = shape;
    ++currentFigures_;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const ShapeCollection& collection) {
    out << "Shape Collection [current: " << collection.currentFigures_ 
        << ", maximum: " << collection.maxFigures_ << "]:" << std::endl;
    
    for (int i = 0; i < collection.currentFigures_; ++i) {
        if (collection.figures_[i] != nullptr) {
            out << i + 1 << ". ";
            collection.figures_[i]->print(out);
            out << std::endl;
        }
    }
    return out;
}

void ShapeCollection::printAreas() const {
    std::cout << "Figure areas:" << std::endl;
    for (int i = 0; i < currentFigures_; ++i) {
        if (figures_[i] != nullptr) {
            std::cout << i + 1 << ". " << figures_[i]->name() << ": " << figures_[i]->area() << std::endl;
        }
    }
}

void ShapeCollection::printNames() const {
    std::cout << "Figure names:" << std::endl;
    for (int i = 0; i < currentFigures_; ++i) {
        if (figures_[i] != nullptr) {
            std::cout << i + 1 << ". " << figures_[i]->name() << std::endl;
        }
    }
}

int ShapeCollection::getNumberRepetitionsName(const std::string& name) const {
    int count = 0;
    for (int i = 0; i < currentFigures_; ++i) {
        if (figures_[i] != nullptr && figures_[i]->name() == name) {
            ++count;
        }
    }
    return count;
}

const Shape* ShapeCollection::findSmallestArea() const {
    if (currentFigures_ == 0 || figures_ == nullptr) {
        return nullptr;
    }
    
    const Shape* smallest = nullptr;
    double minArea = std::numeric_limits<double>::max();
    
    for (int i = 0; i < currentFigures_; ++i) {
        if (figures_[i] != nullptr) {
            double currentArea = figures_[i]->area();
            if (currentArea < minArea) {
                minArea = currentArea;
                smallest = figures_[i];
            }
        }
    }
    return smallest;
}