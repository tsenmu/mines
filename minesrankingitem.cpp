#include "minesrankingitem.h"
#include <cmath>


void MinesRankingItem::computeScore()
{
    score = (int)(100000.0 * (double)mines * exp((double)(-time)) / ((double)nRows * (double)nCols));
}

bool MinesRankingItem::operator < (const MinesRankingItem& rhs) const
{
    return this->score > rhs.score;
}
