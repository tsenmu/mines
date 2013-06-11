#ifndef MINESMENUWIDGET_H
#define MINESMENUWIDGET_H

#include <QWidget>

namespace Ui {
class MinesMenuWidget;
}

class MinesMenuWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MinesMenuWidget(QWidget *parent = 0);
    ~MinesMenuWidget();

signals:
    void windowClosed();
    void newGameDesired();
    void replayDesired();
    void achievementsDesired();
public slots:
    void setStart();
    void setMain();
    void setAchievements();
    void setAchievementsEnabled();
    void setAchievementsDisabled();

protected slots:
    void on_pushButton_close_clicked();
    void on_pushButton_new_clicked();
    void on_pushButton_achievements_clicked();
    void on_pushButton_replay_clicked();
private:
    Ui::MinesMenuWidget *ui;
};

#endif // MINESMENUWIDGET_H
