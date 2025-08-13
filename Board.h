#pragma once
#include <array>
#include <cstdint>
#include <iostream>
#include <string>

#include "Pieces.h"

using namespace std;

enum Square : int {

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

inline Square makeSquare(const int row, const int col) {
	return static_cast<Square>(row << 3 | col);
}

class Board {

    private:

    uint64_t whitePawns;
    uint64_t whiteRooks;
    uint64_t whiteKnights;
    uint64_t whiteBishops;
    uint64_t whiteQueens;
    uint64_t whiteKings;

    uint64_t blackPawns;
    uint64_t blackRooks;
    uint64_t blackKnights;
    uint64_t blackBishops;
    uint64_t blackQueens;
    uint64_t blackKings;

    public:

    Board() {

        whitePawns = 0x000000000000FF00ULL;
        whiteRooks = 0x0000000000000081ULL;
        whiteKnights = 0x0000000000000042ULL;
        whiteBishops = 0x0000000000000024ULL;
        whiteQueens = 0x0000000000000008ULL;
        whiteKings = 0x0000000000000010ULL;

        blackPawns = 0x00FF000000000000ULL;
        blackRooks = 0x8100000000000000ULL;
        blackKnights = 0x4200000000000000ULL;
        blackBishops = 0x2400000000000000ULL;
        blackQueens = 0x0800000000000000ULL;
        blackKings = 0x1000000000000000ULL;
    }

    explicit Board(const array<array<char, 8>, 8>& board);

	[[nodiscard]] bool isOccupied(Square square) const;

    static uint64_t mask(const Square square) {
        return 1ULL << square;
    }

    static uint64_t getCol(const Square square) {
        return 0x0101010101010101ULL << (square & 7);
    }

    static uint64_t getRow(const Square square) {
        return 0x00000000000000FFULL << ((square >> 3) * 8);
    }

    static Square changeRow(Square square, int delta);

    static Square changeCol(Square square, int delta);

    static Square changeSquare(Square square, int deltaRow, int deltaCol);

    static int getRowNum(const Square square) {
        return square / 8;
    }

    static int getColNum(const Square square) {
        return square % 8;
    }

	[[nodiscard]] PieceType getPieceAtSquare(Square square) const;

	void printChessBoard() const;

    void makeMove();

	[[nodiscard]] bool friendlyFire(Square toSquare, Color color) const;

    static string squareToString(Square square) {

        const int row = getRowNum(square);
        const int col = getColNum(square);

        const char rowChar = '1' + row;
        const char colChar = 'a' + col;

        return  string() + colChar + rowChar;
    }

    static Square readSquare() {



        string squareString;
        cin >> squareString;

        while (squareString.size() != 2) {
            cout << "Invalid format, please try again";
            cin >> squareString;
        }

        int file = squareString[0] - 'a';
        int rank = squareString[1] - '1';

        while (file < 0 || file > 7 || rank < 0 || rank > 7) {
            cout << "Invalid format.";
            cin >> squareString;
            file = squareString[0] - 'a';
            rank = squareString[1] - '1';
        }

        return makeSquare(file, rank);
    }
};

extern Board board;
