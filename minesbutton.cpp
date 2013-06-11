#include "minesbutton.h"
#include <QMouseEvent>
#include <QSize>
#include <QDebug>
#include <QTimer>

MinesButton::MinesButton(QWidget *parent) :
    QPushButton(parent)
{
    this->styleSheetStr = "*{background-color:#51A351;"
            "color:#ffffff;"
            "font: 75 bold 20pt \"Arial\"}"
            "*:hover{background-color:qlineargradient(spread:reflect, x1:0.5, y1:0, x2:0.5, y2:0.5, stop:0 #62C462, stop:1 #51A351);"
            "border-color:#458B45;}"
            "*:pressed,*:checked{background-color:#408240}";
    this->setFixedSize(35, 35);
    this->setStyleSheet(styleSheetStr);
    this->setFocusPolicy(Qt::NoFocus);
    this->setCheckable(true);
    this->setIconSize(QSize(24,24));
    this->reg = 0;
    this->number = 0;
    this->flashCount = 0;
}

void MinesButton::setNumber(const int& val)
{
    this->number = val;
}

void MinesButton::init()
{
    this->reg = 0;
    this->number = 0;
    this->flashCount = 0;
    this->setBlank();
    this->setChecked(false);
    this->setNumber(0);
    this->setText("");
    this->setIcon(QIcon());
}


void MinesButton::mousePressEvent(QMouseEvent* e)
{
    if(e->buttons().testFlag(Qt::LeftButton))
    {
        reg |= 1;
    }
    if(e->buttons().testFlag(Qt::RightButton))
    {
        reg |= 2;
    }
    if(reg == 3)
    {
        emit testStarted();
    }
    else if(reg == 2)
    {
        emit marked();
    }
}


void MinesButton::mouseReleaseEvent(QMouseEvent* )
{
    if(reg == 3)
    {
        emit testDone();
    }
    else if(reg == 1)
    {
        emit revealed();
    }
    reg = 0;
}

void MinesButton::setRevealed()
{
    this->setBlank();
    if(this->number > 0)
    {
        this->setText(QString::number(this->number));
    }
    else if(this->number == -1)
    {
        this->setIcon(QIcon(":/img/freehand_funny_skull.png"));
    }
    else if(this->number == -2)
    {
        this->setIcon(QIcon(":/img/flag-red-skull.png"));
    }
    else if(this->number == -3)
    {
        this->setIcon(QIcon(":/img/cross-skull.png"));
    }
    this->setChecked(true);
}

void MinesButton::setTested(bool tested)
{
    this->setChecked(tested);
}

void MinesButton::setFlagged()
{
    this->setIcon(QIcon(":/img/flag-red.png"));
}

void MinesButton::setQuestioned()
{
    this->setIcon(QIcon(":/img/help-contents.svg"));
}

void MinesButton::setBlank()
{
    this->setIcon(QIcon());
}

void MinesButton::setCrossFlashed()
{
    this->flashCount = 0;
    QTimer::singleShot(0, this, SLOT(toggleCross()));
}

void MinesButton::toggleCross()
{
    if(flashCount == 7)
    {
        return;
    }
    if(flashCount % 2)
    {
        this->setIcon(QIcon(":/img/edit-delete.png"));
        this->setText("");
        QTimer::singleShot(100, this, SLOT(toggleCross()));
    }
    else
    {
        this->setIcon(QIcon());
        this->setText(QString::number(this->number));
        QTimer::singleShot(50, this, SLOT(toggleCross()));
    }
    this->flashCount++;
}
