#ifndef MINESRANKINGWIDGET_H
#define MINESRANKINGWIDGET_H

#include <QWidget>

#include "minesranking.h"

class QLabel;
class MinesRankingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MinesRankingWidget(QWidget *parent = 0);
public slots:
    void writeRanking();
    void readRanking();
    void addNewRanking(const QString& playerName,
                       const int& time,
                       const int& nRows,
                       const int& nCols,
                       const int& nMines);
protected:
    void initUi();
    void updateUi();
    void setUiEntry(const int& index, const QString& player, const int& score);
    QList<QLabel*> playerLabels;
    QList<QLabel*> scoreLabels;
    MinesRanking ranking;
    QString dataFileName;
signals:
    
public slots:
    
};

#endif // MINESRANKINGWIDGET_H
