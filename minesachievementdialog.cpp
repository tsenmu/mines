#include "minesachievementdialog.h"
#include "ui_minesachievementdialog.h"

MinesAchievementDialog::MinesAchievementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MinesAchievementDialog)
{
    ui->setupUi(this);
}

MinesAchievementDialog::~MinesAchievementDialog()
{
    delete ui;
}

QString MinesAchievementDialog::playerName() const
{
    return ui->lineEdit->text();
}

void MinesAchievementDialog::on_pushButton_accept_clicked()
{
    this->accept();
}

void MinesAchievementDialog::on_pushButton_cancel_clicked()
{
    this->reject();
}
