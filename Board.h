#pragma once
#include <array>
#include <iostream>
#include <iomanip>
#include "Pieces.h"

using namespace std;

enum class Square : int {

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

Square makeSquare(int row, int col) {
	return static_cast<Square>(row << 3 | col);
}

class Board
{

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

    bool isOccupied(Square square) {

        uint64_t mask = Board::mask(square);

		uint64_t pieces = whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteQueen | whiteKing |
			blackPawns | blackRooks | blackKnights | blackBishops | blackQueen | blackKing;

       
		return (pieces & mask) != 0;
    }



	uint64_t mask(Square square) const {
		return 1ULL << static_cast<int>(square);
	}

	uint64_t mask(int square) {
		return 1ULL << square;
	}

    uint64_t getCol(Square square) {

        int col = static_cast<int>(square) & 7;

        return 0x0101010101010101ULL << col;
    }

    uint64_t getRow(Square square) {
        
        int row = static_cast<int>(square) >> 3;

        return 0x00000000000000FFULL << (row * 8);
    }

    Square changeRow(Square square, int delta) {

        Square changedSquare = static_cast<Square>(static_cast<int>(square) + (delta * 8));

        if (changedSquare < Square::A1 || changedSquare > Square::H8) {
            return Square::OOB;
        }
        else {
            return changedSquare;
        }
    }

    Square changeCol(Square square, int delta) {

        uint64_t beforeRow = getRow(square);

        Square changedSquare = static_cast<Square>(static_cast<int>(square) + delta);

        uint64_t afterRow = getRow(changedSquare);

        if (beforeRow != afterRow) {
            return Square::OOB;
        }
        else {
            return changedSquare;
        }
    }

    int getRowNum(Square square) {

        return (static_cast<int>(square) / 8);
    }

    int getColNum(Square square) {

        return static_cast<int>(square) % 8;
    }

    PieceType getPieceAtSquare(Square square) {

        uint64_t mask = Board::mask(square);

        if ((whitePawns & mask) != 0) {  
            return PieceType::whitePawn;  
        } else if ((whiteRooks & mask) != 0) {  
            return PieceType::whiteRook;  
        } else if ((whiteKnights & mask) != 0) {  
            return PieceType::whiteKnight;  
        } else if ((whiteBishops & mask) != 0) {  
            return PieceType::whiteBishop;  
        } else if ((whiteQueen & mask) != 0) {  
            return PieceType::whiteQueen;  
        } else if ((whiteKing & mask) != 0) {  
            return PieceType::whiteKing;  
        } else if ((blackPawns & mask) != 0) {  
            return PieceType::blackPawn;  
        } else if ((blackRooks & mask) != 0) {  
            return PieceType::blackRook;  
        } else if ((blackKnights & mask) != 0) {  
            return PieceType::blackKnight;  
        } else if ((blackBishops & mask) != 0) {  
            return PieceType::blackBishop;  
        } else if ((blackQueen & mask) != 0) {  
            return PieceType::blackQueen;  
        } else if ((blackKing & mask) != 0) {  
            return PieceType::blackKing;  
        } else {  
            return PieceType::empty;  
        }
    }

	

	void printChessBoard();
};


extern Board board;