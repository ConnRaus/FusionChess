#include "king.h"
#include <QDir>
#include <QCoreApplication>

King::King(int row, int col, Color color)
    : Piece(row, col, KING, color)
{
    type_ = KING;
    // Set the image based on the color of the piece
    if (color == WHITE) {
        image_ = QImage(":/whiteking.png");
    } else {
        image_ = QImage(":/blackking.png");
    }
}

void King::updateMoveGrid() {

    const int deltas[8][2] = {
        {1, 0},   // down
        {-1, 0},  // up
        {0, -1},  // left
        {0, 1},   // right
        {-1, -1}, // up-left
        {-1, 1},  // up-right
        {1, -1},  // down-left
        {1, 1}    // down-right
    };

    for (int dir = 0; dir < 8; dir++) {
        int dy = deltas[dir][0];
        int dx = deltas[dir][1];

        int newRow = row_ + dy;
        int newCol = col_ + dx;

        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && piecegrid_[newRow][newCol].color != this->color_) {
            movegrid_[newRow][newCol] = true;
        }
    }

}