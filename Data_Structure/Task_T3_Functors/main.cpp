#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>


struct Point {
    int x, y;
} ;

bool operator==(const Point& a, const Point& b) {
    return ((a.x == b.x) && (a.y == b.y));
}


struct Polygon {
    std::vector<Point> points;
} ;

bool operator==(const Polygon& a, const Polygon& b) {
    if (a.points.size() != b.points.size()) {
        return false;
    }
    return std::equal(a.points.begin(), a.points.end(), b.points.begin());
}

int main(void) {

    return 0;
}
