#include "minesfieldwidget.h"
#include "minesbutton.h"
#include <QGridLayout>
#include <QSignalMapper>
#include "minesmodel.h"
#include <QDebug>

MinesFieldWidget::MinesFieldWidget(QWidget *parent) :
    QWidget(parent)
{
    initModel();
    initSignalMappers();
    initLayout();
    initButtonsReference();
    initStyleSheet();
}

void MinesFieldWidget::initTiles(const int& nRows, const int& nCols, const int& nMines)
{
    model->initScenario(nRows, nCols, nMines);
    hideButtons();
    assignDimension(nRows, nCols, nMines);
    showButtons();
    this->enable();
}

const int& MinesFieldWidget::mines() const
{
    return nMines;
}

const int& MinesFieldWidget::rows() const
{
    return nRows;
}
const int& MinesFieldWidget::cols() const
{
    return nCols;
}

void MinesFieldWidget::showButtons()
{
    for(int i = 0; i < nRows; ++i)
    {
        for(int j = 0; j < nCols; ++j)
        {
            buttons[i][j]->init();
            buttons[i][j]->show();
        }
    }
}

void MinesFieldWidget::hideButtons()
{
    for(int i = 0; i < nRows; ++i)
    {
        for(int j = 0; j < nCols; ++j)
        {
            buttons[i][j]->hide();
        }
    }
}

void MinesFieldWidget::initButtonsReference()
{
    const int N = 31;
    nRows = 0;
    nCols = 0;
    buttons = new MinesButton**[N];
    for(int i = 0; i < N; ++i)
    {
        buttons[i] = new MinesButton*[N];
        for(int j = 0; j < N; ++j)
        {
            MinesButton* button = new MinesButton();
            button->hide();
            layout->addWidget(button, i, j);
            QString coord = generateCoordinateString(i, j);
            connect(button, SIGNAL(revealed()), revealedSignalMapper, SLOT(map()));
            revealedSignalMapper->setMapping(button, coord);
            connect(button, SIGNAL(testStarted()), testStartedSignalMapper, SLOT(map()));
            testStartedSignalMapper->setMapping(button, coord);
            connect(button, SIGNAL(testDone()), testDoneSignalMapper, SLOT(map()));
            testDoneSignalMapper->setMapping(button, coord);
            connect(button, SIGNAL(marked()), markedSignalMapper, SLOT(map()));
            markedSignalMapper->setMapping(button, coord);
            buttons[i][j] = button;
        }
    }
    connect(revealedSignalMapper, SIGNAL(mapped(QString)), this, SLOT(revealed(QString)));
    connect(testStartedSignalMapper, SIGNAL(mapped(QString)), this, SLOT(testStarted(QString)));
    connect(testDoneSignalMapper, SIGNAL(mapped(QString)), this, SLOT(testDone(QString)));
    connect(markedSignalMapper, SIGNAL(mapped(QString)), this, SLOT(marked(QString)));
}

void MinesFieldWidget::initLayout()
{
    layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(layout);
}

void MinesFieldWidget::assignDimension(const int& nRows, const int& nCols, const int& nMines)
{
    this->nRows = nRows;
    this->nCols = nCols;
    this->nMines = nMines;
}

void MinesFieldWidget::initStyleSheet()
{
    this->setStyleSheet("background-color:#202020");
}

void MinesFieldWidget::initSignalMappers()
{
    revealedSignalMapper = new QSignalMapper(this);
    testStartedSignalMapper = new QSignalMapper(this);
    testDoneSignalMapper = new QSignalMapper(this);
    markedSignalMapper = new QSignalMapper(this);
}

QString MinesFieldWidget::generateCoordinateString(const int& i, const int& j)
{
    return QString("%1,%2").arg(i).arg(j);
}

QPair<int, int> MinesFieldWidget::parseCoordinateString(const QString& str)
{
    QStringList list = str.split(",");
    QPair<int, int> pair;
    pair.first = list[0].toInt();
    pair.second = list[1].toInt();
    return pair;
}

void MinesFieldWidget::revealed(const QString& coord)
{
    QPair<int, int> pair = parseCoordinateString(coord);
    int row = pair.first;
    int col = pair.second;
    model->revealTileAt(row, col);
}

void MinesFieldWidget::testStarted(const QString& coord)
{
    QPair<int, int> pair = parseCoordinateString(coord);
    int row = pair.first;
    int col = pair.second;
    model->testStartedTileAt(row, col);
}

void MinesFieldWidget::testDone(const QString& coord)
{
    QPair<int, int> pair = parseCoordinateString(coord);
    int row = pair.first;
    int col = pair.second;
    model->testDoneTileAt(row, col);
}

void MinesFieldWidget::marked(const QString& coord)
{
    QPair<int, int> pair = parseCoordinateString(coord);
    int row = pair.first;
    int col = pair.second;
    model->markTileAt(row, col);
}


MinesButton* MinesFieldWidget::getButton(const int& i, const int j) const
{
    return buttons[i][j];
}
MinesButton* MinesFieldWidget::getButton(const QString& str)
{
    QPair<int, int> pair = parseCoordinateString(str);
    return buttons[pair.first][pair.second];
}

void MinesFieldWidget::modelRevealed(const int& row, const int& col, const int& number)
{
    MinesButton* button = getButton(row, col);
    button->setNumber(number);
    button->setRevealed();
}

void MinesFieldWidget::modelTested(const int& row, const int& col, const bool& tested)
{
    MinesButton* button = getButton(row, col);
    button->setTested(tested);
}

void MinesFieldWidget::modelFlagged(const int& row, const int& col, const bool& flagged)
{
    MinesButton* button = getButton(row, col);
    if(flagged)
    {
        button->setFlagged();
        emit flagIncreased();
    }
    else
    {
        button->setBlank();
        emit flagDecreased();
    }
}

void MinesFieldWidget::modelQuestioned(const int& row, const int& col, const bool& questioned)
{
    MinesButton* button = getButton(row, col);
    if(questioned)
    {
        button->setQuestioned();
    }
    else
    {
        button->setBlank();
    }
}

void MinesFieldWidget::modelCrossFlashed(const int& row, const int& col)
{
    MinesButton* button = getButton(row, col);
    button->setCrossFlashed();
}

void MinesFieldWidget::initModel()
{
    model = new MinesModel(this);
    connect(model, SIGNAL(tileRevealed(int,int,int)), this, SLOT(modelRevealed(int,int,int)));
    connect(model, SIGNAL(tileTested(int,int,bool)), this, SLOT(modelTested(int,int,bool)));
    connect(model, SIGNAL(tileFlagged(int,int,bool)), this, SLOT(modelFlagged(int,int,bool)));
    connect(model, SIGNAL(tileQuestioned(int,int,bool)), this, SLOT(modelQuestioned(int,int,bool)));
    connect(model, SIGNAL(tileCrossFlashed(int,int)), this, SLOT(modelCrossFlashed(int,int)));
    connect(model, SIGNAL(gameStarted()), this, SIGNAL(gameStarted()));
    connect(model, SIGNAL(gameTerminated()), this, SIGNAL(gameTerminated()));
    connect(model, SIGNAL(gameWon()), this, SIGNAL(gameWon()));
    connect(model, SIGNAL(gameWon()), this, SIGNAL(gameTerminated()));
    connect(model, SIGNAL(gameLost()), this, SIGNAL(gameLost()));
    connect(model, SIGNAL(gameLost()), this, SIGNAL(gameTerminated()));
    connect(model, SIGNAL(gameLost()), this, SLOT(disable()));
}

void MinesFieldWidget::disable()
{
    this->setDisabled(true);
}

void MinesFieldWidget::enable()
{
    this->setEnabled(true);
}
