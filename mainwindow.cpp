#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "minesmodel.h"
#include <QMouseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("background-color:#202020");
    connect(ui->startWidget, SIGNAL(gameStarted(int,int,int)),
            this, SLOT(startGame(int,int,int)));
    connect(ui->menuWidget, SIGNAL(windowClosed()), this, SLOT(close()));
    connect(ui->menuWidget, SIGNAL(achievementsDesired()), this, SLOT(showAchievements()));
    connect(ui->menuWidget, SIGNAL(newGameDesired()), this, SLOT(newGame()));
    connect(ui->menuWidget, SIGNAL(replayDesired()), this, SLOT(replayGame()));
    connect(ui->mainWidget, SIGNAL(replayDesired()), this, SLOT(replayGame()));
    connect(ui->mainWidget, SIGNAL(newAchievementGenerated(QString,int,int,int,int)), ui->achievementsWidget,
            SLOT(addNewRanking(QString,int,int,int,int)));
    connect(ui->mainWidget, SIGNAL(gameStarted()), ui->menuWidget, SLOT(setAchievementsDisabled()));
    connect(ui->mainWidget, SIGNAL(gameTerminated()), ui->menuWidget, SLOT(setAchievementsEnabled()));
    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    newGame();
}

void MainWindow::replayGame()
{
    startGame(regRows, regCols, regMines);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newGame()
{
    this->setCurrentWidget(ui->startWidget);
    ui->menuWidget->setStart();
}

void MainWindow::setCurrentWidget(QWidget* widget)
{
    int len = ui->stackedWidget->count();
    for(int i = 0; i < len; ++i)
    {
        QWidget* w = ui->stackedWidget->widget(i);
        if(w == widget)
        {
            w->setSizePolicy(QSizePolicy::Expanding,
                                  QSizePolicy::Expanding);
            w->adjustSize();
        }
        else
        {
            w->setSizePolicy(QSizePolicy::Ignored,
                                  QSizePolicy::Ignored);
        }
    }
    ui->stackedWidget->setCurrentWidget(widget);
    ui->stackedWidget->adjustSize();
    this->adjustSize();
}

void MainWindow::startGame(const int& rows, const int& cols, const int& mines)
{
    regRows = rows;
    regCols = cols;
    regMines = mines;
    ui->mainWidget->startGame(rows, cols, mines);
    ui->menuWidget->setMain();
    this->setCurrentWidget(ui->mainWidget);
}

void MainWindow::showAchievements()
{
    ui->menuWidget->setAchievements();
    this->setCurrentWidget(ui->achievementsWidget);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) {
            dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
    }
}
