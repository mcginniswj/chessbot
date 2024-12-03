#include "pawnGen.hpp"
#include "knightGen.hpp"
#include "rookGen.hpp"
#include "board.hpp"

int main() {
    Board board;
    PawnGen pawngen;
    KnightGen knightgen;
    RookGen rookgen;
    u64 temp;

    
    board.setBitBoard("White Rooks", 1ULL << 24);
    board.printBoard("White Rooks");
    board.printBoard("Occupied Squares");
    temp = rookgen.generateMoves(board.getBitBoard("White Rooks"), true);
    board.setBitBoard("White Rooks", temp);
    board.printBoard("White Pieces");
    board.printBoard("White Rooks");

    return 0;
}
