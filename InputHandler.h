#pragma once
#include <iostream>
#include<string>
#include "Board.h"

using namespace std;

namespace InputHandler {

	void convertNotation(const string &move);
	void findPiece(char piece, Square toSquare);
	void moveInput();

};

