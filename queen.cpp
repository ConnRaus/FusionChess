#include "queen.h"
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include "rook.h"
#include "bishop.h"

Queen::Queen(int row, int col, Color color)
    : Piece(row, col, QUEEN, color)
{
    type_ = QUEEN;
    // Set the image based on the color of the piece
    if (color == WHITE) {
        image_ = QImage(":/whitequeen.png");
    } else {
        image_ = QImage(":/blackqueen.png");
    }
}

void Queen::updateMoveGrid() {

    // create bishop and rook at current location, combine their moves to get queen's moves
    Rook rook(row_, col_, color_);
    Bishop bishop(row_, col_, color_);

    // call a random isValidMove function to update everything in rook and bishop
    rook.isValidMove(0, 0, piecegrid_);
    bishop.isValidMove(0, 0, piecegrid_);

    QVector<QVector<bool>> rookMoves = rook.getMoveGrid();
    QVector<QVector<bool>> bishopMoves = bishop.getMoveGrid();

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j ++) {
            if(rookMoves[i][j] || bishopMoves[i][j]) {
                movegrid_[i][j] = true;
            }
        }
    }
    
    // remove current location from movegrid
    movegrid_[row_][col_] = false;

    // go through valid moves, remove any that would move to a same colored piece that isn't isCombinable
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j ++) {
            if(movegrid_[i][j] && piecegrid_[i][j].color == color_ && !isCombinable(piecegrid_[i][j].type)) {
                movegrid_[i][j] = false;
            }
        }
    }
    

}


bool Queen::isCombinable(PieceType otherPieceType) {
    QVector<PieceType> combinablePieces =
    {
        KNIGHT
    };
    return combinablePieces.contains(otherPieceType);
}
