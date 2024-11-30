#ifndef PAWN_GEN_H
#define PAWN_GEN_H

#include "board.hpp"

class PawnGen {
public:
    u64 generateMoves(u64 pawns, bool isWhite);
};

#endif // PAWN_GEN_H
