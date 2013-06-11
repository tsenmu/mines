#ifndef MINESVIEW_H
#define MINESVIEW_H

#include <QWidget>

class MinesButton;
class MinesModel;
class QGridLayout;
class QSignalMapper;
class MinesFieldWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MinesFieldWidget(QWidget *parent = 0);
    void initTiles(const int& nRows, const int& nCols, const int &nMines);
    const int& rows() const;
    const int& cols() const;
    const int& mines() const;
protected:
    void initModel();
    void initButtonsReference();
    void initLayout();
    void initStyleSheet();
    void initSignalMappers();
    void assignDimension(const int& nRows, const int& nCols, const int& nMines);
    void showButtons();
    void hideButtons();
    QString generateCoordinateString(const int& i, const int& j);
    QPair<int, int> parseCoordinateString(const QString& str);
    MinesButton* getButton(const int& i, const int j) const;
    MinesButton* getButton(const QString& str);
    QGridLayout* layout;
    MinesButton*** buttons;
    QSignalMapper* revealedSignalMapper;
    QSignalMapper* markedSignalMapper;
    QSignalMapper* testStartedSignalMapper;
    QSignalMapper* testDoneSignalMapper;
    int nRows;
    int nCols;
    int nMines;
    MinesModel* model;

signals:
    void flagIncreased();
    void flagDecreased();
    void gameStarted();
    void gameTerminated();
    void gameWon();
    void gameLost();

public slots:
    void revealed(const QString& coord);
    void testStarted(const QString& coord);
    void testDone(const QString& coord);
    void marked(const QString& coord);

    void modelRevealed(const int& row, const int& col, const int& number);
    void modelTested(const int& row, const int& col, const bool& tested);
    void modelFlagged(const int& row, const int& col, const bool& flagged);
    void modelQuestioned(const int& row, const int& col, const bool& questioned);
    void modelCrossFlashed(const int& row, const int& col);

protected slots:
    void disable();
    void enable();
};

#endif // MINESVIEW_H
