#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "enums.h"

class Queen : public Piece {
public:
    Queen(int row, int col, Color color);

    void updateMoveGrid() override;
    bool isCombinable(PieceType otherPieceType) override;
};

#endif
