#ifndef BOARD_H
#define BOARD_H

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

// Bitboards for white pieces
extern u64 whitePawns;
extern u64 whiteKnights;
extern u64 whiteBishops;
extern u64 whiteRooks;
extern u64 whiteQueens;
extern u64 whiteKing;

// Bitboards for black pieces
extern u64 blackPawns;
extern u64 blackKnights;
extern u64 blackBishops;
extern u64 blackRooks;
extern u64 blackQueens;
extern u64 blackKing;

// Combined bitboards (dependent and must be updated constantly)
extern u64 allWhite;
extern u64 allBlack;
extern u64 occupied;
extern u64 emptySquares;

// Map associating each bitboard with its name
extern unordered_map<u64*, string> bitboardNames;

class Board {

public:
    Board();

    void reset();

    void updateDependentBoards();

    void printBoard(u64& board);

    u64 getBitBoard(string piece); 

    void setBitBoard(string piece, u64 value);
};

#endif // BITBOARD_H
