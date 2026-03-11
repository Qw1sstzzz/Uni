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
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}


bool isOrderedArray(int* array, int number_of_columns) {
    bool flag = true;

    if (number_of_columns == 1) {
        return true;
    }

    for (int i = 0; i < number_of_columns - 1; i++) {
        if (array[i] > array[i+1]) {
            flag = false;
            break;
        }
    }
    return flag;
}


int getNumberOfOrderedRows(int** matrix, int rows, int columns) {
    int count = 0;
    for(int i = 0; i < rows; i++) {
        if (isOrderedArray(matrix[i], columns)) {
            count++;
        }
    }
    return count;
}


int main(void) {
    int rows = 0, columns = 0, result = 0;
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

    try {
        matrix = new int* [rows]{nullptr};
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int [columns];
        }

        std::cout << "Enter matrix elements:\n";
        in_array(matrix, rows, columns);
        
        std::cout << "\nMatrix:\n";
        out_array(matrix, rows, columns);

        result = getNumberOfOrderedRows(matrix, rows, columns);
        std::cout << "\nNumber of ordered rows = " << result << std::endl;
    }

    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';

        if (matrix != nullptr) {
            for (int i = 0; i < rows; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
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
        return 1;
    }

    if (matrix != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
        
    return 0;
}