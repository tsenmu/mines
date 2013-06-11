#ifndef MINESBUTTON_H
#define MINESBUTTON_H

#include <QPushButton>

class MinesButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MinesButton(QWidget *parent = 0);

protected:
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* );
    int reg;
    int number;

    int flashCount;
    QString styleSheetStr;

signals:
    void revealed();
    void testStarted();
    void testDone();
    void marked();
    
public slots:
    void init();
    void setRevealed();
    void setQuestioned();
    void setFlagged();
    void setBlank();
    void setTested(bool tested);
    void setNumber(const int& val);
    void setCrossFlashed();

private slots:
    void toggleCross();
};

#endif // MINESBUTTON_H
