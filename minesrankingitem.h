#ifndef MINESRANKINGITEM_H
#define MINESRANKINGITEM_H

#include <QString>
#include <QHash>
class MinesRankingItem
{

public:

    QString player;
    int score;
    int nRows;
    int nCols;
    int mines;
    int time;
    void computeScore();
    bool operator < (const MinesRankingItem& rhs) const;
};

#endif // MINESRANKINGITEM_H
