#include <iostream>
#include <limits>
#include <fstream>

void allocateMemoryForArray(int**& matrix, int rows, int cols) {
    if ((rows <= 0) || (cols <= 0)) {
        throw std::invalid_argument("ERROR: can't create matrix with negative sides!!!");
    }
    matrix = new int* [rows] { nullptr };
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
}


void inArray(int** matrix, int rows, int columns) {
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


void outArray(int** matrix, int rows, int columns) {
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
}


void transportMatrix(int** matrix, int** t_matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int elem = matrix[i][j];
            t_matrix[j][i] = elem;
        }
    }
}


long long int sumDiagonal(int**matrix, int rows, int cols) {
    int sum_main = 0, sum_sec = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum_main = matrix[i][i];
            sum_sec = matrix[i][rows - 1 - i];
        }
    }    
    long long sum = abs(sum_main) + abs(sum_sec);
    return sum;
}


void findMin(int** matrix, int rows, int cols, const std::string& outputFilename) {
    std::ofstream output(outputFilename, std::ios::app);
    if (!output.is_open()) {
        throw std::runtime_error("Cannot create output file: " + outputFilename);
    }
    for (int i = 0; i < rows; i++) {
        int min = INT_MAX;
        for (int j = 0; j < cols; j++) {
            if (min > matrix[i][j]) {
                min = matrix[i][j];
            }
        }
        output << min << "\t";
        min = INT_MAX; 
    }
    output << "\n";
}

void deleteMatrix(int** matrix, int rows, int cols) {
    if (matrix != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}



int main(void) {
    int rows = 0, cols = 0;
    long long int sum_of_diagnols = 0;
    std::cout << "Enter number of rows:\n";
    std::cin >> rows;
    if ((std::cin.fail()) || (rows <= 0)) {
        std::cerr << "ERROR: Invalid number of rows specified\n";
        return 1;
    }

    std::cout << "Enter number of columns:\n";
    std::cin >> cols;
    if ((std::cin.fail()) || (cols <= 0)) {
        std::cerr<<"ERROR: Invalid number of columns specified\n";
        return 1;
    }
    int** matrix = nullptr;
    int** t_matrix = nullptr;

    try {
        allocateMemoryForArray(matrix, rows, cols);
        allocateMemoryForArray(t_matrix, rows, cols);
        std::cout << "\nMemory has allocated for matrix and it's transported version.\n";

        inArray(matrix, rows, cols);
        std::cout << "\nMatrix was created.\n";

        transportMatrix(matrix, t_matrix, rows, cols);

        std::cout << "\nOG Matrix:\n";
        outArray(matrix, rows, cols);
        std::cout << "\nTransported Matrix:\n";
        outArray(t_matrix, rows, cols);

        sum_of_diagnols = (t_matrix, rows, cols);
        std::cout << "\nSumm of main and pobochnay diagonals: " << sum_of_diagnols << std::endl;
        findMin(t_matrix, rows, cols, "output.txt");
    }
    catch(const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
        deleteMatrix(matrix, rows, cols);
        deleteMatrix(t_matrix, rows, cols);
    }

    deleteMatrix(matrix, rows, cols);
    deleteMatrix(t_matrix, rows, cols);
    return 0;
}