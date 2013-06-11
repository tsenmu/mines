#ifndef MINESACHIEVEMENTDIALOG_H
#define MINESACHIEVEMENTDIALOG_H

#include <QDialog>

namespace Ui {
class MinesAchievementDialog;
}

class MinesAchievementDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MinesAchievementDialog(QWidget *parent = 0);
    ~MinesAchievementDialog();
    QString playerName() const;

protected slots:
    void on_pushButton_accept_clicked();
    void on_pushButton_cancel_clicked();
    
private:
    Ui::MinesAchievementDialog *ui;
};

#endif // MINESACHIEVEMENTDIALOG_H
