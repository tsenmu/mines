#include "minesachievementswidget.h"
#include "ui_minesachievementswidget.h"

MinesAchievementsWidget::MinesAchievementsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinesAchievementsWidget)
{
    ui->setupUi(this);
}

MinesAchievementsWidget::~MinesAchievementsWidget()
{
    delete ui;
}

void MinesAchievementsWidget::addNewRanking(const QString& playerName,
                   const int& time,
                   const int& nRows,
                   const int& nCols,
                   const int& nMines)
{
    ui->minesRankingWidget->addNewRanking(playerName,
                                          time, nRows, nCols, nMines);
}
