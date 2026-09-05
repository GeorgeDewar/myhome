#include "renderer/DoorRenderer.h"
#include "model/Opening.h"
#include "model/Wall.h"

#include <QPainter>
#include <QPainterPath>
#include <QPolygonF>
#include <QVector2D>

void DoorRenderer::renderDoor(const Wall &wall, const Opening &door) {
    const QVector2D wallDirection = wall.unitDirection();
    if (wallDirection.isNull()) { // TODO: Find way to avoid checking this sort of thing
        return;
    }

    const QPointF hinge = wall.startPoint() + wallDirection.toPointF() *
        (door.distanceAlongWall() + door.width() / 2.0);
    const QVector2D openDirection(wallDirection.y(), -wallDirection.x());
    const QPointF closedEndOfCurve = hinge - wallDirection.toPointF() * door.width();
    const QPointF openEndOfCurve = hinge + openDirection.toPointF() * door.width();

    QPen liningPen(Qt::black);
    liningPen.setWidth(0); // Cosmetic: always one physical screen pixel.
    painter_->setPen(liningPen);
    painter_->setBrush(Qt::NoBrush);

    constexpr double quarterCircleControl = 0.5522847498;
    QPainterPath swingPath(closedEndOfCurve);
    swingPath.cubicTo(
        closedEndOfCurve + openDirection.toPointF() * (door.width() * quarterCircleControl),
        openEndOfCurve - wallDirection.toPointF() * (door.width() * quarterCircleControl),
        openEndOfCurve);
    painter_->drawPath(swingPath);

    const QPointF thicknessOffset = -wallDirection.toPointF() * door.thickness();
    const QPolygonF doorLeaf {
        hinge,
        openEndOfCurve,
        openEndOfCurve + thicknessOffset,
        hinge + thicknessOffset,
    };
    painter_->drawPolygon(doorLeaf);
}