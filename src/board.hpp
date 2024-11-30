#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

typedef uint64_t u64;

// Constants for ranks and files
constexpr u64 rank1 = 0x00000000000000FF;
constexpr u64 rank2 = 0x000000000000FF00;
constexpr u64 rank3 = 0x0000000000FF0000;
constexpr u64 rank4 = 0x00000000FF000000;
constexpr u64 rank5 = 0x000000FF00000000;
constexpr u64 rank6 = 0x0000FF0000000000;
constexpr u64 rank7 = 0x00FF000000000000;
constexpr u64 rank8 = 0xFF00000000000000;

constexpr u64 fileA = 0x0101010101010101;
constexpr u64 fileB = 0x0202020202020202;
constexpr u64 fileC = 0x0404040404040404;
constexpr u64 fileD = 0x0808080808080808;
constexpr u64 fileE = 0x1010101010101010;
constexpr u64 fileF = 0x2020202020202020;
constexpr u64 fileG = 0x4040404040404040;
constexpr u64 fileH = 0x8080808080808080;



// Utility functions
#define set(b, i) ((b) |= (1ULL << i))
#define clear(b, i) ((b) &= ~(1ULL << i))
#define get(b, i) ((b) & (1ULL << i))
#define get_lsb(b) (__builtin_ctzll(b))


class Board {

public:
    Board();

    void reset();

    void updateDependentBoards();

    void printBoard(u64& board);

    u64 getBitBoard(string piece); 

    void setBitBoard(string piece, u64 value);

    private:
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
};

#endif // BITBOARD_H
