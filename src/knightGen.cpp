#include "knightGen.hpp"

u64 KnightGen::generateMoves(u64 knights, bool isWhite) {
    u64 attacks = 0ULL;
    u64 friendlyPieces;

    // Generate potential attack squares for knights
    attacks = (((knights >> 6)  | (knights << 10)) & ~(fileA | fileB)) | // Right-Down and Right-Up
              (((knights >> 10) | (knights << 6))  & ~(fileG | fileH)) | // Left-Down and Left-Up
              (((knights >> 15) | (knights << 17)) & ~(fileA))         | // Down-Right and Up-Right
              (((knights >> 17) | (knights << 15)) & ~(fileH));          // Down-Left and Up-Left

    // Exclude friendly pieces from the attack mask
    isWhite ? friendlyPieces = allWhite : friendlyPieces = allBlack;
    attacks &= ~friendlyPieces;

    return attacks;
}
