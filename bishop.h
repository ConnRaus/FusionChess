#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"
#include "enums.h"

class Bishop : public Piece {
public:
    Bishop(int row, int col, Color color);

    void updateMoveGrid() override;
    bool isCombinable(PieceType otherPieceType) override;
};

#endif
