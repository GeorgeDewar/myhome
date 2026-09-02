#pragma once
#include <QPainter>
#include "ui/Canvas.h"

class Building;
class Plan;
class QPointF;
class Wall;

class WallRenderer final {
    public:
        WallRenderer(QPainter *painter, Canvas *canvas) : painter_(painter), canvas_(canvas) {};
        void renderWalls(const Plan &plan, int currentLevel);
    private:
        QPainter *painter_;
        Canvas *canvas_;

        void renderWallFrame(const Wall &wall);
};
