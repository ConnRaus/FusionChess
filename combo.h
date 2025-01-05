#ifndef COMBO_H
#define COMBO_H

#include "piece.h"
#include "enums.h"
#include "piecefactory.h"

class Combo : public Piece {
public:
    Combo(int row, int col, Color color, PieceType piece1, PieceType piece2);
    void updateMoveGrid() override;
    QVector<PieceType> getTypes();

private:
    PieceType piecetype1_;
    PieceType piecetype2_;
    PieceFactory* factory_ = new PieceFactory();
};

#endif
