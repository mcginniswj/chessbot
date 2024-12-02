#include "board.hpp"

// Constructor
Board::Board() {
    // Initialize the bitboards to their default positions
    reset();

    // Populate the bitboardMap
    bitboardMap = {
        {"White Pawns", &whitePawns},
        {"White Knights", &whiteKnights},
        {"White Bishops", &whiteBishops},
        {"White Rooks", &whiteRooks},
        {"White Queens", &whiteQueens},
        {"White King", &whiteKing},
        {"Black Pawns", &blackPawns},
        {"Black Knights", &blackKnights},
        {"Black Bishops", &blackBishops},
        {"Black Rooks", &blackRooks},
        {"Black Queens", &blackQueens},
        {"Black King", &blackKing},
        {"White Pieces", &allWhite},
        {"Black Pieces", &allBlack},
        {"Occupied Squares", &occupied},
        {"Empty Squares", &emptySquares}
    };
}

// Reset the board to its initial state
void Board::reset() {
    // Initial positions for white pieces
    whitePawns = 0x000000000000FF00;
    whiteKnights = 0x0000000000000042;
    whiteBishops = 0x0000000000000024;
    whiteRooks = 0x0000000000000081;
    whiteQueens = 0x0000000000000008;
    whiteKing = 0x0000000000000010;

    // Initial positions for black pieces
    blackPawns = 0x00FF000000000000;
    blackKnights = 0x4200000000000000;
    blackBishops = 0x2400000000000000;
    blackRooks = 0x8100000000000000;
    blackQueens = 0x0800000000000000;
    blackKing = 0x1000000000000000;

    updateDependentBoards();
}

// Update dependent bitboards
void Board::updateDependentBoards() {
    allWhite = whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing;
    allBlack = blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing;
    occupied = allWhite | allBlack;
    emptySquares = ~occupied;
}

// Print a bitboard in a human-readable format
void Board::printBoard(const string& pieceName) const {
    auto it = bitboardMap.find(pieceName);
    if (it != bitboardMap.end()) {
        cout << "Bitboard for " << pieceName << ":" << endl;

        u64 board = *(it->second); // Dereference the pointer to get the bitboard value
        for (int rank = 7; rank >= 0; --rank) {
            cout << rank + 1 << " ";
            for (int file = 0; file < 8; ++file) {
                int square = rank * 8 + file;
                cout << ((board >> square) & 1) << " ";
            }
            cout << endl;
        }
        cout << "  a b c d e f g h" << endl << endl;
    } else {
        cerr << "Error: Invalid piece name '" << pieceName << "' in printBoard()." << endl;
    }
}

// Get the value of a bitboard
u64 Board::getBitBoard(const string& piece) const {
    auto it = bitboardMap.find(piece);
    if (it != bitboardMap.end()) {
        return *(it->second);
    }
    cerr << "Error: Invalid piece name '" << piece << "' in getBitBoard()." << endl;
    return 0;
}

// Set the value of a bitboard
void Board::setBitBoard(const string& piece, u64 value) {
    auto it = bitboardMap.find(piece);
    if (it != bitboardMap.end()) {
        *(it->second) = value;
        updateDependentBoards();
    } else {
        cerr << "Error: Invalid piece name '" << piece << "' in setBitBoard()." << endl;
    }
}
