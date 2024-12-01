#include "board.hpp"

// Bitboards for white pieces
    u64 whitePawns   = 0x000000000000FF00;
    u64 whiteKnights = 0x0000000000000042;
    u64 whiteBishops = 0x0000000000000024;
    u64 whiteRooks   = 0x0000000000000081;
    u64 whiteQueens  = 0x0000000000000008;
    u64 whiteKing    = 0x0000000000000010;

    // Bitboards for black pieces
    u64 blackPawns   = 0x00FF000000000000;
    u64 blackKnights = 0x4200000000000000;
    u64 blackBishops = 0x2400000000000000;
    u64 blackRooks   = 0x8100000000000000;
    u64 blackQueens  = 0x0800000000000000;
    u64 blackKing    = 0x1000000000000000;

    // Combined bitboards (dependent and must be updated constantly)
    u64 allWhite = whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing;
    u64 allBlack = blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing;
    u64 occupied = allWhite | allBlack;
    u64 emptySquares = ~occupied;

    /* Map associating each bitboard with its name */
        unordered_map<u64*, string> bitboardNames = {
            {&whitePawns, "White Pawns"},
            {&whiteKnights, "White Knights"},
            {&whiteBishops, "White Bishops"},
            {&whiteRooks, "White Rooks"},
            {&whiteQueens, "White Queens"},
            {&whiteKing, "White King"},
            {&blackPawns, "Black Pawns"},
            {&blackKnights, "Black Knights"},
            {&blackBishops, "Black Bishops"},
            {&blackRooks, "Black Rooks"},
            {&blackQueens, "Black Queens"},
            {&blackKing, "Black King"},
            {&allWhite, "White Pieces"},
            {&allBlack, "Black Pieces"},
            {&occupied, "Occupied Squares"},
            {&emptySquares, "Empty Squares"}
        };

Board::Board() {
    reset();
}

void Board::reset() {
    // Initial positions for white pieces
    whitePawns   = 0x000000000000FF00;
    whiteKnights = 0x0000000000000042;
    whiteBishops = 0x0000000000000024;
    whiteRooks   = 0x0000000000000081;
    whiteQueens  = 0x0000000000000008;
    whiteKing    = 0x0000000000000010;

    // Initial positions for black pieces
    blackPawns   = 0x00FF000000000000;
    blackKnights = 0x4200000000000000;
    blackBishops = 0x2400000000000000;
    blackRooks   = 0x8100000000000000;
    blackQueens  = 0x0800000000000000;
    blackKing    = 0x1000000000000000;

    updateDependentBoards();
}

void Board::updateDependentBoards() {
    allWhite = whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing;
    allBlack = blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing;
    occupied = allWhite | allBlack;
    emptySquares = ~occupied;
}

void Board::printBoard(u64& board) {
    string name = bitboardNames[&board];

    cout << "Bitboard for " << name << ":" << endl;
    
    for (int rank = 7; rank >= 0; --rank) {
        cout << rank + 1 << " ";
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            cout << ((board >> square) & 1) << " ";
        }
        cout << endl;
    }
    cout << "  a b c d e f g h" << endl << endl;
}


