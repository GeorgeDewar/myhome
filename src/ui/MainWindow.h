#pragma once

#include <QMainWindow>
#include "model/Plan.h"
#include "model/Wall.h"
#include "model/Opening.h"

class QLabel;
class QPointF;

class MainWindow final : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void updateScale(double scale);
    void updateOffset(const QPointF &offset);
    void loadFile(const QString &filePath);
    void updateCurrentLevel(int level);
    void wallSelected(const Wall &wall);
    void doorSelected(const Opening &door);

    QLabel *scaleLabel_;
    QLabel *offsetLabel_;
    QLabel *selectedItemLabel_;
    QLabel *currentLevelLabel_;
    QAction *upAction_;
    QAction *downAction_;

    Plan *currentPlan_ { nullptr };
    const Wall *selectedWall_ { nullptr }; // TODO: change to a generic selected object
    const Opening *selectedDoor_ { nullptr };
};