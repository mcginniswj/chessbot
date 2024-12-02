#ifndef ROOKGEN_H
#define ROOKGEN_H

#include "board.hpp"

class RookGen {
public:
    // Generates all legal rook moves for a given rook bitboard
    u64 generateMoves(u64 rooks, bool isWhite);
};

#endif // ROOKGEN_H
