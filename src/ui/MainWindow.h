#pragma once

#include <QMainWindow>
#include "model/Plan.h"

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

    QLabel *scaleLabel_;
    QLabel *offsetLabel_;
    QAction *upAction_;
    QAction *downAction_;

    Plan *currentPlan_;
};