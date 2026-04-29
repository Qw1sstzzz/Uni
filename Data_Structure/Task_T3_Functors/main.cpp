#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>
#include <iomanip>
#include <cctype>


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
    return std::equal(a.points.begin(), a.points.end(), b.points.begin(), b.points.end());
}


double area(const Polygon& poly) {
    const auto& p = poly.points;
    int n = p.size();
    if (n < 3) return 0.0;

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        sum += (static_cast<long long>(p[i].x) * p[j].y) - (static_cast<long long>(p[j].x) * p[i].y);
    }
    return std::abs(sum) / 2.0;
}

struct AreaCalculator {
    double operator()(const Polygon& p) const {
        return area(p);
    }
} ;


struct IsVertexCountOdd {
    bool operator()(const Polygon& p) const {
        return p.points.size() % 2 != 0;
    }
} ;

struct IsVertexCountEven {
    bool operator()(const Polygon& p) const {
        return p.points.size() % 2 == 0;
    }
} ;

struct HasVertexCount {
    size_t num;
    HasVertexCount(size_t count) : num(count) {}

    bool operator()(const Polygon& p) const {
        return p.points.size() == num;
    }
};


int main(void) {

    return 0;
}
