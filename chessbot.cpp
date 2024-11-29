#include <cstdint>
#include <iostream>
#include <unordered_map>

using namespace std;

/* Initial board layout using bitboards */

//Bitboards for white pieces

uint64_t whitePawns   = 0x000000000000FF00;
uint64_t whiteKnights = 0x0000000000000042;
uint64_t whiteBishops = 0x0000000000000024;
uint64_t whiteRooks   = 0x0000000000000081;
uint64_t whiteQueens  = 0x0000000000000008;
uint64_t whiteKing    = 0x0000000000000010;

//Bitboards for black pieces 

uint64_t blackPawns   = 0x00FF000000000000;
uint64_t blackKnights = 0x4200000000000000;
uint64_t blackBishops = 0x2400000000000000;
uint64_t blackRooks   = 0x8100000000000000;
uint64_t blackQueens  = 0x0800000000000000;
uint64_t blackKing    = 0x1000000000000000;

//Combined bitboards 

uint64_t allWhite = whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing;
uint64_t allBlack = blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing;
uint64_t occupied = allWhite | allBlack;
uint64_t empty = ~occupied;


/* Map associating each bitboard with its name */
unordered_map<uint64_t*, string> bitboardNames = {
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
/* Rank and file mask constants used for bitwise computations*/

// Rank masks
constexpr uint64_t rank1 = 0x00000000000000FF;
constexpr uint64_t rank2 = 0x000000000000FF00;
constexpr uint64_t rank3 = 0x0000000000FF0000;
constexpr uint64_t rank4 = 0x00000000FF000000;
constexpr uint64_t rank5 = 0x000000FF00000000;
constexpr uint64_t rank6 = 0x0000FF0000000000;
constexpr uint64_t rank7 = 0x00FF000000000000;
constexpr uint64_t rank8 = 0xFF00000000000000;

// File masks
constexpr uint64_t fileA = 0x0101010101010101;
constexpr uint64_t fileB = 0x0202020202020202;
constexpr uint64_t fileC = 0x0404040404040404;
constexpr uint64_t fileD = 0x0808080808080808;
constexpr uint64_t fileE = 0x1010101010101010;
constexpr uint64_t fileF = 0x2020202020202020;
constexpr uint64_t fileG = 0x4040404040404040;
constexpr uint64_t fileH = 0x8080808080808080;

/* Define some useful bit manipulations including setting, clearing 
getting and getting LSB.*/

#define set(b, i) ((b) |= (1ULL << i))
#define clear(b, i) ((b) &= ~(1ULL << i))
#define get(b, i) ((b) & (1ULL << i))
#define get_lsb(b) (__builtin_ctzll(b))

/* Move Generation */

//Pawn single push move generation

uint64_t pawnPush(uint64_t pawns, bool isWhite) {
    if (isWhite) {
        return (pawns << 8) & emptySquares; // White pawns move up
    } else {
        return (pawns >> 8) & emptySquares; // Black pawns move down
    }
}

//Pawn double push move generation
uint64_t pawnDoublePush(uint64_t pawns, bool isWhite) {
    if (isWhite) {
        uint64_t singlePush = (pawns << 8) & emptySquares; // First square must be empty
        return (singlePush << 8) & emptySquares & rank4; // Second square must also be empty
    } else {
        uint64_t singlePush = (pawns >> 8) & emptySquares; // First square must be empty
        return (singlePush >> 8) & emptySquares & rank5; // Second square must also be empty
    }
}

//Pawn capture move generation
uint64_t pawnCap(uint64_t pawns, uint64_t opponentPieces, bool isWhite) {
    if (isWhite) {
        uint64_t leftCapture = (pawns << 7) & opponentPieces & ~fileH; // Prevent wrap-around
        uint64_t rightCapture = (pawns << 9) & opponentPieces & ~fileA; // Prevent wrap-around
        return leftCapture | rightCapture;
    } else {
        uint64_t leftCapture = (pawns >> 9) & opponentPieces & ~fileH; // Prevent wrap-around
        uint64_t rightCapture = (pawns >> 7) & opponentPieces & ~fileA; // Prevent wrap-around
        return leftCapture | rightCapture;
    }
}

//Generate all pawn moves 

uint64_t pawnGen(uint64_t pawns, uint64_t opponentPieces, bool isWhite) {
    uint64_t singlePush = pawnPush(pawns, isWhite);
    uint64_t doublePush = pawnDoublePush(pawns, isWhite);
    uint64_t captures = pawnCap(pawns, opponentPieces, isWhite);

    return singlePush | doublePush | captures; // Combine all moves in to single bitboard
}









/* print board for visualization and debugging*/
void printBitboard(uint64_t& board) {
    string name = bitboardNames[&board];
    cout << "Bitboard for " << name << ":" << endl;
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            cout << ((board >> square) & 1) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main () {

    printBitboard(whitePawns);
    printBitboard(blackPawns);

    return 0;
}




