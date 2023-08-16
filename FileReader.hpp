#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class FileReader {
public:
    FileReader(const std::string& filename) : filename(filename) {}

    bool openFile() {
        inputFile.open(filename);
        return inputFile.is_open();
    }

    bool readArray(std::string array[][8], int rows, int cols) {
        for (int i = 0; i < rows; ++i) {
            std::string line;
            if (std::getline(inputFile, line)) {
                std::istringstream iss(line);
                for (int j = 0; j < cols; ++j) {
                    iss >> array[i][j];
                }
            }
            else {
                std::cout << "File does not have enough lines." << std::endl;
                return false;
            }
        }
        return true;
    }

    void closeFile() {
        inputFile.close();
    }

private:
    std::string filename;
    std::ifstream inputFile;
};

class ArrayPrinter {
public:
    static void printArray(const std::string array[][8], int rows, int cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << array[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }
};