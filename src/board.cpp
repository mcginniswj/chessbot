#include "board.hpp"

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

u64 Board::getBitBoard(string piece) {
        if (piece == "whitePawns") {
            return whitePawns;
        } else if (piece == "whiteKnights") {
            return whiteKnights;
        } else if (piece == "whiteBishops") {
            return whiteBishops;
        } else if (piece == "whiteRooks") {
            return whiteRooks;
        } else if (piece == "whiteQueens") {
            return whiteQueens;
        } else if (piece == "whiteKing") {
            return whiteKing;
        } else if (piece == "blackPawns") {
            return blackPawns;
        } else if (piece == "blackKnights") {
            return blackKnights;
        } else if (piece == "blackBishops") {
            return blackBishops;
        } else if (piece == "blackRooks") {
            return blackRooks;
        } else if (piece == "blackQueens") {
            return blackQueens;
        } else if (piece == "blackKing") {
            return blackKing;
        } else if (piece == "allWhite") {
            return allWhite;
        } else if (piece == "allBlack") {
            return allBlack;
        } else if (piece == "occupied") {
            return occupied;
        } else if (piece == "emptySquares") {
            return emptySquares;
        } else {
            // Return an empty board (all 0) if the piece name doesn't match any known bitboard
            return 0;
        }
    }

void Board::setBitBoard(string piece, u64 value) {
    if (piece == "whitePawns") {
        whitePawns = value;
    } else if (piece == "whiteKnights") {
        whiteKnights = value;
    } else if (piece == "whiteBishops") {
        whiteBishops = value;
    } else if (piece == "whiteRooks") {
        whiteRooks = value;
    } else if (piece == "whiteQueens") {
        whiteQueens = value;
    } else if (piece == "whiteKing") {
        whiteKing = value;
    } else if (piece == "blackPawns") {
        blackPawns = value;
    } else if (piece == "blackKnights") {
        blackKnights = value;
    } else if (piece == "blackBishops") {
        blackBishops = value;
    } else if (piece == "blackRooks") {
        blackRooks = value;
    } else if (piece == "blackQueens") {
        blackQueens = value;
    } else if (piece == "blackKing") {
        blackKing = value;
    } else if (piece == "allWhite") {
        allWhite = value;
    } else if (piece == "allBlack") {
        allBlack = value;
    } else if (piece == "occupied") {
        occupied = value;
    } else if (piece == "emptySquares") {
        emptySquares = value;
    } else {
        // If no matching piece is found, print an error message
        cerr << "Error: Invalid bitboard name \"" << piece << "\"." << endl;
    }

    updateDependentBoards();
}
