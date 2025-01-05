#include <QtWidgets>
#include <QDebug>
#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clicktracker.h"
#include "piece.h"
#include "pawn.h"
#include "queen.h"
#include "king.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Create scene and link it to playingField
    QGraphicsScene* scene = new QGraphicsScene();
    ui->playingField->setScene(scene);

    // Create board and draw on the scene
    board = new Board(scene);
    board->initializeBoard();
    board->drawBoard();

    ClickTracker* clickTracker = new ClickTracker(ui->playingField, board);

    QTimer *timer = new QTimer(this);
    timer->setInterval(200);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start();
    mStartTime.start();

    // Create the model and set the headers
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(QStringList() << "Player" << "Move" << "Time");
    // Set the model to the tableView
    ui->tableView->setModel(model);
    setTableSettings();

    connect(board, &Board::playerMove, this, &MainWindow::handlePlayerMove);
    connect(board, &Board::gameOver, this, &MainWindow::gameOver);

    this->setStyleSheet("background-color: #ffe5c5;");
    this->setStyleSheet("background-color: #ffe5c5;");

    ui->resetButton->setStyleSheet("background-color: red; color: white");
    ui->infoButton->setStyleSheet("background-color: #cccccc; color: black");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setTableSettings() {
    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setColumnWidth(0, 46);
    ui->tableView->setColumnWidth(1, 67);
    ui->tableView->setColumnWidth(2, 67);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setStyleSheet("QTableView::item { background-color: #f7ebdc; }");
}

void MainWindow::on_resetButton_clicked()
{
    gameOver_ = false;
    ui->playingField->setEnabled(true);
    ui->turnLabel->setVisible(true);
    ui->winLabel->setText("");
    board->initializeBoard();
    board->drawBoard();
    mStartTime.start();
    // Clear the model
    model->clear();
    model->setHorizontalHeaderLabels(QStringList() << "Player" << "Move" << "Time");
    setTableSettings();
    ui->turnLabel->setText("Current Turn: <b>White</b>");

}

void MainWindow::updateTime()
{
    // Get the elapsed time in seconds
    qint64 elapsed = mStartTime.elapsed() / 1000;

    // Convert the elapsed time to HH:MM:SS format
    QTime time(0, 0, 0);
    time = time.addSecs(elapsed);

    // Update the QLabel text with the elapsed time
    if(!gameOver_) {
        ui->timeLabel->setText(time.toString("hh:mm:ss"));
    }
}

QString pieceTypeToString(PieceType type) {
    switch (type) {
        case PAWN:
            return "P";
        case ROOK:
            return "R";
        case KNIGHT:
            return "N";
        case BISHOP:
            return "B";
        case QUEEN:
            return "Q";
        case KING:
            return "K";
        default:
            return "";
    }
}

void MainWindow::handlePlayerMove(int turn, int fromRow, int fromCol, int toRow, int toCol, Piece* movedPiece, bool pieceTaken) {
    // Gets information and prints it to the tableView
    QStringList headers;
    headers << "Player" << "Move" << "Time";
    // Create a QList to hold the data
    QList<QList<QString>> data;

    // Convert move to algebraic notation
    // Take the piece that was moved and get its type
    PieceType piecetype = movedPiece->getType();
    QString piecetypeString = "";
    if(piecetype == COMBO) {
        // if combo piece, get both types together
        // create combo piece so we can access it's getTypes() function, currently it's a Piece*
        Combo* comboPiece = dynamic_cast<Combo*>(movedPiece);
        piecetypeString = piecetypeString + pieceTypeToString(comboPiece->getTypes()[0]) + pieceTypeToString(comboPiece->getTypes()[1]);
    } else {
        // otherwise, just get the type
        // if piecetype is pawn, we don't want to print it(unless it's a combo piece)
        if(piecetype == PAWN)
            piecetype = EMPTY;
        piecetypeString = pieceTypeToString(piecetype);
    }

    // Get the color of the piece
    Color piececolor = movedPiece->getColor();
    QString piececolorString;
    switch (piececolor) {
        case WHITE:
            piececolorString = "White";
            break;
        case BLACK:
            piececolorString = "Black";
            break;
        default:
            piececolorString = "ERROR";
            break;
    }

    // convert toRow and toCol to algebraic notation
    QString toRowString = QString::number(8 - toRow);
    QString toColString;

    QVector<QString> colVector = {"a", "b", "c", "d", "e", "f", "g", "h"};
    toColString = colVector.at(toCol);

    // if a piece was taken, add an x
    QString piecetakenString;
    if (pieceTaken) {
        piecetakenString = "x";
    } else {
        piecetakenString = "";
    }

    // put it together
    QString move = piecetypeString + piecetakenString + toColString + toRowString;


    // track how long the move took
    qint64 elapsed = mStartTime.elapsed() / 1000;
    QTime time(0, 0, 0);
    time = time.addSecs(elapsed);
    QString timeString = time.toString("hh:mm:ss");


    //  Add the data to the QList as (Player, Move)
    QList<QString> row;
    row.append(piececolorString);
    row.append(move);
    row.append(timeString);
    data.append(row);
    

    QList<QStandardItem *> items;
    items.append(new QStandardItem(piececolorString));
    items.append(new QStandardItem(move));
    items.append(new QStandardItem(timeString));

    model->appendRow(items);
    ui->tableView->setModel(model);
    setTableSettings();

    // set turnLabel to "Current Turn: <bold>White/Black</bold>"
    QString turnString;
    if (turn % 2 == 1) {
        turnString = "White";
    } else {
        turnString = "Black";
    }
    ui->turnLabel->setText("Current Turn: <b>" + turnString + "</b>");

}

void MainWindow::gameOver(int winningPlayer) {

    gameOver_ = true;

    QString winningPlayerString;
    if (winningPlayer == 0) {
        winningPlayerString = "White";
    } else {
        winningPlayerString = "Black";
    }
    ui->turnLabel->setVisible(false);
    ui->winLabel->setText("Game Over! " + winningPlayerString + " wins!");

    // disable the board
    ui->playingField->setDisabled(true);

    // put big black 50% opacity rectangle over the board
    QGraphicsRectItem* rect = new QGraphicsRectItem(0, 0, 600, 600);
    rect->setBrush(QBrush(Qt::black));
    rect->setOpacity(0.5);
    ui->playingField->scene()->addItem(rect);
    

}

void MainWindow::on_infoButton_clicked()
{
    QMessageBox::information(this, "Information",
                                 "FUSION CHESS\n\nFusion chess is a unique and exciting variation of the classic game of chess. In fusion chess, any piece on the board, except for the king, can combine with another piece to create a new, more powerful piece with unique moves.\n\nFor example, a knight can combine with a bishop to create a new piece that moves like a knight and a bishop combined. This opens up a whole new level of strategy and complexity in the game, as players must constantly evaluate the potential benefits of combining pieces versus keeping them separate.\n\nHowever, there are some limitations to fusion chess. If two pieces would combine to create a new piece with the same moves as an existing piece (such as a queen and a bishop combining to create a piece that moves like a queen), then this combination is not allowed.\n\nHave Fun!"
        );

}

