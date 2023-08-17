/*
This module contains the legal move generator class
*/
#ifndef LEGAL_MOVE_GENERATOR_HPP
#define LEGAL_MOVE_GENERATOR_HPP

#include "ChessBoard.hpp"
#include <vector>
#include <utility>

class LegalMoveGenerator {
    public:
    LegalMoveGenerator(ChessBoard& chessBoard) : chessBoard(chessBoard) {}

    std::vector<std::pair<int, int>> generateCapturingMoves() {
        std::vector<std::pair<int, int>> capturingMovesVec;
        // Fill the vector later on with
        // capturing moves
        for(int row = 0; row < 8; row++) {
            for(int col = 0; col < 8; col++) {
                if(!chessBoard.isEmpty(row, col)) {
                    Piece* pieceRef = chessBoard.getPieceAt(row, col);
                    //pieceRef->print();
                    auto capturingMoves = pieceRef->getCapturingMoves(row, col);
                    for( auto& i : capturingMoves) {
                        std::cout<<i.first << " : " << i.second << "\n";
                    }
                }
            }
        }

        return capturingMovesVec;
    }

    private:
    ChessBoard& chessBoard;
};



#endif //LEGAL_MOVE_GENERATOR_HPP