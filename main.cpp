#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setStyleSheet(
        "QWidget { color: black; }"
        "QTableView::item { background-color: #f7ebdc; }"
        "QPushButton { background-color: #cccccc; }"
        );
    w.show();
    return a.exec();
}
