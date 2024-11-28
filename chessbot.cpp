#include <cstdint>
#include <iostream>

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
