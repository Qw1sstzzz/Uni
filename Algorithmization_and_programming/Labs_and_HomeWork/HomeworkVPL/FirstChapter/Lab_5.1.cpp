#include <iostream>
#include <limits>

int is_correct_input() {
    int n;
    std::cin >> n;

    if (std::cin.fail()) {
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Invalid input. You have to write numbers!\n");
    }
    return n;
}

void our_function() {
    int num = 0;

    int sum = 0, sum_positive = 0;
    int count = 0, count_positive = 0;
    int max = INT_MIN, min_positive = INT_MAX;


    while (true) {
        try {
            num = is_correct_input();
        }
        catch(const std::invalid_argument& e) {
            std::cerr << e.what() << "\n";
        }
        
        if (num == 0) {
            break;
        }

        if (num > 0) {
            count_positive++;
            sum_positive += num;
            if (num < min_positive) {
                min_positive = num;
            }
        }

        if (num > max) {
            max = num;
        }

        count++;
        sum += num;
    }

    if (count == 0) {
        throw std::runtime_error("ERROR: Empty sequence");
    }
    else {
        std::cout << "Arithmetic mean of all numbers = " << (double)sum / (double)count << std::endl;
        std::cout << "Maximum value = " << max << std::endl;
        
    }

    if (count_positive == 0) {
        std::cerr << "ERROR: Not positive numbers in the sequence";
    }
    else {
        std::cout << "Arithmetic mean of positive numbers = " << (double)sum_positive / (double)count_positive << std::endl;
        std::cout << "Minimum positive value = " << min_positive << std::endl;
    }

}

int main(void) {
    std::cout << "Enter your sequence: \n";
    try {
        our_function();
    }
    catch(const std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
    }
    catch(const std::domain_error& e) {
        std::cerr << e.what() << "\n";
    }
    catch(const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
    }
    catch(...) {
        std::cerr << "Unknown error occurred\n";
    }
    
    return 0;
}