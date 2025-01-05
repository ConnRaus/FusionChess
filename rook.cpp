#include "rook.h"
#include <QDebug>
#include <QDir>
#include <QCoreApplication>

Rook::Rook(int row, int col, Color color)
    : Piece(row, col, ROOK, color)
{
    type_ = ROOK;
    // Set the image based on the color of the piece
    if (color == WHITE) {
        image_ = QImage(":/whiterook.png");
    } else {
        image_ = QImage(":/blackrook.png");
    }
}

void Rook::updateMoveGrid() {

    int upDist = lookUp();
    int downDist = lookDown();
    int leftDist = lookLeft();
    int rightDist = lookRight();

    // up
    for (int i = 1; i <= upDist; i++) {
        // everything in range of lookUp() is good
        movegrid_[row_-i][col_] = true;
    }
    // if valid spot
    if(row_-upDist-1 >= 0) {

        PieceInfo* piecespot = &piecegrid_[row_-upDist-1][col_];
        bool* movespot = &movegrid_[row_-upDist-1][col_];

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

    // down
    for (int i = 1; i <= downDist; i++) {
        // everything in range of lookDown() is good
        movegrid_[row_+i][col_] = true;
    }
    // if valid spot
    if(row_+downDist+1 <= 7) {

        PieceInfo* piecespot = &piecegrid_[row_+downDist+1][col_];
        bool* movespot = &movegrid_[row_+downDist+1][col_];

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

    // left
    for (int i = 1; i <= leftDist; i++) {
        // everything in range of lookLeft() is good
        movegrid_[row_][col_-i] = true;
    }
    // if valid spot
    if(col_-leftDist-1 >= 0) {

        PieceInfo* piecespot = &piecegrid_[row_][col_-leftDist-1];
        bool* movespot = &movegrid_[row_][col_-leftDist-1];

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

    // right
    for (int i = 1; i <= rightDist; i++) {
        // everything in range of lookRight() is good
        movegrid_[row_][col_+i] = true;
    }
    // if valid spot
    if(col_+rightDist+1 <= 7) {

        PieceInfo* piecespot = &piecegrid_[row_][col_+rightDist+1];
        bool* movespot = &movegrid_[row_][col_+rightDist+1];

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

bool Rook::isCombinable(PieceType otherPieceType) {
    QVector<PieceType> combinablePieces =
    {
        PAWN,
        BISHOP,
        KNIGHT
    };
    return combinablePieces.contains(otherPieceType);
}
