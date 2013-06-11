#ifndef MINESWIDGET_H
#define MINESWIDGET_H

#include <QWidget>

namespace Ui {
class MinesWidget;
}

class MinesWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MinesWidget(QWidget *parent = 0);
    ~MinesWidget();

public slots:
    void startGame(const int& rows, const int& cols, const int& mines);
protected slots:
    void showAchievementDialog();
    void showFailureDialog();
    void winGame();
    void loseGame();
signals:
    void gameStarted();
    void gameTerminated();
    void replayDesired();
    void newAchievementGenerated(QString playerName, int time, int nRows, int nCols, int mines);
private:
    Ui::MinesWidget *ui;
};

#endif // MINESWIDGET_H
