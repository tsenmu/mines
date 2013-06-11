#ifndef MINESACHIEVEMENTSWIDGET_H
#define MINESACHIEVEMENTSWIDGET_H

#include <QWidget>

namespace Ui {
class MinesAchievementsWidget;
}

class MinesAchievementsWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MinesAchievementsWidget(QWidget *parent = 0);
    ~MinesAchievementsWidget();
public slots:
    void addNewRanking(const QString& playerName,
                       const int& time,
                       const int& nRows,
                       const int& nCols,
                       const int& nMines);
    
private:
    Ui::MinesAchievementsWidget *ui;
};

#endif // MINESACHIEVEMENTSWIDGET_H
