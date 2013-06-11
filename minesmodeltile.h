#ifndef MINESMODELTILE_H
#define MINESMODELTILE_H

#include <QObject>

class MinesModelTile : public QObject
{
    Q_OBJECT
public:
    explicit MinesModelTile(QObject *parent = 0);
    void init();
    bool revealed;
    bool flagged;
    bool questioned;
    bool mined;
    bool tested;
    int neighbourMineNumber;
};

#endif // MINESMODELTILE_H
