#include "tictactoewidget.h"
#include <QPushButton>
#include <QGridLayout>
#include <QSignalMapper>

TicTacToeWidget::TicTacToeWidget(QWidget *parent)
    : QWidget(parent)
{
    setupBoard();
}

TicTacToeWidget::~TicTacToeWidget()
{
}

void TicTacToeWidget::setupBoard()
{
    QGridLayout *gridLayout = new QGridLayout;
    QSignalMapper *mapper = new QSignalMapper(this);

    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            QPushButton *button = new QPushButton;
            button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            button->setText(" ");
            gridLayout->addWidget(button, row, column);
            board.append(button);
            mapper->setMapping(button, board.count() - 1);
            connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
        }
    }

    connect(mapper, SIGNAL(mapped(int)), this, SLOT(handleButtonClick(int)));
    setLayout(gridLayout);
}

void TicTacToeWidget::initNewGame()
{
    for (int i=0; i < 9; ++i) board.at(i)->setText(" ");
}

void TicTacToeWidget::handleButtonClick(int index)
{
    if (index < 0 || index >= board.size()) return;

    QPushButton *button = board.at(index);
    if (button->text() != " ") return;

    button->setText(currentPlayer() == Player1 ? "X" : "O");
    Player winner = checkWinCondition(index / 3, index % 3);
    if (winner == Invalid) {
        setCurrentPlayer(currentPlayer() == Player1 ? Player2 : Player1);
        return;
    } else {
        emit gameOver(winner);
    }
}