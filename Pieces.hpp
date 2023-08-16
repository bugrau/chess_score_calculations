#ifndef PIECES_HPP
#define PIECES_HPP

#include <iostream>

class Piece {
public:
    Piece(bool isWhite) : isWhite(isWhite) {}
    virtual ~Piece() {}

    virtual void print() const = 0;

protected:
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
};

#endif // PIECES_HPP