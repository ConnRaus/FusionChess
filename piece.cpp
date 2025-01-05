// Piece.cpp

#include "piece.h"
#include <QDebug>

Piece::Piece(int row, int col, PieceType type, Color color) {
    row_ = row;
    col_ = col;
    color_ = color;

    // Resize movegrid_ to 8x8
    movegrid_.resize(8);
    for (int i = 0; i < 8; i++) {
        movegrid_[i].resize(8);
    }
    resetMoveGrid();

    // Resize piecegrid_ to 8x8
    piecegrid_.resize(8);
    for (int i = 0; i < 8; i++) {
        piecegrid_[i].resize(8);
    }
    resetPieceGrid();


}

bool Piece::isCombinable(PieceType otherPieceType) {
    return false;
}

PieceType Piece::getType() {
    return type_;
}

Color Piece::getColor() {
    return color_;
}

void Piece::setCoords(int row, int col) {
    row_ = row;
    col_ = col;
}

int Piece::lookUp() {
    int counter = 0;
    for(int currRow = row_; currRow > 0; currRow--) {
        if(piecegrid_[currRow-1][col_].type != EMPTY) {
            return counter;
        }
        counter++;
    }
    return counter;
}

int Piece::lookDown() {
    int counter = 0;
    for(int currRow = row_; currRow < 7; currRow++) {
        if(piecegrid_[currRow+1][col_].type != EMPTY) {
            return counter;
        }
        counter++;
    }
    return counter;
}


int Piece::lookLeft() {
    int counter = 0;
    for(int currCol = col_; currCol > 0; currCol--) {
        if(piecegrid_[row_][currCol-1].type != EMPTY) {
            return counter;
        }
        counter++;
    }
    return counter;
}


int Piece::lookRight() {
    int counter = 0;
    for(int currCol = col_; currCol < 7; currCol++) {
        if(piecegrid_[row_][currCol+1].type != EMPTY) {
            return counter;
        }
        counter++;
    }
    return counter;
}


int Piece::lookUpLeft() {
    int counter = 0;
    for(int currCol = col_, currRow = row_; currCol > 0 && currRow > 0; currCol--, currRow--) {
        if(piecegrid_[currRow-1][currCol-1].type != EMPTY) {
            return counter;
        }
        counter++;
    }
    return counter;
}


int Piece::lookUpRight() {
    int counter = 0;
    for(int currCol = col_, currRow = row_; currCol < 7 && currRow > 0; currCol++, currRow--) {
        if(piecegrid_[currRow-1][currCol+1].type != EMPTY) {
            return counter;
        }
        counter++;
    }
    return counter;
}


int Piece::lookDownLeft() {
    int counter = 0;
    for(int currCol = col_, currRow = row_; currCol > 0 && currRow < 7; currCol--, currRow++) {
        if(piecegrid_[currRow+1][currCol-1].type != EMPTY) {
            return counter;
        }
        counter++;
    }
    return counter;
}


int Piece::lookDownRight() {
    int counter = 0;
    for(int currCol = col_, currRow = row_; currCol < 7 && currRow < 7; currCol++, currRow++) {
        if(piecegrid_[currRow+1][currCol+1].type != EMPTY) {
            return counter;
        }
        counter++;
    }
    return counter;
}


bool Piece::isValidMove(int toRow, int toCol, QVector<QVector<PieceInfo>> piecegrid) {
    resetMoveGrid();
    updatePieceGrid(piecegrid);
    updateMoveGrid();
    return movegrid_[toRow][toCol];
}


void Piece::updateMoveGrid() {
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            movegrid_[col][row] = false;
        }
    }
}

void Piece::updatePieceGrid(QVector<QVector<PieceInfo>> piecegrid) {
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            piecegrid_[row][col] = piecegrid[row][col];
        }
    }
}

void Piece::resetMoveGrid() {
    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            movegrid_[i][j] = false;
        }
    }
}

void Piece::resetPieceGrid() {
    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            PieceInfo emptySquare;
            emptySquare.color = NONE;
            emptySquare.type = EMPTY;
            piecegrid_[i][j] = emptySquare;
        }
    }
}

QVector<QVector<bool>> Piece::getMoveGrid() {
    return movegrid_;
}

void Piece::drawPiece(QGraphicsScene* scene) {
    QPixmap pixmap = QPixmap::fromImage(image_);
    if(!pixmap.isNull()) {
        pixmap = pixmap.scaled(50, 50); // resize image
        scene->addPixmap(pixmap)->setPos(col_*75+12, row_*75+12);
    }
}
