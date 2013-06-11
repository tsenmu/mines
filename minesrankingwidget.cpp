#include "minesrankingwidget.h"
#include "minesranking.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QDebug>


MinesRankingWidget::MinesRankingWidget(QWidget *parent) :
    QWidget(parent)
{
    initUi();
    dataFileName = "ranking.xml";
    readRanking();
    updateUi();
}


void MinesRankingWidget::writeRanking()
{
    ranking.writeRanking(dataFileName);
}

void MinesRankingWidget::readRanking()
{
    ranking.readRanking(dataFileName);
}

void MinesRankingWidget::initUi()
{
    QVBoxLayout* vl = new QVBoxLayout();
    this->setLayout(vl);
    int wNumber = 30;
    int wPlayer = 200;
    int wScore = 60;
    QHBoxLayout* hhl = new QHBoxLayout();
    QLabel* hNumber = new QLabel("#");
    hNumber->setStyleSheet("color:#3366FF");
    hNumber->setFont(QFont("Arial", 16, QFont::Bold));
    hNumber->setFixedWidth(wNumber);
    hNumber->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QLabel* hPlayer = new QLabel("Player");
    hPlayer->setStyleSheet("color:#3366FF");
    hPlayer->setFont(QFont("Arial", 16, QFont::Bold));
    hPlayer->setFixedWidth(wPlayer);
    hPlayer->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QLabel* hScore = new QLabel("Score");
    hScore->setStyleSheet("color:#3366FF");
    hScore->setFont(QFont("Arial", 16, QFont::Bold));
    hScore->setFixedWidth(wScore);
    hScore->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    hhl->addWidget(hNumber);
    hhl->addWidget(hPlayer);
    hhl->addWidget(hScore);
    vl->addLayout(hhl);
    for(int i = 0; i < 10; ++i)
    {
        QHBoxLayout* hl = new QHBoxLayout();
        QLabel* numberLabel = new QLabel(QString::number(i + 1));
        numberLabel->setStyleSheet("color:#ffffff");
        numberLabel->setFont(QFont("Arial", 16, 20));
        numberLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        numberLabel->setFixedWidth(wNumber);
        QLabel* playerLabel = new QLabel("");
        playerLabel->setStyleSheet("color:#ffffff");
        playerLabel->setFont(QFont("Arial", 16, 20));
        playerLabel->setFixedWidth(wPlayer);
        playerLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        playerLabels.append(playerLabel);

        QLabel* scoreLabel = new QLabel("");
        scoreLabel->setStyleSheet("color:#ffffff");
        scoreLabel->setFont(QFont("Arial", 16, 20));
        scoreLabel->setFixedWidth(wScore);
        scoreLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        scoreLabels.append(scoreLabel);

        hl->addWidget(numberLabel);
        hl->addWidget(playerLabel);
        hl->addWidget(scoreLabel);
        vl->addLayout(hl);
    }
}

void MinesRankingWidget::updateUi()
{
    for(int i = 0; i < ranking.count(); ++i)
    {
        setUiEntry(i, ranking[i].player, ranking[i].score);
    }
    for(int i = ranking.count(); i < 10; ++i)
    {
        setUiEntry(i, "", -1);
    }
    writeRanking();
}

void MinesRankingWidget::setUiEntry(const int& index, const QString& player, const int& score)
{
    playerLabels[index]->setText(player);
    if(score == -1)
    {
        scoreLabels[index]->setText("");
    }
    else
    {
        scoreLabels[index]->setText(QString::number(score));
    }
}

void MinesRankingWidget::addNewRanking(const QString& playerName,
                   const int& time,
                   const int& nRows,
                   const int& nCols,
                   const int& nMines)
{
    MinesRankingItem item;
    item.player = playerName;
    item.time = time;
    item.nRows = nRows;
    item.nCols = nCols;
    item.mines = nMines;
    item.computeScore();
    ranking.addRankingItem(item);
    updateUi();
}
