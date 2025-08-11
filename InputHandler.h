#pragma once
#include <iostream>
#include<string>
#include "Pieces.h"
#include "Board.h"
#include "Move.h"

using namespace std;

namespace InputHandler {

	void convertNotation(string move);
	void findPiece(char piece, Square toSquare);
	void moveInput();

};

