#include "rookGen.hpp"

u64 RookGen::generateMoves(u64 rooks, bool isWhite) {
    Board board;
    u64 moves = 0ULL;
    u64 occupied = board.getBitBoard("Occupied Squares");
    u64 friendlyPieces;

    isWhite ? friendlyPieces = board.getBitBoard("White Pieces") : friendlyPieces = board.getBitBoard("Black Pieces");

    // Loop over all rook positions
    while (rooks) {
        int square = __builtin_ctzll(rooks); // Get index of the least significant bit set
        rooks &= rooks - 1;                 // Remove the rook from the bitboard

        u64 squareMask = 1ULL << square;

        // Generate moves in all four directions
        moves |= slidingAttack(squareMask, occupied, friendlyPieces, Direction::UP);
        moves |= slidingAttack(squareMask, occupied, friendlyPieces, Direction::DOWN);
        moves |= slidingAttack(squareMask, occupied, friendlyPieces, Direction::LEFT);
        moves |= slidingAttack(squareMask, occupied, friendlyPieces, Direction::RIGHT);
    }

    return moves;
}

// Sliding attack in a specific direction
u64 RookGen::slidingAttack(u64 squareMask, u64 occupied, u64 friendly, Direction dir) {
    u64 attacks = 0ULL;
    int shift;

    // Determine the shift based on the direction
    switch (dir) {
    case Direction::UP: shift = 8; break;
    case Direction::DOWN: shift = -8; break;
    case Direction::LEFT: shift = -1; break;
    case Direction::RIGHT: shift = 1; break;
    }

    u64 blocker = squareMask;

    while (true) {
        // Shift the blocker
        if (shift > 0) blocker <<= shift; // Up, Right
        else blocker >>= -shift;         // Down, Left

        // Break if out of bounds or no more blockers
        if ((dir == Direction::LEFT && (blocker & fileH)) || (dir == Direction::RIGHT && (blocker & fileA)) || blocker == 0) break;

        // Add the blocker to the attacks
        attacks |= blocker;

        // Stop if the blocker hits any occupied square
        if (blocker & occupied) break;

        // Exclude friendly pieces
        attacks &= ~friendly;
    }

    return attacks;
}
