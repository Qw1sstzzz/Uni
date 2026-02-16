#include <iostream>
#include <string>
#include <type_traits>


template <typename T>
T average(T value) {
    std::cout << "Базовый: " << value << " (тип: " << typeid(T).name() << ")" << std::endl;
    return value;
}


template<typename T, typename... Args>
auto average(T first, Args... args) {
    std::cout << "Рекурсивный: " << first << " (тип: " << typeid(T).name() << ")" << std::endl;
    
    auto rest_avg = average(args...);
    
    constexpr size_t count = sizeof...(Args) + 1;
    
    
    auto rest_sum = rest_avg * (count - 1);  
    auto total_sum = first + rest_sum;       
    auto result = total_sum / count;    
    
    return result;
}

int main(void) {
    auto result1 = average(1, 2, 3, 4, 5);
    std::cout << "Среднее 1, 2, 3, 4, 5: " << result1 
              << " (тип: " << typeid(result1).name() << ")" << std::endl;
    
    auto result2 = average(10, 20, .30, 40.57);
    std::cout << "Среднее 10, 20, 0.30 40.57: " << result2 
              << " (тип: " << typeid(result2).name() << ")" << std::endl;
    
    return 0;
}