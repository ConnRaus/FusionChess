#ifndef ROOK_H
#define ROOK_H


#include "piece.h"
#include "enums.h"

class Rook : public Piece {
public:
    Rook(int row, int col, Color color);

    void updateMoveGrid() override;
    bool isCombinable(PieceType otherPieceType) override;
};

#endif
