#ifndef KNIGHT_GEN_H
#define KNIGHT_GEN_H

#include "board.hpp"

class KnightGen {
public:
    u64 generateMoves(u64 knights, bool isWhite);
};

#endif // KNIGHT_GEN_H
