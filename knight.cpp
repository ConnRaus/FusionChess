#include "knight.h"
#include <QDir>
#include <QCoreApplication>

Knight::Knight(int row, int col, Color color)
    : Piece(row, col, KNIGHT, color)
{
    type_ = KNIGHT;
    // Set the image based on the color of the piece
    if (color == WHITE) {
        image_ = QImage(":/whiteknight.png");
    } else {
        image_ = QImage(":/blackknight.png");
    }
}

void Knight::updateMoveGrid() {

    const int deltas[8][2] = {
        {2, 1},   // down
        {2, -1},  // up
        {-2, 1},  // left
        {-2, -1},   // right
        {1, 2}, // up-left
        {1, -2},  // up-right
        {-1, 2},  // down-left
        {-1, -2}    // down-right
    };

    for (int dir = 0; dir < 8; dir++) {
        int dy = deltas[dir][0];
        int dx = deltas[dir][1];

        int newRow = row_ + dy;
        int newCol = col_ + dx;

        // if enemy or empty piece, can move there
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && piecegrid_[newRow][newCol].color != this->color_) {
            movegrid_[newRow][newCol] = true;
        }
        // if same color, can move there if other piece is combinable
        else if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && piecegrid_[newRow][newCol].color == this->color_) {
            if (isCombinable(piecegrid_[newRow][newCol].type)) {
                movegrid_[newRow][newCol] = true;
            }
        }
    }

}


bool Knight::isCombinable(PieceType otherPieceType) {
    QVector<PieceType> combinablePieces =
    {
        PAWN,
        BISHOP,
        ROOK,
        QUEEN
    };
    return combinablePieces.contains(otherPieceType);
}