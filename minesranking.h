#ifndef MINESRANKING_H
#define MINESRANKING_H

#include <QObject>
#include <QVector>
#include "minesrankingitem.h"

class MinesRanking : public QObject
{
    Q_OBJECT
public:
    explicit MinesRanking(QObject *parent = 0);
    void addRankingItem(const MinesRankingItem& item);
    void clear();
    int count() const;
    const MinesRankingItem& operator[] (int index) const;
    MinesRankingItem& operator[](int index);
    void readRanking(const QString& fileName);
    void writeRanking(const QString& fileName);
protected:
    QVector<MinesRankingItem> vector;
signals:
    
public slots:
    
};

#endif // MINESRANKING_H
