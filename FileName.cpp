#include<iostream>
#include<string>
#include<iomanip>
#include<cctype>
#include<array>

using namespace std;

void printChessBoard();
void moveInput();
void convertNotation(string move);
array<char, 6>& colorHandler();
void moveProcessor(char piece, int toRow, int toCol);
void pawnHandler(int toRow, int toCol, bool isTest);
void pawnPromoteHandler(int toRow, int toCol);
bool canPawnPromote(int toRow, int toCol, bool isTest);
void pawnCaptureHandler(int fromRow, int toRow, int toCol, int exitCode);
bool canPawnCapture(int toRow, int toCol, int direction, bool isTest);
void pawnMoveHandler(int fromRow, int toRow, int toCol, int exitCode);
bool canPawnMove(int toRow, int toCol, int direction, array<int,2>& doubleMoveCounter, bool isTest);
void pawnPassantHandler(int toRow, int toCol, int exitCode);
bool canPawnPassant(int toRow, int toCol, array<int,2> doubleMoveCounter, bool isTest);
void rookMoveHandler(int toRow, int toCol);
void knightMoveHandler(int toRow, int toCol);
void bishopMoveHandler(int toRow, int toCol);
void queenMoveHandler(int toRow, int toCol);
void kingMoveHandler(int toRow, int toCol);
char toggleCase(char c);

array<array<char, 8>, 8> board = {{
    {'r','n','b','q','k','b','n','r'}, // Black pieces
    {'p','p','p','p','p','p','p','p'}, // Black pawns
    {' ',' ',' ',' ',' ',' ',' ',' '}, // Empty rows
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {'P','P','P','P','P','P','P','P'}, // White pawns
    {'R','N','B','Q','K','B','N','R'}  // White pieces
}};

int movesMade;





int main() {
	
    printChessBoard();
    
    for (int i = 0; i < 999999; i++) {

        moveInput();
    }

	return 0;
}


void printChessBoard() {

    for (int i = 0; i < 8; i++) {

        cout << " +----+----+----+----+----+----+----+----+" << endl;

        for (int j = 0; j < 8; j++) {

            cout << setw(2) << "|" << setw(3) << board[i][j];
        }

        cout << " |" << (8-i) << endl;
    }

    cout << " +----+----+----+----+----+----+----+----+" << endl;
    cout << "    a    b    c    d    e    f    g    h  " << endl;
}

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

    char toFile = tolower(move[0]); // sets first character of move string to lowercase
    char toRank = move[1]; // stores rank of move string (second character)
    char piece = 'P';

    int toCol;
    int toRow;

    if (isupper(move[0]) && move[0] != 'O') {

        piece = move[0]; // gets the piece type from move string
        toFile = tolower(move[1]); // gets the file from move string
        toRank = move[2]; // gets the rank from move string
        toCol = toFile - 'a'; // converts from algebraic notation to index
        toRow = 8 - (toRank - '0'); // converts from algebraic notation to index

        moveProcessor(piece, toRow, toCol);
    }
    else {

        toCol = toFile - 'a'; // converts from algebraic notation to index
        toRow = 8 - (toRank - '0'); // converts from algebraic notation to index

        moveProcessor(piece, toRow, toCol);
    }


}


array<char,6>& colorHandler() {

    static std::array<char, 6> white = { 'P','R','B','N','Q','K' };
    static std::array<char, 6> black = { 'p','r','b','n','q','k' };
    return (movesMade % 2 == 0) ? white : black;

 

}



void moveProcessor(char piece, int toRow, int toCol) {

    switch (piece) {

        case 'P':
            pawnHandler(toRow, toCol, false);
            break;

        case 'R':
            rookMoveHandler(toRow, toCol);
            break;

        case 'N':
            knightMoveHandler(toRow, toCol);
            break;

        case 'B':
            bishopMoveHandler(toRow, toCol);
            break;

        case 'Q':
            queenMoveHandler(toRow, toCol);
            break;

        case 'K':
            kingMoveHandler(toRow, toCol);
            break;

        default:
            cout << "\nInvalid Piece!\n";
    }
}

void pawnHandler(int toRow, int toCol, bool isTest) {

    if (toCol > 7 || toCol < 0 || toRow > 7 || toRow < 0) {

        cout << "destination square is out of bounds!\n";
        movesMade--;
        return;
    }

    int direction = (movesMade % 2 == 0) ? -1 : 1; // white pawns move up and black pawns move down

    static array<int, 2> doubleMoveCounter = { 0, 0 };


    if (!isspace(board[toRow][toCol])) {

        if (canPawnCapture(toRow, toCol, direction, isTest)) {
            doubleMoveCounter[0]++;
            canPawnPromote(toRow, toCol, isTest);
            return;
        }

    }
    else {
        if (canPawnPassant(toRow, toCol, doubleMoveCounter, isTest)) {
            cout << "[DEBUG] En passant accepted\n";

            doubleMoveCounter[0]++;

            canPawnPromote(toRow, toCol, isTest);
            return;
        }

        if (canPawnMove(toRow, toCol, direction, doubleMoveCounter, isTest)) {
            cout << "[DEBUG] Normal move accepted\n";

            doubleMoveCounter[0]++;

            canPawnPromote(toRow, toCol, isTest);
            return;
        }


        movesMade--;

        return;
    }

}

bool canPawnPromote(int toRow, int toCol, bool isTest) {


    if (toRow == 0 || toRow == 7) {

        if (!isTest) {

            pawnPromoteHandler(toRow, toCol);
        }
        return true;


    }
    else {

        return false;
    }

};
void pawnPromoteHandler(int toRow, int toCol) {

    auto [pawn, rook, bishop, knight, queen, king] = colorHandler();

    char promotedPiece;

    cout << "Pawn can promote! what piece do you want to promote it to? Use the first letter of the piece you want to promote to.";


    cin >> promotedPiece;

    switch (promotedPiece) {

        case 'p':
        case 'P':
            cout << "Pawn cant promote to pawn!";
            break;
        case 'r':
        case 'R':
            cout << "Promoted to rook!";
            board[toRow][toCol] = rook;
            break;
        case 'n':
        case 'N':
            cout << "Promoted to Knight!";
            board[toRow][toCol] = knight;
            break;
        case 'b':
        case 'B':
            cout << "Promoted to Bishop!";
            board[toRow][toCol] = bishop;
            break;
        case 'q':
        case 'Q':
            cout << "Promoted to Queen!";
            board[toRow][toCol] = queen;
            break;
        case 'k':
        case 'K':
            cout << "Wish Granted.";
            board[toRow][toCol] = king;
            break;
        default:
            cout << "Not a valid piece!";
            break;
    }
};

bool canPawnCapture(int toRow, int toCol, int direction, bool isTest) {

    char pawn = colorHandler()[0];

    const int ERR_START_OOB = -100,
        ERR_SELF_CAPTURE = -101,
        ERR_CANT_CAPTURE = -102,
        ERR_CAPTURE_FWRD = -103;

    const int CAPTURE_BOTH = 100,
        CAPTURE_LEFT = 101,
        CAPTURE_RIGHT = 102;

    int fromRow = toRow - direction;

    if (fromRow < 0 || fromRow > 7) {

        pawnCaptureHandler(fromRow, toRow, toCol, ERR_START_OOB);

        return false;
    }

    bool canCaptureLeft = (toCol < 7) && board[fromRow][toCol + 1] == pawn;
    bool canCaptureRight = (toCol > 0) && board[fromRow][toCol - 1] == pawn;
    cout << "Poo\n\n\n" << toCol;

    if (board[fromRow][toCol] == pawn && board[fromRow][toCol + 1] != pawn && board[fromRow][toCol - 1] != pawn) {
        cout << "Poo";
        if (!isTest) {

            pawnCaptureHandler(fromRow, toRow, toCol, ERR_CAPTURE_FWRD);
        }

        return false;

    }

    if (!((isupper(pawn) && islower(board[toRow][toCol])) || (islower(pawn) && isupper(board[toRow][toCol])))) {

        if (!isTest) {

            pawnCaptureHandler(fromRow, toRow, toCol, ERR_SELF_CAPTURE);

        }
        return false;
    }

    if (canCaptureLeft && canCaptureRight) {

        if (!isTest) {

            pawnCaptureHandler(fromRow, toRow, toCol, CAPTURE_BOTH);
        }

        return true;
    }
    else if (canCaptureLeft) {

        if (!isTest) {

            pawnCaptureHandler(fromRow, toRow, toCol, CAPTURE_LEFT);
        }
        return true;
    }
    else if (canCaptureRight) {

        if (!isTest) {

            pawnCaptureHandler(fromRow, toRow, toCol, CAPTURE_RIGHT);
        }
        return true;
    }
    else {
        if (!isTest) {

            pawnCaptureHandler(fromRow, toRow, toCol, ERR_CANT_CAPTURE);
        }
        return false;
    }










};
void pawnCaptureHandler(int fromRow, int toRow, int toCol, int exitCode) {

    char pawn = colorHandler()[0];

    const int ERR_START_OOB = -100,
        ERR_SELF_CAPTURE = -101,
        ERR_CANT_CAPTURE = -102,
        ERR_CAPTURE_FWRD = -103;

    const int CAPTURE_BOTH = 100,
        CAPTURE_LEFT = 101,
        CAPTURE_RIGHT = 102;

    switch (exitCode) {

        case ERR_START_OOB:

            cout << "Move puts starting square out of bounds!\n";

            movesMade--;

            break;

        case ERR_SELF_CAPTURE:

            cout << "Cant capture your own piece!\n";

            movesMade--;

            break;

        case ERR_CAPTURE_FWRD:

            cout << "Cant capture forward!\n";

            movesMade--;

            break;

        case ERR_CANT_CAPTURE:

            cout << "No piece to capture!";

            movesMade--;

            break;

        case CAPTURE_BOTH: {

            string leftOrRight;

            cout << "do you want the left or right pawn to capture? (left/right):";

            cin >> leftOrRight;
            while (leftOrRight != "left" && leftOrRight != "right") {

                cout << "Must enter left or right!";
                cin >> leftOrRight;
            }

            if (leftOrRight == "left") {
                board[fromRow][toCol - 1] = ' ';
                board[toRow][toCol] = pawn;

                // promoteHandler();

                printChessBoard();



            }
            else if (leftOrRight == "right") {

                board[fromRow][toCol + 1] = ' ';
                board[toRow][toCol] = pawn;

                // promoteHandler();

                printChessBoard();
            }
            break;
        }

        case CAPTURE_LEFT:

            board[fromRow][toCol + 1] = ' ';
            board[toRow][toCol] = pawn;

            // promoteHandler();

            printChessBoard();

            break;

        case CAPTURE_RIGHT:

            board[fromRow][toCol - 1] = ' ';
            board[toRow][toCol] = pawn;

            // promoteHandler();

            printChessBoard();

            break;
        default:
            movesMade--;
    }




};

bool canPawnMove(int toRow, int toCol, int direction, array<int, 2>& doubleMoveCounter, bool isTest) {

    char pawn = colorHandler()[0];

    int startRow = (movesMade % 2 == 0) ? 6 : 1; // whites pawns start at row 6, blacks pawns start at row 1

    const int ERR_ILLEGAL_MOVE = -101;
    const int VALID_MOVE = 100;

    for (int moveLength = 1; moveLength <= 2; moveLength++) {

        int fromRow = toRow - direction * moveLength;



        if (fromRow < 0 || fromRow > 7) {
            continue;
        }

        if (board[fromRow][toCol] != pawn) {

            continue;
        }

        if ((moveLength == 1) || (fromRow == startRow && board[fromRow + direction][toCol] == ' ')) {


            if (board[toRow][toCol] != ' ') {

                continue;

            }

            if (!isTest) {

                pawnMoveHandler(fromRow, toRow, toCol, VALID_MOVE);
                if (moveLength == 2) {

                    doubleMoveCounter[0] = 0;
                    doubleMoveCounter[1] = toCol;
                }

            }

            return true;


        }









    }

    if (!isTest) {

        pawnMoveHandler(0, toRow, toCol, ERR_ILLEGAL_MOVE);
    }

    return false;
};
void pawnMoveHandler(int fromRow, int toRow, int toCol, int exitCode) {

    char pawn = colorHandler()[0];
    const int ERR_ILLEGAL_MOVE = -101;
    const int VALID_MOVE = 100;
    cout << endl << endl << pawn << endl << endl;

    switch (exitCode) {

        case ERR_ILLEGAL_MOVE:


            cout << "\nPawn cant go that far / pawn cant go backwards! / Pawn can only move twice on first move!\n";


            break;

        case VALID_MOVE:

            board[toRow][toCol] = pawn;
            board[fromRow][toCol] = ' ';
            printChessBoard();
            break;
    }

};

bool canPawnPassant(int toRow, int toCol, array<int, 2> doubleMoveCounter, bool isTest) {

    char pawn = colorHandler()[0];


    bool canPassant;

    if (doubleMoveCounter[0] < 2 && doubleMoveCounter[1] == toCol) {

        canPassant = true;
    }
    else {
        canPassant = false;
    }

    const int ERR_NO_PASS = -100,
        ERR_UNKNOWN = -101;

    const int PASSANT_BOTH = 100,
        PASSANT_LEFT = 101,
        PASSANT_RIGHT = 102;


    int validToRow = (movesMade % 2 == 0) ? 2 : 5;
    int validFromRow = (movesMade % 2 == 0) ? 3 : 4;


    bool canPassantLeft = (toCol < 7) && board[validFromRow][toCol + 1] == pawn;
    bool canPassantRight = (toCol > 0) && board[validFromRow][toCol - 1] == pawn;



    if (toRow != validToRow) {

        cout << toRow << endl << validToRow << validFromRow;
        return false;
    }

    if (board[validFromRow][toCol] != toggleCase(pawn)) {
        cout << toRow << endl << validToRow << validFromRow;

        return false;
    }


    if (canPassantLeft && canPassantRight) {

        if (!canPassant) {

            if (!isTest) {

                pawnPassantHandler(toRow, toCol, ERR_NO_PASS);
            }
            return false;
        }
        if (!isTest) {
            pawnPassantHandler(toRow, toCol, PASSANT_BOTH);
        }
        return true;

    }
    if (canPassantRight) {

        if (!canPassant) {

            if (!isTest) {
                pawnPassantHandler(toRow, toCol, ERR_NO_PASS);
            }
            return false;
        }
        if (!isTest) {
            pawnPassantHandler(toRow, toCol, PASSANT_RIGHT);
        }
        return true;
    }
    if (canPassantLeft) {

        if (!canPassant) {
            if (!isTest) {
                pawnPassantHandler(toRow, toCol, ERR_NO_PASS);
            }
            return false;
        }
        if (!isTest) {
            pawnPassantHandler(toRow, toCol, PASSANT_LEFT);
        }
        return true;
    }
    if (!isTest) {
        pawnPassantHandler(toRow, toCol, ERR_UNKNOWN);
    }
    return false;
};
void pawnPassantHandler(int toRow, int toCol, int exitCode) {
        
    char pawn = colorHandler()[0];
    const int ERR_NO_PASS = -100,
        ERR_UNKNOWN = -101;

    const int PASSANT_BOTH = 100,
        PASSANT_LEFT = 101,
        PASSANT_RIGHT = 102;

    int validFromRow = (movesMade % 2 == 0) ? 3 : 4;

    switch (exitCode) {


        case ERR_NO_PASS:

            cout << "Can only en passant if attacked pawn moved two spaces last turn!\n";


            break;

        case ERR_UNKNOWN:

            cout << "You shouldnt see this.";


            break;

        case PASSANT_BOTH: {

            string leftOrRight;

            cout << "Both pawns can en passant! Pick one to do the capture! (left/right)\n";

            cin >> leftOrRight;

            if (leftOrRight == "left") {

                board[toRow][toCol] = pawn;

                board[validFromRow][toCol - 1] = ' ';
                board[validFromRow][toCol] = ' ';
                printChessBoard();
            }
            if (leftOrRight == "right") {

                board[toRow][toCol] = pawn;

                board[validFromRow][toCol + 1] = ' ';
                board[validFromRow][toCol] = ' ';
                printChessBoard();

            }
            break;
        }
        case PASSANT_LEFT:

            board[toRow][toCol] = pawn;

            board[validFromRow][toCol + 1] = ' ';
            board[validFromRow][toCol] = ' ';
            printChessBoard();


            break;

        case PASSANT_RIGHT:

            board[toRow][toCol] = pawn;

            board[validFromRow][toCol - 1] = ' ';
            board[validFromRow][toCol] = ' ';
            printChessBoard();

            break;
    }

};








void rookMoveHandler(int, int)
{
}

void knightMoveHandler(int, int)
{
}

void bishopMoveHandler(int, int)
{
}

void queenMoveHandler(int, int)
{
}

void kingMoveHandler(int, int)
{
}

char toggleCase(char c) {
    return std::isupper(static_cast<unsigned char>(c)) ?
        std::tolower(static_cast<unsigned char>(c)) :
        std::toupper(static_cast<unsigned char>(c));
}