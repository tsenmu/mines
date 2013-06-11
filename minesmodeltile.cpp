#include "minesmodeltile.h"

MinesModelTile::MinesModelTile(QObject *parent) :
    QObject(parent)
{
    init();
}

void MinesModelTile::init()
{
    revealed = false;
    flagged = false;
    questioned = false;
    mined = false;
    tested = false;
    neighbourMineNumber = 0;
}
