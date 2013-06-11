#include "minesmodel.h"
#include "minesmodeltile.h"
#include <QTime>
#include <QDebug>

MinesModel::MinesModel(QObject *parent)
    : QObject(parent)
{
    maxn = 31;
    initTiles();
    started = false;
    revealedTiles = 0;
    flaggedMines = 0;
}

MinesModel::~MinesModel()
{
    destroyTiles();
}

int MinesModel::rows() const
{
    return this->nRows;
}
int MinesModel::cols() const
{
    return this->nCols;
}
void MinesModel::initScenario(const int& rowCount, const int& colCount,
                  const int& mineNumber)
{
    nRows = rowCount;
    nCols = colCount;
    for(int i = 0; i < nRows; ++i)
    {
        for(int j = 0; j < nCols; ++j)
        {
            MinesModelTile* tile = tiles[i][j];
            tile->init();
        }
    }
    genMines(mineNumber);
    genNumbers();
    started = false;
    revealedTiles = 0;
    flaggedMines = 0;
}

void MinesModel::revealTileAt(const int& row, const int& col)
{
    MinesModelTile* tile = tiles[row][col];
    if(tile->flagged)
    {
        return;
    }
    if(tile->mined)
    {
        if(!started)
        {
            started = true;
            emit gameStarted();
        }
        if(started)
        {
            started = false;
            emit gameLost();
        }
        revealAllMines();
        return;
    }
    if(tile->questioned)
    {
        emit tileQuestioned(row, col, false);
    }
    if(!tile->revealed)
    {
        if(!started)
        {
            started = true;
            emit gameStarted();
        }
        searchAndRevealTilesAround(row, col);
    }
}

void MinesModel::testStartedTileAt(const int& row, const int& col)
{
    for(int i = row - 1; i <= row + 1; ++i)
    {
        for(int j = col - 1; j <= col + 1; ++j)
        {
            if(!tileCoordinateValid(i, j))
            {
                continue;
            }
            MinesModelTile* tile = tiles[i][j];
            if(!tile->revealed && !tile->flagged)
            {
                tile->tested = true;
                emit tileTested(i, j, true);
            }
        }
    }
}

void MinesModel::testDoneTileAt(const int& row, const int& col)
{
    for(int i = row - 1; i <= row + 1; ++i)
    {
        for(int j = col - 1; j <= col + 1; ++j)
        {
            if(!tileCoordinateValid(i, j))
            {
                continue;
            }
            MinesModelTile* tile = tiles[i][j];
            if(!tile->revealed && !tile->flagged)
            {
                tile->tested = false;
                emit tileTested(i, j, false);
            }
        }
    }
    if(tiles[row][col]->neighbourMineNumber > 0 && tiles[row][col]->revealed)
    {
        int flagCount = countNeighbourFlaggedTiles(row, col);
        if(flagCount == tiles[row][col]->neighbourMineNumber)
        {
            bool flagRight = true;
            for(int i = row - 1; i <= row + 1; ++i)
            {
                for(int j = col - 1; j <= col + 1; ++j)
                {
                    if(!tileCoordinateValid(i, j))
                    {
                        continue;
                    }
                    if(tiles[i][j]->revealed)
                    {
                        continue;
                    }
                    if(!tiles[i][j]->flagged && tiles[i][j]->mined)
                    {
                        flagRight = false;
                        break;
                    }
                }
            }
            if(flagRight)
            {
                for(int i = row - 1; i <= row + 1; ++i)
                {
                    for(int j = col - 1; j <= col + 1; ++j)
                    {
                        if(!tileCoordinateValid(i, j))
                        {
                            continue;
                        }
                        if(tiles[i][j]->revealed)
                        {
                            continue;
                        }
                        if(!tiles[i][j]->flagged)
                        {
                            tiles[i][j]->revealed = true;
                            revealedTiles++;
                            testSuccess();
                            emit tileRevealed(i, j, tiles[i][j]->neighbourMineNumber);
                        }
                    }
                }
            }
            else
            {
                if(started)
                {
                    emit gameLost();
                }
                revealAllMines();
                for(int i = row - 1; i <= row + 1; ++i)
                {
                    for(int j = col - 1; j <= col + 1; ++j)
                    {
                        if(!tileCoordinateValid(i, j))
                        {
                            continue;
                        }
                        if(!tiles[i][j]->revealed)
                        {
                            tiles[i][j]->revealed = true;
                            if(tiles[i][j]->flagged)
                            {
                                emit tileRevealed(i, j, -3);
                            }
                            else
                            {
                                emit tileRevealed(i, j, tiles[i][j]->neighbourMineNumber);
                            }

                        }
                    }
                }
            }
        }
        else
        {
            emit tileCrossFlashed(row, col);
        }
    }

}

void MinesModel::markTileAt(const int& row, const int& col)
{
    MinesModelTile* tile = tiles[row][col];
    if(tile->revealed)
    {
        return;
    }
    if(tile->flagged)
    {
        tile->flagged = false;
        emit tileFlagged(row, col, false);
        tile->questioned = true;
        emit tileQuestioned(row, col, true);
    }
    else if(tile->questioned)
    {
        tile->questioned = false;
        emit tileQuestioned(row, col, false);
    }
    else
    {
        tile->flagged = true;
        if(tile->flagged && tile->mined)
        {
            flaggedMines++;
            testSuccess();
        }
        emit tileFlagged(row, col, true);
    }
}

void MinesModel::revealAllMines()
{
    for(int i = 0; i < nRows; ++i)
    {
        for(int j = 0; j < nCols; ++j)
        {
            MinesModelTile* tile = tiles[i][j];
            if(tile->mined)
            {
                tile->revealed = true;
                if(tile->flagged)
                {
                    emit tileRevealed(i, j, -2);
                }
                else
                {
                    emit tileRevealed(i, j, -1);
                }

            }
        }
    }
}

void MinesModel::initTiles()
{
    tiles = new MinesModelTile**[maxn];
    for(int i = 0; i < maxn; ++i)
    {
        tiles[i] = new MinesModelTile*[maxn];
        for(int j = 0; j < maxn; ++j)
        {
            tiles[i][j] = new MinesModelTile(this);
        }
    }
}

void MinesModel::destroyTiles()
{
    for(int i = 0; i < maxn; ++i)
    {
        for(int j = 0; j < maxn; ++j)
        {
            delete tiles[i][j];
        }
        delete tiles[i];
    }
    delete tiles;
}

int MinesModel::genRandom(const int& minVal, const int& maxVal)
{
    return qrand() % ((maxVal + 1) - minVal) + minVal;
}

void MinesModel::genMines(const int &mineNumber)
{
    qsrand((uint)QTime::currentTime().msec());
    for(int i = 0; i < mineNumber; ++i)
    {
        bool found = false;
        while(!found)
        {
            int r = genRandom(0, nRows - 1);
            int c = genRandom(0, nCols - 1);
            if(!tiles[r][c]->mined)
            {
                tiles[r][c]->mined = true;
                found = true;
            }
        }
    }
}

void MinesModel::genNumbers()
{
    for(int i = 0; i < nRows; ++i)
    {
        for(int j = 0; j < nCols; ++j)
        {
            tiles[i][j]->neighbourMineNumber = countNeighbourMines(i, j);
        }
    }
}

bool MinesModel::tileCoordinateValid(const int& row, const int& col) const
{
    return row >= 0 && row < nRows && col >= 0 && col < nCols;
}

int MinesModel::countNeighbourMines(const int& row, const int& col) const
{
    if(tiles[row][col]->mined)
    {
        return -1;
    }
    int cnt = 0;
    for(int i = row - 1; i <= row + 1; ++i)
    {
        for(int j = col - 1; j <= col + 1; ++j)
        {
            if(tileCoordinateValid(i, j) && tiles[i][j]->mined)
            {
                ++cnt;
            }
        }
    }
    return cnt;
}

void MinesModel::searchAndRevealTilesAround(const int& row, const int& col)
{
    if(!tileCoordinateValid(row, col))
    {
        return;
    }
    MinesModelTile* tile = tiles[row][col];
    if(tile->mined || tile->flagged || tile->revealed)
    {
        return;
    }

    if(tile->questioned)
    {
        tile->questioned = false;
        emit tileQuestioned(row, col, false);
    }
    tile->revealed = true;
    revealedTiles++;
    testSuccess();
    if(tile->neighbourMineNumber >  0)
    {
        emit tileRevealed(row, col, tile->neighbourMineNumber);
        return;
    }
    emit tileRevealed(row, col, 0);
    for(int i = row - 1; i <= row + 1; ++i)
    {
        for(int j = col - 1; j <= col + 1; ++j)
        {
            searchAndRevealTilesAround(i, j);
        }
    }
}

int MinesModel::countNeighbourFlaggedTiles(const int& row, const int& col) const
{
    int cnt = 0;
    for(int i = row - 1; i <= row + 1; ++i)
    {
        for(int j = col - 1; j <= col + 1; ++j)
        {
            if(tileCoordinateValid(i, j) && tiles[i][j]->flagged)
            {
                ++cnt;
            }
        }
    }
    return cnt;
}

void MinesModel::testSuccess()
{
    if(revealedTiles + flaggedMines == nRows * nCols)
    {
        emit gameWon();
    }
}
