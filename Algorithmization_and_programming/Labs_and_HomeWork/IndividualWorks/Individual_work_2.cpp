#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>

double calculateFunction(double x, double absError, int maxNumber) {
    if (x <= -1.0 || x >= 1.0) {
        throw std::invalid_argument("x must be in interval (-1, 1)");
    }
    
    double sum = 1.0; 
    double currentValue = 1.0;
    int n = 1;   

    while (n <= maxNumber) {
        currentValue = currentValue * (-x) * (n + 2) / n;
        if (std::abs(currentValue) < absError) {
            break;
        }
        sum += currentValue;
        n++;
    }
    
    if (n > maxNumber && std::abs(currentValue) >= absError) {
        throw std::runtime_error("Maximum number of terms reached without achieving required accuracy");
    }
    
    return sum;
}

double checkCorrectAnswer(double x) {
    return 1.0 / std::pow(x + 1.0, 3);
}

int main(void) {
    double absError = 0.0, start = 0.0, end = 0.0, step = 0.0;
    int numberMax = 0;
    
    std::cout << "Enter absolute error:\n";
    std::cin >> absError;
    if (absError <= 0.0) {
        std::cerr << "Error: absError must be positive digit\n";
        return 1;
    }
    
    std::cout << "Enter maximum number of terms:\n";
    std::cin >> numberMax;
    if (numberMax <= 0) {
        std::cerr << "Error: numberMax must be positive digit\n";
        return 1;
    }
    
    std::cout << "Enter interval start (must be > -1 and < 1):\n";
    std::cin >> start;
    if ((start <= -1.0) || (start >= 1.0)) {
        std::cerr << "Error: interval must be within (-1, 1)\n";
        return 1;
    }

    std::cout << "Enter interval end (must be > -1 and < 1):\n";
    std::cin >> end;
    if ((end <= -1.0) || (end >= 1.0)) {
        std::cerr << "Error: interval must be within (-1, 1)\n";
        return 1;
    }
    
    if (start >= end) {
        std::cerr << "Error: start must be less than end\n";
        return 1;
    }

    std::cout << "Enter step:\n";
    std::cin >> step;
    if (step <= 0) {
        std::cerr << "Error: step must be positive digit\n";
        return 1;
    }
    int temp = std::ceil((end - start) / step);

    std::cout << "\nOur table:\n";   
    std::cout << "x\t\t\tMy Function\t\tBuilt-in\t\tDifference" << std::endl;    
    for (int i = 0; i <= temp; i++) {
        double x = start + i * step; 
        try {
            double myValue = calculateFunction(x, absError, numberMax);
            double commonValue = checkCorrectAnswer(x);
            double difference = std::abs(myValue - commonValue);
        
            std::cout << std::fixed << std::setprecision(8);
            std::cout << x << "\t\t" << myValue << "\t\t" << commonValue << "\t\t" << difference << std::endl;
        } 
        catch(const std::invalid_argument& e) {
            std::cerr << "ERROR: " << e.what() << " for x = " << x << std::endl;
            continue;
        }
        catch(const std::runtime_error& e) {
            std::cerr << "ERROR: " << e.what() << " for x = " << x << std::endl;
            continue;
        }
        catch(const std::exception& e) {
            std::cerr << "ERROR: " << e.what() << " for x = " << x << std::endl;
            continue;
        }
    }
    return 0;
}