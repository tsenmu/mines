#ifndef MINESCOUNTERWIDGET_H
#define MINESCOUNTERWIDGET_H

#include <QWidget>

class QTimer;

namespace Ui {
class MinesCounterWidget;
}

class MinesCounterWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MinesCounterWidget(QWidget *parent = 0);
    ~MinesCounterWidget();
    int flagValue() const;
    int clockValue() const;

public slots:
    void initCounter(const int& mines);
    void increaseFlag();
    void decreaseFlag();
    void startCounting();
    void stopCounting();

protected slots:
    void increaseClock();

protected:
    void setFlagValue(const int& value);
    void setClockValue(const int& value);


    QTimer* timer;
private:
    Ui::MinesCounterWidget *ui;
};

#endif // MINESCOUNTERWIDGET_H
