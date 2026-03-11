#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <limits>

/*
const int MAX_SIZE = 10;

int fillForward(char* matrix, int size) {
    if (!matrix) {
        throw std::invalid_argument("ERROR: *matrix = nullptr");
    }

    if (size <= 0) {
        throw std::invalid_argument("ERROR: size must be positive");
    }

    char symb;
    int count = 0;
    std::cout << "Enter symbols one by one: \n";

    while (std::cin >> symb) {
        if (symb == '0') {
            break;
        }
        if (count > size) {
            throw std::out_of_range("ERROR: matrix size is out of range");
        }
        matrix[count] = symb;
        count++;
    }
    return count;
}

void printReverse(const char* matrix, int size) {
    std::cout << "\nReversed symbols\n";
    for (int i = size - 1; i >= 0; i--) {
        std::cout << matrix[i] << " ";
    }
    std::cout << "\n";
}

int main(void) {
    char* dynamicMatrix = new char[MAX_SIZE];

    try {
        int n = fillForward(dynamicMatrix, MAX_SIZE);
        printReverse(dynamicMatrix, n); 
    }

    catch(std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        delete[] dynamicMatrix;
        return 1;
    }

    delete[] dynamicMatrix;
    return 0;
}
*/

void inArray(int** matrix, int rows, int columns) {
    if (!matrix) {
        throw std::invalid_argument("ERROR: **matrix = nullptr");
    }
    if ((rows <= 0) || (columns <= 0)) {
            throw std::invalid_argument("ERROR: rows and cols must be positive");
    } 

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (!(std::cin >> matrix[i][j])) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("ERROR: expected integer, but got inavlid data");
            }
        }    
    }
}

void outArray(int** matrix, int rows, int columns) {
    if (!matrix) {
        throw std::invalid_argument("ERROR: **matrix = nullptr");
    }
    if ((rows <= 0) || (columns <= 0)) {
            throw std::invalid_argument("ERROR: rows and cols must be positive");
    } 
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int getMaxOfArray(int* matrix, int rows, int columns) {
    if (!matrix) {
        throw std::invalid_argument("ERROR: **matrix = nullptr");
    }
    if ((rows <= 0) || (columns <= 0)) {
            throw std::invalid_argument("ERROR: rows and cols must be positive");
    } 
    int max = INT_MIN;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            int n = matrix[i*columns + j];
            if (max < n) {
                max = n;
            }
        }
    }
    return max;
}

int main(void) {
    int rows, columns, maximum;
    std::cout << "Enter rows and columns: \n";
    std::cin >> rows >> columns;

    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int [columns];
    }

    int* copy_of_matrix = new int[rows * columns];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            copy_of_matrix[i*columns + j] = matrix[i][j];
        }   
    }

    try {
        inArray(matrix, rows, columns);
        std::cout << "\nMatrix succesfully read!\n";
        outArray(matrix, rows, columns);
        std::cout << "\nMatrix succesfully vivedena!\n";


        maximum = getMaxOfArray(copy_of_matrix, rows, columns);    
        std::cout << "\nMax result is = "<< maximum << "\n";
    }

    catch(const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        return 1;
    }

    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        return 1;
    }
    
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
