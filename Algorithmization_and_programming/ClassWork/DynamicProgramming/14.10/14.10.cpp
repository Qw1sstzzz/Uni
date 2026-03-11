#include <iostream>
#include <fstream>


void allocateMemoryForArray(int** matrix, int nDims) {

    if (nDims <= 0) {
        throw std::invalid_argument("ERROR: can't create matrix with negative sides!!!");
    }
    int rows = nDims;
    int columns = nDims;

    matrix = new int* [rows] { nullptr };
    for (int i = 0; i < columns; i++) {
        matrix[i] = new int[rows] { 0 };
    }

}


void deleteMatrix(int** matrix, int nDims) {
    if (matrix != nullptr) {
        for (int i = 0; i < nDims; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}


void readMatrixFromFile(int** matrix, int nDims, const std::string& filename) {
    std::ifstream in(filename); // Чтение
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open input file: " + filename);
    }

    for (int i = 0; i < nDims; i++) {
        for (int j = 0; j < nDims; j++) {
            if (!(in >> matrix[i][j])) {
                throw std::runtime_error("Invalid or incomplete data in input file: " + filename);
            }
        } 
    }
    in.close();
}


void writeMatrixToFile(int** matrix, int nDims, const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot create output file: " + filename);
    }

    for (int i = 0; i < nDims; i++) {
        for (int j = 0; j < nDims; j++) {
            out << matrix[i][j];
            if (j < nDims - 1) {
                out << "\t";
            }
        }
        out << "\n"; 
    }
}

void rewriteToAnotherFile() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    if (!inputFile.is_open()) {
        std::cerr << "ERROR: can't open 'input.txt'\n";
        outputFile.close();
        exit(1);
    }

    if (!outputFile.is_open()) {
        std::cerr << "ERROR: can't create 'output.txt'\n";
        inputFile.close();
        exit(1);
    }

    std::string line;

    while (std::getline(inputFile, line)) {
        outputFile << line << "\n";
    }

    inputFile.close();
    outputFile.close();
    
    std::cout << "File was copied" << std::endl;
}


int main(void) {
    rewriteToAnotherFile();

    int nDims = 0;
    int** matrix = nullptr;

    std::cout << "Enter number of rows and columns:\n";
    std::cin >> nDims;

    try {
        allocateMemoryForArray(matrix, nDims);
        readMatrixFromFile(matrix, nDims, "in.txt");
        writeMatrixToFile(matrix, nDims, "out.txt");
    }
    catch(const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
        deleteMatrix(matrix, nDims);
    }
    catch(const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        deleteMatrix(matrix, nDims);
    }

    deleteMatrix(matrix, nDims);
    return 0;
}