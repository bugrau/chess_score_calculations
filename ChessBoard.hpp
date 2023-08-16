#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include "Pieces.hpp"

class ChessBoard {
public:
    ChessBoard(const std::string inputBoard[][8]) {
        initializeBoard(inputBoard);
    }

    void printBoard() const {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] == nullptr) {
                    std::cout << "-- ";
                }
                else {
                    board[i][j]->print();
                }
            }
            std::cout << std::endl;
        }
    }

private:
    void initializeBoard(const std::string inputBoard[][8]) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                board[i][j] = createPieceFromSymbol(inputBoard[i][j]);
            }
        }
    }

    Piece* createPieceFromSymbol(const std::string& symbol) {
        bool isWhite = (symbol.back() == 'b');

        if (symbol == "sb" || symbol == "ss") {
            return new King(isWhite);
        }
        else if (symbol == "vb" || symbol == "vs") {
            return new Queen(isWhite);
        }
        else if (symbol == "kb" || symbol == "ks") {
            return new Rook(isWhite);
        }
        else if (symbol == "fb" || symbol == "fs") {
            return new Bishop(isWhite);
        }
        else if (symbol == "ab" || symbol == "as") {
            return new Knight(isWhite);
        }
        else if (symbol == "pb" || symbol == "ps") {
            return new Pawn(isWhite);
        }
        else {
            return nullptr; // Empty square
        }
    }

    Piece* board[8][8];
};

#endif // CHESSBOARD_HPP
