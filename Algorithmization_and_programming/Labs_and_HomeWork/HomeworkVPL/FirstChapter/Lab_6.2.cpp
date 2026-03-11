#include <iostream>
#include <limits>

void in_array(int** matrix, int rows, int columns) {
    if (!matrix) {
        throw std::invalid_argument("ERROR: Memory not allocated for array");
    }
    if (rows <= 0) {
        throw std::invalid_argument("ERROR: Invalid number of rows specified\n");
    }
    if (columns <= 0) {
        throw std::invalid_argument("ERROR: Invalid number of columns specified\n");
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << "Element [" << i << "][" << j << "]: ";
            if (!(std::cin >> matrix[i][j])) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if(std::cin.eof()) {
                    throw std::invalid_argument("ERROR: Not enough matrix elements");
                }
                else {
                    throw std::invalid_argument("ERROR: Invalid matrix element");
                }
            }
        }
    }
}


void out_array(int** matrix, int rows, int columns) {
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
}


void arithmeticMeansOfPositive(int** matrix, int rows, int columns, double* vector) {
     if ((!matrix) || (!vector)) {
        throw std::invalid_argument("ERROR: It is impossible to construct a vector");
    }

    for(int i = 0; i < rows; i++) {
        double sum = 0.0;
        int count = 0;

        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] >= 0) {
                count++;
                sum += (double)matrix[i][j];
            }
        }

        if (count > 0) {
            vector[i] = sum / (double)count;
        } 
        else {
            throw std::invalid_argument("ERROR: It is impossible to construct a vector");
        }
    }

}


void printVector(double* vector, int rows) {
    std::cout << "\nVector of arithmetic means = ";

    for (int i = 0; i < rows; i++) {
        std::cout << vector[i] << " ";
    }
    std::cout << "\n";
}

int main(void) {
    int rows = 0, columns = 0;
    std::cout << "Enter number of rows:\n";
    std::cin >> rows;
    if ((std::cin.fail()) || (rows <= 0)) {
        std::cerr << "ERROR: Invalid number of rows specified\n";
        return 1;
    }

    std::cout << "Enter number of columns:\n";
    std::cin >> columns;
    if ((std::cin.fail()) || (columns <= 0)) {
        std::cerr<<"ERROR: Invalid number of columns specified\n";
        return 1;
    }
    int** matrix = nullptr;
    double* vector = nullptr;
    try {
        matrix = new int* [rows]{nullptr};
        vector = new double [rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int [columns];
        }

        std::cout << "Enter matrix elements:\n";
        in_array(matrix, rows, columns);
        
        std::cout << "\nMatrix:\n";
        out_array(matrix, rows, columns);

        arithmeticMeansOfPositive(matrix, rows, columns, vector);
        printVector(vector, rows);
    }

    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
        
        if (matrix != nullptr) {
            for (int i = 0; i < rows; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
        if (vector != nullptr) {
            delete[] vector;
        }
        return 1;
    }

    catch (std::exception& e) {
        std::cerr << e.what() << '\n';

        if (matrix != nullptr) {
            for (int i = 0; i < rows; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
        if (vector != nullptr) {
            delete[] vector;
        }
        return 1;
    }

    if (matrix != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    if (vector != nullptr) {
        delete[] vector;
    }
    return 0;
}