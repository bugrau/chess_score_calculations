// chess_score_calculations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "FileReader.hpp"
#include "Pieces.hpp"
#include "ChessBoard.hpp"

int main() {

    const int rows = 8;
    const int cols = 8;


    std::string array[rows][cols];  // Define an 8x8 array of strings

    FileReader fileReader("C:/Users/bugra/Desktop/my projects/chess_score_calculations/board1.txt");  // Replace with the actual file path
    if (!fileReader.openFile()) {
        std::cout << "Unable to open the file." << std::endl;
        return 1;
    }

    if (!fileReader.readArray(array, rows, cols)) {
        fileReader.closeFile();
        return 1;
    }

    fileReader.closeFile();

    ChessBoard chessBoard(array);
    chessBoard.printBoard();

    return 0;
}

