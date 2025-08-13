#include "Board.h"

#include <cstdint>
#include <iomanip>
#include <iostream>

#include "Move.h"

Board::Board(const array<array<char, 8>, 8>& board) : whitePawns(0), whiteRooks(0), whiteKnights(0),
                                                      whiteBishops(0), whiteQueens(0), whiteKings(0), blackPawns(0), blackRooks(0), blackKnights(0),
                                                      blackBishops(0), blackQueens(0), blackKings(0){

	for (int row = 7; row >= 0; row--) {

		for (int col = 0; col < 8; col++) {

			const uint64_t mask = Board::mask(makeSquare(row,col));

			switch (board[row][col]) {

				case whitePawn:
					whitePawns |= mask;
					break;
				case whiteRook:
					whiteRooks |= mask;
					break;
				case whiteKnight:
					whiteKnights |= mask;
					break;
				case whiteBishop:
					whiteBishops |= mask;
					break;
				case whiteQueen:
					whiteQueens |= mask;
					break;
				case whiteKing:
					whiteKings |= mask;
					break;
				case blackPawn:
					blackPawns |= mask;
					break;
				case blackRook:
					blackRooks |= mask;
					break;
				case blackKnight:
					blackKnights |= mask;
					break;
				case blackBishop:
					blackBishops |= mask;
					break;
				case blackQueen:
					blackQueens |= mask;
					break;
				case blackKing:
					blackKings |= mask;
					break;
				default:
					break;
			}
		}
	}

}
void Board::printChessBoard() const {

	for (int row = 7; row >= 0; row--) {

		cout << " +----+----+----+----+----+----+----+----+" << endl;

		for (int col = 0; col < 8; col++) {

			const Square square = makeSquare(row, col);

			const uint64_t mask = Board::mask(square);

			char piece;

			if (whitePawns & mask) {
				piece = whitePawn;
			}
			else if (whiteRooks & mask) {
				piece = whiteRook;
			}
			else if (whiteKnights & mask) {
				piece = whiteKnight;
			}
			else if (whiteBishops & mask) {
				piece = whiteBishop;
			}
			else if (whiteQueens & mask) {
				piece = whiteQueen;
			}
			else if (whiteKings & mask) {
				piece = whiteKing;
			}
			else if (blackPawns & mask) {
				piece = blackPawn;
			}
			else if (blackRooks & mask) {
				piece = blackRook;
			}
			else if (blackKnights & mask) {
				piece = blackKnight;
			}
			else if (blackBishops & mask) {
				piece = blackBishop;
			}
			else if (blackQueens & mask) {
				piece = blackQueen;
			}
			else if (blackKings & mask) {
				piece = blackKing;
			}
			else {
				piece = PieceType::empty;
			}

			cout << " | " << setw(2) << piece;
		}

		cout << " |" << (row + 1) << endl;
	}

	cout << " +----+----+----+----+----+----+----+----+" << endl;
	cout << "    a    b    c    d    e    f    g    h  " << endl;
}

bool Board::isOccupied(const Square square) const {

	const uint64_t mask = Board::mask(square);

	const uint64_t pieces = whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteQueens | whiteKings |
		blackPawns | blackRooks | blackKnights | blackBishops | blackQueens | blackKings;


	return (pieces & mask) != 0;
}

Square Board::changeRow(const Square square, const int delta) {

	if (const auto changedSquare = static_cast<Square>(square + delta * 8);
		changedSquare < A1 || changedSquare > H8) {
		return OOB;
	}
	else {
		return changedSquare;
	}
}

Square Board::changeCol(const Square square, const int delta) {

	const uint64_t beforeRow = getRow(square);

	const auto changedSquare = static_cast<Square>(square + delta);

	if (const uint64_t afterRow = getRow(changedSquare); beforeRow != afterRow) {
		return OOB;
	}

	return changedSquare;
}

Square Board::changeSquare(const Square square, const int deltaRow, const int deltaCol) {

	Square changedSquare = square;

	changedSquare = changeRow(changedSquare, deltaRow);
	changedSquare = changeCol(changedSquare, deltaCol);
	return changedSquare;
}

PieceType Board::getPieceAtSquare(const Square square) const {

	const uint64_t mask = Board::mask(square);

	if ((whitePawns & mask) != 0) {
		return whitePawn;
	}
	if ((whiteRooks & mask) != 0) {
		return whiteRook;
	}
	if ((whiteKnights & mask) != 0) {
		return whiteKnight;
	}
	if ((whiteBishops & mask) != 0) {
		return whiteBishop;
	}
	if ((whiteQueens & mask) != 0) {
		return whiteQueen;
	}
	if ((whiteKings & mask) != 0) {
		return whiteKing;
	}
	if ((blackPawns & mask) != 0) {
		return blackPawn;
	}
	if ((blackRooks & mask) != 0) {
		return blackRook;
	}
	if ((blackKnights & mask) != 0) {
		return blackKnight;
	}
	if ((blackBishops & mask) != 0) {
		return blackBishop;
	}
	if ((blackQueens & mask) != 0) {
		return blackQueen;
	}
	if ((blackKings & mask) != 0) {
		return blackKing;
	}

	return PieceType::empty;

}

void Board::makeMove() {

	const uint64_t fromMask = mask(Move::moveInfo.origin);
	const uint64_t toMask = mask(Move::moveInfo.destination);

	const uint64_t notFromMask = ~fromMask;
	const uint64_t notToMask = ~toMask;

	cout << Move::moveInfo.origin << " -> " << Move::moveInfo.destination << endl;


	switch (getPieceAtSquare(Move::moveInfo.origin)) {
		case whitePawn:

			if (Move::checkException(Move::lastMoveInfo, Move::Exceptions::EN_PASSANT)) {
				if (Move::moveInfo.destination == Move::lastMoveInfo.enPassantSquare) {
					const uint64_t passantMask = mask(changeRow(Move::lastMoveInfo.enPassantSquare, -1));
					const uint64_t notPassantMask = ~passantMask;
					blackPawns &= notPassantMask;
				}
			}
			whitePawns &= notFromMask;
			whitePawns &= notToMask;
			whitePawns |= toMask;
			break;
		case whiteRook:
			whiteRooks &= notFromMask;
			whiteRooks &= notToMask;
			whiteRooks |= toMask;
			break;
		case whiteKnight:
			whiteKnights &= notFromMask;
			whiteKnights &= notToMask;
			whiteKnights |= toMask;
			break;
		case whiteBishop:
			whiteBishops &= notFromMask;
			whiteBishops &= notToMask;
			whiteBishops |= toMask;
			break;
		case whiteQueen:
			whiteQueens &= notFromMask;
			whiteQueens &= notToMask;
			whiteQueens |= toMask;
			break;
		case whiteKing:
			whiteKings &= notFromMask;
			whiteKings &= notToMask;
			whiteKings |= toMask;
			break;
		case blackPawn:

			if (Move::checkException(Move::lastMoveInfo, Move::Exceptions::EN_PASSANT)) {

				if (Move::moveInfo.destination == Move::lastMoveInfo.enPassantSquare) {
					const uint64_t passantMask = mask(changeRow(Move::lastMoveInfo.enPassantSquare, 1));
					const uint64_t notPassantMask = ~passantMask;
					whitePawns &= notPassantMask;
				}

			}

			blackPawns &= notFromMask;
			blackPawns &= notToMask;
			blackPawns |= toMask;
			break;
		case blackRook:
			blackRooks &= notFromMask;
			blackRooks &= notToMask;
			blackRooks |= toMask;
			break;
		case blackKnight:
			blackKnights &= notFromMask;
			blackKnights &= notToMask;
			blackKnights |= toMask;
			break;
		case blackBishop:
			blackBishops &= notFromMask;
			blackBishops &= notToMask;
			blackBishops |= toMask;
			break;
		case blackQueen:
			blackQueens &= notFromMask;
			blackQueens &= notToMask;
			blackQueens |= toMask;
			break;
		case blackKing:
			blackKings &= notFromMask;
			blackKings &= notToMask;
			blackKings |= toMask;
			break;
		default:
			cout << "Invalid piece type!";
	}

	Move::lastMoveInfo = Move::moveInfo;

	Move::moveInfo = {};


}

bool Board::friendlyFire(const Square toSquare, const Color color) const  {

	uint64_t teamPieces;

	if (color == white) {
		teamPieces = whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteQueens | whiteKings;
	} else {
		teamPieces = blackPawns | blackRooks | blackKnights | blackBishops | blackQueens | blackKings;
	}

	return (teamPieces & mask(toSquare)) != 0;

}
