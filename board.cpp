#include "board.h"
#include <QDebug>

Board::Board(QGraphicsScene* scene)
{
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            squares[i][j] = new Piece(i, j, EMPTY, WHITE);
        }
    }
    this->scene = scene;

    // Initialize piecegrid_ with empty values
    piecegrid_.resize(8);
    for (int i = 0; i < 8; i++) {
        piecegrid_[i].resize(8);
    }
    updatePieceGrid();

}

void Board::drawBoard() {
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            //Draw a rectangle for each square
            QGraphicsRectItem* rect = new QGraphicsRectItem(col*75, row*75, 75, 75);
            if((row+col)%2 == 0) {
                // Color the square white
                QColor tan(255, 233, 197);
                rect->setBrush(QBrush(tan));
            } else {
                QColor brown(100, 60, 40);
                rect->setBrush(QBrush(brown));
            }
            scene->addItem(rect);


            // Draw pieces
            Piece* piece = squares[row][col];
            if(piece->getType() != EMPTY && piece->getColor() != NONE) {
                piece->drawPiece(scene);
            }

        }
    }

}

void Board::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    squares[toRow][toCol] = squares[fromRow][fromCol];
    squares[toRow][toCol]->setCoords(toRow, toCol);
    Piece* p = new Piece(fromRow, fromCol, EMPTY, NONE);
    squares[fromRow][fromCol] = p;

}

void Board::updatePieceGrid() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            PieceInfo p;
            p.color = squares[i][j]->getColor();
            p.type = squares[i][j]->getType();
            piecegrid_[i][j] = p;
        }
    }
}

void Board::highlightSquare(int row, int col) {
    QGraphicsRectItem* rect = new QGraphicsRectItem(col*75, row*75, 75, 75);
    rect->setBrush(QBrush(Qt::green));
    rect->setOpacity(0.7);
    scene->addItem(rect);
    squares[row][col]->drawPiece(scene);
}

void Board::highlightSquare(int row, int col, QColor color) {
    QGraphicsRectItem* rect = new QGraphicsRectItem(col*75, row*75, 75, 75);
    rect->setBrush(QBrush(color));
    rect->setOpacity(0.7);
    scene->addItem(rect);
    squares[row][col]->drawPiece(scene);
}

void Board::handleLeftClicked(int row, int col) {
//    highlightSquare(row, col);
    Piece* selectedPiece = squares[row][col];
    updatePieceGrid();

    // if piece is not current turn's color, don't allow selection
    if(!selected_ && ((turn_%2 == 0 && selectedPiece->getColor() != WHITE) || (turn_%2 == 1 && selectedPiece->getColor() != BLACK))) {
        return;
    }

    if(!selected_) {
        selectedcol_ = col;
        selectedrow_ = row;
        selected_ = true;
        // turn current square blue
        QColor blue = Qt::blue;
        highlightSquare(row, col, blue);
        // highlight valid moves the piece can do green
        for(int rowi = 0; rowi < 8; rowi++) {
            for(int coli = 0; coli < 8; coli++) {
                if(selectedPiece->isValidMove(rowi, coli, piecegrid_)) {
                    highlightSquare(rowi, coli);
                }
            }
        }
    }
    else {
        selectedPiece = squares[selectedrow_][selectedcol_];
        if(selectedPiece->isValidMove(row,col,piecegrid_)) {
            // if move is on top of another piece, send true to emit
            bool pieceTaken = false;
            if(squares[row][col]->getType() != EMPTY) {
                pieceTaken = true;
            }

            
            // if king is taken, emit game over signal
            if(squares[row][col]->getType() == KING) {
                movePiece(selectedrow_, selectedcol_, row, col);
                emit playerMove(turn_, selectedrow_, selectedcol_, row, col, selectedPiece, pieceTaken);
                drawBoard();
                emit gameOver(turn_%2);
                return;
            }


            // if pieceTaken is true and the piece is the same color and not already a combo, take it and create a combo piece at the destination space
            if(pieceTaken && squares[row][col]->getColor() == selectedPiece->getColor() && squares[row][col]->getType() != COMBO && selectedPiece->getType() != COMBO) {
                // create combo piece
                squares[row][col] = new Combo(row, col, squares[row][col]->getColor(), squares[row][col]->getType(), selectedPiece->getType());
                // remove old piece
                Piece* p = new Piece(selectedrow_, selectedcol_, EMPTY, NONE);
                squares[selectedrow_][selectedcol_] = p;
                emit playerMove(turn_, selectedrow_, selectedcol_, row, col, selectedPiece, pieceTaken);
                turn_++;
                selected_ = false;
                drawBoard();
                return;
            }


            // actually move piece and update table
            movePiece(selectedrow_, selectedcol_, row, col);
            emit playerMove(turn_, selectedrow_, selectedcol_, row, col, selectedPiece, pieceTaken);

            // if pawn reaches end of board, promote to queen
            if(squares[row][col]->getType() == PAWN && (row == 0 || row == 7)) {
                squares[row][col] = new Queen(row, col, squares[row][col]->getColor());
            }

            turn_++;
        }
        selected_ = false;
        drawBoard();
    }


    // if piece is clicked, then set selectedx and selected y, and selected is now true(if piece is color of turn).
    // also run getAllValidMoves() on the selected piece, and then run highlightSquare() on that matrix
    // if player selects an invalid spot to move to, reset selected to false and draw board(remove highlighting)
    // if player selects a valid spot to move to, reset selected to false, move piece, and draw board.
}

void Board::handleRightClicked(int row, int col) {
    selected_ = false;
    drawBoard();
}

void Board::initializeBoard() {

    setBoardEmpty();
    //x, y
    for(int i = 0; i < 8; i++) {
        squares[1][i] = new Pawn(1,i,BLACK);
        squares[6][i] = new Pawn(6,i,WHITE);
    }

    squares[0][0] = new Rook(0,0,BLACK);
    squares[0][7] = new Rook(0,7,BLACK);
    squares[7][0] = new Rook(7,0,WHITE);
    squares[7][7] = new Rook(7,7,WHITE);

    squares[0][1] = new Knight(0,1,BLACK);
    squares[0][6] = new Knight(0,6,BLACK);
    squares[7][1] = new Knight(7,1,WHITE);
    squares[7][6] = new Knight(7,6,WHITE);

    squares[0][2] = new Bishop(0,2,BLACK);
    squares[0][5] = new Bishop(0,5,BLACK);
    squares[7][2] = new Bishop(7,2,WHITE);
    squares[7][5] = new Bishop(7,5,WHITE);

    squares[0][3] = new Queen(0,3,BLACK);
    squares[7][3] = new Queen(7,3,WHITE);

    squares[0][4] = new King(0,4,BLACK);
    squares[7][4] = new King(7,4,WHITE);

    selected_ = false;
    selectedrow_ = 0;
    selectedcol_ = 0;
    turn_ = 0;
    updatePieceGrid();
    drawBoard();

}

void Board::setBoardEmpty() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            Piece* p = new Piece(i, j, EMPTY, NONE);
            squares[i][j] = p;
        }
    }
}
