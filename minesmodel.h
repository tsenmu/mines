#ifndef MINESMODEL_H
#define MINESMODEL_H

#include <QObject>

class MinesModelTile;

class MinesModel : public QObject
{
    Q_OBJECT
public:
    explicit MinesModel(QObject *parent = 0);
    virtual ~MinesModel();
    int rows() const;
    int cols() const;
    void initScenario(const int& rowCount, const int& colCount,
                      const int& mineNumber);

public slots:
    void revealTileAt(const int& row, const int& col);
    void testStartedTileAt(const int& row, const int& col);
    void testDoneTileAt(const int& row, const int& col);
    void markTileAt(const int& row, const int& col);

signals:
    void tileRevealed(int row, int col, int number);
    void tileFlagged(int row, int col, bool isFlagged);
    void tileQuestioned(int row, int col, bool isQuestioned);
    void tileTested(int row, int col, bool isTested);
    void tileCrossFlashed(int row, int col);
    void gameStarted();
    void gameTerminated();
    void gameWon();
    void gameLost();

protected:
    void testSuccess();
    int revealedTiles;
    int flaggedMines;
    bool started;
    int maxn;
    void revealAllMines();
    void initTiles();
    void destroyTiles();
    int genRandom(const int& minVal, const int& maxVal);
    void genMines(const int &mineNumber);
    void genNumbers();
    bool tileCoordinateValid(const int& row, const int& col) const;
    int countNeighbourMines(const int& row, const int& col) const;
    int countNeighbourFlaggedTiles(const int& row, const int& col) const;
    void searchAndRevealTilesAround(const int& row, const int& col);
    int nRows;
    int nCols;
    MinesModelTile*** tiles;
    
};

#endif // MINESMODEL_H
