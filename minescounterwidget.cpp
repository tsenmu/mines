#include "minescounterwidget.h"
#include "ui_minescounterwidget.h"
#include <QTimer>

MinesCounterWidget::MinesCounterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinesCounterWidget)
{
    ui->setupUi(this);
    ui->lcdNumber_flag->setDigitCount(4);
    ui->lcdNumber_clock->setDigitCount(4);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(increaseClock()));
}

MinesCounterWidget::~MinesCounterWidget()
{
    delete ui;
}

void MinesCounterWidget::initCounter(const int &mines)
{
    setFlagValue(mines);
    if(timer->isActive())
    {
        timer->stop();
    }
    setClockValue(0);
}

void MinesCounterWidget::setFlagValue(const int& value)
{
    ui->lcdNumber_flag->display(value);
}

void MinesCounterWidget::setClockValue(const int& value)
{
    ui->lcdNumber_clock->display(value);
}

void MinesCounterWidget::increaseFlag()
{
    setFlagValue(flagValue() + 1);
}

void MinesCounterWidget::decreaseFlag()
{
    setFlagValue(flagValue() - 1);
}

int MinesCounterWidget::flagValue() const
{
    return ui->lcdNumber_flag->value();
}

int MinesCounterWidget::clockValue() const
{
    return ui->lcdNumber_clock->value();
}

void MinesCounterWidget::startCounting()
{
    timer->start(1000);
}

void MinesCounterWidget::increaseClock()
{
    setClockValue(clockValue() + 1);
}

void MinesCounterWidget::stopCounting()
{
    timer->stop();
}
