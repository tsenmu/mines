#ifndef MINESFAILUREDIALOG_H
#define MINESFAILUREDIALOG_H

#include <QDialog>

namespace Ui {
class MinesFailureDialog;
}

class MinesFailureDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MinesFailureDialog(QWidget *parent = 0);
    ~MinesFailureDialog();
    QStringList quotes;
    
protected slots:
    void on_pushButton_replay_clicked();
    void on_pushButton_cancel_clicked();
private:
    Ui::MinesFailureDialog *ui;
};

#endif // MINESFAILUREDIALOG_H
