#include "Board.h"

Board::Board(const array<array<char, 8>, 8>& board) {
	
	for (int row = 7; row >= 0; row--) {

		for (int col = 0; col < 8; col++) {

			Square square = makeSquare(row, col);
			uint64_t mask = Board::mask(square);
			char piece = board[row][col];

			switch (piece) {

				case PieceType::whitePawn:
					whitePawns |= mask;
					break;
				case PieceType::whiteRook:
					whiteRooks |= mask;
					break;
				case PieceType::whiteKnight:
					whiteKnights |= mask;
					break;
				case PieceType::whiteBishop:
					whiteBishops |= mask;
					break;
				case PieceType::whiteQueen:
					whiteQueen |= mask;
					break;
				case PieceType::whiteKing:
					whiteKing |= mask;
					break;
				case PieceType::blackPawn:
					blackPawns |= mask;
					break;
				case PieceType::blackRook:
					blackRooks |= mask;
					break;
				case PieceType::blackKnight:
					blackKnights |= mask;
					break;
				case PieceType::blackBishop:
					blackBishops |= mask;
					break;
				case PieceType::blackQueen:
					blackQueen |= mask;
					break;
				case PieceType::blackKing:
					blackKing |= mask;
					break;
				default:
					break;
			}
		}
	}
	
}
void Board::printChessBoard() {

	for (int row = 7; row >= 0; row--) {

		cout << " +----+----+----+----+----+----+----+----+" << endl;

		for (int col = 0; col < 8; col++) {

			Square square = makeSquare(row, col);

			uint64_t mask = Board::mask(square);

			char piece;

			if (whitePawns & mask) {
				piece = static_cast<char>(PieceType::whitePawn);
			}
			else if (whiteRooks & mask) {
				piece = static_cast<char>(PieceType::whiteRook);
			}
			else if (whiteKnights & mask) {
				piece = static_cast<char>(PieceType::whiteKnight);
			}
			else if (whiteBishops & mask) {
				piece = static_cast<char>(PieceType::whiteBishop);
			}
			else if (whiteQueen & mask) {
				piece = static_cast<char>(PieceType::whiteQueen);
			}
			else if (whiteKing & mask) {
				piece = static_cast<char>(PieceType::whiteKing);
			}
			else if (blackPawns & mask) {
				piece = static_cast<char>(PieceType::blackPawn);
			}
			else if (blackRooks & mask) {
				piece = static_cast<char>(PieceType::blackRook);
			}
			else if (blackKnights & mask) {
				piece = static_cast<char>(PieceType::blackKnight);
			}
			else if (blackBishops & mask) {
				piece = static_cast<char>(PieceType::blackBishop);
			}
			else if (blackQueen & mask) {
				piece = static_cast<char>(PieceType::blackQueen);
			}
			else if (blackKing & mask) {
				piece = static_cast<char>(PieceType::blackKing);
			}
			else {
				piece = ' ';
			}

			cout << " | " << setw(2) << piece;
		}

		cout << " |" << (8 - row) << endl;
	}

	cout << " +----+----+----+----+----+----+----+----+" << endl;
	cout << "    a    b    c    d    e    f    g    h  " << endl;
}