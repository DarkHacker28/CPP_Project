#include <iostream>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>  // This is only available in some environments, like Turbo C++ or MSVC
char ch = _getch();
 // For getch()

using namespace std;

// Defines the chess pieces
enum Piece {
    EMPTY,
    PAWNW,
    ROOKW,
    KNIGHTW,
    BISHOPW,
    QUEENW,
    KINGW,
    PAWNB,
    ROOKB,
    KNIGHTB,
    BISHOPB,
    QUEENB,
    KINGB
};

class ChessGame {
private:
    Piece board[8][8];
    bool whiteTurn;

public:
    ChessGame() {
        initializeBoard();
        whiteTurn = true;
    }

    void intro() {
        cout << "                     *                        " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        cout << "                   * * *                      " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(55));
        cout << "                     *                        " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        cout << "                 * * * * *                    " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(65));
        cout << "                  * * * *                     " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
        cout << "                   * * *                      " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
        cout << "                   * * *                      " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        cout << "                 * * * * *                    " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        cout << "                 * * * * *                    " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(85));
        cout << "                   * * *                      " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(85));
        cout << "                  * * * *                     " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(90));
        cout << "                 * * * * *                    " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(90));
        cout << "                * * * * * *                   " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(90));
        cout << "               * * * * * * *                  " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(90));
        cout << "              * * * * * * * *                 " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(90));
        cout << "            * * * * * * * * * *               " << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        cout << "          * * * * * * * * * * * *             " << endl;
        char ch;
        cout << endl;
        cout << "Made by Tahir" << endl;
        cout << "Press any key to Play....." << endl;
        ch = _getch();  // Waits for user input
    }

    void initializeBoard() {
        // Place the pawns
        for (int i = 0; i < 8; i++) {
            board[1][i] = PAWNB;
            board[6][i] = PAWNW;
        }

        // Place the rooks
        board[0][0] = ROOKB;
        board[0][7] = ROOKB;
        board[7][0] = ROOKW;
        board[7][7] = ROOKW;

        // Place the knights
        board[0][1] = KNIGHTB;
        board[0][6] = KNIGHTB;
        board[7][1] = KNIGHTW;
        board[7][6] = KNIGHTW;

        // Place the bishops
        board[0][2] = BISHOPB;
        board[0][5] = BISHOPB;
        board[7][2] = BISHOPW;
        board[7][5] = BISHOPW;

        // Place the queens
        board[0][3] = QUEENB;
        board[7][3] = QUEENW;

        // Place the Kings
        board[0][4] = KINGB;
        board[7][4] = KINGW;

        // Initialize the chessboard with empty squares
        for (int i = 2; i < 6; i++) {
            for (int j = 0; j < 8; j++) {
                board[i][j] = EMPTY;
            }
        }
    }

    // Display the board on the screen
    void displayBoard() {
        char latter;
        cout << "   ";
        for (int i = 0; i < 8; i++) {
            latter = 'A' + i;
            cout << " " << latter << "  ";
        }
        cout << endl;

        for (int i = 0; i < 8; i++) {
            cout << "  +---+---+---+---+---+---+---+---+" << endl;
            cout << i + 1 << " ";
            for (int j = 0; j < 8; j++) {
                char getch = ' ';
                switch (board[i][j]) {
                    case EMPTY:
                        getch = '-';
                        break;
                    case PAWNW:
                        getch = 'P';
                        break;
                    case ROOKW:
                        getch = 'R';
                        break;
                    case KNIGHTW:
                        getch = 'N';
                        break;
                    case BISHOPW:
                        getch = 'B';
                        break;
                    case QUEENW:
                        getch = 'Q';
                        break;
                    case KINGW:
                        getch = 'K';
                        break;
                    case PAWNB:
                        getch = 'p';
                        break;
                    case ROOKB:
                        getch = 'r';
                        break;
                    case KNIGHTB:
                        getch = 'n';
                        break;
                    case BISHOPB:
                        getch = 'b';
                        break;
                    case QUEENB:
                        getch = 'q';
                        break;
                    case KINGB:
                        getch = 'k';
                        break;
                }

                cout << "|" << " " << getch << " ";
            }
            cout << "|" << endl;
        }
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
    }

    bool isWhitePiece(int srcX, int srcY) {
        return (board[srcX][srcY] == PAWNW || board[srcX][srcY] == ROOKW ||
                board[srcX][srcY] == KNIGHTW || board[srcX][srcY] == BISHOPW ||
                board[srcX][srcY] == QUEENW || board[srcX][srcY] == KINGW);
    }

    bool isBlackPiece(int srcX, int srcY) {
        return (board[srcX][srcY] == PAWNB || board[srcX][srcY] == ROOKB ||
                board[srcX][srcY] == KNIGHTB || board[srcX][srcY] == BISHOPB ||
                board[srcX][srcY] == QUEENB || board[srcX][srcY] == KINGB);
    }

    bool isSameColor(int srcX, int srcY, int destX, int destY) {
        if (isWhitePiece(srcX, srcY) && isWhitePiece(destX, destY)) {
            return true;
        }
        if (isBlackPiece(srcX, srcY) && isBlackPiece(destX, destY)) {
            return true;
        }
        return false;
    }

    bool isValidMove(int srcX, int srcY, int destX, int destY) {
        // Validate moves for each piece type
        if (board[srcX][srcY] == PAWNW || board[srcX][srcY] == PAWNB) {
            // Implement pawn movement logic here
        }
        else if (board[srcX][srcY] == ROOKW || board[srcX][srcY] == ROOKB) {
            // Implement rook movement logic here
        }
        // Similar logic for other pieces (KNIGHT, BISHOP, QUEEN, KING)
        return true; // Placeholder
    }

    bool isKingInCheck(bool whiteKing) {
        int kingX, kingY;
        Piece kingPiece = whiteKing ? KINGW : KINGB;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j] == kingPiece) {
                    kingX = j;
                    kingY = i;
                    break;
                }
            }
        }

        // Check for the opponent's pieces to see if they can attack the king
                for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((whiteKing && isBlackPiece(i, j)) || (!whiteKing && isWhitePiece(i, j))) {
                    if (isValidMove(i, j, kingX, kingY)) {
                        return true; // King is in check
                    }
                }
            }
        }
        return false; // King is not in check
    }

    bool isCheckmate() {
        // Check if the current player's king is in checkmate
        bool kingInCheck = isKingInCheck(whiteTurn);
        
        // If the king is not in check, it's not checkmate
        if (!kingInCheck) {
            return false;
        }

        // Otherwise, check if the player can move any piece to get out of check
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((whiteTurn && isWhitePiece(i, j)) || (!whiteTurn && isBlackPiece(i, j))) {
                    // Check all possible moves for this piece
                    for (int x = 0; x < 8; x++) {
                        for (int y = 0; y < 8; y++) {
                            if (isValidMove(i, j, x, y)) {
                                // Temporarily make the move
                                Piece temp = board[x][y];
                                board[x][y] = board[i][j];
                                board[i][j] = EMPTY;

                                // Check if the king is still in check
                                if (!isKingInCheck(whiteTurn)) {
                                    // Undo the move
                                    board[i][j] = board[x][y];
                                    board[x][y] = temp;
                                    return false; // Found a valid move to get out of check
                                }

                                // Undo the move
                                board[i][j] = board[x][y];
                                board[x][y] = temp;
                            }
                        }
                    }
                }
            }
        }

        // If no valid moves found, it's checkmate
        return true;
    }

    void makeMove() {
        int srcX, srcY, destX, destY;

        while (true) {
            cout << (whiteTurn ? "White's" : "Black's") << " turn, enter move (e.g., A2 to A4): ";
            char srcColumn, destColumn;
            int srcRow, destRow;
            cin >> srcColumn >> srcRow >> destColumn >> destRow;

            srcX = srcColumn - 'A';
            srcY = 8 - srcRow;
            destX = destColumn - 'A';
            destY = 8 - destRow;

            // Check if the move is valid and if the piece belongs to the current player
            if (srcX >= 0 && srcX < 8 && srcY >= 0 && srcY < 8 &&
                destX >= 0 && destX < 8 && destY >= 0 && destY < 8) {
                if (!isSameColor(srcX, srcY, destX, destY) && isValidMove(srcX, srcY, destX, destY)) {
                    // Make the move
                    Piece temp = board[destY][destX];
                    board[destY][destX] = board[srcY][srcX];
                    board[srcY][srcX] = EMPTY;
                    break;
                } else {
                    cout << "Invalid move, try again!" << endl;
                }
            } else {
                cout << "Invalid position, try again!" << endl;
            }
        }

        // Change turn after a valid move
        whiteTurn = !whiteTurn;
    }

    void playGame() {
        intro();
        while (true) {
            displayBoard();

            if (isCheckmate()) {
                cout << (whiteTurn ? "Black" : "White") << " wins by checkmate!" << endl;
                break;
            }

            makeMove();
        }
    }
};

int main() {
    ChessGame game;
    game.playGame();
    return 0;
}

