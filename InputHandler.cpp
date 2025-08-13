#include "InputHandler.h"

#include "Move.h"

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
                    movesMade--;
                }
                else {
                    isValid = true;
                }
            }
            else {
                if (move.size() < 2) {
                    cout << "\nInvalid Move!\n";
                    movesMade--;
                }
                else {
                    isValid = true;
                }
            }
        }

        convertNotation(move);

        movesMade++;
    }

    void convertNotation(const string &move) {

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

            piece = (movesMade % 2 == 0) ?  static_cast<char>(toupper(move[0])) : static_cast<char>(tolower(move[0]));
            toFile = static_cast<char>(tolower(move[1]));
            toRank = move[2];

            if (toFile < 'a' || toFile > 'h' || toRank < '1' || toRank > '8') {
                cout << "Invalid Move.";
                movesMade--;
                return;
            }

            toRow = toRank - '1';
            toCol = toFile - 'a';

            const Square toSquare = makeSquare(toRow, toCol);



            findPiece(piece, toSquare);
        }
        else {

            if (move.length() != 2) {
                cout << "Invalid Move.";
                movesMade--;
                return;
            }

            toFile = static_cast<char>(tolower(move[0]));
            toRank = move[1];

            if (toFile < 'a' || toFile > 'h' || toRank < '1' || toRank > '8') {
                cout << "Invalid Move.";
                movesMade--;
                return;
            }

            toCol = toFile - 'a';
            toRow = toRank - '1';



            const Square toSquare = makeSquare(toRow, toCol);

            findPiece(piece, toSquare);
        }


    }

    void findPiece(const char piece, const Square toSquare) {

        Move::moveInfo.destination = toSquare;


        switch (piece) {

            case whitePawn:
            case blackPawn:

                int doubleStepRow;
                int promotionRow;
                int direction;
                Color color;

                if (piece == whitePawn) {
                    Move::moveInfo.piece = whitePawn;
                    doubleStepRow = 3;
                    promotionRow = 7;
                    direction = -1;
                    color = white;
                }
                else {
                    Move::moveInfo.piece = blackPawn;
                    doubleStepRow = 4;
                    promotionRow = 0;
                    direction = 1;
                    color = black;
                }

                if (board.isOccupied(toSquare)) {
                    cout << "Capturing not implemented!";
                    movesMade--;
                }
                else {

                    const int destinationRow = Board::getRowNum(toSquare);

                    Square origin = Board::changeRow(toSquare, 1 * direction);
                    if (origin == OOB) {
                        cout << "Invalid move!";
                        movesMade--;
                        return;
                    }

                    if (PieceType pathSquare = board.getPieceAtSquare(origin); pathSquare == piece) {
                        Move::moveInfo.origin = origin;

                        if (destinationRow == promotionRow) {
                            Move::moveInfo.exceptions |= Move::Exceptions::PROMOTION;
                        }

                        board.makeMove();
                        board.printChessBoard();
                    }
                    else if (pathSquare == PieceType::empty) {

                        if (destinationRow == doubleStepRow) {

                            origin = Board::changeRow(toSquare, 2 * direction);
                            if (origin == OOB) {
                                cout << "Invalid move!";
                                movesMade--;
                                return;
                            }
                            pathSquare = board.getPieceAtSquare(origin);
                            if (pathSquare == piece) {
                                Move::moveInfo.exceptions |= Move::Exceptions::EN_PASSANT;
                                Move::moveInfo.enPassantSquare = Board::changeRow(toSquare, 1 * direction);
                                Move::moveInfo.origin = origin;

                                board.makeMove();
                                board.printChessBoard();

                            }
                            else {
                                cout << "Not your piece / No pawn to move!";
                                movesMade--;
                            }
                        } else {
                            cout << "Can only move 2 steps on first move!";
                            movesMade--;
                        }
                    }
                    else if (pathSquare == whitePawn || pathSquare == blackPawn) {



                        if (Move::checkException(Move::lastMoveInfo, Move::Exceptions::EN_PASSANT)) {

                            Square leftOrigin = Board::changeSquare(toSquare, 1 * direction, 1 * direction);
                            Square rightOrigin = Board::changeSquare(toSquare, 1 * direction, -1 * direction);

                            if (board.getPieceAtSquare(leftOrigin) == piece && board.getPieceAtSquare(rightOrigin) == piece) {
                                cout << "Two pawns can make en passant! Pick the column of the pawn you want to make the capture. ( "
                                << Board::squareToString(leftOrigin) << ", " << Board::squareToString(rightOrigin) << " ): ";

                                origin = Board::readSquare();

                            }else if (board.getPieceAtSquare(leftOrigin) == piece) {
                                origin = leftOrigin;
                            } else if (board.getPieceAtSquare(rightOrigin) == piece) {
                                origin = rightOrigin;
                            } else {
                                cout << "No valid pawn to do en passant";
                                movesMade--;
                                return;
                            }

                            if (toSquare != Move::lastMoveInfo.enPassantSquare) {
                                cout << "Invalid move!";
                                movesMade--;
                                return;
                            }

                            if (board.friendlyFire(Board::changeRow(Move::lastMoveInfo.enPassantSquare, direction), color)) {
                                cout << "Can't capture your own piece!";
                                movesMade--;
                                return;
                            }

                            Move::moveInfo.origin = origin;


                            board.makeMove();
                            board.printChessBoard();

                        } else {
                            cout << "Can only en passant right after a two step move!";
                            movesMade--;
                        }
                    }
                    else {
                        cout << "Not your piece! / Piece in the way!";
                        movesMade--;
                    }
                }

                break;
            default: ;
        }
    }

}
