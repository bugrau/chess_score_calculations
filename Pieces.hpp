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

    void setUnderThreat(bool underThreat) {
        this->isUnderThreat = underThreat;
    }

    virtual float getScore() const = 0;

    bool isWhite;
    bool isUnderThreat = false;
private:
};

class King : public Piece {
public:
    King(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "sb" : "ss") << " ";
    }

    float getScore() const override {
        return this->isUnderThreat ? 50.0 : 100.0;
    }

};

class Queen : public Piece {
public:
    Queen(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "vb" : "vs") << " ";
    }

    float getScore() const override {
        return this->isUnderThreat ? 4.5 : 9.0;
    }
};

class Rook : public Piece {
public:
    Rook(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "kb" : "ks") << " ";
    }

    float getScore() const override {
        return this->isUnderThreat ? 2.5 : 5.0;
    }
};

class Bishop : public Piece {
public:
    Bishop(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "fb" : "fs") << " ";
    }

    float getScore() const override {
        return this->isUnderThreat ? 1.5 : 3.0;
    }
};

class Knight : public Piece {
public:
    Knight(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "ab" : "as") << " ";
    }

    float getScore() const override {
        return this->isUnderThreat ? 1.5 : 3.0;
    }

};

class Pawn : public Piece {
public:
    Pawn(bool isWhite) : Piece(isWhite) {}

    void print() const override {
        std::cout << (isWhite ? "pb" : "ps") << " ";
    }

    float getScore() const override {
        return this->isUnderThreat ? 0.5 : 1;
    }

};


#endif // PIECES_HPP