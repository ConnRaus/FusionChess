#include "piecefactory.h"

PieceFactory::PieceFactory()
{

}

Piece* PieceFactory::create(int row, int col, PieceType type, Color color)
{
    switch (type) {
        case PAWN:
            return new Pawn(row, col, color);
        case ROOK:
            return new Rook(row, col, color);
        case KNIGHT:
            return new Knight(row, col, color);
        case BISHOP:
            return new Bishop(row, col, color);
        case QUEEN:
            return new Queen(row, col, color);
        default:
            return nullptr;
    }
}


