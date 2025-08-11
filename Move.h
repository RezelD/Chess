#pragma once
#include "Pieces.h"


namespace Move {

	struct MoveInfo {

		PieceType piece;
		Square origin;
		Square destination;
		uint8_t exceptions;
		PieceType promotion;

	};

	struct LastMoveInfo {

		PieceType piece;
		Square origin;
		Square destination;
		uint8_t exceptions;
		PieceType promotion;
	};

	enum class Exceptions {

		NONE = 0,
		CAPTURE = 1 << 0,
		PROMOTION = 1 << 1,
		EN_PASSANT = 1 << 2,
		CASTLE = 1 << 3

	};



	void makeMove(const MoveInfo& move) {


	}

}