#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H
#include "piece.h"
#include "enums.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"


class PieceFactory
{
public:
    PieceFactory();
    Piece* create(int row, int col, PieceType type, Color color);
};

#endif // PIECEFACTORY_H
