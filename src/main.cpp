#include "pawnGen.hpp"
#include "knightGen.hpp"
#include "rookGen.hpp"
#include "board.hpp"

int main() {
    Board board;
    PawnGen pawngen;
    KnightGen knightgen;

    board.reset();

    board.printBoard(whitePawns);
    board.printBoard(whiteKnights);

    whitePawns = pawngen.generateMoves(whitePawns, true);
    whiteKnights = knightgen.generateMoves(whiteKnights, true);
    board.updateDependentBoards();

    board.printBoard(whitePawns);
    board.printBoard(whiteKnights);

    return 0;
}
