#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_resetButton_clicked();
    void updateTime();
    void handlePlayerMove(int turn, int fromRow, int fromCol, int toRow, int toCol, Piece* movedPiece, bool pieceTaken);
    void gameOver(int winningPlayer);

    void on_infoButton_clicked();

private:
    Ui::MainWindow *ui;
    Board* board;
    QElapsedTimer mStartTime;
    QStandardItemModel *model;
    bool gameOver_ = false;
    void setTableSettings();
};
#endif // MAINWINDOW_H
