#include "pawnGen.hpp"



u64 PawnGen::generateMoves(u64 pawns, bool isWhite) {
    Board Board;
    u64 singlePush = 0ULL;
    u64 doublePush = 0ULL;
    u64 captures = 0ULL;

    Board.updateDependentBoards();
    u64 opponentPieces;
    u64 emptySquares = Board.getBitBoard("emptySquares");

    isWhite ? opponentPieces = Board.getBitBoard("allWhite") : opponentPieces = Board.getBitBoard("allBlack");

    if (isWhite) {
        singlePush = (pawns << 8) & emptySquares;
        doublePush = (singlePush << 8) & emptySquares & rank4;
        u64 leftCapture = (pawns << 7) & opponentPieces & ~fileH;
        u64 rightCapture = (pawns << 9) & opponentPieces & ~fileA;
        captures = leftCapture | rightCapture;
    } else {
        singlePush = (pawns >> 8) & emptySquares;
        doublePush = (singlePush >> 8) & emptySquares & rank5;
        u64 leftCapture = (pawns >> 9) & opponentPieces & ~fileH;
        u64 rightCapture = (pawns >> 7) & opponentPieces & ~fileA;
        captures = leftCapture | rightCapture;
    }

    return singlePush | doublePush | captures;
}
