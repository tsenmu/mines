#include "minesspinbox.h"
#include "ui_minesspinbox.h"
#include <QDebug>

MinesSpinBox::MinesSpinBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinesSpinBox)
{
    ui->setupUi(this);
    validator = new QIntValidator(this);
    ui->lineEdit->setValidator(new QIntValidator());
    connect(ui->lineEdit, SIGNAL(editingFinished()), this, SLOT(validate()));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(validate()));
}

MinesSpinBox::~MinesSpinBox()
{
    delete ui;
}

void MinesSpinBox::setLabel(const QString &str)
{
    ui->label->setText(str);
}

void MinesSpinBox::setValue(const int &val)
{
    ui->lineEdit->setText(QString::number(val));
}

void MinesSpinBox::setValueRange(const int &minVal, const int &maxVal)
{
    this->validator->setRange(minVal, maxVal);
}

void MinesSpinBox::on_pushButton_plus_clicked()
{
    int val = ui->lineEdit->text().toInt();
    if(val != validator->top())
    {
        ui->lineEdit->setText(QString::number(val + 1));
        emit valueChanged(val + 1);
    }
}

void MinesSpinBox::on_pushButton_minus_clicked()
{
    int val = ui->lineEdit->text().toInt();
    if(val != validator->bottom())
    {
        ui->lineEdit->setText(QString::number(val - 1));
        emit valueChanged(val - 1);
    }
}

int MinesSpinBox::value() const
{
    return ui->lineEdit->text().toInt();
}

void MinesSpinBox::validate()
{
    if(ui->lineEdit->text().isEmpty())
    {
        ui->lineEdit->setText(QString::number(validator->bottom()));
        emit valueChanged(validator->bottom());
    }
    else
    {
        int val = ui->lineEdit->text().toInt();
        if(val < validator->bottom())
        {
            ui->lineEdit->setText(QString::number(validator->bottom()));
            emit valueChanged(validator->bottom());
        }
        else if(val > validator->top())
        {
            ui->lineEdit->setText(QString::number(validator->top()));
            emit valueChanged(validator->top());
        }
    }
}
