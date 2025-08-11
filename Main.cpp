#include<iostream>
#include<string>
#include<iomanip>
#include<cctype>
#include<array>
#include<vector>
#include "Board.h"
#include "InputHandler.h"
using namespace std;

Board board;


int main() {
	
    

    board.printChessBoard();
    
    for (int i = 0; i < 999999; i++) {

        InputHandler::moveInput();
    }

	return 0;
}


