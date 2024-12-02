#include "rookGen.hpp"

u64 RookGen::generateMoves(u64 rooks, bool isWhite) {
    Board board;
    u64 moves = 0ULL;  // To store all possible moves

    // Get bitboards for occupied squares and opponent pieces
    u64 occupied = board.getBitBoard("Occupied Squares");
    u64 opponentPieces = isWhite ? board.getBitBoard("Black Pieces") : board.getBitBoard("White Pieces");

    // Iterate over each square on the rook's bitboard
    while (rooks) {
        // Get the index of the current rook (lowest set bit)
        int square = __builtin_ctzll(rooks);
        
        // Mask to isolate the square of interest
        u64 currentSquare = 1ULL << square;

        // Generate moves in all 4 directions

        // 1. Upwards (north)
        u64 upMoves = (currentSquare << 8) & ~occupied; // Move upwards until blocked
        while (upMoves) {
            int moveSquare = __builtin_ctzll(upMoves);
            moves |= (1ULL << moveSquare);  // Add move to list
            if (occupied & (1ULL << moveSquare)) break;  // Blocked by a piece
            upMoves <<= 8;
        }

        // 2. Downwards (south)
        u64 downMoves = (currentSquare >> 8) & ~occupied; // Move downwards until blocked
        while (downMoves) {
            int moveSquare = __builtin_ctzll(downMoves);
            moves |= (1ULL << moveSquare);
            if (occupied & (1ULL << moveSquare)) break;  // Blocked by a piece
            downMoves >>= 8;
        }

        // 3. Leftwards (west)
        u64 leftMoves = (currentSquare << 1) & ~fileA & ~occupied; // Move left until blocked
        while (leftMoves) {
            int moveSquare = __builtin_ctzll(leftMoves);
            moves |= (1ULL << moveSquare);
            if (occupied & (1ULL << moveSquare)) break;  // Blocked by a piece
            leftMoves <<= 1;
        }

        // 4. Rightwards (east)
        u64 rightMoves = (currentSquare >> 1) & ~fileH & ~occupied; // Move right until blocked
        while (rightMoves) {
            int moveSquare = __builtin_ctzll(rightMoves);
            moves |= (1ULL << moveSquare);
            if (occupied & (1ULL << moveSquare)) break;  // Blocked by a piece
            rightMoves >>= 1;
        }

        // Remove the current rook from the rooks bitboard
        rooks &= rooks - 1;
    }

    return moves;
}
