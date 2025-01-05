#include "pawn.h"
#include <QDir>
#include <QCoreApplication>

Pawn::Pawn(int row, int col, Color color)
    : Piece(row, col, PAWN, color)
{
    type_ = PAWN;
    // Set the image based on the color of the piece
    if (color == WHITE) {
        image_ = QImage(":/whitepawn.png");
    } else {
        image_ = QImage(":/blackpawn.png");
    }
}

bool Pawn::checkAdjacentDiagonal(int x, int y) {
    // if samecolor, check if combinable
    if(piecegrid_[row_+x][col_+y].color == color_) {
        if(isCombinable(piecegrid_[row_+x][col_+y].type)) {
            return true;
        } else {
            return false;
        }
    }
    else {
        return true;
    }
}

void Pawn::updateMoveGrid() {
    if(color_ == BLACK) {
        if(lookDown() >= 1) {
            movegrid_[row_+1][col_] = true;
        }
        //first turn
        if(row_ == 1 && lookDown() >= 2) {
            movegrid_[row_+2][col_] = true;
        }
        //capture
        if(row_ < 7 && col_ < 7 && piecegrid_[row_+1][col_+1].type != EMPTY) {
            movegrid_[row_+1][col_+1] = checkAdjacentDiagonal(1, 1);
        }
        if(row_ < 7 && col_ > 0 && piecegrid_[row_+1][col_-1].type != EMPTY) {
            // if same color, check if combinable
            movegrid_[row_+1][col_-1] = checkAdjacentDiagonal(1, -1);
        }
    }
    else if(color_ == WHITE) {
        if(lookUp() >= 1) {
            movegrid_[row_-1][col_] = true;
        }
        //first turn
        if(row_ == 6 && lookUp() >= 2) {
            movegrid_[row_-2][col_] = true;
        }
        //capture
        if(row_ > 0 && col_ < 7 && piecegrid_[row_-1][col_+1].type != EMPTY) {
            // if samecolor, check if combinable
            movegrid_[row_-1][col_+1] = checkAdjacentDiagonal(-1, 1);
        }
        if(row_ > 0 && col_ > 0 && piecegrid_[row_-1][col_-1].type != EMPTY) {
            // if same color, check if combinable
            movegrid_[row_-1][col_-1] = checkAdjacentDiagonal(-1, -1);
        }

    }
}

bool Pawn::isCombinable(PieceType otherPieceType) {
    QVector<PieceType> combinablePieces =
    {
        KNIGHT,
        BISHOP,
        ROOK,
        QUEEN
    };
    return combinablePieces.contains(otherPieceType);
}
