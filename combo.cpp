#include "combo.h"
#include <QDebug>
#include <QDir>
#include <QCoreApplication>

// Combo piece takes in two pieces and combines their move grids
Combo::Combo(int row, int col, Color color, PieceType piecetype1, PieceType piecetype2)
    : Piece(row, col, COMBO, color)
{
    type_ = COMBO;
    piecetype1_ = piecetype1;
    piecetype2_ = piecetype2;
    
    // Set the image based on the color of the piece
    QVector<QString> pieceTypes = {"pawn", "rook", "knight", "bishop", "queen"};
    QString colorString = (color == WHITE) ? "white" : "black";
    // To avoid having to have 2 images for each combo piece, we go in order of pieceTypes
    // Piece names are in format (color)(pieceType1)(pieceType2).png
    // Compare the two piece enums and pieceType1 must be the smaller one
    if (piecetype1 > piecetype2) {
        PieceType temp = piecetype1;
        piecetype1 = piecetype2;
        piecetype2 = temp;
    }

    QString imageName = ":/combos/" + colorString + pieceTypes[piecetype1] + pieceTypes[piecetype2] + ".png";
    image_ = QImage(imageName);
    qDebug() << imageName;

}

void Combo::updateMoveGrid() {

    // call a random isValidMove function to update everything in piece1 and piece2
    Piece* piece1 = factory_->create(row_, col_, piecetype1_, color_);
    Piece* piece2 = factory_->create(row_, col_, piecetype2_, color_);
    
    piece1->isValidMove(0, 0, piecegrid_);
    piece2->isValidMove(0, 0, piecegrid_);

    QVector<QVector<bool>> piece1Moves = piece1->getMoveGrid();
    QVector<QVector<bool>> piece2Moves = piece2->getMoveGrid();

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j ++) {
            if(piece1Moves[i][j] || piece2Moves[i][j]) {
                movegrid_[i][j] = true;
            }
        }
    }

    // remove current location from movegrid
    movegrid_[row_][col_] = false;

    // remove any currently valid moves that would move to a square that has a piece of the same color
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j ++) {
            if(movegrid_[i][j] && piecegrid_[i][j].color == color_) {
                movegrid_[i][j] = false;
            }
        }
    }

}

QVector<PieceType> Combo::getTypes() {
    QVector<PieceType> returnThis = {piecetype1_, piecetype2_};
    return returnThis;
}

