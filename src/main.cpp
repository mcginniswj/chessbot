#include "pawnGen.hpp"
#include "knightGen.hpp"
#include "rookGen.hpp"
#include "board.hpp"

int main() {
    Board board;
    PawnGen pawngen;
    KnightGen knightgen;
    u64 temp;

    board.setBitBoard("White Knights", (1ULL << 21));
    board.printBoard("White Pieces");

    temp = knightgen.generateMoves(board.getBitBoard("White Knights"), true);
    board.setBitBoard("White Knights", temp);

    board.printBoard("White Knights");
    board.printBoard("White Pieces");

    return 0;
}
