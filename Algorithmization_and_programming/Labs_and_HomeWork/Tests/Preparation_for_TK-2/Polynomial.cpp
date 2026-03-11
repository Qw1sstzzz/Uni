#include "Polynomial.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <cstring>  // Для std::swap

using std::swap;

Polynomial::Polynomial() : coefficients_(nullptr), degree_(0), capacity_(0) {}

Polynomial::Polynomial(size_t degree) : degree_(degree), capacity_(degree + 1) {
    try {
        coefficients_ = new double[capacity_]();
    } catch (const std::bad_alloc& e) {
        throw std::runtime_error("Failed to allocate memory for polynomial");
    }
}

Polynomial::Polynomial(const double* coeffs, size_t degree) : degree_(degree), capacity_(degree + 1) {
    try {
        coefficients_ = new double[capacity_];
        for (size_t i = 0; i <= degree; ++i) {
            coefficients_[i] = coeffs[i];
        }
    } catch (const std::bad_alloc& e) {
        throw std::runtime_error("Failed to allocate memory for polynomial");
    }
}

Polynomial::Polynomial(const Polynomial& other) : degree_(other.degree_), capacity_(other.capacity_) {
    try {
        coefficients_ = new double[capacity_];
        for (size_t i = 0; i <= degree_; ++i) {
            coefficients_[i] = other.coefficients_[i];
        }
    } catch (const std::bad_alloc& e) {
        throw std::runtime_error("Failed to copy polynomial");
    }
}

Polynomial::Polynomial(Polynomial&& other) noexcept 
    : coefficients_(other.coefficients_), degree_(other.degree_), capacity_(other.capacity_) {
    other.coefficients_ = nullptr;
    other.degree_ = 0;
    other.capacity_ = 0;
}

Polynomial& Polynomial::operator=(Polynomial other) noexcept {
    swap(other);
    return *this;
}

Polynomial::~Polynomial() {
    delete[] coefficients_;
}

size_t Polynomial::degree() const { 
    return degree_; 
}

double Polynomial::evaluate(double x) const {
    double result = 0.0;
    double power = 1.0;
    for (size_t i = 0; i <= degree_; ++i) {
        result += coefficients_[i] * power;
        power *= x;
    }
    return result;
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    size_t maxDegree = std::max(degree_, other.degree_);
    Polynomial result(maxDegree);
    
    for (size_t i = 0; i <= maxDegree; ++i) {
        double coeff = 0.0;
        if (i <= degree_) coeff += coefficients_[i];
        if (i <= other.degree_) coeff += other.coefficients_[i];
        result.coefficients_[i] = coeff;
    }
    
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    size_t maxDegree = std::max(degree_, other.degree_);
    Polynomial result(maxDegree);
    
    for (size_t i = 0; i <= maxDegree; ++i) {
        double coeff = 0.0;
        if (i <= degree_) coeff += coefficients_[i];
        if (i <= other.degree_) coeff -= other.coefficients_[i];
        result.coefficients_[i] = coeff;
    }
    
    return result;
}

Polynomial Polynomial::operator*(double scalar) const {
    Polynomial result(degree_);
    for (size_t i = 0; i <= degree_; ++i) {
        result.coefficients_[i] = coefficients_[i] * scalar;
    }
    return result;
}

Polynomial Polynomial::operator/(double scalar) const {
    if (std::abs(scalar) < 1e-10) {
        throw std::invalid_argument("Division by zero");
    }
    return *this * (1.0 / scalar);
}

bool Polynomial::operator==(const Polynomial& other) const {
    if (degree_ != other.degree_) return false;
    
    for (size_t i = 0; i <= degree_; ++i) {
        if (std::abs(coefficients_[i] - other.coefficients_[i]) > 1e-7) {
            return false;
        }
    }
    return true;
}

std::istream& operator>>(std::istream& in, Polynomial& poly) {
    size_t degree;
    in >> degree;
    
    poly.cleanup();
    poly.degree_ = degree;
    poly.capacity_ = degree + 1;
    
    try {
        poly.coefficients_ = new double[poly.capacity_];
    } catch (const std::bad_alloc& e) {
        throw std::runtime_error("Failed to allocate memory for polynomial coefficients");
    }
    
    for (size_t i = 0; i <= degree; ++i) {
        in >> poly.coefficients_[i];
        if (in.fail()) {
            delete[] poly.coefficients_;
            poly.coefficients_ = nullptr;
            throw std::invalid_argument("Invalid coefficient");
        }
    }
    
    return in;
}

std::ostream& operator<<(std::ostream& out, const Polynomial& poly) {
    out << "Polynomial(degree=" << poly.degree_ << "): ";
    for (size_t i = poly.degree_; i > 0; --i) {
        out << poly.coefficients_[i] << "x^" << i << " + ";
    }
    out << poly.coefficients_[0];
    return out;
}

void Polynomial::cleanup() {
    delete[] coefficients_;
    coefficients_ = nullptr;
    degree_ = 0;
    capacity_ = 0;
}

void Polynomial::swap(Polynomial& other) noexcept {
    std::swap(coefficients_, other.coefficients_);
    std::swap(degree_, other.degree_);
    std::swap(capacity_, other.capacity_);
}