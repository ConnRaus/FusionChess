#ifndef BOARD_H
#define BOARD_H

#include <QtWidgets>
#include <QObject>
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "bishop.h"
#include "knight.h"
#include "combo.h"
#include "enums.h"
#include "pieceinfo.h"


class Board : public QObject {
    Q_OBJECT
public:
    Board(QGraphicsScene* scene);
    void initializeBoard();
    void setBoardEmpty();
    void showMoves(Piece* p);
    void movePiece(int fromRow, int fromCol, int toRow, int toCol);
    void drawBoard();
    void highlightSquare(int x, int y);
    void highlightSquare(int row, int col, QColor color);
    void updatePieceGrid();

public slots:
    void handleLeftClicked(int row, int col);
    void handleRightClicked(int row, int col);

signals:
    void playerMove(int turn, int fromRow, int fromCol, int toRow, int ToCol, Piece* movePiece, bool pieceTaken);
    void gameOver(int winningPlayer);

private:
    Piece* squares[8][8];
    QGraphicsScene* scene;
    bool selected_ = false;
    int selectedrow_;
    int selectedcol_;
    int turn_ = 0;
    QVector<QVector<PieceInfo>> piecegrid_;
};

#endif // BOARD_H
