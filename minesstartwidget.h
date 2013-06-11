#ifndef MINESSTARTWIDGET_H
#define MINESSTARTWIDGET_H

#include <QWidget>

namespace Ui {
class MinesStartWidget;
}

class MinesStartWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MinesStartWidget(QWidget *parent = 0);
    ~MinesStartWidget();
protected slots:
    void changeHorizontalValue(const int& val);
    void changeVerticalValue(const int& val);
    void on_pushButton_playGame_clicked();
signals:
    void gameStarted(const int& rows, const int& cols, const int& mines);
private:
    Ui::MinesStartWidget *ui;
};

#endif // MINESSTARTWIDGET_H
