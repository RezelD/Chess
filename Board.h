#pragma once
#include <array>
#include <iostream>
#include <iomanip>
#include "Pieces.h"

using namespace std;

enum Square {

    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
    OOB = -1
};

inline Square makeSquare(int row, int col) {
	return static_cast<Square>(row << 3 | col);
}

class Board {

    private:

    uint64_t whitePawns;
    uint64_t whiteRooks;
    uint64_t whiteKnights;
    uint64_t whiteBishops;
    uint64_t whiteQueen;
    uint64_t whiteKing;

    uint64_t blackPawns;
    uint64_t blackRooks;
    uint64_t blackKnights;
    uint64_t blackBishops;
    uint64_t blackQueen;
    uint64_t blackKing;

    public:

    Board() {

        whitePawns = 0x000000000000FF00ULL;
        whiteRooks = 0x0000000000000081ULL;
        whiteKnights = 0x0000000000000042ULL;
        whiteBishops = 0x0000000000000024ULL;
        whiteQueen = 0x0000000000000008ULL;
        whiteKing = 0x0000000000000010ULL;

        blackPawns = 0x00FF000000000000ULL;
        blackRooks = 0x8100000000000000ULL;
        blackKnights = 0x4200000000000000ULL;
        blackBishops = 0x2400000000000000ULL;
        blackQueen = 0x0800000000000000ULL;
        blackKing = 0x1000000000000000ULL;
    }

    Board(const array<array<char, 8>, 8>& board);

    bool isOccupied(Square square);

    uint64_t mask(Square square) {
        return 1ULL << square;
    }

    uint64_t getCol(Square square) {
        return 0x0101010101010101ULL << (square & 7);
    }

    uint64_t getRow(Square square) {
        return 0x00000000000000FFULL << ((square >> 3) * 8);
    }

    Square changeRow(Square square, int delta);

    Square changeCol(Square square, int delta);

    int getRowNum(Square square) {
        return square / 8;
    }

    int getColNum(Square square) {
        return square % 8;
    }

    PieceType getPieceAtSquare(Square square);

    void printChessBoard();
};

extern Board board;
