#include <iostream>
#include <fstream>
// Variant 2

void allocateMemoryForMatrix(int**& matrix, int rows, int cols) {
    if ((rows <= 0) || (cols <= 0)) {
        throw std::invalid_argument("ERROR: can't create matrix with negative sides!!!");
    }
    matrix = new int* [rows]{nullptr};
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int [cols]{ 0 };
    }
}


void getElementsForMatrix(int** matrix, int rows, int cols, std::ifstream& inFile) {
    if (!matrix) {
        throw std::invalid_argument("ERROR! Memory not allocated to matrix...");
    }

    if (!inFile.is_open()) {
        throw std::runtime_error("ERROR! File is closed...");
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(inFile >> matrix[i][j])) {
                throw std::invalid_argument("ERROR: Invalid matrix element");
            }
        }
    }
}


void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}


int countUniqueElementsInRow(int** matrix, int row, int cols) {
    int countUnique = 0;
    for (int i = 0; i < cols; i++) {
        bool isUnique = true;
        for (int j = 0; j < cols; j++) {
            if ((i != j) && (matrix[row][i] == matrix[row][j])) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            countUnique++;
        }
    }
    return countUnique;
}


void fillFile(int* result, int rows, std::ofstream& outFile) {
    if (!outFile.is_open()) {
        throw std::runtime_error("ERROR! File is closed...");
    }
    for (int i = 0; i < rows; i++) {
        outFile << "Number of unique elements in row №" << i << ": " << result[i] << "\n";
        std::cout << "Number of unique elements in row №" << i << ": " << result[i] << "\n";
    }

    std::cout << "\nData was added!\n";
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

    std::cout << "Enter the number of rows:\n";
    std::cin >> rows;

    if ((rows <= 0) || (std::cin.fail())) {
        std::cerr << "ERROR! Invalid argument for rows...";
        return 1;
    }

    std::cout << "Enter the number of columns:\n";
    std::cin >> cols;

    if ((cols <= 0) || (std::cin.fail())) {
        std::cerr << "ERROR! Invalid argument for columns...";
        return 1;
    }

    std::ifstream inFile("input.txt");
    std::ofstream outFile("output.txt");

    if (!inFile.is_open()) {
        std::cerr << "ERROR! Cannot open input.txt\n";
        return 1;
    }
    if (!outFile.is_open()) {
        std::cerr << "ERROR! Cannot open output.txt\n";
        inFile.close();
        return 1;
    }


    int** matrix = nullptr;
    int* result = nullptr;

    try {
        allocateMemoryForMatrix(matrix, rows, cols);
        result = new int[rows]{ 0 };

        getElementsForMatrix(matrix, rows, cols, inFile);

        std::cout << "Matrix:\n" << std::endl;
        printMatrix(matrix, rows, cols);

        for (int i = 0; i < rows; i++) { 
            result[i] = countUniqueElementsInRow(matrix, i, cols);
        }

        std::cout << "\nTask:\n";
        fillFile(result, rows, outFile);
    }

    catch(const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';

        delete[] result;
        deleteMatrix(matrix, rows, cols);
        outFile.close();
        return 1;
    }

    catch(const std::runtime_error& e) {
        std::cerr << e.what() << '\n';

        delete[] result;
        deleteMatrix(matrix, rows, cols);
        outFile.close();
        return 1;
    }

    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';

        delete[] result;
        deleteMatrix(matrix, rows, cols);
        outFile.close();
        return 1;
    }
    
    delete[] result;
    deleteMatrix(matrix, rows, cols);
    outFile.close();
    return 0;
}