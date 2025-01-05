#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "enums.h"

class Knight : public Piece {
public:
    Knight(int row, int col, Color color);

    void updateMoveGrid() override;
    bool isCombinable(PieceType otherPieceType) override;
};

#endif
