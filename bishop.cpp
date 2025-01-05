#include "bishop.h"
#include <QDir>
#include <QCoreApplication>
#include <QDebug>

Bishop::Bishop(int row, int col, Color color)
    : Piece(row, col, BISHOP, color)
{
    type_ = BISHOP;
    // Set the image based on the color of the piece
    if (color == WHITE) {
        image_ = QImage(":/whitebishop.png");
    } else {
        image_ = QImage(":/blackbishop.png");
    }
}

void Bishop::updateMoveGrid() {

    int upLeftDist = lookUpLeft();
    int upRightDist = lookUpRight();
    int downLeftDist = lookDownLeft();
    int downRightDist = lookDownRight();

    // up left
    for(int i = 1; i <= upLeftDist; i++) {
        if(row_-i >= 0 && col_-i >= 0 && piecegrid_[row_-i][col_-i].color != color_) {
            movegrid_[row_-i][col_-i] = true;
        }
    }
    // look one farther, if valid spot
    if(row_-upLeftDist-1 >= 0 && col_-upLeftDist-1 >= 0) {

        PieceInfo* piecespot = &piecegrid_[row_-upLeftDist-1][col_-upLeftDist-1];
        bool* movespot = &movegrid_[row_-upLeftDist-1][col_-upLeftDist-1];
        //combining
        // if other is different color
        if(piecespot->color != this->color_) {
            *movespot = true;
        }
        // if other is same color
        else if(piecespot->color == this->color_) {
            if(this->isCombinable(piecespot->type)) {
                *movespot = true;
            }
        }
        else{
            // otherwise
            *movespot = false;
        }

    }

    // up right
    for(int i = 1; i <= upRightDist; i++) {
        if(row_-i >= 0 && col_+i <= 7 && piecegrid_[row_-i][col_+i].color != color_) {
            movegrid_[row_-i][col_+i] = true;
        }
    }
    // look one farther, if valid spot
    if(row_-upRightDist-1 >= 0 && col_+upRightDist+1 <= 7) {

        PieceInfo* piecespot = &piecegrid_[row_-upRightDist-1][col_+upRightDist+1];
        bool* movespot = &movegrid_[row_-upRightDist-1][col_+upRightDist+1];
        //combining
        // if other is different color
        if(piecespot->color != this->color_) {
            *movespot = true;
        }
        // if other is same color
        else if(piecespot->color == this->color_) {
            if(this->isCombinable(piecespot->type)) {
                *movespot = true;
            }
        }
        else{
            // otherwise
            *movespot = false;
        }

    }

    // down left
    for(int i = 1; i <= downLeftDist; i++) {
        if(row_+i <= 7 && col_-i >= 0 && piecegrid_[row_+i][col_-i].color != color_) {
            movegrid_[row_+i][col_-i] = true;
        }
    }
    // look one farther, if valid spot
    if(row_+downLeftDist+1 <= 7 && col_-downLeftDist-1 >= 0) {

        PieceInfo* piecespot = &piecegrid_[row_+downLeftDist+1][col_-downLeftDist-1];
        bool* movespot = &movegrid_[row_+downLeftDist+1][col_-downLeftDist-1];
        //combining
        // if other is different color
        if(piecespot->color != this->color_) {
            *movespot = true;
        }
        // if other is same color
        else if(piecespot->color == this->color_) {
            if(this->isCombinable(piecespot->type)) {
                *movespot = true;
            }
        }
        else{
            // otherwise
            *movespot = false;
        }

    }

    // down right
    for(int i = 1; i <= downRightDist; i++) {
        if(row_+i <= 7 && col_+i <= 7 && piecegrid_[row_+i][col_+i].color != color_) {
            movegrid_[row_+i][col_+i] = true;
        }
    }
    // look one farther, if valid spot
    if(row_+downRightDist+1 <= 7 && col_+downRightDist+1 <= 7) {

        PieceInfo* piecespot = &piecegrid_[row_+downRightDist+1][col_+downRightDist+1];
        bool* movespot = &movegrid_[row_+downRightDist+1][col_+downRightDist+1];
        //combining
        // if other is different color
        if(piecespot->color != this->color_) {
            *movespot = true;
        }
        // if other is same color
        else if(piecespot->color == this->color_) {
            if(this->isCombinable(piecespot->type)) {
                *movespot = true;
            }
        }
        else{
            // otherwise
            *movespot = false;
        }

    }

}


    
bool Bishop::isCombinable(PieceType otherPieceType) {
    QVector<PieceType> combinablePieces =
    {
        PAWN,
        ROOK,
        KNIGHT
    };
    return combinablePieces.contains(otherPieceType);
}
