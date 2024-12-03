#ifndef ROOKGEN_HPP
#define ROOKGEN_HPP

#include "board.hpp"
#include <cstdint>

typedef uint64_t u64;

class RookGen {
public:
    enum class Direction { UP, DOWN, LEFT, RIGHT };

    u64 generateMoves(u64 rooks, bool isWhite);

private:
    u64 slidingAttack(u64 squareMask, u64 occupied, u64 friendly, Direction dir);
};

#endif // ROOKGEN_HPP
