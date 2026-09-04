#include "renderer/WindowRenderer.h"
#include "model/Wall.h"
#include "model/Opening.h"
#include <QVector2D>
#include <QPainter>

void WindowRenderer::renderWindow(const Wall &wall, const Opening &window) {
    QPointF windowStart = wall.startPoint() + (wall.unitDirection().toPointF() * (window.distanceAlongWall() - window.width() / 2.0));
    QPointF windowEnd = windowStart + (wall.unitDirection().toPointF() * window.width());
    qDebug() << "Window start:" << windowStart << "Window end:" << windowEnd;
     QPen liningPen(Qt::black);
    liningPen.setWidth(0); // Cosmetic: always one physical screen pixel.
    painter_->setPen(liningPen);
    painter_->setBrush(Qt::NoBrush);
    painter_->drawLine(windowStart, windowEnd);
}