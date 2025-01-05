#ifndef CLICKTRACKER_H
#define CLICKTRACKER_H

#include <QGraphicsView>
#include "board.h"

class ClickTracker : public QGraphicsView
{
    Q_OBJECT
public:
    ClickTracker(QWidget* parent = nullptr, Board* board = nullptr);

signals:
    void leftButtonClicked(int x, int y);
    void rightButtonClicked(int x, int y);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    QWidget* parent;
    Board* board;
};

#endif // CLICKTRACKER_H
