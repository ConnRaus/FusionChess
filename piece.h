// Piece.h

#ifndef PIECE_H
#define PIECE_H

#include "enums.h"
#include "pieceinfo.h"
//#include "board.h" (dont do this)
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QVector>

class Piece {
public:
    Piece(int row, int col, PieceType type, Color color);
    void drawPiece(QGraphicsScene* scene);
    PieceType getType();
    Color getColor();
    void setCoords(int row, int col);
    bool isValidMove(int toX, int toY, QVector<QVector<PieceInfo>> piecegrid);
    QVector<QVector<bool>> getMoveGrid();


protected:
    PieceType type_ = EMPTY;
    QImage image_;
    Color color_;
    int row_;
    int col_;
    QVector<QVector<bool>> movegrid_;
    QVector<QVector<PieceInfo>> piecegrid_;
    void resetMoveGrid();
    void resetPieceGrid();
    virtual void updateMoveGrid();
    virtual bool isCombinable(PieceType otherPieceType);
    void updatePieceGrid(QVector<QVector<PieceInfo>> piecegrid);
    int lookUp();
    int lookDown();
    int lookLeft();
    int lookRight();
    int lookUpLeft();
    int lookUpRight();
    int lookDownLeft();
    int lookDownRight();
};

#endif // PIECE_H
