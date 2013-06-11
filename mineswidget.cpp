#include "mineswidget.h"
#include "ui_mineswidget.h"

#include <QDebug>
#include <QTimer>
#include "minesachievementdialog.h"
#include "minesfailuredialog.h"

MinesWidget::MinesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinesWidget)
{
    ui->setupUi(this);
    connect(ui->minesWidget, SIGNAL(flagIncreased()), ui->minesCounterWidget, SLOT(decreaseFlag()));
    connect(ui->minesWidget, SIGNAL(flagDecreased()), ui->minesCounterWidget, SLOT(increaseFlag()));
    connect(ui->minesWidget, SIGNAL(gameStarted()), ui->minesCounterWidget, SLOT(startCounting()));
    connect(ui->minesWidget, SIGNAL(gameTerminated()), ui->minesCounterWidget, SLOT(stopCounting()));
    connect(ui->minesWidget, SIGNAL(gameWon()), this, SLOT(winGame()));
    connect(ui->minesWidget, SIGNAL(gameLost()), this, SLOT(loseGame()));
    connect(ui->minesWidget, SIGNAL(gameStarted()), this, SIGNAL(gameStarted()));
    connect(ui->minesWidget, SIGNAL(gameTerminated()), this, SIGNAL(gameTerminated()));
}

MinesWidget::~MinesWidget()
{
    delete ui;
}

void MinesWidget::startGame(const int &rows, const int &cols, const int &mines)
{
    this->ui->minesWidget->initTiles(rows, cols, mines);
    this->ui->minesCounterWidget->initCounter(mines);
}

void MinesWidget::winGame()
{
    QTimer::singleShot(100, this, SLOT(showAchievementDialog()));
}

void MinesWidget::loseGame()
{
    QTimer::singleShot(100, this, SLOT(showFailureDialog()));
}



void MinesWidget::showAchievementDialog()
{
    MinesAchievementDialog dialog(this);
    int ret = dialog.exec();
    if(ret == MinesAchievementDialog::Accepted)
    {
        emit newAchievementGenerated(dialog.playerName(),
                                     ui->minesCounterWidget->clockValue(),
                                     ui->minesWidget->rows(),
                                     ui->minesWidget->cols(),
                                     ui->minesWidget->mines());
    }
}

void MinesWidget::showFailureDialog()
{
    MinesFailureDialog dialog(this);
    int ret = dialog.exec();
    if(ret == MinesFailureDialog::Accepted)
    {
        emit replayDesired();
    }
}

