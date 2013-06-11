#ifndef MINESSPINBOX_H
#define MINESSPINBOX_H

#include <QWidget>

class QIntValidator;
namespace Ui {
class MinesSpinBox;
}

class MinesSpinBox : public QWidget
{
    Q_OBJECT
    
public:
    explicit MinesSpinBox(QWidget *parent = 0);
    ~MinesSpinBox();
    int value() const;

public slots:
    void setLabel(const QString& str);
    void setValue(const int& val);
    void setValueRange(const int& minVal, const int& maxVal);
    void validate();
signals:
    void valueChanged(int value);
protected slots:
    void on_pushButton_plus_clicked();
    void on_pushButton_minus_clicked();

protected:
    QIntValidator* validator;
private:
    Ui::MinesSpinBox *ui;
};

#endif // MINESSPINBOX_H
