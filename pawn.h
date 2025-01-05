#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "enums.h"

class Pawn : public Piece {
public:
    Pawn(int row, int col, Color color);

    bool checkAdjacentDiagonal(int x, int y);
    void updateMoveGrid() override;
    bool isCombinable(PieceType otherPieceType) override;
};

#endif
