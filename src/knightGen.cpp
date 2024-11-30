#include "knightGen.hpp"

u64 KnightGen::generateMoves(u64 knights, bool isWhite) {
    Board Board;
    u64 attacks = 0ULL;
    u64 friendlyPieces;

    // Generate potential attack squares for knights
    attacks = (((knights >> 6)  | (knights << 10)) & ~(fileG | fileH)) | // Left-Down and Left-Up
              (((knights >> 10) | (knights << 6))  & ~(fileA | fileB)) | // Right-Down and Right-Up
              (((knights >> 15) | (knights << 17)) & ~(fileH))         | // Down-Left and Up-Left
              (((knights >> 17) | (knights << 15)) & ~(fileA));          // Down-Right and Up-Right

    // Exclude friendly pieces from the attack mask
    Board.updateDependentBoards();
    isWhite ? friendlyPieces = Board.getBitBoard("allWhite") : friendlyPieces = Board.getBitBoard("allBlack");
    attacks &= ~friendlyPieces;

    return attacks;
}
