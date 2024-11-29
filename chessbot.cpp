#include <cstdint>
#include <iostream>
#include <unordered_map>

using namespace std;

typedef uint64_t u64;

/* Initial board layout using bitboards */

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

// Combined bitboards
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
    {&blackKing, "Black King"}
};

/* Rank and file mask constants used for bitwise computations */
// Rank masks
constexpr u64 rank1 = 0x00000000000000FF;
constexpr u64 rank2 = 0x000000000000FF00;
constexpr u64 rank3 = 0x0000000000FF0000;
constexpr u64 rank4 = 0x00000000FF000000;
constexpr u64 rank5 = 0x000000FF00000000;
constexpr u64 rank6 = 0x0000FF0000000000;
constexpr u64 rank7 = 0x00FF000000000000;
constexpr u64 rank8 = 0xFF00000000000000;

// File masks
constexpr u64 fileA = 0x0101010101010101;
constexpr u64 fileB = 0x0202020202020202;
constexpr u64 fileC = 0x0404040404040404;
constexpr u64 fileD = 0x0808080808080808;
constexpr u64 fileE = 0x1010101010101010;
constexpr u64 fileF = 0x2020202020202020;
constexpr u64 fileG = 0x4040404040404040;
constexpr u64 fileH = 0x8080808080808080;

// File exclusion masks
constexpr u64 FILE_AB = fileA | fileB; // For moves crossing into files A or B
constexpr u64 FILE_GH = fileG | fileH; // For moves crossing into files G or H
constexpr u64 FILE_A  = fileA;         // Single file A
constexpr u64 FILE_H  = fileH;         // Single file H

/* Define some useful bit manipulations including setting, clearing 
getting and getting LSB. */
#define set(b, i) ((b) |= (1ULL << i))
#define clear(b, i) ((b) &= ~(1ULL << i))
#define get(b, i) ((b) & (1ULL << i))
#define get_lsb(b) (__builtin_ctzll(b))

/* Move Generation */

// Pawn move generation (pseudo-legal moves)
u64 pawnGen(u64 pawns, u64 emptySquares, u64 opponentPieces, bool isWhite) {
    u64 singlePush = 0;
    u64 doublePush = 0;
    u64 captures = 0;

    // Generate single pushes and double pushes
    if (isWhite) {
        singlePush = (pawns << 8) & emptySquares; // White pawns move up
        doublePush = (singlePush << 8) & emptySquares & 0x00000000FF000000; // White pawns from rank 2
    } else {
        singlePush = (pawns >> 8) & emptySquares; // Black pawns move down
        doublePush = (singlePush >> 8) & emptySquares & 0x0000FF0000000000; // Black pawns from rank 7
    }

    // Generate captures
    if (isWhite) {
        u64 leftCapture = (pawns << 7) & opponentPieces & ~fileH; // Up-left
        u64 rightCapture = (pawns << 9) & opponentPieces & ~fileA; // Up-right
        captures = leftCapture | rightCapture;
    } else {
        u64 leftCapture = (pawns >> 9) & opponentPieces & ~fileH; // Down-left
        u64 rightCapture = (pawns >> 7) & opponentPieces & ~fileA; // Down-right
        captures = leftCapture | rightCapture;
    }

    // Combine all moves
    return singlePush | doublePush | captures;
}

// Knight move generation
u64 knightGen(u64 knights, u64 friendlyPieces) {
    u64 attacks = 0ULL;
    attacks = (((knights >> 6)  | (knights << 10)) & ~FILE_GH) |
              (((knights >> 10) | (knights << 6))  & ~FILE_AB) |
              (((knights >> 15) | (knights << 17)) & ~FILE_H)  |
              (((knights >> 17) | (knights << 15)) & ~FILE_A);

              attacks &= friendlyPieces;
    return attacks;
}

/* Print board for visualization and debugging */
void printBitboard(u64& board) {
    string name = bitboardNames[&board];

    cout << "Bitboard for " << name << ":" << endl;
    cout << "  a b c d e f g h" << endl;
    for (int rank = 7; rank >= 0; --rank) {
        cout << rank + 1 << " ";
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            cout << ((board >> square) & 1) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    printBitboard(whiteKnights);
    
    whiteKnights = knightGen(whiteKnights, allWhite);

    printBitboard(whiteKnights);

    return 0;
}
