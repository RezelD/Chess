#pragma once
#include "Pieces.h"
#include "Board.h"


namespace Move {

	struct MoveInfo {

		PieceType piece;
		Square origin;
		Square destination;
		Square enPassantSquare;
		uint8_t exceptions;
		PieceType promotion;

	};

	extern MoveInfo moveInfo;
	extern MoveInfo lastMoveInfo;

	enum Exceptions {

		NONE = 0,
		CAPTURE = 1 << 0,
		PROMOTION = 1 << 1,
		EN_PASSANT = 1 << 2,
		CASTLE = 1 << 3

	};

	inline bool checkException(const MoveInfo& moveInfo, const Exceptions exception) {
		return (moveInfo.exceptions & exception) != 0;
	}

}