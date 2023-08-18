#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include "Pieces.hpp"
#include <string>

class ChessBoard {
public:
    ChessBoard(const std::string inputBoard[][8]) {
        initializeBoard(inputBoard);
    }

    bool isEmpty(int row, int col) const {
        return board[row][col] == nullptr;
    }

    bool isOccupiedByOpponent(int row, int col, bool currentPlayerIsWhite) const {
        if (row < 0 || row >= 8 || col < 0 || col >= 8) {
            return false; // Out of bounds
        }

        Piece* piece = board[row][col];
        return piece != nullptr && piece->isWhite != currentPlayerIsWhite;
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

    float getWhiteScore() {
        float score = 0.0;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] == nullptr || !board[i][j]->isWhite) {
                    continue;
                }
                else {
                    score += board[i][j]->getScore();
                }
            }
        }
        return score;
    }

    float getBlackScore() {
        float score = 0.0;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] == nullptr || board[i][j]->isWhite) {
                    continue;
                }
                else {
                    score += board[i][j]->getScore();
                }
            }
        }
        return score;
    }

    Piece* getPieceAt(int row, int col) const {
        if ((0 <= row && row < 8) && (0 <= col && col < 8)) {
            return this->board[row][col];
        }
        else {
            return nullptr;
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
