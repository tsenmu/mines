#include "minesstartwidget.h"
#include "ui_minesstartwidget.h"
#include <QDebug>

MinesStartWidget::MinesStartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinesStartWidget)
{
    ui->setupUi(this);
    ui->widget_horizontal->setLabel("Horizontal:");
    ui->widget_horizontal->setValue(8);
    ui->widget_horizontal->setValueRange(4, 30);
    ui->widget_vertical->setLabel("Vertical:");
    ui->widget_vertical->setValue(8);
    ui->widget_vertical->setValueRange(4, 30);
    ui->widget_mines->setLabel("Number of mines:");
    ui->widget_mines->setValue(10);
    ui->widget_mines->setValueRange(1, 30*30-10);
    connect(ui->widget_horizontal, SIGNAL(valueChanged(int)),
            this, SLOT(changeHorizontalValue(int)));
    connect(ui->widget_vertical, SIGNAL(valueChanged(int)),
            this, SLOT(changeVerticalValue(int)));
}

void MinesStartWidget::changeHorizontalValue(const int& val)
{
    int maxVal = val * ui->widget_vertical->value() - 10;
    ui->widget_mines->setValueRange(1, maxVal);
    if(ui->widget_mines->value() > maxVal)
    {
        ui->widget_mines->setValue(maxVal);
    }
}

void MinesStartWidget::changeVerticalValue(const int& val)
{
    int maxVal = val * ui->widget_horizontal->value() - 10;
    ui->widget_mines->setValueRange(1, maxVal);
    if(ui->widget_mines->value() > maxVal)
    {
        ui->widget_mines->setValue(maxVal);
    }
}

MinesStartWidget::~MinesStartWidget()
{
    delete ui;
}



void MinesStartWidget::on_pushButton_playGame_clicked()
{
    ui->widget_horizontal->validate();
    ui->widget_vertical->validate();
    ui->widget_mines->validate();
    emit gameStarted(ui->widget_vertical->value(),
                     ui->widget_horizontal->value(),
                     ui->widget_mines->value());
}
