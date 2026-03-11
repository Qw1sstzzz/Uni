#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
public:
    Point();
    Point(double x, double y);
    
    // Копирование и присваивание по умолчанию
    Point(const Point& other) = default;
    Point& operator=(const Point& other) = default;
    
    // Перемещение по умолчанию
    Point(Point&& other) noexcept = default;
    Point& operator=(Point&& other) noexcept = default;
    
    ~Point() = default;
    
    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);
    
    double distance(const Point& other) const;
    
    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;
    Point& operator+=(const Point& other);
    Point& operator-=(const Point& other);
    
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
    
    friend std::istream& operator>>(std::istream& in, Point& p);
    friend std::ostream& operator<<(std::ostream& out, const Point& p);

private:
    double x_, y_;
};

#endif // POINT_H