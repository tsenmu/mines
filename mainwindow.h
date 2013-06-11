#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class MinesFieldWidget;

class MinesModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent * event);
    QPoint dragPosition;
    int regRows;
    int regCols;
    int regMines;
protected slots:
    void newGame();
    void startGame(const int& rows, const int& cols, const int& mines);
    void showAchievements();
    void setCurrentWidget(QWidget* widget);
    void replayGame();
private:
    Ui::MainWindow *ui;
    MinesFieldWidget* minesWidget;
};

#endif // MAINWINDOW_H
