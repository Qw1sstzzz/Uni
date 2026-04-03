#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Student {
    std::string name;
    int grade;
    int age;
} ;


struct Order {
    int id;
    double price;
    bool isPaid;
} ;


template<typename Filter>
std::vector<Order> processOrders(const std::vector<Order>& orders, Filter filter) {
    std::vector<Order> res;
    for (const auto& i : orders) {
        if (filter(i)) {
            res.push_back(i);
        }
    }
}


int main(void) {
    std::vector<Student> students = {
    {"Alice", 85, 20},
    {"Bob", 92, 19},
    {"Charlie", 78, 21},
    {"Diana", 92, 20}
    } ;

    std::sort(students.begin(), students.end(), [](Student a, Student b){
        return a.name < b.name;
    }) ;

    for (auto i : students) {
        std::cout << i.name << " ";
    }

    std::cout << std::endl;

    std::sort(students.begin(), students.end(), [](Student a, Student b){
        return a.grade > b.grade;
    }) ;

    for (auto i : students) {
        std::cout << i.name << ", " << i.grade << ", " << i.age << "\n";
    }


    std::vector<Order> orders = {
    {1, 1500.0, true},
    {2, 800.0, false},
    {3, 2200.0, true},
    {4, 450.0, false},
    {5, 3100.0, true}
    } ;


}
