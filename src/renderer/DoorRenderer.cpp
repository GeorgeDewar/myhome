#include "renderer/DoorRenderer.h"
#include "model/Opening.h"
#include "model/Wall.h"
#include "model/StandardDoor.h"
#include <QPainter>
#include <QPainterPath>
#include <QPolygonF>
#include <QVector2D>
#include <QRectF>

void DoorRenderer::renderDoor(const Wall &wall, const Opening &opening, const StandardDoor &door) {
    const QVector2D wallDirection = wall.unitDirection();
    if (wallDirection.isNull()) { // TODO: Find way to avoid checking this sort of thing
        return;
    }

    const QPointF doorStart = wall.startPoint() + wallDirection.toPointF() * (opening.distanceAlongWall() - opening.width() / 2.0);
    const QPointF doorEnd = doorStart + wallDirection.toPointF() * opening.width();
    const QPointF hinge = door.hingeSide == HingeSide::Right ? doorEnd : doorStart;
    QVector2D openDirection(wallDirection.y(), -wallDirection.x());
    openDirection *= (door.swingDirection == SwingDirection::Inward) ? -1.0 : 1.0;
    
    /** The absolute angle, anticlockwise from the positive x-axis, of the open door */
    const double openAngle = std::fmod((door.swingDirection == SwingDirection::Inward) ? (360-wall.angle() - 90) : (360-wall.angle() + 90.0), 360.0);
    /** The relative angle, again anticlockwise, that the door must sweep through to get back to the closed position */
    const double sweepAngle = (door.hingeSide == HingeSide::Left && door.swingDirection == SwingDirection::Inward) || (door.hingeSide == HingeSide::Right && door.swingDirection == SwingDirection::Outward) ? 90.0 : -90.0;

    // The center of this rectangle is the hinge, about which we are drawing the door swing. QPainterPath::arcTo() uses this.
    const QRectF boundingRect(hinge.x() - door.width(), hinge.y() - door.width(), door.width() * 2, door.width() * 2);

    // Draw an arc representing the swing of the door, from the open angle to the closed position, about the hinge point
    QPainterPath swingPath;
    swingPath.moveTo(hinge);
    swingPath.arcTo(boundingRect, openAngle, sweepAngle);
    QPen liningPen(Qt::black);
    liningPen.setWidth(0); // Cosmetic: always one physical screen pixel.
    painter_->setPen(liningPen);
    painter_->setBrush(Qt::NoBrush);
    painter_->drawPath(swingPath);

    // Draw a polygon representing the door leaf, with the correct thickness, from the hinge to the open position
    const QPointF thicknessOffset = -wallDirection.toPointF() * door.thickness;
    const QPolygonF doorLeaf {
        hinge,
        hinge + openDirection.toPointF() * door.width(),
        hinge + openDirection.toPointF() * door.width() + thicknessOffset,
        hinge + thicknessOffset,
    };
    painter_->drawPolygon(doorLeaf);

    qDebug() << "Door " << door.id() << ": Door start:" << doorStart << "Door end:" << doorEnd << "Hinge:" << hinge << "Open angle:" << openAngle << "Sweep angle:" << sweepAngle;
}