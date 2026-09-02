#include "WallRenderer.h"
#include "model/Plan.h"
#include <QPen>
#include <QPainterPath>
#include <QVector2D>

void WallRenderer::renderWalls(const Plan &plan, int currentLevel) {
    const auto &buildings = plan.getBuildings();
    for (const auto &building : buildings) {
        const auto &levels = building.getLevels();
        if (currentLevel < 0 || currentLevel >= levels.size()) {
            qWarning() << "Current level" << currentLevel << "is out of bounds for building with" << levels.size() << "levels.";
            continue; // Skip if the current level is out of bounds
        }
        const auto &level = levels[currentLevel];
        const auto &walls = level.getWalls();
        QPainterPath wallArea;
        for (const auto &wall : walls) {
            //  renderWallFrame(wall);

            QPointF direction = wall.endPoint() - wall.startPoint();
            QVector2D dirVector(direction);
            const double length = dirVector.length();
            if (length == 0) {
                qWarning() << "Wall has zero length, skipping.";
                continue; // Skip zero-length walls
            }
            QVector2D unitDirection = dirVector.normalized();
            QVector2D unitNormal(-unitDirection.y(), unitDirection.x());
            const QVector2D halfThickness = unitNormal * (wall.thickness() / 2.0);
            // Extend the wall endpoints by half the wall thickness, as it is the centrelines that join, not the edges
            const QPointF start = wall.startPoint() - unitDirection.toPointF() * (wall.thickness() / 2.0);
            const QPointF end = wall.endPoint() + unitDirection.toPointF() * (wall.thickness() / 2.0);
            // Construct a four-point polygon representing the wall's area
            QPolygonF polygon {
                start + halfThickness.toPointF(),
                end + halfThickness.toPointF(),
                end - halfThickness.toPointF(),
                start - halfThickness.toPointF(),
            };

            QPainterPath wallPath;
            wallPath.addPolygon(polygon);
            wallPath.closeSubpath();
            wallArea = wallArea.united(wallPath);
        }

        // Fill in the wall area, representing the framing, in solid yellow
        painter_->setPen(Qt::NoPen);
        painter_->setBrush(QColor(255, 215, 0));
        painter_->drawPath(wallArea);

        // Draw the wall outlines in black
        QPen liningPen(Qt::black);
        liningPen.setWidth(0); // Cosmetic: always one physical screen pixel.
        painter_->setPen(liningPen);
        painter_->setBrush(Qt::NoBrush);
        painter_->drawPath(wallArea);
    }
}

void WallRenderer::renderWallFrame(const Wall &wall) {
    qDebug() << "Drawing wall from" << wall.startPoint() << "to" << wall.endPoint();
    QPen pen(QColor(255, 215, 0), wall.thickness()); // 0.01 metres thick, scaled to pixels
    painter_->setPen(pen);
    painter_->drawLine(wall.startPoint(), wall.endPoint());
}