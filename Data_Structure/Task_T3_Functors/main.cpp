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
    return std::equal(a.points.begin(), a.points.end(), b.points.begin());
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


Polygon parsePolygon(const std::string& line) {
    std::istringstream iss(line);
    int n;
    if (!(iss >> n) || n < 3) {
        return {};
    }

    Polygon poly;

    for (int i = 0; i < n; ++i) {
        char open, semicolon, close;
        int x, y;
        if (!(iss >> open >> x >> semicolon >> y >> close)) {
            return {};
        }
        if (open != '(' || semicolon != ';' || close != ')') {
            return {};
        }
        poly.points.push_back({x, y});
    }

    std::string extra;
    if (iss >> extra) {
        return {};
    }

    return poly;
}


struct AreaSummator {
    std::function<bool(const Polygon&)> filter;

    AreaSummator(std::function<bool(const Polygon&)> f) : filter(f) {}

    double operator()(double acc, const Polygon& p) const {
        return filter(p) ? acc + area(p) : acc;
    }
} ;

struct CompareByArea {
    bool operator()(const Polygon& a, const Polygon& b) const {
        return area(a) < area(b);
    }
} ;

struct CompareByVertexes {
    bool operator()(const Polygon& a, const Polygon& b) const {
        return a.points.size() < b.points.size();
    }
} ;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: no filename provided\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: cannot open file\n";
        return 1;
    }

    std::vector<Polygon> polygons;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        Polygon p = parsePolygon(line);
        if (!p.points.empty()) {
            polygons.push_back(p);
        }
    }

    std::cout << std::fixed << std::setprecision(1);

    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "AREA") {
            std::string sub;
            std::cin >> sub;

            if (sub == "ODD") {
                double res = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double acc, const Polygon& p) {
                    return IsVertexCountOdd()(p) ? acc + area(p) : acc;
                });
                std::cout << res << std::endl;
            }

            else if (sub == "EVEN") {
                double res = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double acc, const Polygon& p){
                    return IsVertexCountEven()(p) ? acc + area(p) : acc;
                });
                std::cout << res << std::endl;
            }

            else if (sub == "MEAN") {
                if (polygons.empty()) {
                    std::cout << "<INVALID COMMAND>\n";
                    continue;
                }
                double res = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double acc, const Polygon& p){
                    return acc + area(p);
                });
                std::cout << res / polygons.size() << std::endl;
            }

            else {
                bool isNumber = !sub.empty() && std::all_of(sub.begin(), sub.end(), ::isdigit);
                if (isNumber) {
                    size_t n = std::stoul(sub);
                    if (n > 2) {
                        double res = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                        [n](double acc, const Polygon& p) {
                            return HasVertexCount(n)(p) ? acc + area(p) : acc;
                        });
                        std::cout << res << std::endl;
                    }
                    else {
                        std::cout << "<INVALID COMMAND>\n";
                    }
                }
                else {
                    std::cout << "<INVALID COMMAND>\n";
                }
            }
        }

        else if (cmd == "MAX") {
            std::string sub;
            std::cin >> sub;

            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }

            if (sub == "AREA") {
                auto it = std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return area(a) < area(b);
                });
                std::cout << area(*it) << std::endl;
            }

            else if (sub == "VERTEXES") {
                auto it = std::max_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.points.size() < b.points.size();
                });
                std::cout << it->points.size() << std::endl;
            }

            else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }

        else if (cmd == "MIN") {
            std::string sub;
            std::cin >> sub;

            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }

            if (sub == "AREA") {
                auto it = std::min_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return area(a) < area(b);
                });
                std::cout << area(*it) << std::endl;
            }

            else if (sub == "VERTEXES") {
                auto it = std::min_element(polygons.begin(), polygons.end(),
                [](const Polygon& a, const Polygon& b) {
                    return a.points.size() < b.points.size();
                });
                std::cout << it->points.size() << std::endl;
            }

            else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }

        else if (cmd == "COUNT") {
            std::string sub;
            std::cin >> sub;

            if (sub == "ODD") {
                std::cout << std::count_if(polygons.begin(), polygons.end(), IsVertexCountOdd()) << std::endl;
            }

            else if (sub == "EVEN") {
                std::cout << std::count_if(polygons.begin(), polygons.end(), IsVertexCountEven()) << std::endl;
            }

            else {
                bool isNumber = !sub.empty() && std::all_of(sub.begin(), sub.end(), ::isdigit);
                if (isNumber) {
                    size_t n = std::stoul(sub);
                    if (n > 2) {
                        std::cout << std::count_if(polygons.begin(), polygons.end(), HasVertexCount(n)) << std::endl;
                    }
                    else {
                        std::cout << "<INVALID COMMAND>\n";
                    }
                }
                else {
                    std::cout << "<INVALID COMMAND>\n";
                }
            }
        }
        else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
    return 0;
}
