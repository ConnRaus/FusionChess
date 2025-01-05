#ifndef KING_H
#define KING_H

#include "piece.h"
#include "enums.h"

class King : public Piece {
public:
    King(int row, int col, Color color);

    void updateMoveGrid() override;
};

#endif
