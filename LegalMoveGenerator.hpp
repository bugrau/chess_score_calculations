/*
This module contains the legal move generator class
*/
#ifndef LEGAL_MOVE_GENERATOR_HPP
#define LEGAL_MOVE_GENERATOR_HPP

#include "ChessBoard.hpp"
#include "Pieces.hpp"
#include <system_error>
#include <vector>
#include <utility>

class LegalMoveGenerator {
public:
    LegalMoveGenerator(ChessBoard& chessBoard) : chessBoard(chessBoard) {}

    auto generateCapturingMoves() const {

        std::vector<std::pair<int, int>> whiteCaptMoves;
        std::vector<std::pair<int, int>> blackCaptMoves;

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                Piece* pieceRef = chessBoard.getPieceAt(row, col);

                if (pieceRef) {
                    if (Knight* knight = dynamic_cast<Knight*>(pieceRef)) {
                        // Handle Knight-specific logic
                        auto moves = knightCapturingMoves(row, col);
                        if (chessBoard.getPieceAt(row, col)->isWhite) {
                            whiteCaptMoves.insert(whiteCaptMoves.end(), moves.begin(), moves.end());
                        }
                        else {
                            blackCaptMoves.insert(blackCaptMoves.end(), moves.begin(), moves.end());
                        }
                    }
                    else if (Bishop* bishop = dynamic_cast<Bishop*>(pieceRef)) {
                        auto moves = diagonalCapturingMoves(row, col);
                        if (chessBoard.getPieceAt(row, col)->isWhite) {
                            whiteCaptMoves.insert(whiteCaptMoves.end(), moves.begin(), moves.end());
                        }
                        else {
                            blackCaptMoves.insert(blackCaptMoves.end(), moves.begin(), moves.end());
                        }
                    }
                    else if (Rook* rook = dynamic_cast<Rook*>(pieceRef)) {
                        auto moves = vertAndHorzCapturingMoves(row, col);
                        if (chessBoard.getPieceAt(row, col)->isWhite) {
                            whiteCaptMoves.insert(whiteCaptMoves.end(), moves.begin(), moves.end());
                        }
                        else {
                            blackCaptMoves.insert(blackCaptMoves.end(), moves.begin(), moves.end());
                        }
                    }
                    else if (Queen* queen = dynamic_cast<Queen*>(pieceRef)) {
                        auto vertAndHorzMoves = vertAndHorzCapturingMoves(row, col);
                        auto diagonalMoves = diagonalCapturingMoves(row, col);
                        if (chessBoard.getPieceAt(row, col)->isWhite) {
                            whiteCaptMoves.insert(whiteCaptMoves.end(), vertAndHorzMoves.begin(), vertAndHorzMoves.end());
                            whiteCaptMoves.insert(whiteCaptMoves.end(), diagonalMoves.begin(), diagonalMoves.end());
                        }
                        else {
                            blackCaptMoves.insert(blackCaptMoves.end(), vertAndHorzMoves.begin(), vertAndHorzMoves.end());
                            blackCaptMoves.insert(blackCaptMoves.end(), diagonalMoves.begin(), diagonalMoves.end());
                        }
                    }
                    else if (King* king = dynamic_cast<King*>(pieceRef)) {
                        auto moves = kingCapturingMoves(row, col);
                        if (chessBoard.getPieceAt(row, col)->isWhite) {
                            whiteCaptMoves.insert(whiteCaptMoves.end(), moves.begin(), moves.end());
                        }
                        else {
                            blackCaptMoves.insert(blackCaptMoves.end(), moves.begin(), moves.end());
                        }
                    }
                    else if (Pawn* pawn = dynamic_cast<Pawn*>(pieceRef)) {
                        auto moves = pawnCapturingMoves(row, col);
                        if (chessBoard.getPieceAt(row, col)->isWhite) {
                            whiteCaptMoves.insert(whiteCaptMoves.end(), moves.begin(), moves.end());
                        }
                        else {
                            blackCaptMoves.insert(blackCaptMoves.end(), moves.begin(), moves.end());
                        }
                    }
                    else {
                        std::cout << "Unknown type !\n";
                    }
                }
            }
        }
        return std::make_tuple(whiteCaptMoves, blackCaptMoves);
    }

    void setPiecesUnderThreat() {
        auto moves = generateCapturingMoves();

        // Process white capturing moves
        for (auto& move : std::get<0>(moves)) {
            if (chessBoard.isOccupiedByOpponent(move.first, move.second, true)) {
                chessBoard.getPieceAt(move.first, move.second)->setUnderThreat(true);
            }
        }

        // Process black capturing moves
        for (auto& move : std::get<1>(moves)) {
            if (chessBoard.isOccupiedByOpponent(move.first, move.second, false)) {
                chessBoard.getPieceAt(move.first, move.second)->setUnderThreat(true);
            }
        }
    }

private:
    ChessBoard& chessBoard;

    bool withinBounds(int row, int col) const {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }

    std::vector<std::pair<int, int>> knightCapturingMoves(int row, int col) const {
        std::vector<std::pair<int, int>> capturingMoves;
        std::vector<std::pair<int, int>> filteredMoves;

        capturingMoves.emplace_back(std::make_pair(row + 2, col + 1));
        capturingMoves.emplace_back(std::make_pair(row + 2, col - 1));
        capturingMoves.emplace_back(std::make_pair(row - 2, col + 1));
        capturingMoves.emplace_back(std::make_pair(row - 2, col - 1));

        capturingMoves.emplace_back(std::make_pair(row - 1, col + 2));
        capturingMoves.emplace_back(std::make_pair(row - 1, col - 2));
        capturingMoves.emplace_back(std::make_pair(row + 1, col + 2));
        capturingMoves.emplace_back(std::make_pair(row + 1, col - 2));

        for (auto& i : capturingMoves) {
            if (i.first >= 0 && i.first < 8 && i.second >= 0 && i.second < 8) {
                filteredMoves.emplace_back(i);
            }
        }
        return filteredMoves;
    }

    std::vector<std::pair<int, int>> pawnCapturingMoves(int row, int col) const {
        std::vector<std::pair<int, int>> capturingMoves;

        int newRow = chessBoard.getPieceAt(row, col)->isWhite ? row - 1 : row + 1;
        int newCol = col - 1;
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            capturingMoves.emplace_back(std::make_pair(newRow, newCol));
        }
        newCol = col + 1;
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            capturingMoves.emplace_back(std::make_pair(newRow, newCol));
        }

        return capturingMoves;
    }

    std::vector<std::pair<int, int>> kingCapturingMoves(int row, int col) const {
        std::vector<std::pair<int, int>> capturingMoves;

        for (int newRow = row - 1; newRow <= row + 1; newRow++) {
            for (int newCol = col - 1; newCol <= col + 1; newCol++) {
                if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                    capturingMoves.emplace_back(std::make_pair(newRow, newCol));
                }
            }
        }
        return capturingMoves;
    }

    std::vector<std::pair<int, int>> diagonalCapturingMoves(int row, int col) const {
        std::vector<std::pair<int, int>> capturingMoves;
        bool isWhite = chessBoard.getPieceAt(row, col)->isWhite;
        // Top-left diagonal
        int rowNext = row - 1;
        int colNext = col - 1;
        while (withinBounds(rowNext, colNext)) {
            if (!chessBoard.isEmpty(rowNext, colNext)) {
                if (chessBoard.isOccupiedByOpponent(rowNext,
                    colNext, isWhite)) {
                    capturingMoves.emplace_back(std::make_pair(rowNext, colNext));
                }
                break;
            }
            else {
                capturingMoves.emplace_back(std::make_pair(rowNext, colNext));
            }
            rowNext -= 1;
            colNext -= 1;
        }

        // Top-right diagonal
        rowNext = row - 1;
        colNext = col + 1;
        while (withinBounds(rowNext, colNext)) {
            if (!chessBoard.isEmpty(rowNext, colNext)) {
                if (chessBoard.isOccupiedByOpponent(rowNext,
                    colNext, isWhite)) {
                    capturingMoves.emplace_back(std::make_pair(rowNext, colNext));
                }
                break;
            }
            else {
                capturingMoves.emplace_back(std::make_pair(rowNext, colNext));
            }
            rowNext -= 1;
            colNext += 1;
        }

        // Bottom-left diagonal
        rowNext = row + 1;
        colNext = col - 1;
        while (withinBounds(rowNext, colNext)) {
            if (!chessBoard.isEmpty(rowNext, colNext)) {
                if (chessBoard.isOccupiedByOpponent(rowNext,
                    colNext, isWhite)) {
                    capturingMoves.emplace_back(std::make_pair(rowNext, colNext));
                }
                break;
            }
            else {
                capturingMoves.emplace_back(std::make_pair(rowNext, colNext));
            }
            rowNext += 1;
            colNext -= 1;
        }

        // Bottom-right diagonal
        rowNext = row + 1;
        colNext = col + 1;
        while (withinBounds(rowNext, colNext)) {
            if (!chessBoard.isEmpty(rowNext, colNext)) {
                if (chessBoard.isOccupiedByOpponent(rowNext,
                    colNext, isWhite)) {
                    capturingMoves.emplace_back(std::make_pair(rowNext, colNext));
                }
                break;
            }
            else {
                capturingMoves.emplace_back(std::make_pair(rowNext, colNext));
            }
            rowNext += 1;
            colNext += 1;
        }

        return capturingMoves;
    }

    std::vector<std::pair<int, int>> vertAndHorzCapturingMoves(int row, int col) const {
        std::vector<std::pair<int, int>> capturingMoves;
        bool isWhite = chessBoard.getPieceAt(row, col)->isWhite;
        // Top
        int rowNext = row - 1;
        while (withinBounds(rowNext, col)) {
            if (!chessBoard.isEmpty(rowNext, col)) {
                if (chessBoard.isOccupiedByOpponent(rowNext,
                    col, isWhite)) {
                    capturingMoves.emplace_back(std::make_pair(rowNext, col));
                }
                break;
            }
            else {
                capturingMoves.emplace_back(std::make_pair(rowNext, col));
            }
            rowNext -= 1;
        }

        // Bottom
        rowNext = row + 1;
        while (withinBounds(rowNext, col)) {
            if (!chessBoard.isEmpty(rowNext, col)) {
                if (chessBoard.isOccupiedByOpponent(rowNext,
                    col, isWhite)) {
                    capturingMoves.emplace_back(std::make_pair(rowNext, col));
                }
                break;
            }
            else {
                capturingMoves.emplace_back(std::make_pair(rowNext, col));
            }
            rowNext += 1;
        }

        // Right
        int colNext = col + 1;
        while (withinBounds(row, colNext)) {
            if (!chessBoard.isEmpty(row, colNext)) {
                if (chessBoard.isOccupiedByOpponent(row,
                    colNext, isWhite)) {
                    capturingMoves.emplace_back(std::make_pair(row, colNext));
                }
                break;
            }
            else {
                capturingMoves.emplace_back(std::make_pair(row, colNext));
            }
            colNext += 1;
        }

        // Left
        colNext = col - 1;
        while (withinBounds(row, colNext)) {
            if (!chessBoard.isEmpty(row, colNext)) {
                if (chessBoard.isOccupiedByOpponent(row,
                    colNext, isWhite)) {
                    capturingMoves.emplace_back(std::make_pair(row, colNext));
                }
                break;
            }
            else {
                capturingMoves.emplace_back(std::make_pair(row, colNext));
            }
            colNext -= 1;
        }

        return capturingMoves;
    }


};



#endif //LEGAL_MOVE_GENERATOR_HPP