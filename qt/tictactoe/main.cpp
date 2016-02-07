#include "tictactoewidget.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TicTacToeWidget w;
    w.show();
    return a.exec();
}
