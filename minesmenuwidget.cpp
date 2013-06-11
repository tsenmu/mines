#include "minesmenuwidget.h"
#include "ui_minesmenuwidget.h"

MinesMenuWidget::MinesMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinesMenuWidget)
{
    ui->setupUi(this);
}

MinesMenuWidget::~MinesMenuWidget()
{
    delete ui;
}

void MinesMenuWidget::on_pushButton_close_clicked()
{
    emit windowClosed();
}

void MinesMenuWidget::on_pushButton_new_clicked()
{
    emit newGameDesired();
}

void MinesMenuWidget::on_pushButton_achievements_clicked()
{
    emit achievementsDesired();
}

void MinesMenuWidget::setStart()
{
    ui->pushButton_new->setEnabled(false);
    ui->pushButton_replay->setEnabled(false);
    ui->pushButton_achievements->setEnabled(true);
}

void MinesMenuWidget::setMain()
{
    ui->pushButton_new->setEnabled(true);
    ui->pushButton_replay->setEnabled(true);
    ui->pushButton_achievements->setEnabled(true);
}

void MinesMenuWidget::setAchievements()
{
    ui->pushButton_new->setEnabled(true);
    ui->pushButton_replay->setEnabled(false);
    ui->pushButton_achievements->setEnabled(false);
}

void MinesMenuWidget::on_pushButton_replay_clicked()
{
    emit replayDesired();
}

void MinesMenuWidget::setAchievementsEnabled()
{
    ui->pushButton_achievements->setEnabled(true);
}

void MinesMenuWidget::setAchievementsDisabled()
{
    ui->pushButton_achievements->setEnabled(false);
}
