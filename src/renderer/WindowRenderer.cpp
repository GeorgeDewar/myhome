#include "renderer/WindowRenderer.h"
#include "model/Wall.h"
#include "model/Opening.h"
#include <QVector2D>
#include <QPainter>

void WindowRenderer::renderWindow(const Wall &wall, const Opening &window) {
    QPointF windowStart = wall.startPoint() + (wall.unitDirection().toPointF() * (window.distanceAlongWall() - window.width() / 2.0));
    QPointF windowEnd = windowStart + (wall.unitDirection().toPointF() * window.width());
    QPen liningPen(Qt::black);
    liningPen.setWidth(0); // Cosmetic: always one physical screen pixel.
    painter_->setPen(liningPen);
    painter_->setBrush(Qt::NoBrush);

    // Central line
    painter_->drawLine(windowStart, windowEnd);

    const QVector2D halfThickness(-wall.unitDirection().y() * wall.thickness() / 2.0,
                                  wall.unitDirection().x() * wall.thickness() / 2.0);

    QPointF startA = windowStart + halfThickness.toPointF();
    QPointF startB = windowStart - halfThickness.toPointF();
    QPointF endA = windowEnd + halfThickness.toPointF();
    QPointF endB = windowEnd - halfThickness.toPointF();

    // Draw the two edge window lines
    painter_->drawLine(startA, endA);
    painter_->drawLine(endB, startB);
}