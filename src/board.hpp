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

class Board {
private:
    // Bitboards for white pieces
    u64 whitePawns;
    u64 whiteKnights;
    u64 whiteBishops;
    u64 whiteRooks;
    u64 whiteQueens;
    u64 whiteKing;

    // Bitboards for black pieces
    u64 blackPawns;
    u64 blackKnights;
    u64 blackBishops;
    u64 blackRooks;
    u64 blackQueens;
    u64 blackKing;

    // Combined bitboards
    u64 allWhite;
    u64 allBlack;
    u64 occupied;
    u64 emptySquares;

    // Map associating bitboard names to their corresponding variables
    unordered_map<string, u64*> bitboardMap;

    // Updates dependent bitboards
    void updateDependentBoards();
    
public:
    Board();

    void reset();
    void printBoard(const string& pieceName) const;

    // Getter and setter for bitboards
    u64 getBitBoard(const string& piece) const;
    void setBitBoard(const string& piece, u64 value);
};

#endif // BOARD_H
