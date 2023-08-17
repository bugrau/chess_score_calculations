#ifndef PIECES_HPP
#define PIECES_HPP

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility> // For std::pair

class Piece {
public:
    Piece(bool isWhite) : isWhite(isWhite) {}
    virtual ~Piece() {}

    virtual void print() const = 0;

    virtual std::vector<std::pair<int, int>> getCapturingMoves(int row, int col) const = 0;

    bool isWhite;

};

class King : public Piece {
public:
    King(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "sb" : "ss") << " ";
    }

    std::vector<std::pair<int, int>> getCapturingMoves(int row, int col) const override {
        std::vector<std::pair<int, int>> capturingMoves;
        //TODO KING 
        return capturingMoves;
    }
};

class Queen : public Piece {
public:
    Queen(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "vb" : "vs") << " ";
    }

    std::vector<std::pair<int, int>> getCapturingMoves(int row, int col) const override {
        std::vector<std::pair<int, int>> capturingMoves;
        return capturingMoves;
    }
};

class Rook : public Piece {
public:
    Rook(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "kb" : "ks") << " ";
    }

    std::vector<std::pair<int, int>> getCapturingMoves(int row, int col) const override {
        std::vector<std::pair<int, int>> capturingMoves;
        return capturingMoves;
    }
};

class Bishop : public Piece {
public:
    Bishop(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "fb" : "fs") << " ";
    }

    std::vector<std::pair<int, int>> getCapturingMoves(int row, int col) const override {
        std::vector<std::pair<int, int>> capturingMoves;
        return capturingMoves;
    }
};

class Knight : public Piece {
public:
    Knight(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "ab" : "as") << " ";
    }

    std::vector<std::pair<int, int>> getCapturingMoves(int row, int col) const override {
        std::vector<std::pair<int, int>> capturingMoves;
        // TODO KNIGHT
        return capturingMoves;
    }

};

class Pawn : public Piece {
public:
    Pawn(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "pb" : "ps") << " ";
    }

    std::vector<std::pair<int, int>> getCapturingMoves(int row, int col) const override {
        
        std::vector<std::pair<int, int>> capturingMoves;
        // Generate every possible move
        int newRow = 0;//this->isWhite ? row-1 : row+1;
        /*
        Board:
          0 1 2 3 4 5 6 7  
        0 X X X X X X X X -> Black
        1 P X O X O X X X -> Black
        2 X O X X X O X X
        3 X X X A X X X X
        4 X O X X X O X X
        5 X X O X O X X X
        6 X X X X X X X X -> White
        7 X X X X X X X X -> White
        */


        if(this->isWhite) {
            newRow = row - 1;
        } else {
            newRow = row + 1;
        }
        capturingMoves.emplace_back(std::make_pair(newRow, col+1));
        capturingMoves.emplace_back(std::make_pair(newRow, col-1));

        // Filter out invalid values
        std::vector<std::pair<int,int>> updatedCapturingMoves;
        for (const auto& pair : capturingMoves) {
            bool hasNegative = false;
            if(pair.first < 0 || pair.second < 0) {
                hasNegative = true;
            }
            if (!hasNegative) {
                updatedCapturingMoves.push_back(pair);
            }
        }

        return updatedCapturingMoves;
    }

private:
    bool isValidSquare(int row, int col) const {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }
};


#endif // PIECES_HPP