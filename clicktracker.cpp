#include "clicktracker.h"
#include <QMouseEvent>
#include <QDebug>

ClickTracker::ClickTracker(QWidget* parent, Board* board)
    : QGraphicsView(parent), board(board)
{
    this->setGeometry(0, 0, parent->width(), parent->height());
    setStyleSheet("background-color: transparent;");
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->parent = parent;
    this->board = board;

    connect(this, &ClickTracker::leftButtonClicked, board, &Board::handleLeftClicked);
    connect(this, &ClickTracker::rightButtonClicked, board, &Board::handleRightClicked);
}

void ClickTracker::mousePressEvent(QMouseEvent* event)
{

    QPointF point = mapToScene(event->pos());
    int x = point.x() + parent->width()/2;
    int y = point.y() + parent->height()/2;
    int col = x/75;
    int row = y/75;

    if (event->button() == Qt::LeftButton) {
        emit leftButtonClicked(row, col);
    } else if (event->button() == Qt::RightButton) {
        emit rightButtonClicked(row, col);
    }
}
