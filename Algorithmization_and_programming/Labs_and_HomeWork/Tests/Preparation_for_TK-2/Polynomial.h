#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <cstddef>  // Для size_t

class Polynomial {
public:
    Polynomial();
    Polynomial(size_t degree);
    Polynomial(const double* coeffs, size_t degree);
    
    // Правило пяти
    Polynomial(const Polynomial& other);
    Polynomial(Polynomial&& other) noexcept;
    Polynomial& operator=(Polynomial other) noexcept;
    ~Polynomial();
    
    size_t degree() const;
    double evaluate(double x) const;
    
    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator-(const Polynomial& other) const;
    Polynomial operator*(double scalar) const;
    Polynomial operator/(double scalar) const;
    
    bool operator==(const Polynomial& other) const;
    
    friend std::istream& operator>>(std::istream& in, Polynomial& poly);
    friend std::ostream& operator<<(std::ostream& out, const Polynomial& poly);

private:
    double* coefficients_;
    size_t degree_;
    size_t capacity_;
    
    void cleanup();
    void swap(Polynomial& other) noexcept;
};

#endif // POLYNOMIAL_H