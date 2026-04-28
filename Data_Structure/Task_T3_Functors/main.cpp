#include <iostream>
#include <vector>
#include <functional>


struct Point {
    int x, y;
} ;

bool operator==(const Point& a, const Point& b) {
    return ((a.x == b.x) && (a.y == b.y));
}


int main(void) {

    return 0;
}
