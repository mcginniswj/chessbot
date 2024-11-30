#include "pawnGen.hpp"
#include "knightGen.hpp"
#include "rookGen.hpp"
#include "board.hpp"

int main() {
    Board Board;

    Board.reset();

    u64 whitePawns = Board.getBitBoard("whitePawns");
    Board.printBoard(whitePawns);
    u64 whiteKnights = Board.getBitBoard("whiteKnights");
    Board.printBoard(whiteKnights);

    PawnGen pawnGen;
    whitePawns= pawnGen.generateMoves(whitePawns, true);

    KnightGen knightGen;
    whiteKnights = knightGen.generateMoves(whiteKnights, true);

    Board.printBoard(whitePawns);
    Board.printBoard(whiteKnights);

    return 0;
}
