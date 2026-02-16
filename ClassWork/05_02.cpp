#include <iostream>
#include <cstddef>

template<typename T>
T square(T x) { return x * x; } 



template<std::size_t N>
struct Fibonacci {
    static constexpr std::size_t value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
} ;

template<>
struct Fibonacci<0> {
    static constexpr std::size_t value = 0;
} ;

template<>
struct Fibonacci<1> {
    static constexpr std::size_t value = 1;
} ;



template<std::size_t n, std::size_t k>
struct BinominalCoefficent {
    static_assert (n >= k, "n must be greater than or equal to k");
    static constexpr std::size_t value = BinominalCoefficent<n - 1, k - 1>::value + BinominalCoefficent<n - 1, k>::value;
} ;

template<std::size_t n>
struct BinominalCoefficent<n, 0> {
    static constexpr std::size_t value = 1;
} ;


template<std::size_t n>
struct BinominalCoefficent<n, n> {
    static constexpr std::size_t value = 1;
} ;



int main(void) {
    std::cout << "Square of 4: " << square(4) << std::endl;
    std::cout << "Square of 3.14: " << square(3.14) << std::endl;

    std::cout << "================================\n";

    std::cout << "Fibonacci<10>: " << Fibonacci<10>::value << std::endl;
    static_assert(Fibonacci<4>::value == 3, "");

    std::cout << "================================\n";
    
    std::cout << "BinomialCoefficent<7, 3>: " << BinominalCoefficent<7, 3>::value << std::endl;
    
    return 0;
}