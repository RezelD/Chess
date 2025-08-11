#include "InputHandler.h"

namespace InputHandler {

    int movesMade = 0;

    void moveInput() {

        string move;

        bool isValid = false;

        while (isValid == false) {

            if (movesMade == 0) {
                cout << "Welcome to chesstur! White goes first, please enter your move in algebraic notation: ";
            }
            else if (movesMade % 2 == 0) {
                cout << "Whites turn!: ";
            }
            else {
                cout << "Blacks turn!: ";
            }

            cin >> move;

            if (isupper(move[0]) && move[0] != 'O') {

                if (move.length() < 3) {
                    cout << "\nInvalid Move!\n";
                }
                else {
                    isValid = true;
                }
            }
            else {
                if (move.size() < 2) {
                    cout << "\nInvalid Move!\n";
                }
                else {
                    isValid = true;
                }
            }
        }

        convertNotation(move);

        movesMade++;
    }

    void convertNotation(string move) {

        char toFile;
        char toRank;
        char piece = (movesMade % 2 == 0) ? PieceType::whitePawn : PieceType::blackPawn;

        int toCol;
        int toRow;

        if (isupper(move[0]) && move[0] != 'O') {

            if (move.length() != 3) {
                cout << "Invalid Move.";
                movesMade--;
                return;
            }

            piece = (movesMade % 2 == 0) ? toupper(move[0]) : tolower(move[0]);
            toFile = tolower(move[1]);
            toRank = move[2];

            if (toFile < 'a' || toFile > 'h' || toRank < '1' || toRank > '8') {
                cout << "Invalid Move.";
                movesMade--;
                return;
            }

            toRow = toRank - '1';
            toCol = toFile - 'a';

            Square toSquare = makeSquare(toRow, toCol);



            findPiece(piece, toSquare);
        }
        else {

            if (move.length() != 2) {
                cout << "Invalid Move.";
                movesMade--;
                return;
            }

            toFile = tolower(move[0]);
            toRank = move[1];

            if (toFile < 'a' || toFile > 'h' || toRank < '1' || toRank > '8') {
                cout << "Invalid Move.";
                movesMade--;
                return;
            }

            toCol = toFile - 'a';
            toRow = toRank - '1';



            Square toSquare = makeSquare(toRow, toCol);

            findPiece(piece, toSquare);
        }


    }

    void findPiece(char piece, Square toSquare) {

        Square origin;

        Move::moveInfo.destination = toSquare;



        switch (piece) {

            case PieceType::whitePawn:
            case PieceType::blackPawn:

                int doubleStepDest;
                int direction;

                if (piece == PieceType::whitePawn) {
                    Move::moveInfo.piece = PieceType::whitePawn;
                    doubleStepDest = 3;
                    direction = -1;
                }
                else {
                    Move::moveInfo.piece = PieceType::blackPawn;
                    doubleStepDest = 4;
                    direction = 1;
                }

                if (board.isOccupied(toSquare)) {

                }
                else {
                    int rowNum = board.getRowNum(toSquare);

                    origin = board.changeRow(toSquare, 1 * direction);
                    if (origin == Square::OOB) {
                        cout << "Invalid move!";
                        movesMade--;
                        return;
                    }

                    PieceType pathSquare = board.getPieceAtSquare(origin);

                    if (pathSquare == piece) {
                        Move::moveInfo.origin = origin;

                        //make move
                        return;
                    }
                    else if (pathSquare == PieceType::empty) {

                        if (rowNum == doubleStepDest) {

                            origin = board.changeRow(toSquare, 2 * direction);
                            if (origin == Square::OOB) {
                                cout << "Invalid move!";
                                movesMade--;
                                return;
                            }
                            pathSquare = board.getPieceAtSquare(origin);
                            if (pathSquare == piece) {
                                //make double step move

                                return;
                            }
                            else {
                                cout << "Not your piece / No pawn to move!";
                                movesMade--;
                                return;
                            }
                        }




                    }
                    else if (pathSquare == PieceType::whitePawn || pathSquare == PieceType::blackPawn) {

                        if (Move::lastMoveInfo.exceptions & static_cast<uint8_t>(Move::Exceptions::EN_PASSANT)) {
                            // en passant move
                        }
                    }
                    else {
                        cout << "Not your piece! / Piece in the way!";
                        movesMade--;
                        return;
                    }
                }

                break;
        }
    }

}