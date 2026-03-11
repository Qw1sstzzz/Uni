#include <iostream>
#include <limits>
#include <fstream>


void inArray(int** matrix, int rows, int columns, std::ifstream& inFile) {
    if (!matrix) {
        throw std::invalid_argument("ERROR: Memory not allocated for array");
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (!(inFile >> matrix[i][j])) {
                throw std::invalid_argument("ERROR: Invalid matrix element");
            }
        }
    }
}



void outFile(int res, std::ofstream& outFile){
    if (!outFile.is_open()) {
        throw std::exception("ERROR: file is closed!\n");
    }
    
    outFile << "The number of rows that do not contain consecutive identical elements: " << res << "\n";

    std::cout << "\nData were recorded!\n";
}


void outArray(int** matrix, int rows, int columns) {
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}


void deleteMatrix(int** matrix, int rows, int cols) {
    if (matrix != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}


int countRowsWithoutRecur(int** matrix, int rows, int columns) {
    int res = 0;
    for (int i = 0; i < rows; i++) {
        bool flag = true;
        for (int j = 0; j < columns - 1; j++) {
            if (matrix[i][j] == matrix[i][j+1]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            res++;
        }
    }
    return res;
}


void fillFile(int res, std::ofstream& outFile){
    if (!outFile.is_open()) {
        std::cerr << "ERROR: file is closed!\n";
        exit(1);
    }
    outFile << "The number of rows that do not contain consecutive identical elements: " << res << "\n";

    std::cout << "\nData were recorded!\n";
}



int main(void) {
    std::cout << "Variant - 9\n";

    std::ifstream inFile("Input_Individual_1.txt");
    int rows = 0, columns = 0, result = 0;

    inFile >> rows >> columns;
    std::cout << "Number of rows: " << rows << "\n";
    if (rows <= 0) {
        std::cerr << "ERROR: Invalid number of rows specified\n";
        return 1;
    }

    std::cout << "Number of columns: " << columns << "\n";
    if (columns <= 0) {
        std::cerr<<"ERROR: Invalid number of columns specified\n";
        return 1;
    }


    std::ofstream outFile("Output_Individual_1.txt");
    int** matrix = nullptr;

    try {
        matrix = new int* [rows]{nullptr};
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int [columns]{0};
        }

        inArray(matrix, rows, columns, inFile);
        
        std::cout << "\nMatrix:\n";
        outArray(matrix, rows, columns);

        result = countRowsWithoutRecur(matrix, rows, columns);
        std::cout << "\nTask№9: " << result << std::endl;

        fillFile(result, outFile);
    }

    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';

        deleteMatrix(matrix, rows, columns);
        outFile.close();
        return 1;
    }

    catch (std::exception& e) {
        std::cerr << e.what() << '\n';

        deleteMatrix(matrix, rows, columns);
        outFile.close();
        return 1;
    }

    deleteMatrix(matrix, rows, columns);
    outFile.close();
    return 0;
}