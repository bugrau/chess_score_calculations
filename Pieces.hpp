#ifndef PIECES_HPP
#define PIECES_HPP

#include <iostream>
#include <vector>
#include <utility> // For std::pair

class Piece {
public:
    Piece(bool isWhite) : isWhite(isWhite) {}
    virtual ~Piece() {}

    virtual void print() const = 0;

    bool isWhite;

};

class King : public Piece {
public:
    King(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "sb" : "ss") << " ";
    }
};

class Queen : public Piece {
public:
    Queen(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "vb" : "vs") << " ";
    }
};

class Rook : public Piece {
public:
    Rook(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "kb" : "ks") << " ";
    }
};

class Bishop : public Piece {
public:
    Bishop(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "fb" : "fs") << " ";
    }
};

class Knight : public Piece {
public:
    Knight(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "ab" : "as") << " ";
    }
};

class Pawn : public Piece {
public:
    Pawn(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "pb" : "ps") << " ";
    }

    //std::vector<std::pair<int, int>> getLegalMoves(int row, int col, const ChessBoard& chessBoard) const;

private:
    bool isValidSquare(int row, int col) const {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }
};

/*std::vector<std::pair<int, int>> Pawn::getLegalMoves(int row, int col, const ChessBoard& chessBoard) const {
    std::vector<std::pair<int, int>> legalMoves;

    int forwardStep = (isWhite ? -1 : 1);

    int nextRow = row + forwardStep;

    if (isValidSquare(nextRow, col) && chessBoard.isEmpty(nextRow, col)) {
        legalMoves.emplace_back(nextRow, col);
    }

    if ((isWhite && row == 6) || (!isWhite && row == 1)) {
        int doubleStepRow = row + 2 * forwardStep;
        if (isValidSquare(doubleStepRow, col) && chessBoard.isEmpty(doubleStepRow, col) && chessBoard.isEmpty(nextRow, col)) {
            legalMoves.emplace_back(doubleStepRow, col);
        }
    }

    int leftDiagonal = col - 1;
    int rightDiagonal = col + 1;

    if (isValidSquare(nextRow, leftDiagonal) && chessBoard.isOccupiedByOpponent(nextRow, leftDiagonal, isWhite)) {
        legalMoves.emplace_back(nextRow, leftDiagonal);
    }

    if (isValidSquare(nextRow, rightDiagonal) && chessBoard.isOccupiedByOpponent(nextRow, rightDiagonal, isWhite)) {
        legalMoves.emplace_back(nextRow, rightDiagonal);
    }

    return legalMoves;
}
*/



#endif // PIECES_HPP